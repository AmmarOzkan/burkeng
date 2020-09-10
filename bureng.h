#pragma once

#ifndef BURENG
#define BURENG

#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>

struct tValBool {
	bool b1, b2;
};

struct Texturee {
	sf::Texture texture;
	int height, width;
	std::string id;
};

struct f2 {
	float f1, f2;
};

struct valueXY {
	float x, y;
};



void setTexturee(Texturee* urTexture, int width, int height, std::string id, sf::String filePath) {
	urTexture->width = width;
	urTexture->height = height;
	urTexture->id = id;
	std::cout << std::endl << "Texture:" << urTexture->id << " yukleme durumu: " << urTexture->texture.loadFromFile(filePath);
}

struct collideRes {
	std::string id;
	bool res;
};
struct collideRes2 {
	std::string id;
	bool res1, res2;
};

#ifndef SUPERSTR
#error SUPERSTR dizisinin ka� tane oldu�u belirtilmeli #define SUPERSTR [dizisayisi]
#else
struct superStr {
	std::string str[SUPERSTR];
	int nextString = 0;
};

void startSS(superStr* str) {
	str->nextString = 0;
}

/// <summary>
/// SuperSTR'ye string ekler
/// </summary>
/// <param name="str">Senin str nesnen</param>
/// <param name="string">String verisi</param>
void addString(superStr* str, std::string string) {
	if (str->nextString == SUPERSTR) {
		std::cout << std::endl << "SUPERSTR MAXIMUM SINIRI ASILDI";
	}
	else {
		str->str[str->nextString] = string;
		str->nextString++;
	}
}

/// <summary>
/// SuperSTR'de hi� �u string varm�
/// </summary>
/// <param name="str">str nesnen</param>
/// <param name="string">kontrol edilecek string</param>
/// <returns>var?</returns>
bool isThereAnySTR(superStr str, std::string string) {
	for (int i = 0; i < SUPERSTR; i++) {
		if (str.str[i] == string) {
			return true;
		}
	}
	return false;
}
#endif

/// <summary>
/// Pencereni senin i�in haz�rlar
/// </summary>
/// <param name="window">Pencerenin Adresi</param>
/// <param name="frameRate">Penceredeki Yenilenme H�z�</param>
void setWindow(sf::RenderWindow& window, int frameRate) {
	window.setActive(true);
	window.setFramerateLimit(frameRate);
	window.setMouseCursorVisible(false);
}

/// <summary>
/// Fontu ayarlar ve font ayarlan�p ayarlanamad���n� komut penceresine yazd�r�r.
/// E�er bir hata meydana geldiyse bunu komut penceresinde yazd�r�r.
/// </summary>
/// <param name="filePath">Dosya Yolu</param>
/// <param name="id">Komut penceresinde yaz�lacak olan ismi</param>
/// <returns>Yeni fontu d�nd�r�r.</returns>
sf::Font setFont(sf::String filePath, std::string id) {
	sf::Font font;
	std::cout << std::endl << "Font " << id << " Yukleme Durumu: " << font.loadFromFile("res/fonts/batmfo__.ttf");
	if (!font.loadFromFile("res/fonts/batmfo__.ttf")) {
		std::cout << std::endl << "Font " << id << " yuklenmesinde bir hata meydana geldi.";

	}
	return font;
}



