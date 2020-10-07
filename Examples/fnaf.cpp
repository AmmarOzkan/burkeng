#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <ctime>


#define UIELEMENTS 100
#define TRIGGERCONTROL 50
#define MULTIS 50
#define DOUBLESTRINGN 50
#define SUPERSTR 50
#define ANIMPERFRAME 30
#define DRAWOBJECTAMOUNT 50

#define NODEBUG

#include "RENG/bureng_exten.h"
#include "RENG/bureng.h"
#include "RENG/GameTools.h"
#include "monsterlib.h"

#define WIDTH 1200
#define HEIGHT 900
#define PROPORTION 10

#define PERFORMANCE 1.0

/*
*			0
*	7	 1		2
*	
*			3
*		 4		5
*/



int main()
{

	srand(time(0));
	//PENCERE OLUŞTURMA
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "FNAF");
	setWindow(window, 60);

	//KAMERA
	valueXY camera = { 0,0 };
	valueXY non = { 0,0 };
	//Textureler
	//CURSOR
	Texturee cursorTexture = setTexturee(330, 418, "CursorTexture", "res/flappybird/mouse.png");
	Texturee officeTexture= setTexturee(1000, 480, "OfficeTexture", "res/fnaf/office.png");
	Texturee cameraButtonTexture = setTexturee( 512, 512, "ArrowButtonTexture", "res/fnaf/arrowButton.png");
	Texturee cameraSystemTexture = setTexturee( 420, 420, "CameraSystemTexture", "res/fnaf/cameraSystem.png");
	Texturee buttonTexture = setTexturee(512, 231, "TestButtonTexture", "res/fnaf/testButton.png");
	Texturee benekTexture = setTexturee(14, 13, "BenekTexture", "res/fnaf/benek.png");

	Texturee cameraIdle[6];
	Texturee cameraF[6];
	Texturee cameras[6];

	Texturee test = setTexturee(100,100,"",loadImage());
	gameObject testObject(test, 0, 0, 1, 1, false, &window, &non);

	cameraIdle[0] = setTexturee(1280, 720, "camera1Idle", "res/fnaf/mainCam.jpg");
	cameraF[0] = setTexturee(1280, 720, "camera1F", "res/fnaf/mainCamF.png");
	cameras[0] = cameraIdle[0];

	cameraIdle[1] = setTexturee(1175, 630, "camera2Idle", "res/fnaf/cam1.png");
	cameraF[1] = setTexturee(1175, 630, "camera2F", "res/fnaf/cam1F.png");
	cameras[1] = cameraIdle[1];

	cameraIdle[2] = setTexturee(825, 650, "camera3Idle", "res/fnaf/exitCam.png");
	cameraF[2] = setTexturee(825, 650, "camera3F", "res/fnaf/exitCamF.png");
	cameras[2] = cameraIdle[2];

	cameraIdle[3] = setTexturee(1250, 540, "camera4Idle", "res/fnaf/cam.png");
	cameraF[3] = setTexturee(1250, 540, "camera4F", "res/fnaf/camF.png");
	cameras[3] = cameraIdle[3];

	cameraIdle[4] = setTexturee(825, 650, "camera5Idle", "res/fnaf/vent2.png");
	cameraF[4] = setTexturee(825, 650, "camera5F", "res/fnaf/vent2F.png");
	cameras[4] = cameraIdle[4];

	cameraIdle[5] = setTexturee(825, 650, "camera6Idle", "res/fnaf/vent.png");
	cameraF[5] = setTexturee(825, 650, "camera6F", "res/fnaf/ventF.png");
	cameras[5] = cameraIdle[5];

	Texturee jumpscareTexture = setTexturee(315, 760, "spring", "res/fnaf/spring.png");
	Texturee alertTexture = setTexturee(1138, 1024, "alert", "res/fnaf/alert.png");

	gameObject cursor(cursorTexture, 0, 0, WIDTH * 0.5 / PROPORTION, WIDTH * 0.5 / PROPORTION, true, &window, &non);
	gameObject office(officeTexture, 0, 0, 1200, 900, true, &window, &camera);
	gameObject videoCamera(cameraIdle[0], 50, 150, 900, 600, true, &window, &non);
	gameObject jumpscare(jumpscareTexture, 200, 100, 1, 1, false, &window, &camera);
	gameObject alert(alertTexture, WIDTH - 100, 0, 100, 100, true, &window, &non);

	Button cameraButton(cameraButtonTexture, "cameraButton", WIDTH/2+50, HEIGHT-100, 100, 100, false, &window);
	Button rightE(cameraButtonTexture, "rightE", 1100, 800, 100, 100, false, &window);
	Button leftE(cameraButtonTexture, "leftE", 0, 800, 100, 100, false, &window);

	UI ui("res/fnaf/PixelFJVerdana.ttf", "Ana Font", &window);
	ui.setText(0, "Test", 0, 0);

	UI cameraUI("res/fnaf/PixelFJVerdana.ttf", "Ana Font", &window);
	Panel cameraPanel({ 50,50 }, { 1100,800 }, cameraSystemTexture, false, &cameraUI, &window);
	cameraPanel.addButton(buttonTexture, "SecuritySystemButton", 800, 0, 300, 100, false);
	cameraPanel.addText("CameraSystem", 0, 0, 0);
	cameraPanel.addText("Geçiş Yap", 1, 800, 0);
	///Kamera Butonları
	cameraPanel.addButton(buttonTexture, "Cam0Button", 950, 450, 50, 50, false);
	cameraPanel.addButton(buttonTexture, "Cam1Button", 900, 500, 50, 50, false);
	cameraPanel.addButton(buttonTexture, "Cam2Button", 1000, 500, 50, 50, false);
	cameraPanel.addButton(buttonTexture, "Cam3Button", 950, 600, 50, 50, false);
	cameraPanel.addButton(buttonTexture, "Cam4Button", 900, 650, 50, 50, false);
	cameraPanel.addButton(buttonTexture, "Cam5Button", 1000, 650, 50, 50, false);
	cameraPanel.addText("Pil", 2, 900, 100);


	cameraPanel.addButton(buttonTexture, "CCCC", 1000, 100, 50, 50, false);


	UI securityUI("res/fnaf/PixelFJVerdana.ttf", "Ana Font", &window);
	Panel securityPanel({ 50,50 }, { 1100,800 }, cameraSystemTexture, false, &securityUI, &window);
	securityPanel.addText("SecurityPanel", 0, 0, 0);
	securityPanel.addButton(buttonTexture, "SecuritySystemButton", 800, 0, 300, 100, false);
	securityPanel.addText("Geçiş Yap", 1, 800, 0);
	securityPanel.addButton(buttonTexture, "GeneratorButton", 50, 100, 500, 100, true);
	securityPanel.addButton(buttonTexture, "CameraFix", 50, 200, 100, 100, true);
	securityPanel.addText("Pil", 2, 800, 100);

	Panel mainPanel = cameraPanel;

	//SOUND
	PreSound electricEffect("res/fnaf/electric.wav", "electric");
	PreSound cameraSwitch("res/fnaf/cameraSwitch.wav", "cameraSwitch");
	PreSound start("res/seslendirme/anla.wav", "start");
	bool cameraPanelOn = false, menu = false;

	float electric = 100.0;

	Monster m;
	m.setGoal(-1);
	int onCamera = 1;

	int speed = 200;
	int counter = speed;
	bool gameEnd = false;
	int jumpScareCounter = 100;
	int jumpScareM = 0;

	bool jumpScare = false;

	bool generator = false;
	int pre = 0;
	bool cameraWorking = true;

	//start play
	//start.play();
	while (window.isOpen()) {
		//KURALLAR
		mainPanel.getUI()->getText(2)->setString(std::to_string((int)electric));
		gameEnd = jumpScareCounter < 0 || electric < 0;
		jumpScareCounter -= jumpScareM;
		jumpScareM = (m.getRoom() == 6) * 1;
		int panelClicked = -1;
		electric -= 0.01 * cameraPanelOn;

		sf::Event event;
		while (window.pollEvent(event)) {
			//Cursor
			cameraButton.control(event);
			panelClicked = mainPanel.getClickId(event);
			electric -= 1.0 * rightE.control(event);
			electric -= 1.0 * leftE.control(event);
			if (event.type == sf::Event::MouseMoved) {
				cursor.position()->x = event.mouseMove.x;
				cursor.position()->y = event.mouseMove.y;
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
				m.setRoom(0);
			}
		}
		//KONTROL OLAYLARI
		if (cameraButton.getClick()) {
			cameraPanelOn = !cameraPanelOn;
		}
		if (menu == false) {
			mainPanel = cameraPanel;
		}
		else if (menu == true) {
			mainPanel = securityPanel;
		}
		mainPanel.setActivite(cameraPanelOn && jumpScareM == 0);
		//Panel değiştirme
		if (panelClicked == 0) menu = !menu;
		//Hile :D
		if (panelClicked == 7 && !menu) m.setGoal(0);
		//Kamera Değişme
		if (panelClicked < 7 && panelClicked > 0 && !menu) {
			cameraSwitch.play();
			onCamera = panelClicked;
		}

		if (panelClicked == 1 && menu) generator = !generator;
		else if (panelClicked == 2 && menu) cameraWorking = true;
		electric += generator * 0.03;

		counter--;
		pre = m.getRoom();
		if (counter < 0) {
			m.moveGoal();
			counter = speed;
		}
		if (m.getRoom() == 7) {
			std::cout << "camera cut down" << std::endl;
			cameraWorking = false;
		}
		if (m.getGoal() == -1) {
			if (rand() % 2) m.setGoal(4);
			else m.setGoal(5);
		}
		for (int i = 0; i < 6; i++) {
			if (m.getRoom() == i) {
				cameras[i] = cameraF[i];
			}
			else {
				cameras[i] = cameraIdle[i];
			}
		}

		videoCamera.setTexturee(cameras[onCamera - 1], true);

		if (rightE.getClick() && electric > 0 && m.getRoom() == 5 && !generator) {
			electric -= 1;
			m.setGoal(7);
			m.moveGoal();
			counter = speed;
			electricEffect.get()->play();
		}
		else if (leftE.getClick() && electric > 0 && m.getRoom() == 4 && !generator) {
			electric -= 1;
			m.setGoal(7);
			m.moveGoal();
			counter = speed;
			electricEffect.get()->play();
		}
		//ÇARPIŞMA OLAYLARI
		//FIZIK OLAYLARI
		//ANİMASYON OLAYLARI
		//ÇİZİM OLAYLARI
		window.clear(sf::Color::Black);
		if (!gameEnd) {
			office.draw();
			if (m.getRoom() == 6) {
				jumpscare.draw();
			}
			cameraButton.draw();
			rightE.draw();
			leftE.draw();
			mainPanel.draw();
			if (menu == false && cameraPanelOn && jumpScareM == 0 && cameraWorking) videoCamera.draw();
			if (m.getRoom() == 7) alert.draw();
			//mPosition.draw();
			ui.draw();
		}

		if (gameEnd) {
			break;
		}



		cursor.draw();
		testObject.draw();
		window.display();
	}
	std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;
	int val = rand() % 4;
	std::cout << val;

	sf::String file;
	if (val == 0) {
		file = "res/fnaf/komikseyler.wav";
	}
	else if(val == 1){
		file = "res/fnaf/haha.wav";
	}
	else if (val == 2) {
		file = "res/fnaf/yemek.wav";
	}
	else if (val == 3) {
		file = "res/fnaf/metalplaka.wav";
	}
	PreSound speech(file, "spch");
	speech.play();

	while (window.isOpen()) {


		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::MouseMoved) {
				cursor.position()->x = event.mouseMove.x;
				cursor.position()->y = event.mouseMove.y;
			}
		}

		window.clear(sf::Color::Black);

		cursor.draw();
		window.display();
		window.setTitle("GAME OVER");
	}

	return 0;

}