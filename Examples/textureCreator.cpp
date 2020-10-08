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

#define WIDTH 800
#define HEIGHT 800
#define PROPORTION 10

#define PERFORMANCE 1.0


int main()
{

	std::string filePath = "data/character.mg";

	srand(time(0));
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Test");
	setWindow(window, 60);

	valueXY camera = { 0,0 };
	valueXY non = { 0,0 };

	sf::Image img;
	char fileChar[8][8];
	img.create(8, 8, sf::Color::Transparent);
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			fileChar[x][y] = '-';
			img.setPixel(x, y, sf::Color::Transparent);
		}
	}
	sf::Texture txtr;
	txtr.loadFromImage(img);
	Texturee cursorTexture = setTexturee(100, 100, "cursor", txtr);
	gameObject cursor(cursorTexture,0,0,100,100,true,&window,&camera);
	int color = 1;
	while (window.isOpen()) {

		{
			sf::Image ccc;
			if (color == 1) {
				ccc.create(100, 100, sf::Color::Red);
			}
			else if (color == 2) {
				ccc.create(100, 100, sf::Color::Blue);
			}
			else if (color == 3) {
				ccc.create(100, 100, sf::Color::Green);
			}
			else if (color == 4) {
				ccc.create(100, 100, sf::Color::Yellow);
			}
			else if (color == 5) {
				ccc.create(100, 100, sf::Color::Magenta);
			}
			else if (color == 0) {
				ccc.create(100, 100, sf::Color::Black);
			}
			else if (color == -1) {
				ccc.create(100, 100, sf::Color::Color(100, 100, 100));
			}
			else if (color == -2) {
				ccc.create(100, 100, sf::Color::Color(255, 255, 255));
			}
			cursorTexture.texture.loadFromImage(ccc);
		}

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::MouseMoved) {
				cursor.position()->x = event.mouseMove.x;
				cursor.position()->y = event.mouseMove.y;
			}else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::C){
				color++;
				if (color > 5) color = -2;
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S) {
				std::ofstream file(filePath, std::ios::app);
				if (file) {
					for (int y = 0; y < 8; y++) {
						for (int x = 0; x < 8; x++) {
							file << fileChar[x][y];
						}
					}
					file << std::endl;
				}
			}
			else if (event.type == sf::Event::MouseButtonPressed) {
				int x = event.mouseButton.x/100;
				int y = event.mouseButton.y / 100;
				std::cout << x << " " << y << std::endl;
				if (color == 1) {img.setPixel(x, y, sf::Color::Red);fileChar[x][y] = '1';}
				else if (color == 2) {img.setPixel(x, y, sf::Color::Blue);fileChar[x][y] = '2';}
				else if (color == 3) {img.setPixel(x, y, sf::Color::Green);fileChar[x][y] = '3';}
				else if (color == 4) {img.setPixel(x, y, sf::Color::Yellow);fileChar[x][y] = '4';}
				else if (color == 5) {img.setPixel(x, y, sf::Color::Magenta);fileChar[x][y] = '5';}
				else if (color == 0) {img.setPixel(x, y, sf::Color::Transparent);fileChar[x][y] = '-';}
				else if (color == -1) {img.setPixel(x, y, sf::Color::Color(100, 100, 100));fileChar[x][y] = '*';}
				else if (color == -2) {img.setPixel(x, y, sf::Color::Color(255, 255, 255));fileChar[x][y] = '+';}
			}
		}
		window.clear(sf::Color::Color(50,25,25));
		std::string cmd;
		int posX, posY;
		std::string color;


		cursor.setTexturee(cursorTexture, true);

		if (cmd == "addtofile") {
			std::cin >> cmd;
			std::ofstream file(cmd, std::ios::app);
			if (file) {
				for (int y = 0; y < 8; y++) {
					for (int x = 0; x < 8; x++) {
						file << fileChar[x][y];
					}
				}
				file << std::endl;
			}
		}

		txtr.loadFromImage(img);
		Texturee t = setTexturee(8, 8, "d", txtr);
		gameObject gm(t, 0, 0, WIDTH, HEIGHT, true, &window, &camera);
		gm.draw();
		cursor.draw();
		window.display();
	}

	return 0;

}