class gameObject {
private:
	valueXY pos, scale, * camera;
	sf::Texture texture;
	Texturee texturee;
	sf::RenderWindow* window;
	bool scaleSetted, posSetted;
public:
	/// <summary>
	/// Oyun objesinin pozisyonunu b�y�kl���n� vs ayarlar. Hoj bir s�n�ft�r.
	/// </summary>
	/// <param name="filePath">Texture'�n oldu�u dosya yolu</param>
	/// <param name="x">X pozisyonu</param>
	/// <param name="y">Y pozisyonu</param>
	/// <param name="scaleX">X geni�leme katsay�s�</param>
	/// <param name="scaleY">Texture'�n y'inin ne kadar b�y�t�lece�i</param>
	/// <param name="textureHeight">Texture dikey pixel say�s�</param>
	/// <param name="textureWidth">Texture dikey pixel say�s�</param>
	/// <param name="id">Komut penceresinde yaz�lacak olan ismi</param>
	/// <param name="yourWindow">�izilecek olan ekran de�i�keninin adresi</param>
	gameObject(sf::String filePath, float x, float y, float scaleX, float scaleY, int textureHeight, int textureWidth, std::string id, sf::RenderWindow* yourWindow, valueXY* urCamera) {
		scaleSetted = true;
		posSetted = true;
		texturee.height = textureHeight; texturee.width = textureWidth; texturee.id = id;
		std::cout << std::endl << "Texture:" << texturee.id << " yukleme durumu: " << texturee.texture.loadFromFile(filePath);
		pos.x = x; pos.y = y;
		scale.x = scaleX;
		scale.y = scaleY;
		window = yourWindow;
		camera = urCamera;
	}
	/// <summary>
	/// Oyun objesinin pozisyonunu b�y�kl���n� vs ayarlar. Hoj bir s�n�ft�r.
	/// </summary>
	/// <param name="urTexturee">Texturee de�i�keni</param>
	/// <param name="x">X pozisyonu</param>
	/// <param name="y">Y pozisyonu</param>
	/// <param name="scaleX">X geni�leme katsay�s�</param>
	/// <param name="scaleY">Y geni�leme katsay�s�</param>
	/// <param name="yourWindow">�izilecek olan ekran de�i�keninin adresi</param>
	gameObject(Texturee urTexturee, float x, float y, float scaleX, float scaleY, sf::RenderWindow* yourWindow, valueXY* urCamera) {
		scaleSetted = true;
		posSetted = true;
		std::cout << std::endl << "Texture " << urTexturee.id << " ekleniyor.";
		texturee = urTexturee;
		pos.x = x; pos.y = y;
		scale.x = scaleX;
		scale.y = scaleY;
		window = yourWindow;
		camera = urCamera;
	}
	/// <summary>
	/// Objeyi ekrana �izer
	/// </summary>
	void draw() {
		sf::Sprite sprite;
		sprite.setTexture(texturee.texture);
		if (scaleSetted) {
			sprite.setScale(scale.x, scale.y);
		}if (posSetted) {
			sprite.setPosition(pos.x + camera->x, pos.y + camera->y);
		}
		else {
			sprite.setPosition(10, 10);
		}
		window->draw(sprite);
	}

	void setTexturee(Texturee txr) {
		texturee = txr;
	}

	/// <summary>
	/// Pozisyonu ayarlar
	/// </summary>
	/// <param name="x">Pozisyon X</param>
	/// <param name="y">Pozisyon Y</param>
	valueXY* position() {
		return &pos;
	}valueXY* getScale() {
		return &scale;
	}Texturee* getTexturee() {
		return &texturee;
	}
};

//FOR PHYSICS

///Dir
enum Dir { LEFT, RIGHT, UP, DOWN, NONE };

/// <summary>
/// �arp��ma kontrolc�s� verilerini tutan de�i�ken
/// </summary>
struct Trigger {
	float posX, posY, height, width;
	std::string id;
};

/// <summary>
/// �arp��mayla alakal� olaylar� kontrol eden yapan s�n�f
/// </summary>
class TriggerClass {
public:
	/// <summary>
	/// �arp���yormu �arp��m�yormu
	/// </summary>
	/// <param name="fTrigger">�lk trigger</param>
	/// <param name="sTrigger">�kinci trigger</param>
	/// <returns>�arp���p �arp��mad���n� true false olarak d�nd�r�r</returns>
	bool isColliding(Trigger fTrigger, Trigger sTrigger) {
		bool xCol = fTrigger.posX + fTrigger.width >= sTrigger.posX && sTrigger.posX + sTrigger.width >= fTrigger.posX;
		bool yCol = fTrigger.posY + fTrigger.height >= sTrigger.posY && sTrigger.posY + sTrigger.height >= fTrigger.posY;
		return xCol && yCol;
	}

