#pragma once
#ifndef BURENG_MAIN
#define BURENG_MAIN

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
	std::string objectId;
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
		bool val = texturee.texture.loadFromFile(filePath);
#ifndef NODEBUG
		std::cout << std::endl << GAMEOBJECTTEXTURELOAD;
#endif
		pos.x = x; pos.y = y;
		scale.x = scaleX / (texturee.width * math) + (1 * !math);
		scale.y = scaleY / (texturee.height * math) + (1 * !math);
		window = yourWindow;
		camera = urCamera;

		objectId = id;
	}

	std::string getId() {
		return objectId;
	}

	void setHW(float width, float height) {
		scale.x = width / texturee.width;
		scale.y = height / texturee.height;
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
#ifndef NODEBUG
		std::cout << std::endl << ADDINGTEXTURE;
#endif
		texturee = urTexturee;
		pos.x = x; pos.y = y;
		scale.x = scaleX / (texturee.width * math) + (1 * !math);
		scale.y = scaleY / (texturee.height * math) + (1 * !math);
		window = yourWindow;
		camera = urCamera;
	}

	/// <summary>
	/// Objeyi ekrana çizer
	/// </summary>
	void draw() {
		sf::Sprite sprite(texturee.texture);
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
	void setTexturee(Texturee txr, bool math) {
		if (!math) {
			texturee = txr;
		}
		else {
			float shouldX = scale.x * texturee.width;
			float shouldY = scale.y * texturee.height;
			scale.x = shouldX / txr.width;
			scale.y = shouldY / txr.height;
			texturee = txr;
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
	}valueXY* getCamera() {
		return camera;
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
	void setTrigger(Trigger* trigger, gameObject* urObject, std::string publicId) {
		trigger->posX = urObject->position()->x;
		trigger->posY = urObject->position()->y;
		trigger->height = urObject->getTexturee()->height * urObject->getScale()->y;
		trigger->width = urObject->getTexturee()->width * urObject->getScale()->x;
		trigger->id = urObject->getId();
		trigger->publicId = publicId;
	}
	void setTrigger(Trigger* trigger, float x, float y, float height, float width, float scaleX, float scaleY, std::string id, std::string publicId) {
		trigger->posX = x; trigger->posY = y;
		trigger->height = height * scaleX;
		trigger->width = width * scaleY;
		trigger->id = id;
		trigger->publicId = publicId;
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
void addNewTrigger(Triggers* urTriggers, Trigger* urTrigger) {

#ifndef NODEBUG
	if (urTriggers->nextTrigger == TRIGGERCONTROL) {
		std::cout << std::endl << "maksimum triggers sayisina ersildi";
	}
	else {
		urTriggers->trigger[urTriggers->nextTrigger] = urTrigger;
		urTriggers->nextTrigger++;
	}
#else
	if (urTriggers->nextTrigger != TRIGGERCONTROL) {
		urTriggers->trigger[urTriggers->nextTrigger] = urTrigger;
		urTriggers->nextTrigger++;
	}
#endif
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
	void addControl(Trigger* urTrigger) {
		addNewTrigger(&triggerControl, urTrigger);
	}

	/// <summary>
	/// Kendi trigger'ýný gameObjecte göre ayarlar.
	/// </summary>
	void setTrigger(std::string publicId) {
		triggerClass.setTrigger(&trigger, object, publicId);
	}
	/// <summary>
	/// Physics Object oluþturulurken kullandýðým hep olan bir start fonksiyonu. Kullanýcýnýn kullanmasýna gerek yok.
	/// </summary>
	void fixStart(std::string publicId) {
		setTriggers(&triggerControl);
		setTrigger(publicId);
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
	physicsObject(gameObject* urObject, bool physicsIsActive, float gravity, std::string id, std::string publicId)
		: object(urObject), physicsActive(physicsIsActive)
	{
		fixStart(publicId);
		setPhyVal(&val, gravity);
#ifndef NODEBUG
		std::cout << std::endl << CREATINGPHYOBJ;
#endif
	}
	/// <summary>
	/// physicsObject oluþturucusu
	/// </summary>
	/// <param name="urObject">gameObjectin adresi</param>
	/// <param name="physicsIsActive">fiziði olucakmý olmayacakmý (sonradan deðiþtirilebilir)</param>
	/// <param name="urVal">Fizik deðiþkeni varsa yerçekimi verisi vs girmek yerine bu girilir</param>
	/// <param name="id">oluþturulurken komut satýrýnda kontorl için yazýcak olan id</param>
	physicsObject(gameObject* urObject, bool physicsIsActive, PhyVal urVal, std::string id, std::string publicId)
		: object(urObject), val(urVal), physicsActive(physicsIsActive)
	{
		fixStart(publicId);
#ifndef NODEBUG
		std::cout << std::endl << CREATINGPHYOBJ;
#endif
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
				if (!isThereAnySTR(collided, triggerControl.trigger[i][0].publicId)) {
					addString(&collided, triggerControl.trigger[i][0].publicId);
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
			if (triggerClass.isColliding(triggerControl.trigger[i][0], oObject) && ((triggerControl.trigger[i][0].publicId == willControl) != (willControl == ""))) {
				res.res = true;
				res.id = triggerControl.trigger[i][0].id;
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

	PhyVal* getPhysics() {
		return &val;
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
			//KONTROL EDILECEK
			control = (isColliding(triggerControl.trigger[i][0]) && triggerControl.trigger[i][0].publicId == willControl || willControl == "") || control;
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
				triggerClass.setTrigger(&preTrigger, object, "");
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
				triggerClass.setTrigger(&preTrigger, object, "");
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
				triggerClass.setTrigger(&preTrigger, object, "");
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
				triggerClass.setTrigger(&preTrigger, object, "");
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
		force.x /= (1.5 * isX) + (1 * !isX);
		force.x *= (-1 * isX) + (1 * !isX);
		force.y /= (1.5 * !isX) + (1 * isX);
		force.y *= (-1 * !isX) + (1 * isX);
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

#endif