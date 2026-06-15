#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window( sf::VideoMode( { 700, 500 } ), "Boids CPP" );

	sf::ConvexShape bird;
	bird.setPointCount(3);
	bird.setPoint(0, sf::Vector2f(0, 0));
	bird.setPoint(1, sf::Vector2f(0, 10));
	bird.setPoint(2, sf::Vector2f(25, 5));
	bird.setOutlineColor(sf::Color::Green);
	bird.setOutlineThickness(5);
	bird.setPosition( { 100, 100 } );

	while ( window.isOpen() )
	{
		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() )
				window.close();
		}

		window.clear();
		window.draw( bird );
		window.display();
	}
}
