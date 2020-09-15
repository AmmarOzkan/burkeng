#pragma once

#ifndef BURENG
#define BURENG

/*
* 
* 
* GEREKLÝ #DEFINE
* 
* 
*/

#ifndef ANIMPERFRAME
#error #define ANIMPERFRAME [Kac frame'de bir animasyon degisecegi] tanýmýný yapmak zorundasýn
#endif

//Bir dizide kaç tane UIELEMENT olduðunu belirtmemiz istenir.
//Bu þekilde kütüphaneyi yapan deðil kütüphaneyi kullanan dizilerin kaç tane olduðunu belirtmiþ olur.
#ifndef UIELEMENTS
#error UIELEMENTS'i define edip bir sayý belirtmen gerekiyor.
//Bu UIELEMENTS programýnda kaç tane UI element'i kullanacaðýný belirtir.
#endif

//Yukardakilerle benzer þeyler
#ifndef MULTIS
#error MultiDraw için MULTIlerin max kaç tane olmasýný istediðini giriniz. (define MULTIS)
#endif

#ifndef SUPERSTR
#error SUPERSTR dizisinin kaç tane olduðu belirtilmeli #define SUPERSTR [dizisayisi]
#endif

#define TEXTURELOAD "Texture:" << urTexture->id << " yukleme durumu: " << urTexture->texture.loadFromFile(filePath)
#define FONTLOAD "Font " << id << " Yukleme Durumu: " << font.loadFromFile("res/fonts/batmfo__.ttf")
#define FONTERROR "Font " << id << " yuklenmesinde bir hata meydana geldi."
#define GAMEOBJECTTEXTURELOAD "Texture:" << texturee.id << " yukleme durumu: " << texturee.texture.loadFromFile(filePath)
#define ADDINGTEXTURE "Texture " << urTexturee.id << " ekleniyor."
#define CREATINGPHYOBJ "Fizik Objesi: " << id << " olusturuldu."
#define CREATINGBUTTON "Buton:" << id << " olusturuldu."
#define CREATINGANIM "Animasyon:" << id << "olusturuldu."

#ifndef TEXTURELOAD
#error #define TEXTURELOAD komut penceresine yazýlacak olan yazýyý belirtir. (Texture yükleme) Kullanabileceklerin:
#error urTexture->id = texture idsi; urTexture->texture.loadFromFile(filePath) = yükleme durumu;
#endif
#ifndef FONTLOAD
#error #define FONTLOAD komut penceresinde yazýlacak olan yazýyý belirtir. (Font yükleme) Kullanabileceklerin:
#error id = font idsi; font.loadFromFile("res/fonts/batmfo__.ttf") = yüklenme durumu
#endif
#ifndef FONTERROR
#error #define FONTERROR komut penceresinde yazýlacak olan yazýyý belirtir. (Font hatasý) Kullanabileceklerin:
#error id = font idsi
#endif
#ifndef GAMEOBJECTTEXTURELOAD
#error #define GAMEOBJECTTEXTURELOAD komut penceresinde yazýlacak olan yazýyý belirtir. (Game object için texture yükleme) Kullanabileceklerin:
#error texturee->id = texture idsi; texturee.texture.loadFromFile(filePath) = yükleme durumu;
#endif
#ifndef ADDINGTEXTURE
#error #define ADDINGTEXTURE komut penceresinde yazýlacak olan yazýyý belirtir. (Objeye Texture ekleme) Kullanabileceklerin:
#error urTexturee.id = texture idsi
#endif
#ifndef CREATINGPHYOBJ
#error #define FONTERROR komut penceresinde yazýlacak olan yazýyý belirtir. (Fizik Objesi Yaratma) Kullanabileceklerin:
#error id = fizik objesi idsi
#endif
#ifndef CREATINGBUTTON
#error #define FONTERROR komut penceresinde yazýlacak olan yazýyý belirtir. (Font hatasi) Kullanabileceklerin:
#error id = buton idsi
#endif
#ifndef CREATINGANIM
#error #define FONTERROR komut penceresinde yazýlacak olan yazýyý belirtir. (Animasyon oluþturma) Kullanabileceklerin:
#error id = animasyon idsi
#endif

