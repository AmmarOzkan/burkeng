#pragma once
#include "bureng_variables.h"
#include "bureng_main.h"
#include "bureng_functions.h"
#include "bureng_triggers.h"
#ifndef BURENG_PHYSICS
#define BURENG_PHYSICS





class Physics {
private:
	Vector2 force;
	gameObject *gameobject;
	Trigger *willControl[100], trigger;
	int triggerControlCounter;
public:
	void resetTrigger() {
		trigger = getTriggerFor(gameobject);
	}


	Physics(gameObject *urObject)
		: gameobject(urObject)
	{
		resetTrigger();
		force.x = 0; force.y = 0; triggerControlCounter = 0;
	}

	

	void moveX(float willMove) {
		resetTrigger();
		Vector2 position = gameobject->position()[0];
		position.x += willMove;
		TriggerId id = { "","" };
		trigger = getTriggerFor(gameobject);
		for (int i = 0; i < triggerControlCounter; i++) {
			setTrigger(&trigger, position.x, position.y, gameobject->getTexturee()->width, gameobject->getTexturee()->height, gameobject->getScale()->x, gameobject->getScale()->y, trigger.id, trigger.publicId);
			if (isColliding(trigger, willControl[i][0])) {
				id = { willControl[i]->id, willControl[i]->publicId };
				if (willMove > 0) position.x = willControl[i]->pos.x - (gameobject->getScale()->x * gameobject->getTexturee()->width);
				else if (willMove < 0) position.x = willControl[i]->pos.x + (willControl[i]->scale.x);
			}
		}
		std::cout << position.x<<std::endl;
		gameobject->setPosition(position);
	}

	void moveY(float willMove) {
		resetTrigger();
		Vector2 position = gameobject->position()[0];
		position.y += willMove;
		TriggerId id = { "","" };
		trigger = getTriggerFor(gameobject);
		for (int i = 0; i < triggerControlCounter; i++) {
			setTrigger(&trigger, position.x, position.y, gameobject->getTexturee()->width, gameobject->getTexturee()->height, gameobject->getScale()->x, gameobject->getScale()->y, trigger.id, trigger.publicId);
			if (isColliding(trigger, willControl[i][0])) {
				id = { willControl[i]->id, willControl[i]->publicId };
				if (willMove > 0) position.y = position.y - (gameobject->getScale()->y * gameobject->getTexturee()->width);
				else if (willMove < 0) position.y = willControl[i]->pos.y + (willControl[i]->scale.y);
			}
		}
		std::cout << position.y << std::endl;
		gameobject->setPosition(position);
	}

	void move(Vector2 v) { moveX(v.x);moveY(v.y);}
	void phy() {move(force);force = { 0,0 };}

	void phyDraw() {phy();gameobject->draw();}
	gameObject* gm() {return gameobject;}

	void setGm(gameObject* gmo) { gameobject = gmo; }

	void addTrigger(Trigger *trigger) {
		willControl[triggerControlCounter++] = trigger;
	}
};

#endif