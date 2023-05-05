#include "menu.h"
int main()
{
    
 //   sf::RenderWindow window(sf::VideoMode(780, 780), "OOP-Project, Spring-2023");
 //   sf::Event event;

 //   while (window.isOpen())
 //   {
 //       while (window.pollEvent(event))
 //       {
	//		if (event.type == sf::Event::Closed) // If cross/close is clicked/pressed
	//			window.close(); //close the game
	//	}
	//	window.clear(sf::Color::Black); //clears the screen
	//	//window.draw(background);  // setting background
	//	//window.draw(p->sprite);   // setting player on screen
	//	window.display(); //displays the screen
	//}

    Menu m;
    m.display_menu(); 
    return 0;
}