	/// <summary>
	/// Trigger de�i�kenini bizim i�in gameObject de�i�kenine g�re haz�rlar
	/// </summary>
	/// <param name="trigger">Trigger de�i�keninin adresi</param>
	/// <param name="urObject">Oyun objesi</param>
	void setTrigger(Trigger* trigger, gameObject* urObject) {
		trigger->posX = urObject->position()->x;
		trigger->posY = urObject->position()->y;
		trigger->height = urObject->getTexturee()->height * urObject->getScale()->y;
		trigger->width = urObject->getTexturee()->width * urObject->getScale()->x;
	}
}triggerClass;

/// <summary>
/// Fizik verilerini tutan de�i�ken (�imdilik tek �ey var ama daha �ok �ey ekleyecem)
/// </summary>
struct PhyVal {
	float gravity;
};

/// <summary>
/// PhyVal de�i�kenini bizim i�in ayarlar
/// </summary>
/// <param name="urVal">De�i�kenin adresi</param>
/// <param name="gravity">Yer�ekimi</param>
void setPhyVal(PhyVal* urVal, float gravity) {
	urVal->gravity = gravity;
}

//Bir dizide ka� tane trigger oldu�unu belirtmemiz istenir.
//Bu �ekilde k�t�phaneyi yapan de�il k�t�phaneyi kullanan dizilerin ka� tane oldu�unu belirtmi� olur.
#ifndef TRIGGERCONTROL
#error Kac tane trigger control oldugunu define TRIGGERCONTROL [sayi] olarak belirlemelisin
#else

/// <summary>
/// Triggerlar�n hepsini kontrol edebilmek i�in gerekli olan de�i�ken.
/// </summary>
struct Triggers {
	Trigger* trigger[TRIGGERCONTROL];
	std::string* id[TRIGGERCONTROL];
	int nextTrigger;
};

/// <summary>
/// Triggers'� bizim i�in ayarlar
/// </summary>
/// <param name="urTriggers">De�i�kenin adresi</param>
void setTriggers(Triggers* urTriggers) {
	urTriggers->nextTrigger = 0;
}
/// <summary>
/// Triggers de�i�kenine yeni bir trigger ekleme i�lemini ger�ekle�tirir
/// </summary>
/// <param name="urTriggers">De�i�kenin adresi</param>
/// <param name="urTrigger">Eklenecek trigger'�n adresi</param>
/// <param name="id">Yaz�sal id (�arp��malarda neye �arp�p �arpmad���n� kontrol etmeye yar�yor)</param>
void addNewTrigger(Triggers* urTriggers, Trigger* urTrigger, std::string* id) {
	if (urTriggers->nextTrigger == TRIGGERCONTROL) {
		std::cout << std::endl << "maksimum triggers sayisina ersildi";
	}
	else {
		urTriggers->trigger[urTriggers->nextTrigger] = urTrigger;
		urTriggers->id[urTriggers->nextTrigger] = id;
		urTriggers->nextTrigger++;
	}
}



/// <summary>
/// Fizik olaylar�n� i�inde bulunduran gameObject
/// </summary>
class physicsObject {
private:
	gameObject* object;
	Trigger trigger;
	bool physicsActive;
	PhyVal val;
	valueXY force;
	Triggers triggerControl;
	superStr collided;
public:
	/// <summary>
	/// Kontrol edilecek trigger oldu�unda kontrol edileceklere ekler
	/// </summary>
	/// <param name="urTrigger">Eklenecek trigger'�n idsi</param>
	/// <param name="id">Trigger'�n yaz�sal idsi</param>
	void addControl(Trigger* urTrigger, std::string* id) {
		addNewTrigger(&triggerControl, urTrigger, id);
	}

