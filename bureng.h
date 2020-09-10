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
#error SUPERSTR dizisinin kaç tane olduðu belirtilmeli #define SUPERSTR [dizisayisi]
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
/// SuperSTR'de hiç þu string varmý
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
/// Pencereni senin için hazýrlar
/// </summary>
/// <param name="window">Pencerenin Adresi</param>
/// <param name="frameRate">Penceredeki Yenilenme Hýzý</param>
void setWindow(sf::RenderWindow& window, int frameRate) {
	window.setActive(true);
	window.setFramerateLimit(frameRate);
	window.setMouseCursorVisible(false);
}

/// <summary>
/// Fontu ayarlar ve font ayarlanýp ayarlanamadýðýný komut penceresine yazdýrýr.
/// Eðer bir hata meydana geldiyse bunu komut penceresinde yazdýrýr.
/// </summary>
/// <param name="filePath">Dosya Yolu</param>
/// <param name="id">Komut penceresinde yazýlacak olan ismi</param>
/// <returns>Yeni fontu döndürür.</returns>
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
	/// Oyun objesinin pozisyonunu büyüklüðünü vs ayarlar. Hoj bir sýnýftýr.
	/// </summary>
	/// <param name="filePath">Texture'ýn olduðu dosya yolu</param>
	/// <param name="x">X pozisyonu</param>
	/// <param name="y">Y pozisyonu</param>
	/// <param name="scaleX">X geniþleme katsayýsý</param>
	/// <param name="scaleY">Texture'ýn y'inin ne kadar büyütüleceði</param>
	/// <param name="textureHeight">Texture dikey pixel sayýsý</param>
	/// <param name="textureWidth">Texture dikey pixel sayýsý</param>
	/// <param name="id">Komut penceresinde yazýlacak olan ismi</param>
	/// <param name="yourWindow">Çizilecek olan ekran deðiþkeninin adresi</param>
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
	/// Oyun objesinin pozisyonunu büyüklüðünü vs ayarlar. Hoj bir sýnýftýr.
	/// </summary>
	/// <param name="urTexturee">Texturee deðiþkeni</param>
	/// <param name="x">X pozisyonu</param>
	/// <param name="y">Y pozisyonu</param>
	/// <param name="scaleX">X geniþleme katsayýsý</param>
	/// <param name="scaleY">Y geniþleme katsayýsý</param>
	/// <param name="yourWindow">Çizilecek olan ekran deðiþkeninin adresi</param>
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
	/// Objeyi ekrana çizer
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
/// Çarpýþma kontrolcüsü verilerini tutan deðiþken
/// </summary>
struct Trigger {
	float posX, posY, height, width;
	std::string id;
};

/// <summary>
/// Çarpýþmayla alakalý olaylarý kontrol eden yapan sýnýf
/// </summary>
class TriggerClass {
public:
	/// <summary>
	/// Çarpýþýyormu Çarpýþmýyormu
	/// </summary>
	/// <param name="fTrigger">Ýlk trigger</param>
	/// <param name="sTrigger">Ýkinci trigger</param>
	/// <returns>çarpýþýp çarpýþmadýðýný true false olarak döndürür</returns>
	bool isColliding(Trigger fTrigger, Trigger sTrigger) {
		bool xCol = fTrigger.posX + fTrigger.width >= sTrigger.posX && sTrigger.posX + sTrigger.width >= fTrigger.posX;
		bool yCol = fTrigger.posY + fTrigger.height >= sTrigger.posY && sTrigger.posY + sTrigger.height >= fTrigger.posY;
		return xCol && yCol;
	}

	/// <summary>
	/// Trigger deðiþkenini bizim için gameObject deðiþkenine göre hazýrlar
	/// </summary>
	/// <param name="trigger">Trigger deðiþkeninin adresi</param>
	/// <param name="urObject">Oyun objesi</param>
	void setTrigger(Trigger* trigger, gameObject* urObject) {
		trigger->posX = urObject->position()->x;
		trigger->posY = urObject->position()->y;
		trigger->height = urObject->getTexturee()->height * urObject->getScale()->y;
		trigger->width = urObject->getTexturee()->width * urObject->getScale()->x;
	}
}triggerClass;