/*
*
* 
* DAHÝL EDÝLMESÝ GEREKENLER
* 
*
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>


/*
*
*
* DEÐÝÞKENLER
* 
*
*/

/// <summary>
/// 2 Bool veri tutan deðiþken
/// </summary>
struct tValBool {
	bool b1, b2;
};


///Dir
enum Dir { LEFT, RIGHT, UP, DOWN, NONE };


/// <summary>
/// Texturelar için özel deðiþken
/// Texturee deðiþkeni texturelarda dikey yatay pixel sayýsý gibi birçok veriyi tutar.
/// </summary>
struct Texturee {
	sf::Texture texture;
	int height, width;
	std::string id;
};

/// <summary>
/// 2 tane float tutan deðiþken
/// </summary>
struct f2 {
	float f1, f2;
};

/// <summary>
/// X ve Y verisi tutan Vector2
/// </summary>
struct valueXY {
	float x, y;
};

/// <summary>
/// Fizik verilerini tutan deðiþken (Þimdilik tek þey var ama daha çok þey ekleyecem)
/// </summary>
struct PhyVal {
	float gravity;
};

/// <summary>
/// Çarpýþma kontrolcüsü verilerini tutan deðiþken
/// </summary>
struct Trigger {
	float posX, posY, height, width;
	std::string id;
};

/// <summary>
/// Objelerin çarpýþmalarýndan sonra döndürülen deðer.
/// </summary>
struct collideRes {
	std::string id;
	bool res;
};

/// <summary>
/// Objelerin çarpýþmalarýndan sonra döndürülen deðer.
/// </summary>
struct collideRes2 {
	std::string id;
	bool res1, res2;
};


/// <summary>
/// Ýçinde bir çok string deðeri barýndýran deðiþken
/// </summary>
struct superStr {
	std::string str[SUPERSTR];
	int nextString = 0;
};

/*
*
*
* FONKSIYONLAR
*
*
*/

/// <summary>
/// Texturee deðiþkeni baþlatýcýsý
/// </summary>
/// <param name="urTexture">Texturee deðiþkeninin adresi</param>
/// <param name="width">Dosyanýn yatay pixel sayýsý</param>
/// <param name="height">Dosyanýn dikey pixel sayýsý</param>
/// <param name="id">Texture idsi</param>
/// <param name="filePath">Dosya yolu</param>
void setTexturee(Texturee* urTexture, int width, int height, std::string id, sf::String filePath) {
	urTexture->width = width;
	urTexture->height = height;
	urTexture->id = id;
	std::cout << std::endl << TEXTURELOAD;
}



/// <summary>
/// superStr deðiþkeni için bir baþlatýcý
/// </summary>
/// <param name="str">superStr deðiþkeninin adresi</param>
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

void clearSTR(superStr* str) {
	for (int i = 0; i < SUPERSTR; i++) {
		str->str[i] = "";
	}
}

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
	std::cout << std::endl << FONTLOAD;
	if (!font.loadFromFile("res/fonts/batmfo__.ttf")) {
		std::cout << std::endl << FONTERROR;

	}
	return font;
}

