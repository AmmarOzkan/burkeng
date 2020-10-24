#pragma once
#include "bureng_variables.h"
#include "bureng_functions.h"
#include "bureng_triggers.h"

#ifndef BURENG_EXTENSIONS
#define BURENG_EXTENSIONS
/// <summary>
/// Animasyon deðiþkeni.
/// </summary>
class Animation {
private:
	Texturee animTextures[ANIMPERFRAME];
	int anim = 0, nextAnim = 0, addedAnim = 0;
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
#ifndef NODEBUG
		std::cout << std::endl << CREATINGANIM;
#endif
		animId = id;
	}
	Animation(std::string id) {
#ifndef NODEBUG
		std::cout << std::endl << CREATINGANIM;
#endif
		animId = id;
	}

	/// <summary>
	/// Texturee'yi ekler. Eðer kare sayýsýný geçiyorsa uyarý verir.
	/// </summary>
	/// <param name="texture">Eklenecek texture</param>
	void addAnimTexture(Texturee texture) {
		if (nextAnim >= ANIMPERFRAME) {
#ifndef NODEBUG
			std::cout << std::endl << "DAHA FAZLA ANIMASYON TEXTURE EKLENEMIYOR:" << animId;
#endif
		}
		else {
			animTextures[nextAnim] = texture;
#ifndef NODEBUG
			std::cout << std::endl << "ANIMASYON EKLENDI:" << animId << ":" << texture.id;
#endif
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
		return animTextures[anim / (ANIMPERFRAME / (nextAnim))];
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
	Vector2 pos;
	Vector2 scale;
	sf::RenderWindow* window;
	Trigger t;
	bool click = false, holdButton;
public:
	/// <summary>
	/// Baþlangýç
	/// </summary>
	/// <param name="texture">Texture deðiþkeni</param>
	/// <param name="id">Button id</param>
	/// <param name="x">X pozisyonu</param>
	/// <param name="y">Y pozisyonu</param>
	/// <param name="urWindow">Pencerenin adresi</param>
	Button(Texturee texture, std::string id, float x, float y, float width, float height, bool holdButtonn, sf::RenderWindow* urWindow)
		: txr(texture), window(urWindow)
	{
		pos.x = x; pos.y = y;
		scale.x = width / txr.width;
		scale.y = height / txr.height;
		setTrigger(&t, pos.x, pos.y, txr.height * scale.y, txr.width * scale.x, 1, 1, id, "button");
		holdButton = holdButtonn;
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
		mouseTrigger.pos.x = event.mouseButton.x; mouseTrigger.pos.y = event.mouseButton.y; mouseTrigger.scale.y = 0; mouseTrigger.scale.x = 0; mouseTrigger.id = "MOUSE TRIGGER";
		setTrigger(&t, pos.x, pos.y, txr.height * scale.y, txr.width * scale.x, 1, 1, "mouse", "mouse");
		bool fix = event.mouseButton.button == sf::Mouse::Left && isColliding(t, mouseTrigger);
		bool b = event.type == sf::Event::MouseButtonPressed && fix;
		bool c = event.type == sf::Event::MouseButtonReleased;
		if (b && holdButton) {
			click = true;
		}
		else if (c && holdButton) {
			click = false;
		}

		b = event.type == sf::Event::MouseButtonPressed && fix;
		if (b && !holdButton) {
			click = true;
		}
		return click;
	}

	Vector2* getPos() { return &pos; }

	/// <summary>
	/// Butona basýlýp basýlmadýðýný döndürür
	/// </summary>
	/// <returns>basýldý?</returns>
	bool getClick() {
		bool a = click;
		if (!holdButton) { click = false; }
		return a;
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
void addButtons(Buttons* urButtons, Texturee buttonTexture, std::string id, float posX, float posY, float scaleX, float scaleY, bool holdButton, sf::RenderWindow* urWindow) {
	if (urButtons->nextButton >= BUTTONARRAY) {
#ifndef NODEBUG
		std::cout << std::endl << "MAX_BUTTON_ARRAY";
#endif
	}
	else {
		urButtons->buttons[urButtons->nextButton] = new Button(buttonTexture, id, posX, posY, scaleX, scaleY, holdButton, urWindow);
		urButtons->nextButton++;
	}
}



/// <summary>
/// Panel Class
/// </summary>
class Panel {
private:
	Vector2 pos, scale, moveScale;

	Texturee texture;
	Buttons buttons;
	int nextText;
	bool isActive, moveSetted;
	bool isMoving;
	sf::RenderWindow* window;
	sf::Font defaultFont;
	UI* ui;
	Vector2 mousePos;

public:

	/// <summary>
	/// Panel oluþturucu fonksiyonu
	/// </summary>
	/// <param name="position">Vector2 deðerinden pozisyon</param>
	/// <param name="widthHeight">Vector2 deðerinden geniþlik ve yükseklik</param>
	/// <param name="urTexture">texture</param>
	/// <param name="isActiveController">baþlangýçta panel açýk?</param>
	/// <param name="urUI">Panelde kullanýlacak UI objesi</param>
	/// <param name="urWindow"></param>
	Panel(Vector2 position, Vector2 widthHeight, Texturee urTexture, bool isActiveController, UI* urUI, sf::RenderWindow* urWindow)
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
	bool move(sf::Event event) {
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && moveSetted && isActive) {
			Trigger panelTrigger;
			panelTrigger.pos.x = pos.x; panelTrigger.pos.y = pos.y; panelTrigger.scale.y = moveScale.y; panelTrigger.scale.x = moveScale.x;
			Trigger mouseTrigger;
			mouseTrigger.pos.x = event.mouseButton.x; mouseTrigger.pos.y = event.mouseButton.y; mouseTrigger.scale.y= 0; mouseTrigger.scale.x = 0;
			if (isColliding(panelTrigger, mouseTrigger)) {
				isMoving = true;
				mousePos.x = event.mouseButton.x; mousePos.y = event.mouseButton.y;
			}
		}if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && moveSetted && isActive) {
			Trigger panelTrigger;
			panelTrigger.pos.x = pos.x; panelTrigger.pos.y = pos.y; panelTrigger.scale.y = moveScale.y; panelTrigger.scale.x = moveScale.x;
			Trigger mouseTrigger;
			mouseTrigger.pos.x = event.mouseButton.x; mouseTrigger.pos.y = event.mouseButton.y; mouseTrigger.scale.y = 0; mouseTrigger.scale.x = 0;
			if (isMoving) {
				isMoving = false;
				mousePos.x = event.mouseButton.x; mousePos.y = event.mouseButton.y;
			}
		}if (event.type == sf::Event::MouseMoved && isMoving == true && isActive) {
			pos.x = event.mouseMove.x - mousePos.x;
			pos.y = event.mouseMove.y - mousePos.y;
		}
		return isMoving;
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
	void addButton(Texturee buttonTexture, std::string id, float posX, float posY, float scaleX, float scaleY, bool holdButton) {
		addButtons(&buttons, buttonTexture, id, posX, posY, scaleX, scaleY, holdButton, window);
	}

	/// <summary>
	/// text ekle
	/// </summary>
	/// <param name="string">yazý</param>
	/// <param name="array">dizide kaçýncý sýrada olsun?</param>
	/// <param name="posX">pozisyon x</param>
	/// <param name="posY">pozisyon y</param>
	/// <returns></returns>
	bool addText(sf::String string, int array, float posX, float posY) {
		if (array >= UIELEMENTS) {
			std::cout << std::endl << "MAX_TEXT_ARRAY";
			return false;
		}
		else {
			ui->setText(array, string, posX + pos.x, posY + pos.y);
			return true;
		}
	}

	Button getButton(int array) {
		Button button = buttons.buttons[array][0];
		button.getPos()->x += pos.x;
		button.getPos()->y += pos.y;
		return button;
	}

	UI* getUI() {
		return ui;
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
				button.control(event);
				if (button.getClick()) {
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
	gameObject* gmObjects[MULTIS];
	int nextMulti = 0;
	int nextGmObject = 0;
public:
	/// <summary>
	/// Çizilecek þeylere bir physicsObject atar
	/// </summary>
	/// <param name="object">Fizik Objesi</param>

	void addObject(gameObject* object) {
		if (nextGmObject == MULTIS) {
#ifndef NODEBUG
			std::cout << std::endl << "Maksimum MULTIS";
#endif
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
		for (int i = 0; i < nextGmObject; i++) {
			gmObjects[i]->draw();
		}
	}

};


class PreSound {
private:
	sf::SoundBuffer buffer;
	sf::Sound sound;
public:
	PreSound(sf::String filePath, std::string id) {
		bool val = buffer.loadFromFile(filePath);
#ifndef NODEBUG
		std::cout << SOUNDLOAD;
#endif
		sound.setBuffer(buffer);
	}
	void setPlayingOffset(float sec) {
		sound.setPlayingOffset(sf::seconds(sec));
	}
	void setVolume(float volume) {
		sound.setVolume(volume);
	}

	void play() { sound.play(); }
	void stop() { sound.stop(); }
	void pause() { sound.pause(); }


	sf::Sound* get() {
		return &sound;
	}
};

class Sound {
private:
	sf::Music music;
public:
	Sound(sf::String filePath, std::string id) {
		bool val = music.openFromFile(filePath);
#ifndef NODEBUG
		std::cout << SOUNDLOAD;
#endif
	}

	sf::Music* get() {
		return &music;
	}
};



#endif