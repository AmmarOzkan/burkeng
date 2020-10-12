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
#error #define TEXTURELOAD komut penceresine yazýlacak olan yazýyý belirtir. (Texture yükleme) Kullanabileceklerin:
#error urTexture->id = texture idsi; val = yükleme durumu;
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
#error texturee->id = texture idsi; val = yükleme durumu;
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