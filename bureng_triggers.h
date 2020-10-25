#pragma once

#ifndef BURENGTRIGGERS
#define BURENGTRIGGERS
bool isColliding(Trigger t1, Trigger t2) {
	bool b = t1.pos.x + t1.scale.x > t2.pos.x && t2.pos.x + t2.scale.x > t1.pos.x;
	bool a = t1.pos.y + t1.scale.y > t2.pos.y && t2.pos.y + t2.scale.y > t1.pos.y;
	return a && b;
}

Trigger getTriggerFor(gameObject* gmo) {
	Trigger trigger;
	trigger.pos.x = gmo->position()->x; trigger.scale.x = gmo->getScale()->x * gmo->getTexturee()->width;
	trigger.pos.y = gmo->position()->y; trigger.scale.y = gmo->getScale()->y * gmo->getTexturee()->height;
	return trigger;
}

void setTrigger(Trigger* trigger, float x, float y, float height, float width, float scaleX, float scaleY, std::string id, std::string publicId) {
	trigger->pos.x = x; trigger->pos.x = y;
	trigger->scale.y = height * scaleX;
	trigger->scale.x = width * scaleY;
	trigger->id = id;
	trigger->publicId = publicId;
}


#endif