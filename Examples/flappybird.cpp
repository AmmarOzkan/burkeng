#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>


#define UIELEMENTS 100
#define TRIGGERCONTROL 50
#define MULTIS 50
#define DOUBLESTRINGN 50
#define SUPERSTR 50
#define ANIMPERFRAME 30
#define DRAWOBJECTAMOUNT 50

#include "RENG/bureng_exten.h"
#include "RENG/bureng.h"
#include "RENG/GameTools.h"

#define WIDTH 1200
#define HEIGHT 900
#define PROPORTION 10

#define PERFORMANCE 1.0



int main()
{

	//PENCERE OLUŞTURMA
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Burka Art Offline");
	setWindow(window, 60);

	//KAMERA
	valueXY camera = { 0,0 };
	valueXY non = { 0,0 };
	//Textureler
	Texturee bird; setTexturee(&bird, 377, 221, "BirdTexture", "res/flappybird/bird.png");
	Texturee cursorTexture; setTexturee(&cursorTexture, 330, 418, "CursorTexture", "res/flappybird/mouse.png");
	Texturee pipeTexture; setTexturee(&pipeTexture, 261, 701, "PipeTexture", "res/flappybird/pipe.png");
	//CURSOR
	gameObject cursor(cursorTexture, 0, 0, WIDTH*0.5/ PROPORTION, WIDTH*0.5/ PROPORTION, true, &window, &non);


	bex::Object player(1.0,bird,&window,&camera,"player","player");
	float scaleX = WIDTH/PROPORTION, scaleY = scaleX/2;
	player.setScale(scaleX, scaleY);
	player.setPosition(WIDTH / 2-(scaleX/2), HEIGHT / 2-(scaleY/2));


	bex::Object pipe(1.0, pipeTexture, &window, &camera, "pipe","pipe");
	float PipeScaleX = WIDTH / PROPORTION, PipeScaleY = PipeScaleX *4;
	pipe.setScale(PipeScaleX, PipeScaleY);
	pipe.add(player.getPhyObject());
	player.add(pipe.getPhyObject());

	bex::Object pipe2(1.0, pipeTexture, &window, &camera, "pipe2","pipe");
	pipe2.setScale(PipeScaleX, -PipeScaleY);
	player.add(pipe2.getPhyObject());
	pipe2.add(player.getPhyObject());


	float pipeP = 100.0;
	float counter = WIDTH- PipeScaleX;
	float distance = 200;
	pipe.setPosition(counter, HEIGHT - PipeScaleY + pipeP);
	pipe2.setPosition(counter, HEIGHT - PipeScaleY - (WIDTH / PROPORTION / 2) - distance + pipeP);
	
	bool jump = false , prevJump = jump;
	int jumpCounter = 0;
	bex::TDimensionDrawer drawer;
	drawer.setWindowProperties(HEIGHT,WIDTH);
	drawer.addObject(&player);
	drawer.addObject(&pipe);
	drawer.addObject(&pipe2);

	UI ui("res/fonts/batmfa__.ttf","FONT",&window);
	ui.setText(0, "0", 100, -400);
	ui.getText(0)->setScale(40, 40);
	int point = 0;
	int highScore = 0;
	bool prevPoint = false;
	bool controlPoint = false;
	float speed = 10.0;
	while (window.isOpen()) {
		//KURALLAR
		if (point > highScore) highScore = point;
		speed = (point)*5 + 5;

		//EVENT OLAYLARI
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) jump = true;
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space) jump = false;
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::F) point++;
			//Cursor
			if (event.type == sf::Event::MouseMoved) {
				cursor.position()->x = event.mouseMove.x;
				cursor.position()->y = event.mouseMove.y;
			}
		}
		if (jumpCounter > 0) {
			jumpCounter--;
		}
		else {
			player.addForce(0.0, 25.0 / WIDTH);
		}
		//KONTROL OLAYLARI
		if (prevJump != jump && jump) {
			jumpCounter = 30;
		}
		if (jumpCounter > 0) {
			jumpCounter--;
			player.addPos(0.0, -5000.0 / WIDTH);
		}
		else {
			player.addPos(0.0, 5000.0 / WIDTH);
		}
		prevJump = jump;
		///OYUN BITTIMI BITMEDIMI KONTROL
		if (player.getPos()->y > HEIGHT) {
			std::cout << "OYUN BITTI" << std::endl; point = 0;
		}

		//Pipes
		pipe.getObject()->position()->x += -speed;
		pipe2.getObject()->position()->x += -speed;
		if (pipe.getPos()->x < 0-pipe.getPhyObject()->getTrigger()->height) {
			pipe.setPosition(counter, HEIGHT - PipeScaleY + pipeP);
			pipe2.setPosition(counter, HEIGHT - PipeScaleY - (WIDTH / PROPORTION / 2) - distance + pipeP);
			pipeP = rand() % (HEIGHT/3);
		}
		pipe.getPhyObject()->setTrigger("pipe");
		pipe2.getPhyObject()->setTrigger("pipe");
		player.getPhyObject()->setTrigger("player");
		Trigger pipe2Trigger;
		triggerClass.setTrigger(&pipe2Trigger,
			pipe2.getPos()->x,
			pipe2.getPos()->y + pipe2.getPhyObject()->getTrigger()->height,
			-pipe2.getPhyObject()->getTrigger()->height,
			pipe2.getPhyObject()->getTrigger()->width,
			1,
			1,
			"pipe2",
			"pipe"
		);
		if (triggerClass.isColliding(pipe.getPhyObject()->getTrigger()[0], player.getPhyObject()->getTrigger()[0])) {
			std::cout << "OYUN BITTI"; point = 0;
		}
		else if (triggerClass.isColliding(pipe2Trigger, player.getPhyObject()->getTrigger()[0])) {
			std::cout << "OYUN BITTI"; point = 0;
		}
		Trigger pointTrigger;
		triggerClass.setTrigger(&pointTrigger,
			pipe2.getPos()->x,
			pipe2.getPos()->y,
			PipeScaleX,
			pipe.getPos()->y - pipe2.getPos()->y,
			1, 1,
			"pointTrigger",
			"pointTrigger"
		);
  		controlPoint = triggerClass.isColliding(pointTrigger, player.getPhyObject()->getTrigger()[0]);
		if (prevPoint != controlPoint && controlPoint) {
			point++;
			std::cout << "PUAN" << std::endl;
		}
		prevPoint = controlPoint;

		/// Animasyon
		
		//ÇARPIŞMA OLAYLARI
		//FIZIK OLAYLARI
		//ANİMASYON OLAYLARI
		//ÇİZİM OLAYLARI
		window.clear(sf::Color::Black);
		ui.draw();
		pipe.draw();
		pipe2.draw();
		player.draw();
		cursor.draw();

		ui.getText(0)->setString(std::to_string(point));
		window.setTitle(std::to_string(point)+":"+std::to_string(controlPoint)+":"+std::to_string(prevPoint)+" Highscore:"+std::to_string(highScore));
		window.display();
	}

	return 0;

}