/// <summary>
/// Fizik verilerini tutan deðiþken (Þimdilik tek þey var ama daha çok þey ekleyecem)
/// </summary>
struct PhyVal {
	float gravity;
};

/// <summary>
/// PhyVal deðiþkenini bizim için ayarlar
/// </summary>
/// <param name="urVal">Deðiþkenin adresi</param>
/// <param name="gravity">Yerçekimi</param>
void setPhyVal(PhyVal* urVal, float gravity) {
	urVal->gravity = gravity;
}

//Bir dizide kaç tane trigger olduðunu belirtmemiz istenir.
//Bu þekilde kütüphaneyi yapan deðil kütüphaneyi kullanan dizilerin kaç tane olduðunu belirtmiþ olur.
#ifndef TRIGGERCONTROL
#error Kac tane trigger control oldugunu define TRIGGERCONTROL [sayi] olarak belirlemelisin
#else

/// <summary>
/// Triggerlarýn hepsini kontrol edebilmek için gerekli olan deðiþken.
/// </summary>
struct Triggers {
	Trigger* trigger[TRIGGERCONTROL];
	std::string* id[TRIGGERCONTROL];
	int nextTrigger;
};

/// <summary>
/// Triggers'ý bizim için ayarlar
/// </summary>
/// <param name="urTriggers">Deðiþkenin adresi</param>
void setTriggers(Triggers* urTriggers) {
	urTriggers->nextTrigger = 0;
}
/// <summary>
/// Triggers deðiþkenine yeni bir trigger ekleme iþlemini gerçekleþtirir
/// </summary>
/// <param name="urTriggers">Deðiþkenin adresi</param>
/// <param name="urTrigger">Eklenecek trigger'ýn adresi</param>
/// <param name="id">Yazýsal id (Çarpýþmalarda neye çarpýp çarpmadýðýný kontrol etmeye yarýyor)</param>
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
/// Fizik olaylarýný içinde bulunduran gameObject
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
	/// Kontrol edilecek trigger olduðunda kontrol edileceklere ekler
	/// </summary>
	/// <param name="urTrigger">Eklenecek trigger'ýn idsi</param>
	/// <param name="id">Trigger'ýn yazýsal idsi</param>
	void addControl(Trigger* urTrigger, std::string* id) {
		addNewTrigger(&triggerControl, urTrigger, id);
	}

	/// <summary>
	/// Kendi trigger'ýný gameObjecte göre ayarlar.
	/// </summary>
	void setTrigger() {
		triggerClass.setTrigger(&trigger, object);
	}
	/// <summary>
	/// Physics Object oluþturulurken kullandýðým hep olan bir start fonksiyonu. Kullanýcýnýn kullanmasýna gerek yok.
	/// </summary>
	void fixStart() {
		setTriggers(&triggerControl);
		setTrigger();
		force.x = 0;
		force.y = 0;
		startSS(&collided);
	}

	/// <summary>
	/// physicsObject oluþturucusu
	/// </summary>
	/// <param name="urObject">gameObjectin adresi</param>
	/// <param name="physicsIsActive">fiziði olucakmý olmayacakmý (sonradan deðiþtirilebilir)</param>
	/// <param name="gravity">yerçekimi</param>
	/// <param name="id">oluþturulurken komut satýrýnda kontorl için yazýcak olan id</param>
	physicsObject(gameObject* urObject, bool physicsIsActive, float gravity, std::string id)
		: object(urObject), physicsActive(physicsIsActive)
	{
		fixStart();
		setPhyVal(&val, gravity);
		std::cout << std::endl << "Fizik Objesi: " << id << " olusturuldu.";
	}
	/// <summary>
	/// physicsObject oluþturucusu
	/// </summary>
	/// <param name="urObject">gameObjectin adresi</param>
	/// <param name="physicsIsActive">fiziði olucakmý olmayacakmý (sonradan deðiþtirilebilir)</param>
	/// <param name="urVal">Fizik deðiþkeni varsa yerçekimi verisi vs girmek yerine bu girilir</param>
	/// <param name="id">oluþturulurken komut satýrýnda kontorl için yazýcak olan id</param>
	physicsObject(gameObject* urObject, bool physicsIsActive, PhyVal urVal, std::string id)
		: object(urObject), val(urVal), physicsActive(physicsIsActive)
	{
		fixStart();
		std::cout << std::endl << "Fizik Objesi: " << id << " olusturuldu.";
	}

	/// <summary>
	/// Objeyi çizer
	/// </summary>
	void draw() {
		object->draw();
	}

	/// <summary>
	/// 2 Çarpýþmada 2. objenin 1. objenin neresinde olduðunu döndürür
	/// </summary>
	/// <param name="urTrigger">Trigger 1</param>
	/// <param name="objectTrigger">Trigger 2</param>
	/// <returns>nerede olduðunu döndürür</returns>
	Dir where(Trigger urTrigger, Trigger objectTrigger) {
		if (urTrigger.posX > objectTrigger.posX) return RIGHT;
		else if (urTrigger.posX + urTrigger.width < objectTrigger.posX + objectTrigger.width) return LEFT;
		else if (urTrigger.posY > objectTrigger.posY) return UP;
		else if (urTrigger.posY + urTrigger.height < objectTrigger.posY + objectTrigger.height) return DOWN;
		else return NONE;
	}

	/// <summary>
	/// Obje bir objeyle çarpýþýyormu
	/// </summary>
	/// <param name="oObject">Kontrol edilecek objenin Trigger deðiþkeni</param>
	/// <returns>Çarpýþýyomu çarpýþmýyomu</returns>
	bool isColliding(Trigger oObject) {
		oObject.id = "Dýþ Obje";
		trigger.id = "Burka";
		bool test = triggerClass.isColliding(oObject, trigger);
		return test;

	}

	/// <summary>
	/// Çoklu obje kontrolünden herhangi bir objeyle çarpýþýyor mu
	/// </summary>
	/// <param name="oObject">Obje triggerý</param>
	/// <param name="id">Çoklu obje kontrolünden kontrol edilecek olan þeyin idsi</param>
	/// <returns>Çarpýþtý?</returns>
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
	/// Çarpýþan Triggerlarýn idlerini döndürür
	/// </summary>
	/// <returns>superStr idler</returns>
	superStr getCollidings() {
		superStr res = collided;
		startSS(&collided);
		return res;
	}

	/// <summary>
	/// Fizik aktifmi deðilmi
	/// </summary>
	/// <param name="isActive">akitfmi?</param>
	void setPhysics(bool isActive) {
		physicsActive = isActive;
	}

	/// <summary>
	/// Genel id kontrolüyle çarpýþma.
	/// Herhangi bir çimenle çarpýþtýmý?
	/// Herhangi bir topla çarpýþtýmý?
	/// </summary>
	/// <param name="willControl">Kontrol edilecek Triggers id'si</param>
	/// <returns>Çarpýþýyomu?</returns>
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
	/// Güvenli bir þekilde x pozisyonunda haraket iþlemi.
	/// Eðer ilerlerken parametredeki id ile bir obje çarpýþtýysa eklemeyi durdurur ve eklenmemiþ hale getirir.
	/// </summary>
	/// <param name="w">Ýlerlenecek birim sayýsý</param>
	/// <param name="perf">Performans sayýsý. Kaçar kaçar kontrol edeceði yani</param>
	/// <param name="willControl">Kontrol edilecek id</param>
	/// <returns>Ne taraftan çarptýðýna göre 2lik bool döndürür</returns>
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
					//Burda çarpýþtý ve çarpýþmamýþ hale geri döndü.
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
					//Burda çarpýþtý ve çarpýþmamýþ hale geri döndü.
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
	/// Güvenli bir þekilde y pozisyonunda haraket iþlemi.
	/// Eðer ilerlerken parametredeki id ile bir obje çarpýþtýysa eklemeyi durdurur ve eklenmemiþ hale getirir.
	/// </summary>
	/// <param name="w">Ýlerlenecek birim sayýsý</param>
	/// <param name="perf">Performans sayýsý. Kaçar kaçar kontrol edeceði yani</param>
	/// <param name="willControl">Kontrol edilecek id</param>
	/// <returns>Ne taraftan çarptýðýna göre 2lik bool döndürür</returns>
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
					//Burda çarpýþtý ve çarpýþmamýþ hale geri döndü.
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
					//Burda çarpýþtý ve çarpýþmamýþ hale geri döndü.
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
	/// <param name="isX">Eðer X sekecekse buraya true Y sekecekse false girilir.</param>
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
	/// Force x ve y sini 0'a eþitler
	/// </summary>
	void forceClear() {
		force.x = 0; force.y = 0;
	}

	/// <summary>
	/// Force'a x ve y deðerleri ekler
	/// </summary>
	/// <param name="x">Eklenecek X deðeri</param>
	/// <param name="y">Eklenecek Y deðeri</param>
	void forceAdd(float x, float y) {
		force.x += x;
		force.y += y;
	}

	/// <summary>
	/// Forcedaki deðerleri kullanarak haraket iþlemini yapar
	/// </summary>
	/// <param name="perf">Performans deðeri. Kaç birimde bir kontrol edileceði.</param>
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
	/// Eðer triggers deðiþkeni çok objeye eklenecekse Triggers deðiþkeni kod içinde tanýmlanýr, Triggerlar eklenir ve bu fonksiyon ile objeye atanýr.
	/// </summary>
	/// <param name="urTriggers">Triggers objen</param>
	void setPhyTriggers(Triggers urTriggers) {
		triggerControl = urTriggers;
	}

	/// <summary>
	/// gameObject'in adresini döndürür
	/// </summary>
	/// <returns>physicsObject.gameObject</returns>
	gameObject* getObject() {
		return object;
	}

	/// <summary>
	/// Objenin trigger deðiþkeninin adresini döndürür
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


