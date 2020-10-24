#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#ifndef BURENG_VARIABLES
#define BURENG_VARIABLES
/*
*
*
* DE���KENLER
*
*
*/

/// <summary>
/// 2 Bool veri tutan de�i�ken
/// </summary>
struct tValBool {
	bool b1, b2;
};


///Dir
enum Dir { LEFT, RIGHT, UP, DOWN, NONE };


/// <summary>
/// Texturelar i�in �zel de�i�ken
/// Texturee de�i�keni texturelarda dikey yatay pixel say�s� gibi bir�ok veriyi tutar.
/// </summary>
struct Texturee {
	sf::Texture texture;
	int height, width;
	std::string id;
};

/// <summary>
/// 2 tane float tutan de�i�ken
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
/// Fizik verilerini tutan de�i�ken (�imdilik tek �ey var ama daha �ok �ey ekleyecem)
/// </summary>
struct PhyVal {
	float gravity;
};


struct TriggerId { std::string id, publicId; };

/// <summary>
/// Objelerin �arp��malar�ndan sonra d�nd�r�len de�er.
/// </summary>
struct collideRes {
	std::string id;
	bool res;
};

/// <summary>
/// Objelerin �arp��malar�ndan sonra d�nd�r�len de�er.
/// </summary>
struct collideRes2 {
	std::string id;
	bool res1, res2;
};


/// <summary>
/// ��inde bir �ok string de�eri bar�nd�ran de�i�ken
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