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

#include "RENG/bureng.h"

#define WIDTH 800
#define HEIGHT 800
#define PROPORTION 10

#define PERFORMANCE 1.0

#define PLATFORMS 4

int main(int argc, char* argv[])
{
	std::string filePath = "data/character.mg";

	srand(time(0));
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Test");
	setWindow(window, 60,true);

	Vector2 camera = { 0,0 };
	Vector2 non = { 0,0 };

	Texturee solid = setTexturee("solid", loadImage("data/world.mg", 1, 16));
	Texturee stone = setTexturee("Stone", loadImage("data/world.mg", 3, 16));

	Texturee charIdle = setTexturee("id", loadImage("data/character.mg", 1, 16));
	gameObject characterObject(charIdle, WIDTH/2-50, HEIGHT/2-50, 100, 100, &window, &non);

	Animation rwa("RightWalkAnimation");
	sf::Texture s = loadImage("data/character.mg", 2, 16);
	for (int i = 0; i < 5; i++) {rwa.addAnimTexture(setTexturee("rightWalk" + std::to_string(i), loadImage("data/character.mg", i + 2, 16)));}
	Animation lwa("LeftWalkAnimation");
	for (int i = 0; i < 5; i++) {lwa.addAnimTexture(setTexturee("rightWalk" + std::to_string(i), loadImage("data/character.mg", i + 8, 16)));}



	bool leftMove = false, rightMove = false;
	float testF = 0.0,speed = 0.5;
	bool prev = false;

	//Vector2 pos,scale;
	//std::string id, publicId;

	Physics testPhyObject(&characterObject);
	Trigger tr = { {10,100},{800,600},"invisibleWall","world" };
	testPhyObject.addTrigger(&tr);

	while (window.isOpen()) {
		testF += (speed*prev) + (-speed*!prev);
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A) leftMove = true;
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D) rightMove = true;

			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::A) leftMove = false;
			else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::D) rightMove = false;
		}
		if (leftMove) { characterObject.setTexturee(rwa.animate()); speed = -1.5; }
		else if (rightMove) { characterObject.setTexturee(lwa.animate()); prev = true; speed = 1.5;}
		else { characterObject.setTexturee(charIdle); speed = 0.5; }
		testPhyObject.move({ -10,-10 });

		characterObject.setRotation(testF);
		window.clear(sf::Color::Color(50, 25, 25));
		characterObject.draw();
		window.display();
	}

	return 0;

}