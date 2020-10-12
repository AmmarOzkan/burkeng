#pragma once
#include <SFML/Graphics.hpp>
#include "bureng_variables.h"
#ifndef BURENG_FUNCTIONS
#define BURENG_FUNCTIONS
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
Texturee setTexturee(int width, int height, std::string id, sf::String filePath) {
	Texturee urTexture;
	urTexture.width = width;
	urTexture.height = height;
	urTexture.id = id;
	bool val = urTexture.texture.loadFromFile(filePath);
#ifndef NODEBUG
	std::cout << std::endl << TEXTURELOAD;
#endif
	return urTexture;
}

Texturee setTexturee(int width, int height, std::string id, sf::Image img) {
	Texturee urTexture;
	urTexture.width = width;
	urTexture.height = height;
	urTexture.id = id;
	bool val = urTexture.texture.loadFromImage(img);
#ifndef NODEBUG
	std::cout << std::endl << TEXTURELOAD;
#endif
	return urTexture;
}

Texturee setTexturee(int width, int height, std::string id, sf::Texture texture) {
	Texturee urTexture;
	urTexture.width = width;
	urTexture.height = height;
	urTexture.id = id;
	urTexture.texture = texture;
	return urTexture;
}



sf::Texture loadImage(std::string path, int a, int bit) {
	sf::Image img;
	std::ifstream file(path);
	img.create(bit, bit, sf::Color::Transparent);
	colorByChar colors[20];
	for (int i = 0; i < 20; i++) {
		std::string command;
		file >> command;
		if (command == "spr") {
			break;
		}
		else if (command == "color") {
			char ch; int r, g, b;
			file >> ch >> r >> g >> b;
			colors[i].ch = ch; colors[i].r = r; colors[i].g = g; colors[i].b = b;
		}
	}
	for (int i = 0; i < a; i++) {
		std::string t;
		file >> t; char c;
		file.get(c);
	}
	file.get();
	if (file.is_open()) {
		for (int yPx = 0; yPx < bit; yPx++) {
			for (int xPx = 0; xPx < bit; xPx++) {
				char c; file.get(c); sf::Color color = sf::Color::Transparent;
				for (int i = 0; i < 20; i++) {
					if (c == colors[i].ch) { color = sf::Color::Color(colors[i].r, colors[i].g, colors[i].b); break; }
				}
				img.setPixel(xPx, yPx, color);
			}
		}
	}
	sf::Texture tx;
	tx.loadFromImage(img);
	return tx;
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
#ifndef NODEBUG
		std::cout << std::endl << "SUPERSTR MAXIMUM SINIRI ASILDI";
#endif
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
	bool val;
	if (!font.loadFromFile(filePath)) {
#ifndef NODEBUG
		std::cout << std::endl << FONTERROR;
#endif
		val = false;
	}
	else { val = true; }
#ifndef NODEBUG
	std::cout << std::endl << FONTLOAD;
#endif
	return font;
}
#endif