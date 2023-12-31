#include "Renderer.h"

Renderer::Renderer(sf::RenderWindow& window,
	std::vector<Block>& blocks,
	WorldProperties& worldProperties,
	ScoreController& scoreController,
	TextDrawer textDrawer,
	MapDisplayer& mapDisplayer)
	:
	window{ window },
	blocks{ blocks },
	worldProperties{ worldProperties },
	positionToPixelConverter{ worldProperties },
	scoreController{ scoreController },
	textDrawer{ textDrawer },
	backgroundTexture{},
	background{},
	mapDisplayer{ mapDisplayer }
{
	backgroundTexture.loadFromFile("Background02.jpg");
	background.setSize({ static_cast<float>(backgroundTexture.getSize().x),static_cast<float>(backgroundTexture.getSize().y) });
	background.setTexture(&backgroundTexture);
}

void Renderer::render()
{
	window.clear(sf::Color::Black);

	window.draw(background);

	for (const auto& paddingBlock : mapDisplayer.getPaddingBlocks())
	{
		window.draw(paddingBlock);
	}

	for (const auto& block : blocks)
	{
		for (const auto& e : block.getElements())
		{
			auto image = e.GetImage();
			auto position{ positionToPixelConverter.getPixelsForPosition(e.GetPosition()) };
			position.x += mapDisplayer.getLeftPadding();
			image.setPosition(position);
			window.draw(image);
		}
	}

	window.draw(textDrawer.write("Score: " + std::to_string(scoreController.getScore())));

	window.display();
}
