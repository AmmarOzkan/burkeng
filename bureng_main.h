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
	Vector2 pos, scale, * camera;
	float rotation;
	sf::Texture texture;
	Texturee texturee;
	sf::RenderWindow* window;
	bool scaleSetted, posSetted;
	std::string objectId;
	Vector2 spriteHW;
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
	gameObject(sf::String filePath, float x, float y, float scaleX, float scaleY, int textureHeight, int textureWidth, std::string id, sf::RenderWindow* yourWindow, Vector2* urCamera) {
		scaleSetted = true;
		posSetted = true;
		texturee.height = textureHeight; texturee.width = textureWidth; texturee.id = id;
		bool val = texturee.texture.loadFromFile(filePath);
#ifndef NODEBUG
		std::cout << std::endl << GAMEOBJECTTEXTURELOAD;
#endif
		pos.x = x; pos.y = y;
		scale.x = scaleX / texturee.width;
		scale.y = scaleY / texturee.height;
		window = yourWindow;
		camera = urCamera;

		objectId = id;
		spriteHW.x = spriteHW.y = 1;
		rotation = 0;
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
	gameObject(Texturee urTexturee, float x, float y, float scaleX, float scaleY, sf::RenderWindow* yourWindow, Vector2* urCamera) {
		scaleSetted = true;
		posSetted = true;
#ifndef NODEBUG
		std::cout << std::endl << ADDINGTEXTURE;
#endif
		texturee = urTexturee;
		pos.x = x; pos.y = y;
		scale.x = scaleX / texturee.width;
		scale.y = scaleY / texturee.height;
		window = yourWindow;
		camera = urCamera;
		rotation = 0;
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
		sprite.setOrigin(sf::Vector2f(texturee.width/2, texturee.height/2));
		sprite.setRotation(rotation);
		window->draw(sprite);
	}

	/// <summary>
	/// Belirli yükseklik ve geniþliði sabit tutarak veya tutmayarak texture deðiþtirir.
	/// </summary>
	/// <param name="txr">Texturee</param>
	/// <param name="math">sabit tutammý?</param>
	void setTexturee(Texturee txr) {
		float shouldX = scale.x * texturee.width;
		float shouldY = scale.y * texturee.height;
		scale.x = shouldX / txr.width;
		scale.y = shouldY / txr.height;
		texturee = txr;
	}
	void setRotation(float nRotation) {
		rotation = nRotation;
	}
	void setPosition(Vector2 Position) {
		pos = Position;
	}

	void addPos(Vector2 v) { pos.x += v.x; pos.y += v.y; }

	/// <summary>
	/// Pozisyonu ayarlar
	/// </summary>
	/// <param name="x">Pozisyon X</param>
	/// <param name="y">Pozisyon Y</param>
	Vector2* position() {
		return &pos;
	}Vector2* getScale() {
		return &scale;
	}Texturee* getTexturee() {
		return &texturee;
	}Vector2* getCamera() {
		return camera;
	}float* getRotation() { return &rotation; }
};

//FOR PHYSICS


#endif