#include <SFML/Graphics.hpp>
#include <iostream>


#define UIELEMENTS 15
#define TRIGGERCONTROL 50
#define MULTIS 50

#include "RENG/bureng.h"

#define WIDTH 800
#define HEIGHT 600



int main()
{
	std::string zeminId = "zemin";

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Burkeng");
	setWindow(window,120);
	//TEXTURE
	Texturee burkaTexture;
	setTexturee(&burkaTexture, 300, 300, "Burka", "res/imgs/burka.jpg");
	Texturee mouseTexture;
	setTexturee(&mouseTexture, 540, 540, "Mouse", "res/imgs/mouse.png");
	Texturee grassTexture;
	setTexturee(&grassTexture, 450, 338, "Grass", "res/imgs/grass.jpg");
	Texturee duvarTexture;
	setTexturee(&duvarTexture, 400, 271, "Duvar", "res/imgs/duvar.jpg");
	//GAMEOBJECT
	gameObject mouse(mouseTexture,10,10,0.10,0.10,&window);
	gameObject burkaObj(burkaTexture,140,10,0.50,0.50,&window);
	gameObject grassObj(grassTexture, 50, 300, 0.50, 0.50, &window);
	gameObject grass2Obj(grassTexture, 200, 300, 0.50, 0.50, &window);
	gameObject grass3Obj(grassTexture, 400, 300, 0.50, 0.50, &window);
	gameObject duvarObj(duvarTexture, 400,100, 0.50, 0.50, &window);
	physicsObject burka(&burkaObj,true,1.0,"BURKA");
	physicsObject grass (&grassObj,false,0.0,"Cimen");
	physicsObject grass2(&grass2Obj, false, 0.0, "Cimen2");
	physicsObject grass3(&grass3Obj, false, 0.0, "Cimen3");
	physicsObject duvar(&duvarObj, false, 0.0, "Duvar");

	MultiDraw draw;
	draw.addObject(&burka); draw.addObject(&grass); draw.addObject(&grass2); draw.addObject(&grass3); draw.addObject(&duvar);

	Triggers zeminler;
	setTriggers(&zeminler);
	addNewTrigger(&zeminler, grass.getTrigger(), &zeminId);
	addNewTrigger(&zeminler, grass2.getTrigger(), &zeminId);
	addNewTrigger(&zeminler, grass3.getTrigger(), &zeminId);
	addNewTrigger(&zeminler, duvar.getTrigger(), &zeminId);

	burka.setPhyTriggers(zeminler);

	UI ui("res/fonts/batmfo__.ttf","Ana",&window);
	ui.setObj(0,"Karakter", 10, 10);

	bool sol = false, sag = false;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::MouseMoved) {
				mouse.position()->x = event.mouseMove.x; mouse.position()->y = event.mouseMove.y;
				ui.getText(0)->setPosition(event.mouseMove.x, event.mouseMove.y+300*0.1);
			}
			else if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
				case sf::Keyboard::D:
					sag = true;
					break;
				case sf::Keyboard::A:
					sol = true;
					break;
				}
			}
			else if (event.type == sf::Event::KeyReleased) {
				switch (event.key.code) {
				case sf::Keyboard::D:
					sag = false;
					break;
				case sf::Keyboard::A:
					sol = false;
					break;
				}
			}
		}
		grass.setTrigger();
		grass2.setTrigger();
		grass3.setTrigger(),
		burka.setTrigger();
		if (sag) {
			burka.addX(5.0,1.0,zeminId);
		}
		else if (sol) {
			burka.addX(-5.0, 1.0, zeminId);
		}
		window.clear(sf::Color::Black);
		draw.draw();
		ui.draw();
		mouse.draw();
		window.display();
	}

	return 0;

}