/*
*
*
* SINIFLAR
*
*
*/

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
	gameObject(sf::String filePath, float x, float y, float scaleX, float scaleY, bool math, int textureHeight, int textureWidth, std::string id, sf::RenderWindow* yourWindow, valueXY* urCamera) {
		scaleSetted = true;
		posSetted = true;
		texturee.height = textureHeight; texturee.width = textureWidth; texturee.id = id;
		std::cout << std::endl << GAMEOBJECTTEXTURELOAD;
		pos.x = x; pos.y = y;
		if (!math) {
			scale.x = scaleX;
			scale.y = scaleY;
		}
		else {
			scale.x = scaleX / texturee.width;
			scale.y = scaleY / texturee.height;
		}
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
	/// <param name="math">Eðer true ise scaleX ve scaleY geniþletme katsayýsý deðil hedef uzunluk ve yükseklik olur</param>
	/// <param name="yourWindow">Çizilecek olan ekran deðiþkeninin adresi</param>
	gameObject(Texturee urTexturee, float x, float y, float scaleX, float scaleY, bool math, sf::RenderWindow* yourWindow, valueXY* urCamera) {
		scaleSetted = true;
		posSetted = true;
		std::cout << std::endl << ADDINGTEXTURE;
		texturee = urTexturee;
		pos.x = x; pos.y = y;
		if (!math) {
			scale.x = scaleX;
			scale.y = scaleY;
		}
		else {
			scale.x = scaleX / texturee.width;
			scale.y = scaleY / texturee.height;
		}
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

	/// <summary>
	/// Belirli yükseklik ve geniþliði sabit tutarak veya tutmayarak texture deðiþtirir.
	/// </summary>
	/// <param name="txr">Texturee</param>
	/// <param name="math">sabit tutammý?</param>
	void setTexturee(Texturee txr,bool math) {
		texturee = txr;
		if (!math) {
			texturee = txr;
		}
		else {
			float shouldX = scale.x * texturee.width;
			float shouldY = scale.y * texturee.height;
			scale.x = shouldX / txr.width;
			scale.y = shouldY / txr.height;
		}
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
	void setTrigger(Trigger* trigger, float x, float y, float height, float width, float scaleX, float scaleY) {
		trigger->posX = x; trigger->posY = y;
		trigger->height = height * scaleX;
		trigger->width = width * scaleY;
	}
}triggerClass;


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
		std::cout << std::endl << CREATINGPHYOBJ;
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
		std::cout << std::endl << CREATINGPHYOBJ;
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

	void setColliding() {
		for (int i = 0; i < triggerControl.nextTrigger; i++) {
			if (triggerClass.isColliding(triggerControl.trigger[i][0], trigger)) {
				if (!isThereAnySTR(collided, triggerControl.id[i][0])) {
					addString(&collided, triggerControl.id[i][0]);
				}
			}
		}
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
		clearSTR(&collided);
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

	/// <summary>
	/// Force ondan bundan yüksekmi
	/// </summary>
	/// <param name="x">Yüksek olmamasý gereken x ve düþük olmamasý gereken -x deðerindeki X</param>
	/// <param name="y">Yüksek olmamasý gereken y ve düþük olmamasý gereken -y deðerindeki Y</param>
	void forceControl(float x, float y) {
		if (force.x > x) {
			force.x = x;
		}
		else if (force.x < -x) {
			force.x = -x;
		}if (force.y > y) {
			force.y = y;
		}
		else if (force.y < -y) {
			force.y = -y;
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

/// <summary>
/// Animasyon deðiþkeni.
/// </summary>
class Animation {
private:
	Texturee animTextures[ANIMPERFRAME];
	int anim = 0 ,nextAnim = 0, addedAnim = 0;
	std::string animId;
public:
	/// <summary>
	/// Animasyon objesi oluþturma
	/// </summary>
	/// <param name="urAnimationTextures">Animasyon texturelarýnýn dizi halindeki þeysi</param>
	/// <param name="id">Komut penceresinde yazýlacak olan id. </param>
	Animation(Texturee urAnimationTextures[ANIMPERFRAME], std::string id)
	{
		for (int i = 0; i < ANIMPERFRAME; i++) {
			animTextures[i] = urAnimationTextures[i];
		}
		std::cout << std::endl << CREATINGANIM;
		animId = id;
	}
	Animation(std::string id) {
		std::cout << std::endl << CREATINGANIM;
		animId = id;
	}

	/// <summary>
	/// Texturee'yi ekler. Eðer kare sayýsýný geçiyorsa uyarý verir.
	/// </summary>
	/// <param name="texture">Eklenecek texture</param>
	void addAnimTexture(Texturee texture) {
		if (nextAnim >= ANIMPERFRAME) {
			std::cout << std::endl << "DAHA FAZLA ANIMASYON TEXTURE EKLENEMIYOR:" << animId;
		}
		else {
			animTextures[nextAnim] = texture;
			std::cout << std::endl << "ANIMASYON EKLENDI:" << animId << ":" << texture.id;
			nextAnim++;
		}
	}

	/// <summary>
	/// Animasyon texture'ýný döndürür
	/// </summary>
	/// <returns>animasyon texture</returns>
	Texturee animate() {
		anim++;
		if (anim >= ANIMPERFRAME) {
			anim = 0;
		}
		return animTextures[ anim / (ANIMPERFRAME / (nextAnim)) ];
	}

	void reset() {
		anim = 0;
	}
};


/// <summary>
/// Buton Classý
/// </summary>
class Button {
private:
	Texturee txr;
	valueXY pos;
	valueXY scale;
	sf::RenderWindow *window;
	Trigger t;
	bool click = false;
public:
	/// <summary>
	/// Baþlangýç
	/// </summary>
	/// <param name="texture">Texture deðiþkeni</param>
	/// <param name="id">Button id</param>
	/// <param name="x">X pozisyonu</param>
	/// <param name="y">Y pozisyonu</param>
	/// <param name="urWindow">Pencerenin adresi</param>
	Button(Texturee texture,std::string id, float x, float y, float width, float height,sf::RenderWindow *urWindow)
		: txr(texture), window(urWindow)
	{
		pos.x = x; pos.y = y;
		scale.x = width / txr.width;
		scale.y = height / txr.height;
		triggerClass.setTrigger(&t, pos.x, pos.y, txr.height*scale.y, txr.width*scale.x, 1, 1);
	}

	/// <summary>
	/// Buton objesini ekrana çizdirir
	/// </summary>
	void draw() {
		sf::Sprite sprite;
		sprite.setTexture(txr.texture);

		sprite.setScale(scale.x, scale.y);
		sprite.setPosition(pos.x, pos.y);

		window->draw(sprite);
	}

	/// <summary>
	/// Butona basýlýp basýlmadýðýný kontrol etmeyi saðlar
	/// </summary>
	/// <param name="event">Pencere Eventi</param>
	bool control(sf::Event event) {
		Trigger mouseTrigger;
		mouseTrigger.posX = event.mouseButton.x; mouseTrigger.posY = event.mouseButton.y; mouseTrigger.height = 0; mouseTrigger.width = 0; mouseTrigger.id = "MOUSE TRIGGER";
		triggerClass.setTrigger(&t, pos.x, pos.y, txr.height * scale.y, txr.width * scale.x, 1, 1);
		bool fix = event.mouseButton.button == sf::Mouse::Left && triggerClass.isColliding(t, mouseTrigger);
		bool b = event.type == sf::Event::MouseButtonPressed && fix;
		bool c = event.type == sf::Event::MouseButtonReleased;
		if (b) {
			click = true;
		}
		else if (c) {
			click = false;
		}
		return click;
	}

	valueXY * getPos(){return &pos;}

	/// <summary>
	/// Butona basýlýp basýlmadýðýný döndürür
	/// </summary>
	/// <returns>basýldý?</returns>
	bool getClick() {
		return click;
	}
};


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
	void setText(int array, sf::String string, int posX, int posY) {
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

#define BUTTONARRAY 10

/// <summary>
/// Button arraylarýný tutacak olan deðiþken
/// </summary>
struct Buttons {
	Button* buttons[BUTTONARRAY];
	int nextButton = 0;
};

/// <summary>
/// Bu deðiþkene eklenecek butonu otomatik olarak ayarlayacak olan fonksiyon
/// </summary>
/// <param name="urButtons">Butonun adresi</param>
/// <param name="buttonTexture">Texture</param>
/// <param name="id">string id</param>
/// <param name="posX">pozisyon x</param>
/// <param name="posY">pozisyon y</param>
/// <param name="scaleX">istenen geniþlik</param>
/// <param name="scaleY">istenen yükseklik</param>
/// <param name="urWindow">pencerenin adresi</param>
void addButtons(Buttons* urButtons, Texturee buttonTexture, std::string id, float posX, float posY, float scaleX, float scaleY, sf::RenderWindow* urWindow) {
	if (urButtons->nextButton >= BUTTONARRAY) {
		std::cout << std::endl << "MAX_BUTTON_ARRAY";
	}
	else {
		urButtons->buttons[urButtons->nextButton] = new Button(buttonTexture, id, posX, posY, scaleX, scaleY, urWindow);
		urButtons->nextButton++;
	}
}



/// <summary>
/// Panel Class
/// </summary>
class Panel {
private:
	valueXY pos, scale, moveScale;

	Texturee texture;
	Buttons buttons;
	int nextText;
	bool isActive,moveSetted;
	bool isMoving;
	sf::RenderWindow* window;
	sf::Font defaultFont;
	UI *ui;
	valueXY mousePos;

public:

	/// <summary>
	/// Panel oluþturucu fonksiyonu
	/// </summary>
	/// <param name="position">valueXY deðerinden pozisyon</param>
	/// <param name="widthHeight">valueXY deðerinden geniþlik ve yükseklik</param>
	/// <param name="urTexture">texture</param>
	/// <param name="isActiveController">baþlangýçta panel açýk?</param>
	/// <param name="urUI">Panelde kullanýlacak UI objesi</param>
	/// <param name="urWindow"></param>
	Panel(valueXY position, valueXY widthHeight, Texturee urTexture, bool isActiveController, UI *urUI,sf::RenderWindow* urWindow)
		: texture(urTexture), window(urWindow), ui(urUI)
	{
		buttons.nextButton = 0;
		nextText = 0;
		isActive = isActiveController;
		scale.x = widthHeight.x / texture.width;
		scale.y = widthHeight.y / texture.height;
		pos = position;
		moveSetted = false; isMoving = false;
	}

	/// <summary>
	/// Haraket sisteminin triggerýný ayarlamak için gereken fonksiyon
	/// </summary>
	/// <param name="scaleX">X geniþliði</param>
	/// <param name="scaleY">Y geniþliði</param>
	void setMove(float scaleX, float scaleY) {
		moveScale.x = scaleX; moveScale.y = scaleY;
		moveSetted = true;
	}

	/// <summary>
	/// Panel haraket sisteminin haraketini kontrol eder.
	/// </summary>
	/// <param name="event">Pencere eventi</param>
	void move(sf::Event event) {
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && moveSetted && isActive) {
			Trigger panelTrigger;
			panelTrigger.posX = pos.x; panelTrigger.posY = pos.y; panelTrigger.height = moveScale.y; panelTrigger.width = moveScale.x; panelTrigger.id = "panelTrigger";
			Trigger mouseTrigger;
			mouseTrigger.posX = event.mouseButton.x; mouseTrigger.posY = event.mouseButton.y; mouseTrigger.height = 0; mouseTrigger.width = 0;
			if (triggerClass.isColliding(panelTrigger, mouseTrigger)) {
				isMoving = true;
				mousePos.x = event.mouseButton.x; mousePos.y = event.mouseButton.y;
			}
		}if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && moveSetted && isActive) {
			Trigger panelTrigger;
			panelTrigger.posX = pos.x; panelTrigger.posY = pos.y; panelTrigger.height = moveScale.y; panelTrigger.width = moveScale.x; panelTrigger.id = "panelTrigger";
			Trigger mouseTrigger;
			mouseTrigger.posX = event.mouseButton.x; mouseTrigger.posY = event.mouseButton.y; mouseTrigger.height = 0; mouseTrigger.width = 0;
			if (isMoving) {
				isMoving = false;
				mousePos.x = event.mouseButton.x; mousePos.y = event.mouseButton.y;
			}
		}if (event.type == sf::Event::MouseMoved && isMoving == true && isActive) {
			pos.x = event.mouseMove.x - mousePos.x;
			if (mousePos.y < 0) {
				pos.y = event.mouseMove.y + mousePos.y;
			}else{
				pos.y = event.mouseMove.y - mousePos.y;
			}
		}
	}

	/// <summary>
	/// Buton ekleme fonksiyonu
	/// </summary>
	/// <param name="buttonTexture">texture</param>
	/// <param name="id">id</param>
	/// <param name="posX">panel üstünde pozisyon x. Eðer panel 100x pozisyonunda buton 20x pozisyonundaysa buton ekranda 120x pozisyonundadýr</param>
	/// <param name="posY">ayný þekilde yukarýda</param>
	/// <param name="scaleX">geniþlik</param>
	/// <param name="scaleY">yükseklik</param>
	void addButton(Texturee buttonTexture, std::string id, float posX, float posY, float scaleX, float scaleY) {
		addButtons(&buttons, buttonTexture, id, posX, posY, scaleX, scaleY, window);
	}

	/// <summary>
	/// text ekle
	/// </summary>
	/// <param name="string">yazý</param>
	/// <param name="array">dizide kaçýncý sýrada olsun?</param>
	/// <param name="posX">pozisyon x</param>
	/// <param name="posY">pozisyon y</param>
	/// <returns></returns>
	bool addText(sf::String string,int array, float posX, float posY) {
		if (array >= UIELEMENTS) {
			std::cout << std::endl << "MAX_TEXT_ARRAY";
			return false;
		}
		else {
			ui->setText(array, string, posX+pos.x, posY+pos.y);
			return true;
		}
	}

	Button getButton(int array) {
		Button button = buttons.buttons[array][0];
		button.getPos()->x += pos.x;
		button.getPos()->y += pos.y;
		return button;
	}

	/// <summary>
	/// Týklanan butonun idsini döndürür
	/// </summary>
	/// <param name="event">Event</param>
	/// <returns>butonun idsi</returns>
	int getClickId(sf::Event event) {
		if (isActive) {
			for (int i = 0; i < buttons.nextButton; i++) {
				Button button = getButton(i);
				if (button.control(event)) {
					return i;
				}
			}
		}
		return -1;
	}

	/// <summary>
	/// Aktifliðini deðiþtir
	/// </summary>
	/// <param name="a">aktif?</param>
	void setActivite(bool a) {
		isActive = a;
	}

	/// <summary>
	/// Panel'i çizdirir
	/// </summary>
	void draw() {
		if (isActive) {
			sf::Sprite sprite;
			sprite.setTexture(texture.texture);
			sprite.setScale(scale.x, scale.y);
			sprite.setPosition(pos.x, pos.y);
			window->draw(sprite);
			for (int i = 0; i < buttons.nextButton; i++) {
				getButton(i).draw();
			}
			for (int i = 0; i < UIELEMENTS; i++) {
				sf::Text text;
				text.setFont(ui->getText(i)[0].getFont()[0]);
				text.setString(ui->getText(i)[0].getString());
				text.setPosition(ui->getText(i)->getPosition().x + pos.x, ui->getText(i)->getPosition().y + pos.y);
				window->draw(text);
			}
		}
	}
};

/// <summary>
/// Çoklu obje çizimleri için sýnýf
/// </summary>
class MultiDraw {
private:
	physicsObject* objects[MULTIS];
	gameObject* gmObjects[MULTIS];
	int nextMulti = 0;
	int nextGmObject = 0;
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
	
	void addObject(gameObject* object) {
		if (nextGmObject == MULTIS) {
			std::cout << std::endl << "Maksimum MULTIS";
		}
		else {
			gmObjects[nextGmObject] = object;
			nextGmObject++;
		}
	}

	/// <summary>
	/// Çoklu çizim yapýlacak objeleri ekranlarýna çizdirir
	/// </summary>
	void draw() {
		for (int i = 0; i < nextMulti; i++) {
			objects[i]->draw();
		}
		for (int i = 0; i < nextGmObject; i++) {
			gmObjects[i]->draw();
		}
	}

};

#endif