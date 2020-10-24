#pragma once

#include "bureng.h"
#ifndef BURENGEXTEN
#define BURENGEXTEN


namespace bex {

	struct result {
		collideRes2 physicsres;
		superStr colResults;
	};

	struct CollideResult2 {
		collideRes res1;
		collideRes res2;
	};

	class Object {
	private:
		gameObject gameobject;
		physicsObject physicsobject;
		Animation objAnim;
		valueXY * camera;
		bool anim;
		float perf;
	public:
		Object(float movePerf,Texturee texture, sf::RenderWindow* urWindow, valueXY* urCamera, std::string id, std::string publicId)
			: gameobject(texture, 0, 0, texture.width, texture.height, true, urWindow, urCamera),
			physicsobject(&gameobject, false, 0.0, id,publicId),
			objAnim(id),
			perf(movePerf)
		{
			camera = urCamera;
			anim = false;
		}

		Object(float movePerf, Animation urAnim, sf::RenderWindow* urWindow, valueXY* urCamera, std::string id,std::string publicId)
			: gameobject(urAnim.animate(),0,0,1,1,false,urWindow,urCamera),
			physicsobject(&gameobject, false, 0.0, id,publicId),
			objAnim(urAnim),
			perf(movePerf)
		{
			camera = urCamera;
			anim = true;
		}

		void ready(std::string publicId) {
			physicsobject.setTrigger(publicId);
		}

		void setAnimation(Animation urAnim) {
			objAnim = urAnim;
			anim = true;
		}

		void delAnimation() {
			anim = false;
		}

		void setPosition(float x, float y) {
			gameobject.position()->x = x;
			gameobject.position()->y = y;
		}

		void setScale(float width, float height) {
			gameobject.setHW(width, height);
		}

		void setProperties(float x, float y, float width, float height) {
			setPosition(x, y);
			setScale(width, height);
		}

		void addTrigger(physicsObject* urObject) {
			physicsobject.addControl(urObject->getTrigger());
		}

		bool isColliding(Trigger was) {
			return physicsobject.isColliding(was);
		}

		valueXY * getPos() {
			return gameobject.position();
		}

		valueXY getCameraPos() {
			valueXY result = gameobject.position()[0];
			result.x += camera->x;
			result.y += camera->y;
			return result;
		}

		valueXY* getForce() {
			return physicsobject.getForce();
		}

		Trigger * getTrigger() {
			return physicsobject.getTrigger();
		}

		void setForce(float newNum, bool isX) {
			if (isX) {
				physicsobject.getForce()->x = newNum;
			}
			else {
				physicsobject.getForce()->y = newNum;
			}
		}

		void addForce(float x, float y) {
			physicsobject.forceAdd(x, y);
		}

		void clearForce() {
			physicsobject.forceClear();
		}

		CollideResult2 addPos(float x, float y) {
			collideRes fRes = physicsobject.addX(x,perf,"");
			collideRes sRes = physicsobject.addY(y, perf, "");
			return { fRes,sRes };
		}

		void addTo(physicsObject *urObject) {
			urObject->addControl(physicsobject.getTrigger());
		}

		void add(physicsObject* urObject) {
			physicsobject.addControl(urObject->getTrigger());
		}

		void add(Trigger* urTrig) {
			physicsobject.addControl(urTrig);
		}

		void physics(float gravity, bool phy) {
			physicsobject.setPhysics(phy);
			physicsobject.getPhysics()->gravity = gravity;
		}

		superStr getCollidings() {
			physicsobject.setColliding();
			superStr b = physicsobject.getCollidings();
			return b;
		}

		result exec() {
			physicsobject.setColliding();
			collideRes2 a = physicsobject.phyMove(perf, "");
			superStr b = physicsobject.getCollidings();

			if (anim) {
				gameobject.setTexturee(objAnim.animate(),true);
			}

			return { a, b };
		}

		void draw() {
			physicsobject.draw();
		}

		gameObject * getObject() {
			return &gameobject;
		}

		physicsObject * getPhyObject() {
			return &physicsobject;
		}

	};

	class JustTextureObject {
	private:
		gameObject gameobject;
	public:
		JustTextureObject(Texturee texture,float posX, float posY, float width, float height, sf::RenderWindow *urWindow,valueXY * urCamera) 
			: gameobject(texture,posX,posY,width,height,true,urWindow,urCamera)
		{

		}

		gameObject * getObject() {
			return &gameobject;
		}
	};


#ifndef DRAWOBJECTAMOUNT
#error YOU SHOULD DEFINE DRAW OBJECT AMOUNT
#else
	class TDimensionDrawer {
	private:
		int addedNumber = 0;
		gameObject *objects[DRAWOBJECTAMOUNT];
		int height = 800, width = 1000;
	public:
		void setWindowProperties(int newH, int newWidth) {
			height = newH;
			width = newWidth;
		}
		void addObject(Object * willAdd) {
			if (addedNumber < DRAWOBJECTAMOUNT) {
				objects[addedNumber] = willAdd->getObject();
				addedNumber++;
			}
		}

		void addObject(gameObject* willAdd) {
			if (addedNumber < DRAWOBJECTAMOUNT) {
				objects[addedNumber] = willAdd;
				addedNumber++;
			}
		}

		void addObject(JustTextureObject* willAdd) {
			if(addedNumber < DRAWOBJECTAMOUNT){
				objects[addedNumber] = willAdd->getObject();
				addedNumber++;
			}
		}

		void draw() {
			for (int i = -height; i < height; i++) {
				for (int j = 0; j < addedNumber; j++) {
					if (objects[j]->position()->y + objects[j]->getCamera()->y < i+1 && objects[j]->position()->y + objects[j]->getCamera()->y > i-1) {
						objects[j]->draw();
					}
				}
			}
		}
	};

#endif
}


#endif