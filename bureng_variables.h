#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#ifndef BURENG_VARIABLES
#define BURENG_VARIABLES
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
struct Vector2 {
	float x, y;
};

/// <summary>
/// Fizik verilerini tutan deðiþken (Þimdilik tek þey var ama daha çok þey ekleyecem)
/// </summary>
struct PhyVal {
	float gravity;
};


struct TriggerId { std::string id, publicId; };

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

/// <summary>
/// Renk ve karakter verilerini tutar
/// </summary>
struct colorByChar {
	char ch;
	int r, g, b;
};

struct Trigger {
	Vector2 pos,scale;
	std::string id,publicId;
};
#endif