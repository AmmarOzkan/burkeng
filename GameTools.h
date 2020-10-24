#pragma once

#include "bureng.h"
#include "bureng_exten.h"

namespace gm {
	class PlatformController {
	private:
		bool left, right;
		bool prevLeft, prevRight;
		bool isthereIdle;
		Animation leftAnim, rightAnim, idleAnim;
		bex::Object* object;
		float speed;
	public:
		/// <summary>
		/// PlatformController oluþturucusu
		/// </summary>
		/// <param name="leftAnimation">Sola giderken oluþacak animasyon</param>
		/// <param name="rightAnimation">Saða giderken oluþiacak animasyon</param>
		PlatformController(Animation leftAnimation, Animation rightAnimation, Animation idleAnimation, bex::Object* urObject, float urSpeed)
			: leftAnim(leftAnimation), rightAnim(rightAnimation), object(urObject), idleAnim(idleAnimation)
		{
			left = right = false;
			speed = urSpeed; isthereIdle = true;
		}

		PlatformController(Animation leftAnimation, Animation rightAnimation, bex::Object* urObject, float urSpeed)
			: leftAnim(leftAnimation), rightAnim(rightAnimation), object(urObject), idleAnim("")
		{
			left = right = false;
			speed = urSpeed; isthereIdle = false;
		}

		bool event(sf::Event urEvent) {
			if (urEvent.type == sf::Event::KeyPressed && urEvent.key.code == sf::Keyboard::A) left = true;
			else if (urEvent.type == sf::Event::KeyReleased && urEvent.key.code == sf::Keyboard::A) left = false;

			else if (urEvent.type == sf::Event::KeyPressed && urEvent.key.code == sf::Keyboard::D) right = true;
			else if (urEvent.type == sf::Event::KeyReleased && urEvent.key.code == sf::Keyboard::D) right = false;
			return left || right;
		}


		bool lrGet(bool isLeft) {
			if (isLeft) return left;
			else return right;
		}

		void exec() {
			if (left && !prevLeft) {
				object->setAnimation(leftAnim);
			}
			else if (right && !prevRight) {
				object->setAnimation(rightAnim);
			}
			else if (!left && !right) {
				if (isthereIdle) {
					object->delAnimation();
				}
				else {
					object->setAnimation(idleAnim);
				}
			}
			prevLeft = left;
			prevRight = right;
		}
	};


	class ClassicController {
	private:
		bool left, right, up, down;
		bool prevLeft, prevRight, prevUp, prevDown;
		bool isthereIdle;
		Animation leftAnim, rightAnim, idleAnim;
		bex::Object* object;
		float speed;
	public:
		/// <summary>
		/// PlatformController oluþturucusu
		/// </summary>
		/// <param name="leftAnimation">Sola giderken oluþacak animasyon</param>
		/// <param name="rightAnimation">Saða giderken oluþiacak animasyon</param>
		ClassicController(Animation leftAnimation, Animation rightAnimation, Animation idleAnimation, bex::Object* urObject, float urSpeed)
			: leftAnim(leftAnimation), rightAnim(rightAnimation), object(urObject), idleAnim(idleAnimation)
		{
			left = right = false;
			speed = urSpeed; isthereIdle = true;
		}

		ClassicController(Animation leftAnimation, Animation rightAnimation, bex::Object* urObject, float urSpeed)
			: leftAnim(leftAnimation), rightAnim(rightAnimation), object(urObject), idleAnim("")
		{
			left = right = false;
			speed = urSpeed; isthereIdle = false;
		}

		bool event(sf::Event urEvent) {
			if (urEvent.type == sf::Event::KeyPressed && urEvent.key.code == sf::Keyboard::A) left = true;
			else if (urEvent.type == sf::Event::KeyReleased && urEvent.key.code == sf::Keyboard::A) left = false;

			else if (urEvent.type == sf::Event::KeyPressed && urEvent.key.code == sf::Keyboard::D) right = true;
			else if (urEvent.type == sf::Event::KeyReleased && urEvent.key.code == sf::Keyboard::D) right = false;

			else if (urEvent.type == sf::Event::KeyPressed && urEvent.key.code == sf::Keyboard::W) up = true;
			else if (urEvent.type == sf::Event::KeyReleased && urEvent.key.code == sf::Keyboard::W) up = false;


			else if (urEvent.type == sf::Event::KeyPressed && urEvent.key.code == sf::Keyboard::S) down = true;
			else if (urEvent.type == sf::Event::KeyReleased && urEvent.key.code == sf::Keyboard::S) down = false;
			return left || right;
		}


		int lrGet() {
			if (left) return -1;
			else if (right) return 1;
			else return 0;
		}

		int udGet() {
			if (up) return -1;
			else if (down) return 1;
			else return 0;
		}

		void exec() {
			if (left && !prevLeft) {
				object->setAnimation(leftAnim);
			}
			else if (right && !prevRight) {
				object->setAnimation(rightAnim);
			}
			else if (!left && !right) {
				if (isthereIdle) {
					object->delAnimation();
				}
				else {
					object->setAnimation(idleAnim);
				}
			}
			prevLeft = left;
			prevRight = right;
			prevUp = up;
			prevDown = down;
		}
	};


	
}