	/// <summary>
	/// Kendi trigger'�n� gameObjecte g�re ayarlar.
	/// </summary>
	void setTrigger() {
		triggerClass.setTrigger(&trigger, object);
	}
	/// <summary>
	/// Physics Object olu�turulurken kulland���m hep olan bir start fonksiyonu. Kullan�c�n�n kullanmas�na gerek yok.
	/// </summary>
	void fixStart() {
		setTriggers(&triggerControl);
		setTrigger();
		force.x = 0;
		force.y = 0;
		startSS(&collided);
	}

	/// <summary>
	/// physicsObject olu�turucusu
	/// </summary>
	/// <param name="urObject">gameObjectin adresi</param>
	/// <param name="physicsIsActive">fizi�i olucakm� olmayacakm� (sonradan de�i�tirilebilir)</param>
	/// <param name="gravity">yer�ekimi</param>
	/// <param name="id">olu�turulurken komut sat�r�nda kontorl i�in yaz�cak olan id</param>
	physicsObject(gameObject* urObject, bool physicsIsActive, float gravity, std::string id)
		: object(urObject), physicsActive(physicsIsActive)
	{
		fixStart();
		setPhyVal(&val, gravity);
		std::cout << std::endl << "Fizik Objesi: " << id << " olusturuldu.";
	}
	/// <summary>
	/// physicsObject olu�turucusu
	/// </summary>
	/// <param name="urObject">gameObjectin adresi</param>
	/// <param name="physicsIsActive">fizi�i olucakm� olmayacakm� (sonradan de�i�tirilebilir)</param>
	/// <param name="urVal">Fizik de�i�keni varsa yer�ekimi verisi vs girmek yerine bu girilir</param>
	/// <param name="id">olu�turulurken komut sat�r�nda kontorl i�in yaz�cak olan id</param>
	physicsObject(gameObject* urObject, bool physicsIsActive, PhyVal urVal, std::string id)
		: object(urObject), val(urVal), physicsActive(physicsIsActive)
	{
		fixStart();
		std::cout << std::endl << "Fizik Objesi: " << id << " olusturuldu.";
	}

	/// <summary>
	/// Objeyi �izer
	/// </summary>
	void draw() {
		object->draw();
	}

	/// <summary>
	/// 2 �arp��mada 2. objenin 1. objenin neresinde oldu�unu d�nd�r�r
	/// </summary>
	/// <param name="urTrigger">Trigger 1</param>
	/// <param name="objectTrigger">Trigger 2</param>
	/// <returns>nerede oldu�unu d�nd�r�r</returns>
	Dir where(Trigger urTrigger, Trigger objectTrigger) {
		if (urTrigger.posX > objectTrigger.posX) return RIGHT;
		else if (urTrigger.posX + urTrigger.width < objectTrigger.posX + objectTrigger.width) return LEFT;
		else if (urTrigger.posY > objectTrigger.posY) return UP;
		else if (urTrigger.posY + urTrigger.height < objectTrigger.posY + objectTrigger.height) return DOWN;
		else return NONE;
	}

	/// <summary>
	/// Obje bir objeyle �arp���yormu
	/// </summary>
	/// <param name="oObject">Kontrol edilecek objenin Trigger de�i�keni</param>
	/// <returns>�arp���yomu �arp��m�yomu</returns>
	bool isColliding(Trigger oObject) {
		oObject.id = "D�� Obje";
		trigger.id = "Burka";
		bool test = triggerClass.isColliding(oObject, trigger);
		return test;

	}

