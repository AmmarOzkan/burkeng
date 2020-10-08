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

#define WIDTH 900
#define HEIGHT 900
#define PROPORTION 10

#define PERFORMANCE 1.0


int main()
{

	srand(time(0));
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Test");
	setWindow(window, 60);

	valueXY camera = { 0,0 };
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
	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {
		}
		window.clear(sf::Color::Black);
		std::string cmd;
		int posX, posY;
		std::string color;
		std::cout << "posX posY color" << std::endl;
		std::cin >> cmd;
		if (cmd == "input") {
			std::cin >> posX >> posY >> color;
			sf::Color col = sf::Color::Transparent;
			char c = '-';
			if (color == "red") { col = sf::Color::Red; c = '1'; }
			else if (color == "blue") { col = sf::Color::Blue; c = '2'; }
			else if (color == "green") { col = sf::Color::Green; c = '3'; }
			img.setPixel(posX, posY, col);
			fileChar[posX][posY] = c;
		}
		else if (cmd == "addtofile") {
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
		for (int y = 0; y < 8; y++) {
			for (int x = 0; x < 8; x++) {
				std::cout << fileChar[x][y];
			}
			std::cout << std::endl;
		}

		std::cout << txtr.loadFromImage(img) << std::endl;
		Texturee t = setTexturee(8, 8, "d", txtr);
		gameObject gm(t, 0, 0, 900, 900, true, &window, &camera);
		gm.draw();
		window.display();
	}

	return 0;

}