#ifndef __MASK_H__
#define __MASK_H__

#include <SDL2/SDL.h>
#include "Log.h"
#include "ExternalLibs/bitmask.h"

class Mask {
	protected:
		bitmask_t* bitmask = NULL;
		int Width;
		int Height;
		int x_offset;
		int y_offset;
		bool SetBitmask(SDL_Texture*, SDL_Rect, int);

	public:
		Mask(SDL_Texture*, SDL_Rect, int);
		~Mask();
		bool Overlap(Mask*, int, int);
		bitmask_t* GetBitmask();
};
#endif