	/// <summary>
	/// �oklu obje kontrol�nden herhangi bir objeyle �arp���yor mu
	/// </summary>
	/// <param name="oObject">Obje trigger�</param>
	/// <param name="id">�oklu obje kontrol�nden kontrol edilecek olan �eyin idsi</param>
	/// <returns>�arp��t�?</returns>
	collideRes isColliding(Trigger oObject, std::string willControl) {
		collideRes res = { "",false };
		for (int i = 0; i < triggerControl.nextTrigger; i++) {
			if (triggerClass.isColliding(triggerControl.trigger[i][0], oObject) && ((triggerControl.id[i][0] == willControl) != (willControl == ""))) {
				res.res = true;
				res.id = triggerControl.id[i][0];
				if (!isThereAnySTR(collided, res.id)) {
					addString(&collided, res.id);
					std::cout << std::endl << collided.nextString << ":" << collided.str[i];
				}
			}
		}
		return res;
	}

	/// <summary>
	/// �arp��an Triggerlar�n idlerini d�nd�r�r
	/// </summary>
	/// <returns>superStr idler</returns>
	superStr getCollidings() {
		superStr res = collided;
		startSS(&collided);
		return res;
	}

	/// <summary>
	/// Fizik aktifmi de�ilmi
	/// </summary>
	/// <param name="isActive">akitfmi?</param>
	void setPhysics(bool isActive) {
		physicsActive = isActive;
	}

	/// <summary>
	/// Genel id kontrol�yle �arp��ma.
	/// Herhangi bir �imenle �arp��t�m�?
	/// Herhangi bir topla �arp��t�m�?
	/// </summary>
	/// <param name="willControl">Kontrol edilecek Triggers id'si</param>
	/// <returns>�arp���yomu?</returns>
	bool control(std::string willControl) {
		bool control = false;
		for (int i = 0; i < triggerControl.nextTrigger; i++) {
			if (isColliding(triggerControl.trigger[i][0]) && triggerControl.id[i][0] == willControl || willControl == "") {
				control = true;
			}
		}
		return control;
	}

	/// <summary>
	/// G�venli bir �ekilde x pozisyonunda haraket i�lemi.
	/// E�er ilerlerken parametredeki id ile bir obje �arp��t�ysa eklemeyi durdurur ve eklenmemi� hale getirir.
	/// </summary>
	/// <param name="w">�lerlenecek birim say�s�</param>
	/// <param name="perf">Performans say�s�. Ka�ar ka�ar kontrol edece�i yani</param>
	/// <param name="willControl">Kontrol edilecek id</param>
	/// <returns>Ne taraftan �arpt���na g�re 2lik bool d�nd�r�r</returns>
	collideRes addX(float w, float perf, std::string willControl) {
		collideRes res;
		res.res = false;
		res.id = "";
		if (w > 0) {
			for (float i = 0.0; i < w; i += perf) {
				Trigger preTrigger;
				triggerClass.setTrigger(&preTrigger, object);
				preTrigger.posX += perf;
				collideRes colliding = isColliding(preTrigger, willControl);
				if (colliding.res) {
					//Burda �arp��t� ve �arp��mam�� hale geri d�nd�.
					res.res = true;
					res.id = colliding.id;
					break;
				}
				else {
					object->position()->x += perf;
				}
			}
		}
		else if (w < 0) {
			for (float i = 0.0; i > w; i -= perf) {
				Trigger preTrigger;
				triggerClass.setTrigger(&preTrigger, object);
				preTrigger.posX -= perf;
				collideRes colliding = isColliding(preTrigger, willControl);
				if (colliding.res) {
					//Burda �arp��t� ve �arp��mam�� hale geri d�nd�.
					res.res = true;
					break;
				}
				else {
					object->position()->x -= perf;
				}
			}
		}
		return res;
	}

