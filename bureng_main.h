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
	/// Oyun objesinin pozisyonunu b�y�kl���n� vs ayarlar. Hoj bir s�n�ft�r.
	/// </summary>
	/// <param name="urTexturee">Texturee de�i�keni</param>
	/// <param name="x">X pozisyonu</param>
	/// <param name="y">Y pozisyonu</param>
	/// <param name="scaleX">X geni�leme katsay�s�</param>
	/// <param name="scaleY">Y geni�leme katsay�s�</param>
	/// <param name="math">E�er true ise scaleX ve scaleY geni�letme katsay�s� de�il hedef uzunluk ve y�kseklik olur</param>
	/// <param name="yourWindow">�izilecek olan ekran de�i�keninin adresi</param>
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
	/// Objeyi ekrana �izer
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
	/// Belirli y�kseklik ve geni�li�i sabit tutarak veya tutmayarak texture de�i�tirir.
	/// </summary>
	/// <param name="txr">Texturee</param>
	/// <param name="math">sabit tutamm�?</param>
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
	void addControl(Trigger* urTrigger) {
		addNewTrigger(&triggerControl, urTrigger);
	}

	/// <summary>
	/// Kendi trigger'�n� gameObjecte g�re ayarlar.
	/// </summary>
	void setTrigger(std::string publicId) {
		triggerClass.setTrigger(&trigger, object, publicId);
	}
	/// <summary>
	/// Physics Object olu�turulurken kulland���m hep olan bir start fonksiyonu. Kullan�c�n�n kullanmas�na gerek yok.
	/// </summary>
	void fixStart(std::string publicId) {
		setTriggers(&triggerControl);
		setTrigger(publicId);
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
	/// physicsObject olu�turucusu
	/// </summary>
	/// <param name="urObject">gameObjectin adresi</param>
	/// <param name="physicsIsActive">fizi�i olucakm� olmayacakm� (sonradan de�i�tirilebilir)</param>
	/// <param name="urVal">Fizik de�i�keni varsa yer�ekimi verisi vs girmek yerine bu girilir</param>
	/// <param name="id">olu�turulurken komut sat�r�nda kontorl i�in yaz�cak olan id</param>
	physicsObject(gameObject* urObject, bool physicsIsActive, PhyVal urVal, std::string id, std::string publicId)
		: object(urObject), val(urVal), physicsActive(physicsIsActive)
	{
		fixStart(publicId);
#ifndef NODEBUG
		std::cout << std::endl << CREATINGPHYOBJ;
#endif
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
	/// �oklu obje kontrol�nden herhangi bir objeyle �arp���yor mu
	/// </summary>
	/// <param name="oObject">Obje trigger�</param>
	/// <param name="id">�oklu obje kontrol�nden kontrol edilecek olan �eyin idsi</param>
	/// <returns>�arp��t�?</returns>
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
	/// �arp��an Triggerlar�n idlerini d�nd�r�r
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
			//KONTROL EDILECEK
			control = (isColliding(triggerControl.trigger[i][0]) && triggerControl.trigger[i][0].publicId == willControl || willControl == "") || control;
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
				triggerClass.setTrigger(&preTrigger, object, "");
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
				triggerClass.setTrigger(&preTrigger, object, "");
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
				triggerClass.setTrigger(&preTrigger, object, "");
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
				triggerClass.setTrigger(&preTrigger, object, "");
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
		force.x /= (1.5 * isX) + (1 * !isX);
		force.x *= (-1 * isX) + (1 * !isX);
		force.y /= (1.5 * !isX) + (1 * isX);
		force.y *= (-1 * !isX) + (1 * isX);
	}

	/// <summary>
	/// Force ondan bundan y�ksekmi
	/// </summary>
	/// <param name="x">Y�ksek olmamas� gereken x ve d���k olmamas� gereken -x de�erindeki X</param>
	/// <param name="y">Y�ksek olmamas� gereken y ve d���k olmamas� gereken -y de�erindeki Y</param>
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

#endif