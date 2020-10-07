#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <ctime>


#define UIELEMENTS 100
#define TRIGGERCONTROL 50
#define MULTIS 50
#define DOUBLESTRINGN 50
#define SUPERSTR 50
#define ANIMPERFRAME 15
#define DRAWOBJECTAMOUNT 50

#define NODEBUG

#include "RENG/bureng_exten.h"
#include "RENG/bureng.h"
#include "monsterlib.h"

#define WIDTH 1200
#define HEIGHT 900
#define PROPORTION 10

#define PERFORMANCE 1.0


int main()
{

	srand(time(0));
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Test");
	setWindow(window, 60);

	valueXY camera = { 0,0 };
	valueXY non = { 0,0 };
	Texturee cursorTexture = setTexturee(330, 418, "CursorTexture", "res/flappybird/mouse.png");

	gameObject cursor(cursorTexture, 0, 0, WIDTH * 0.5 / PROPORTION, WIDTH * 0.5 / PROPORTION, true, &window, &non);

	Texturee anim1 = setTexturee(8, 8, "test", loadImage("data/testchar.mg",0));
	Texturee anim2 = setTexturee(8, 8, "test", loadImage("data/testchar.mg", 1));
	gameObject testObj(anim1, 100, 100, 100, 100, true, &window, &non);

	Animation anim("testAnimation");
	anim.addAnimTexture(anim1);
	anim.addAnimTexture(anim2);
	anim.addAnimTexture(anim2);
	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::MouseMoved) {
				cursor.position()->x = event.mouseMove.x;
				cursor.position()->y = event.mouseMove.y;
			}
		}
		testObj.setTexturee(anim.animate(), true);
		window.clear(sf::Color::Black);

		testObj.draw();
		cursor.draw();

		window.display();
	}

	return 0;

}