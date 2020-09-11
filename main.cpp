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

#define PERFORMANCE 1.0


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
	std::string playerId = "player";

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
	Texturee backgroundTexture;
	setTexturee(&backgroundTexture, 275, 183, "BackGround", "res/imgs/arkaplan.jpg");
	Texturee replayTexture;
	setTexturee(&replayTexture, 600, 600, "ReplayButtonTexture", "res/imgs/replay.png");


	//Mouse
	gameObject mouse(mouseTexture, 10, 10, 0.10, 0.10, false, &window,&mouseCamera);

	//Arkaplan
	gameObject background(backgroundTexture, -10, -300, 5, 5, false, &window, &mouseCamera);

	//Platformlarý oluþturma objeleri
	gameObject grassObj(grassTexture, 50, 300, 2, 0.50, false, &window, &camera);
	gameObject grass2Obj(grassTexture, -800, 300, 0.50, 0.50, false, &window, &camera);
	gameObject grass3Obj(grassTexture, -450, 300, 0.5, 0.50, false, &window, &camera);
	gameObject dashGrassObj(grassTexture, 500,300,20.0,0.5, false, &window,&camera);
	physicsObject grass (&grassObj,false,0.0,"Cimen");
	physicsObject grass2(&grass2Obj, false, 0.0, "Cimen2");
	physicsObject grass3(&grass3Obj, false, 0.0, "Cimen3");
	physicsObject dashGrass(&dashGrassObj, false, 0.0, "DashGrass");

	//Duvar oluþturma objeleri
	gameObject duvarObj(duvarTexture, 400, 100, 0.50, 0.50, false, &window, &camera);
	gameObject duvar2Obj(duvarTexture, 600,-50,0.50,0.50, false, &window,&camera);
	gameObject duvar3Obj(duvarTexture, 450, 200, 0.50, 0.50, false, &window, &camera);
	gameObject duvar4Obj(duvarTexture, 800, -100, 0.50, 0.50, false, &window, &camera);
	gameObject duvar5Obj(duvarTexture, 1100, -200, 0.50, 0.50, false, &window, &camera);

	physicsObject duvar(&duvarObj, false, 0.0, "Duvar");
	physicsObject duvar2(&duvar2Obj, false, 0.0, "Duvar");
	physicsObject duvar3(&duvar3Obj, false, 0.0, "Duvar");
	physicsObject duvar4(&duvar4Obj, false, 0.0, "Duvar");
	physicsObject duvar5(&duvar5Obj, false, 0.0, "Duvar");

	//Para oluþturma objeleri
	gameObject coinObj(burkaTexture, 1000, 100, 0.50, 0.50, false, &window, &camera);
	physicsObject coin(&coinObj,false,0.0,coinId);

	//Karakter oluþturma objeleri
	gameObject burkaObj(burkaTexture, 0, 0, 0.10, 0.10,false, &window, &camera);
	physicsObject burka(&burkaObj, true, 2.0, "BURKA");

	//Butonlar
	Button jumpButton(mouseTexture,"JumpButton",0,500,100,100,&window);
	Button replayButton(replayTexture,"ReplayButton", 700, 0, 100, 100, &window);

	//Çoklu çizim için triggerlar
	MultiDraw draw;
	//player
	draw.addObject(&burka); 
	//Çimenler
	draw.addObject(&grass); draw.addObject(&grass2); draw.addObject(&grass3); draw.addObject(&dashGrass); 
	//Duvarlar
	draw.addObject(&duvar); draw.addObject(&duvar2); draw.addObject(&duvar3); draw.addObject(&duvar4); draw.addObject(&duvar5);
	//Paralar
	draw.addObject(&coin);

	//Dünyadaki triggerlar
	Triggers world;
	setTriggers(&world);
	addNewTrigger(&world, grass.getTrigger(), &zeminId);
	addNewTrigger(&world, grass2.getTrigger(), &zeminId);
	addNewTrigger(&world, grass3.getTrigger(), &zeminId);
	addNewTrigger(&world, dashGrass.getTrigger(), &zeminId);
	//Duvar triggerlarý
	addNewTrigger(&world, duvar.getTrigger(), &duvarId);
	addNewTrigger(&world, duvar2.getTrigger(), &duvarId);
	addNewTrigger(&world, duvar3.getTrigger(), &duvarId);
	addNewTrigger(&world, duvar4.getTrigger(), &duvarId);
	addNewTrigger(&world, duvar5.getTrigger(), &duvarId);

	addNewTrigger(&world, coin.getTrigger(), &coinId);

	burka.setPhyTriggers(world);

	//burka trigger'ýný coine ekleme
	coin.addControl(burka.getTrigger(), &playerId);

	//UI
	UI ui("res/fonts/batmfo__.ttf","Ana",&window);
	ui.setText(0,"Karakter", 10, 10);
	ui.setText(1, "Puan:", 10, 10);

	//Oyun kontrolleri
	bool sol = false, sag = false;
	bool canJump = false;
	int jump = 1;
	int puan = 0;
	bool super = false;
	float superJump = 50;
	bool superJumping = false;
	while (window.isOpen())
	{
		if (super) mouse.setTexturee(aimTexture);
		//Eventler
		sf::Event event;
		while (window.pollEvent(event)) {
			if (jumpButton.control(event)) {
				burka.forceAdd(0.0, -40.0);
				std::cout << std::endl << "Butona Tiklandi";
			}if (replayButton.control(event)) {
				burka.getObject()->position()->x = 0;
				burka.getObject()->position()->y = 0;
				burka.forceClear();
				super = false;
				coin.getObject()->position()->x = 1000;
				coin.getObject()->position()->y = 100;
				coin.setTrigger();
			}


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
					break;
				case sf::Keyboard::W:
					superJumping = true;
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
				case sf::Keyboard::W:
					superJumping = false;
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

		if (superJumping) {
			if (superJump > 0) {
				burka.forceAdd(0, -10);
				superJump--;
			}
		}
		

		//Haraket iþlemleri
		if (sag) {
			//burka.addX(7.0, 0.1, zeminId);
			burka.forceAdd(1.0, 0.0);
			burka.setTrigger();
		}
		else if (sol) {
			//burka.addX(-7.0, 0.1, zeminId);
			burka.forceAdd(-1.0, 0.0);
			burka.setTrigger();
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

		//Arkaplan Haraketleri
		background.position()->x = -burka.getObject()->position()->x / 20-350;
		if (super) {
			background.position()->x = -burka.getObject()->position()->x / 20 - 350 + (-mouse.position()->x / 10);
			background.position()->y = -burka.getObject()->position()->y / 10 -50 + (-mouse.position()->y / 10);
		}
		
		//Çarpýþma Kontrolleri
		superStr burkaCols = burka.getCollidings();
		if (isThereAnySTR(burkaCols, coinId)) {
			super = true;
			coin.getObject()->position()->x = 9999;
			coin.getObject()->position()->y = 9999;
			coin.setTrigger();
		}
		else if (isThereAnySTR(burkaCols, zeminId)) {
			superJump = 7;
		}

		

		//Burka fizikleri
		collideRes2 burkaPhy = burka.phyMove(PERFORMANCE, "");
		if (burkaPhy.res2) {
			canJump = true;
			jump = 1;
			burka.getForce()->y *= -1;
		}
		else {
			canJump = false;
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
		std::string puanStr = std::to_string(burka.getForce()->x);
		ui.getText(1)->setString(puanStr);

		//Çizdirme
		window.clear(sf::Color::Black);
		background.draw();
		draw.draw();

		//Buton
		jumpButton.draw();
		replayButton.draw();

		//UI
		ui.draw();

		mouse.draw();


		window.setTitle(std::to_string(burka.getObject()->position()->x) + " " + std::to_string(burka.getObject()->position()->y) + ": burkeng");
		window.display();
	}

	return 0;

}