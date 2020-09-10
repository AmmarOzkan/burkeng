#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>


#define UIELEMENTS 15
#define TRIGGERCONTROL 50
#define MULTIS 50
#define DOUBLESTRINGN 50
#define SUPERSTR 50
#include "RENG/bureng.h"

#define WIDTH 800
#define HEIGHT 600



int main()
{

	//Kamera pozisyon vs
	valueXY mouseCamera;
	mouseCamera.x = 0;
	mouseCamera.y = 0;
	valueXY camera;
	camera.x = 0;
	camera.y = 0;

	std::string zeminId = "zemin";
	std::string duvarId = "duvar";
	std::string coinId = "para";

	//Pencere
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Burkeng");
	setWindow(window,60);

	//Textureleri oyuna ekleme
	Texturee burkaTexture;
	setTexturee(&burkaTexture, 300, 300, "Burka", "res/imgs/burka.jpg");
	Texturee mouseTexture;
	setTexturee(&mouseTexture, 540, 540, "Mouse", "res/imgs/mouse.png");
	Texturee grassTexture;
	setTexturee(&grassTexture, 450, 338, "Grass", "res/imgs/grass.jpg");
	Texturee duvarTexture;
	setTexturee(&duvarTexture, 400, 271, "Duvar", "res/imgs/duvar.jpg");
	Texturee aimTexture;
	setTexturee(&aimTexture, 400, 400, "AIM", "res/imgs/aim.png");

	//Mouse
	gameObject mouse(mouseTexture, 10, 10, 0.10, 0.10, &window,&mouseCamera);

	//Platformlarý oluþturma objeleri
	gameObject grassObj(grassTexture, 50, 300, 2, 0.50, &window, &camera);
	gameObject grass2Obj(grassTexture, -800, 300, 0.50, 0.50, &window, &camera);
	gameObject grass3Obj(grassTexture, -450, 300, 0.5, 0.50, &window, &camera);
	gameObject dashGrassObj(grassTexture, 500,300,5.0,0.5,&window,&camera);
	physicsObject grass (&grassObj,false,0.0,"Cimen");
	physicsObject grass2(&grass2Obj, false, 0.0, "Cimen2");
	physicsObject grass3(&grass3Obj, false, 0.0, "Cimen3");
	physicsObject dashGrass(&dashGrassObj, false, 0.0, "DashGrass");

	//Duvar oluþturma objeleri
	gameObject duvarObj(duvarTexture, 400, 100, 0.50, 0.50, &window, &camera);
	gameObject duvar2Obj(duvarTexture, 600,-50,0.50,0.50,&window,&camera);
	gameObject duvar3Obj(duvarTexture, 450, 200, 0.50, 0.50, &window, &camera);
	physicsObject duvar(&duvarObj, false, 0.0, "Duvar");
	physicsObject duvar2(&duvar2Obj, false, 0.0, "Duvar");
	physicsObject duvar3(&duvar3Obj, false, 0.0, "Duvar");

	//Para oluþturma objeleri
	gameObject coinObj(burkaTexture, 1000, 100, 0.50, 0.50, &window, &camera);
	physicsObject coin(&coinObj,false,0.0,coinId);

	//Karakter oluþturma objeleri
	gameObject burkaObj(burkaTexture, 140, 0, 0.10, 0.10, &window, &camera);
	physicsObject burka(&burkaObj, true, 2.0, "BURKA");

	//Çoklu çizim için triggerlar
	MultiDraw draw;
	//player
	draw.addObject(&burka); 
	//Çimenler
	draw.addObject(&grass); draw.addObject(&grass2); draw.addObject(&grass3); draw.addObject(&dashGrass); 
	//Duvarlar
	draw.addObject(&duvar); draw.addObject(&duvar2); draw.addObject(&duvar3);
	//Paralar
	draw.addObject(&coin);

	//Dünyadaki triggerlar
	Triggers world;
	setTriggers(&world);
	addNewTrigger(&world, grass.getTrigger(), &zeminId);
	addNewTrigger(&world, grass2.getTrigger(), &zeminId);
	addNewTrigger(&world, grass3.getTrigger(), &zeminId);
	addNewTrigger(&world, duvar.getTrigger(), &duvarId);
	addNewTrigger(&world, duvar2.getTrigger(), &duvarId);
	addNewTrigger(&world, duvar3.getTrigger(), &duvarId);
	addNewTrigger(&world, dashGrass.getTrigger(), &zeminId);
	addNewTrigger(&world, coin.getTrigger(), &coinId);

	burka.setPhyTriggers(world);

	//UI
	UI ui("res/fonts/batmfo__.ttf","Ana",&window);
	ui.setObj(0,"Karakter", 10, 10);
	ui.setObj(1, "Puan:", 10, 10);

	//Oyun kontrolleri
	bool sol = false, sag = false;
	bool canJump = false;
	int jump = 1;
	int puan = 0;
	bool super = false;
	while (window.isOpen())
	{
		if (super) mouse.setTexturee(aimTexture);
		//Eventler
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
				case sf::Keyboard::Space:
					if (canJump) {
						burka.forceAdd(0, -30);
					}
					else if (jump > 0) {
						if (sol) {
							burka.forceAdd(-15, 0);
							jump--;
						}
						else if (sag) {
							burka.forceAdd(15, 0);
							jump--;
						}
						else {
							burka.forceAdd(0, -15);
							jump--;
						}
					}
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
		//Kontrol olaylarý
		if (canJump) {
			ui.getText(0)->setString("Ziplayabilir");
		}
		else {
			ui.getText(0)->setString("Ziplayamaz");
		}
		//Fizik Olaylarý
		grass.setTrigger();
		grass2.setTrigger();
		grass3.setTrigger(),
		burka.setTrigger();

		if (sag) {
			//burka.addX(7.0, 0.1, zeminId);
			burka.forceAdd(1.0, 0.0);
		}
		else if (sol) {
			//burka.addX(-7.0, 0.1, zeminId);
			burka.forceAdd(-1.0, 0.0);
		}

		//Kamera Haraketleri
		if (super) {
			camera.x = -burka.getObject()->position()->x + 200 + (-mouse.position()->x / 2) + 300;
			camera.y = -burka.getObject()->position()->y + 200 + (-mouse.position()->y / 2) + 100;
		}
		else { 
			camera.x = -burka.getObject()->position()->x + 200;
			if (burka.getObject()->position()->y < -1) {
				camera.y = -burka.getObject()->position()->y + 100;
			}
			else {
				camera.y = 0;
			}
		}
		
		

		//Burka fizikleri
		collideRes2 burkaPhy = burka.phyMove(0.1, "");
		if (burkaPhy.res2) {
			canJump = true;
			jump = 1;
			burka.getForce()->y *= -1;
			if (burkaPhy.id == coinId) {
				puan += 1;
			}
		}
		else {
			canJump = false;
		}

		superStr burkaCols = burka.getCollidings();
		if (isThereAnySTR(burkaCols, coinId)) {
			super = true;
		}
		if (burka.control(coinId)) {
			puan += 1;
		}

		//Oyuna restart atma
		if (burka.getObject()->position()->y > 2000) {
			burka.forceClear();
			burka.getObject()->position()->x = 10;
			burka.getObject()->position()->y = 0;
		}
		//Puan deðiþimi
		std::string puanStr = std::to_string(puan);
		ui.getText(1)->setString(puanStr);

		//Çizdirme
		window.clear(sf::Color::Black);
		draw.draw();
		ui.draw();
		mouse.draw();

		window.display();
	}

	return 0;

}