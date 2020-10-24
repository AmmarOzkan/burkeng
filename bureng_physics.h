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
	gameObject *gmo;
	Trigger *willControl[100], trigger;
	int triggerControlCounter;
public:
	Physics(gameObject *urObject)
		: gmo(urObject)
	{
		trigger = getTriggerFor(gmo);
		force.x = 0; force.y = 0; triggerControlCounter = -1;
	}

	void moveX(float willMove) {
		Vector2 position = gmo->position()[0];
		position.x += willMove;
		TriggerId id = { "","" };
		trigger = getTriggerFor(gmo);
		for (int i = 0; i < triggerControlCounter; i++) {
			setTrigger(&trigger, position.x, position.y, gmo->getTexturee()->width, gmo->getTexturee()->height, gmo->getScale()->x, gmo->getScale()->y, trigger.id, trigger.publicId);
			if (isColliding(trigger, willControl[i][0])) {
				id = { willControl[i]->id, willControl[i]->publicId };
				if (willMove > 0) position.x = willControl[i]->pos.x - (gmo->getScale()->x * gmo->getTexturee()->width);
				else if (willMove < 0) position.x = willControl[i]->pos.x + (willControl[i]->scale.x);
			}
		}
		std::cout << position.x<<std::endl;
		gmo->setPosition(position);
	}

	void moveY(float willMove) {
		Vector2 position = gmo->position()[0];
		position.y += willMove;
		TriggerId id = { "","" };
		trigger = getTriggerFor(gmo);
		for (int i = 0; i < triggerControlCounter; i++) {
			setTrigger(&trigger, position.x, position.y, gmo->getTexturee()->width, gmo->getTexturee()->height, gmo->getScale()->x, gmo->getScale()->y, trigger.id, trigger.publicId);
			if (isColliding(trigger, willControl[i][0])) {
				id = { willControl[i]->id, willControl[i]->publicId };
				if (willMove > 0) position.y = position.y - (gmo->getScale()->y * gmo->getTexturee()->width);
				else if (willMove < 0) position.y = willControl[i]->pos.y + (willControl[i]->scale.y);
			}
		}
		std::cout << position.y << std::endl;
		gmo->setPosition(position);
	}

	void move(Vector2 v) { moveX(v.x); moveY(v.y); }
	void phy() {move(force);force = { 0,0 };}

	void phyDraw() { phy(); gmo->draw(); }


	void addTrigger(Trigger *trigger) {
		willControl[triggerControlCounter++] = trigger;
	}
};

#endif