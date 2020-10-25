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

	

	void moveX(float willMove,bool physics) {
		resetTrigger();
		Vector2 position = gameobject->position()[0];
		position.x += willMove;
		TriggerId id = { "","" };
		trigger = getTriggerFor(gameobject);
		for (int i = 0; i < triggerControlCounter; i++) {
			trigger.pos.x = position.x; trigger.pos.y = position.y;
			if (isColliding(trigger, willControl[i][0])) {
				id = { willControl[i]->id, willControl[i]->publicId };
				if (willMove > 0) position.x = willControl[i]->pos.x -(trigger.scale.x + 0.01);
				else if (willMove < 0) position.x = willControl[i]->pos.x + willControl[i]->scale.x+0.01;
				if (physics)force.x = 0;
			}
		}
		gameobject->setPosition(position);
	}

	void moveY(float willMove,bool physics) {
		resetTrigger();
		Vector2 position = gameobject->position()[0];
		position.y += willMove;
		TriggerId id = { "","" };
		trigger = getTriggerFor(gameobject);
		for (int i = 0; i < triggerControlCounter; i++) {
			trigger.pos.x = position.x; trigger.pos.y = position.y;
			if (isColliding(trigger, willControl[i][0])) {
				id = { willControl[i]->id, willControl[i]->publicId };
				if (willMove > 0) position.y = willControl[i][0].pos.y-(trigger.scale.y + 0.01);
				else if (willMove < 0) position.y = willControl[i]->pos.y + willControl[i]->scale.y+0.01;
				if (physics)force.y = 0;
			}
		}
		gameobject->setPosition(position);
	}

	void move(Vector2 v,bool physics) { moveY(v.y, physics); moveX(v.x, physics); }
	void phy() {move(force,true);}

	void phyDraw() {phy();gameobject->draw();}
	gameObject* gm() {return gameobject;}

	void setGm(gameObject* gmo) { gameobject = gmo; }


	void addTrigger(Trigger *trigger) {
		willControl[triggerControlCounter++] = trigger;
	}
};

#endif