#pragma once

#ifndef BURENG
#define BURENG

/*
*
*
* GEREKL� #DEFINE
*
*
*/

#ifndef ANIMPERFRAME
#error #define ANIMPERFRAME [Kac frame'de bir animasyon degisecegi] tan�m�n� yapmak zorundas�n
#endif

//Bir dizide ka� tane UIELEMENT oldu�unu belirtmemiz istenir.
//Bu �ekilde k�t�phaneyi yapan de�il k�t�phaneyi kullanan dizilerin ka� tane oldu�unu belirtmi� olur.
#ifndef UIELEMENTS
#error UIELEMENTS'i define edip bir say� belirtmen gerekiyor.
//Bu UIELEMENTS program�nda ka� tane UI element'i kullanaca��n� belirtir.
#endif

//Yukardakilerle benzer �eyler
#ifndef MULTIS
#error MultiDraw i�in MULTIlerin max ka� tane olmas�n� istedi�ini giriniz. (define MULTIS)
#endif

#ifndef SUPERSTR
#error SUPERSTR dizisinin ka� tane oldu�u belirtilmeli #define SUPERSTR [dizisayisi]
#endif

#define TEXTURELOAD "Texture:" << urTexture->id << " yukleme durumu: " << val
#define FONTLOAD "Font " << id << " Yukleme Durumu: " << val
#define FONTERROR "Font " << id << " yuklenmesinde bir hata meydana geldi."
#define GAMEOBJECTTEXTURELOAD "Texture:" << texturee.id << " yukleme durumu: " << val
#define ADDINGTEXTURE "Texture " << urTexturee.id << " ekleniyor."
#define CREATINGPHYOBJ "Fizik Objesi: " << id << " olusturuldu."
#define CREATINGBUTTON "Buton:" << id << " olusturuldu."
#define CREATINGANIM "Animasyon:" << id << "olusturuldu."
#define SOUNDLOAD "Ses:" << id << " yukleme durumu: " << val

#ifndef TEXTURELOAD
#error #define TEXTURELOAD komut penceresine yaz�lacak olan yaz�y� belirtir. (Texture y�kleme) Kullanabileceklerin:
#error urTexture->id = texture idsi; val = y�kleme durumu;
#endif
#ifndef FONTLOAD
#error #define FONTLOAD komut penceresinde yaz�lacak olan yaz�y� belirtir. (Font y�kleme) Kullanabileceklerin:
#error id = font idsi; font.loadFromFile("res/fonts/batmfo__.ttf") = y�klenme durumu
#endif
#ifndef FONTERROR
#error #define FONTERROR komut penceresinde yaz�lacak olan yaz�y� belirtir. (Font hatas�) Kullanabileceklerin:
#error id = font idsi
#endif
#ifndef GAMEOBJECTTEXTURELOAD
#error #define GAMEOBJECTTEXTURELOAD komut penceresinde yaz�lacak olan yaz�y� belirtir. (Game object i�in texture y�kleme) Kullanabileceklerin:
#error texturee->id = texture idsi; val = y�kleme durumu;
#endif
#ifndef ADDINGTEXTURE
#error #define ADDINGTEXTURE komut penceresinde yaz�lacak olan yaz�y� belirtir. (Objeye Texture ekleme) Kullanabileceklerin:
#error urTexturee.id = texture idsi
#endif
#ifndef CREATINGPHYOBJ
#error #define FONTERROR komut penceresinde yaz�lacak olan yaz�y� belirtir. (Fizik Objesi Yaratma) Kullanabileceklerin:
#error id = fizik objesi idsi
#endif
#ifndef CREATINGBUTTON
#error #define FONTERROR komut penceresinde yaz�lacak olan yaz�y� belirtir. (Font hatasi) Kullanabileceklerin:
#error id = buton idsi
#endif
#ifndef CREATINGANIM
#error #define FONTERROR komut penceresinde yaz�lacak olan yaz�y� belirtir. (Animasyon olu�turma) Kullanabileceklerin:
#error id = animasyon idsi
#endif

/*
*
*
* DAH�L ED�LMES� GEREKENLER
*
*
*/

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <thread>
#include <fstream>
#include <sstream>

#include "bureng_variables.h"

#include "bureng_functions.h"

#include "bureng_main.h"

#include "bureng_extensions.h"


#endif