//Bir dizide kaç tane UIELEMENT olduðunu belirtmemiz istenir.
//Bu þekilde kütüphaneyi yapan deðil kütüphaneyi kullanan dizilerin kaç tane olduðunu belirtmiþ olur.
#ifndef UIELEMENTS
#error UIELEMENTS'i define edip bir sayý belirtmen gerekiyor.
//Bu UIELEMENTS programýnda kaç tane UI element'i kullanacaðýný belirtir.
#else
/// <summary>
/// UI CLASS UI objelerini oluþturmaya çizmeye ve kontrolü saðlar
/// </summary>
class UI {
private:
	sf::Font font;
	sf::Text texts[UIELEMENTS];
	std::string id;
	sf::RenderWindow* window;
public:
	/// <summary>
	/// UI Sýnýfý oluþturucusu
	/// </summary>
	/// <param name="fontFilePath">Fontun dosya yolu</param>
	/// <param name="fontId">Font yüklenirken kontrol için komut satýrýnda gözükecek olan id</param>
	/// <param name="urWindow">Çizilecek olan pencerenin adresi</param>
	UI(sf::String fontFilePath, std::string fontId, sf::RenderWindow* urWindow) {
		font = setFont(fontFilePath, fontId);
		id = fontId;
		window = urWindow;
	}
	/// <summary>
	/// Dizideki herhangi bir objenin verilerini girmeye yarar. Bu yeni bir obje oluþturmada olabilir. Makismum UIELEMENTS kadar obje girilebilir.
	/// </summary>
	/// <param name="array">Kaçýncý obje</param>
	/// <param name="string">Yazý</param>
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
	/// <param name="array">Dizideki kaçýncý</param>
	/// <returns>Seçtiðimiz objenin adresini döndürür</returns>
	sf::Text* getText(int array) {
		return &texts[array];
	}

	/// <summary>
	/// UI Objelerini ekrana çizdirir.
	/// </summary>
	void draw() {
		for (int i = 0; i < UIELEMENTS; i++) {
			window->draw(texts[i]);
		}
	}
};
#endif

//Yukardakilerle benzer þeyler
#ifndef MULTIS
#error MultiDraw için MULTIlerin max kaç tane olmasýný istediðini giriniz. (define MULTIS)
#else
/// <summary>
/// Çoklu obje çizimleri için sýnýf
/// </summary>
class MultiDraw {
private:
	physicsObject* objects[MULTIS];
	int nextMulti = 0;
public:
	/// <summary>
	/// Çizilecek þeylere bir physicsObject atar
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
	/// Çoklu çizim yapýlacak objeleri ekranlarýna çizdirir
	/// </summary>
	void draw() {
		for (int i = 0; i < nextMulti; i++) {
			objects[i]->draw();
		}
	}

};

#endif

#endif