	/// <summary>
	/// G�venli bir �ekilde y pozisyonunda haraket i�lemi.
	/// E�er ilerlerken parametredeki id ile bir obje �arp��t�ysa eklemeyi durdurur ve eklenmemi� hale getirir.
	/// </summary>
	/// <param name="w">�lerlenecek birim say�s�</param>
	/// <param name="perf">Performans say�s�. Ka�ar ka�ar kontrol edece�i yani</param>
	/// <param name="willControl">Kontrol edilecek id</param>
	/// <returns>Ne taraftan �arpt���na g�re 2lik bool d�nd�r�r</returns>
	collideRes addY(float w, float perf, std::string willControl) {
		collideRes res;
		res.res = false;
		res.id = "";
		if (w > 0) {
			for (float i = 0.0; i < w; i += perf) {
				Trigger preTrigger;
				triggerClass.setTrigger(&preTrigger, object);
				preTrigger.posY += perf;
				collideRes colliding = isColliding(preTrigger, willControl);
				if (colliding.res) {
					//Burda �arp��t� ve �arp��mam�� hale geri d�nd�.
					res.res = true;
					res.id = colliding.id;
					break;
				}
				else {
					object->position()->y += perf;
				}
			}
		}
		else if (w < 0) {
			for (float i = 0.0; i > w; i -= perf) {
				Trigger preTrigger;
				triggerClass.setTrigger(&preTrigger, object);
				preTrigger.posY -= perf;
				collideRes colliding = isColliding(preTrigger, willControl);
				if (colliding.res) {
					//Burda �arp��t� ve �arp��mam�� hale geri d�nd�.
					res.res = true;
					res.id = colliding.id;
					break;
				}
				else {
					object->position()->y -= perf;
				}
			}
		}
		return res;
	}

	/// <summary>
	/// Obje X veya Y pozisyonunda seker
	/// </summary>
	/// <param name="isX">E�er X sekecekse buraya true Y sekecekse false girilir.</param>
	void bounce(bool isX) {
		if (isX) {
			force.x /= 1.5;
			force.x *= -1;
		}
		else {
			force.y /= 1.5;
			force.y *= -1;
		}
	}

	void forceControl() {
		if (force.x > 50) {
			force.x = 50;
		}
		else if (force.y > 50) {
			force.y = 50;
		}
	}

	/// <summary>
	/// Force x ve y sini 0'a e�itler
	/// </summary>
	void forceClear() {
		force.x = 0; force.y = 0;
	}

	/// <summary>
	/// Force'a x ve y de�erleri ekler
	/// </summary>
	/// <param name="x">Eklenecek X de�eri</param>
	/// <param name="y">Eklenecek Y de�eri</param>
	void forceAdd(float x, float y) {
		force.x += x;
		force.y += y;
	}

	/// <summary>
	/// Forcedaki de�erleri kullanarak haraket i�lemini yapar
	/// </summary>
	/// <param name="perf">Performans de�eri. Ka� birimde bir kontrol edilece�i.</param>
	/// <param name="willControl">Kontrol edilecek id</param>
	collideRes2 phyMove(float perf, std::string willControl) {
		collideRes2 res;
		res.id = "";
		res.res1 = false;
		res.res2 = false;
		if (physicsActive) {
			forceAdd(0.0, val.gravity);
		}
		force.x /= 1.05;
		collideRes collideX = addX(force.x, perf, willControl);
		collideRes collideY = addY(force.y, perf, willControl);
		if (collideX.res) {
			force.x = 0;
			bounce(true);
			res.res1 = true;
		}
		else if (collideY.res) {
			force.y = 0;
			bounce(false);
			res.res2 = true;
		}
		return res;
	}

	/// <summary>
	/// E�er triggers de�i�keni �ok objeye eklenecekse Triggers de�i�keni kod i�inde tan�mlan�r, Triggerlar eklenir ve bu fonksiyon ile objeye atan�r.
	/// </summary>
	/// <param name="urTriggers">Triggers objen</param>
	void setPhyTriggers(Triggers urTriggers) {
		triggerControl = urTriggers;
	}

	/// <summary>
	/// gameObject'in adresini d�nd�r�r
	/// </summary>
	/// <returns>physicsObject.gameObject</returns>
	gameObject* getObject() {
		return object;
	}

