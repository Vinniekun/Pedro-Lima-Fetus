#ifndef __GAMEOBJECT_H__
	#define __GAMEOBJECT_H__

#include <string>
#include <SDL2/SDL.h>
#include "Mask.h"

class GameObject{
	private:
		int 	 	Current;
		void 	 	SetCurrentSprite(int);
		SDL_Rect	src, dest;
		std::string ID;

	public:
		GameObject(std::string);
		void Update();
		void Render();
		bool Collide(GameObject*);
		Mask* 	    GetCurrentMask();
		SDL_Point   GetPos();
		void 		SetPos(int, int);
		std::string GetID();
};
#endif