	/// <summary>
	/// Objenin trigger de�i�keninin adresini d�nd�r�r
	/// </summary>
	/// <returns>Objedeki Trigger</returns>
	Trigger* getTrigger() {
		return &trigger;
	}

	valueXY* getForce() {
		return &force;
	}
};
#endif


//Bir dizide ka� tane UIELEMENT oldu�unu belirtmemiz istenir.
//Bu �ekilde k�t�phaneyi yapan de�il k�t�phaneyi kullanan dizilerin ka� tane oldu�unu belirtmi� olur.
#ifndef UIELEMENTS
#error UIELEMENTS'i define edip bir say� belirtmen gerekiyor.
//Bu UIELEMENTS program�nda ka� tane UI element'i kullanaca��n� belirtir.
#else
/// <summary>
/// UI CLASS UI objelerini olu�turmaya �izmeye ve kontrol� sa�lar
/// </summary>
class UI {
private:
	sf::Font font;
	sf::Text texts[UIELEMENTS];
	std::string id;
	sf::RenderWindow* window;
public:
	/// <summary>
	/// UI S�n�f� olu�turucusu
	/// </summary>
	/// <param name="fontFilePath">Fontun dosya yolu</param>
	/// <param name="fontId">Font y�klenirken kontrol i�in komut sat�r�nda g�z�kecek olan id</param>
	/// <param name="urWindow">�izilecek olan pencerenin adresi</param>
	UI(sf::String fontFilePath, std::string fontId, sf::RenderWindow* urWindow) {
		font = setFont(fontFilePath, fontId);
		id = fontId;
		window = urWindow;
	}
	/// <summary>
	/// Dizideki herhangi bir objenin verilerini girmeye yarar. Bu yeni bir obje olu�turmada olabilir. Makismum UIELEMENTS kadar obje girilebilir.
	/// </summary>
	/// <param name="array">Ka��nc� obje</param>
	/// <param name="string">Yaz�</param>
	/// <param name="posX">Pozisyon X</param>
	/// <param name="posY">Pozisyon Y</param>
	void setObj(int array, sf::String string, int posX, int posY) {
		texts[array].setString(string);
		texts[array].setFont(font);
		texts[array].setPosition(posX, posY);
	}

	/// <summary>
	/// Herhangi bir Text objesinin adresini alma.
	/// </summary>
	/// <param name="array">Dizideki ka��nc�</param>
	/// <returns>Se�ti�imiz objenin adresini d�nd�r�r</returns>
	sf::Text* getText(int array) {
		return &texts[array];
	}

	/// <summary>
	/// UI Objelerini ekrana �izdirir.
	/// </summary>
	void draw() {
		for (int i = 0; i < UIELEMENTS; i++) {
			window->draw(texts[i]);
		}
	}
};
#endif

//Yukardakilerle benzer �eyler
#ifndef MULTIS
#error MultiDraw i�in MULTIlerin max ka� tane olmas�n� istedi�ini giriniz. (define MULTIS)
#else
/// <summary>
/// �oklu obje �izimleri i�in s�n�f
/// </summary>
class MultiDraw {
private:
	physicsObject* objects[MULTIS];
	int nextMulti = 0;
public:
	/// <summary>
	/// �izilecek �eylere bir physicsObject atar
	/// </summary>
	/// <param name="object">Fizik Objesi</param>
	void addObject(physicsObject* object) {
		if (nextMulti == MULTIS) {
			std::cout << std::endl << "Maksimum MULTIS";
		}
		else {
			objects[nextMulti] = object;
			nextMulti++;
		}
	}
	/// <summary>
	/// �oklu �izim yap�lacak objeleri ekranlar�na �izdirir
	/// </summary>
	void draw() {
		for (int i = 0; i < nextMulti; i++) {
			objects[i]->draw();
		}
	}

};

#endif

#endif