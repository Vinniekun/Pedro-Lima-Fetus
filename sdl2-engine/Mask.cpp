#include "Mask.h"

Mask::Mask(SDL_Texture* t, SDL_Rect rect, int pitch){
	Width = rect.w;
	Height = rect.h;
	x_offset = rect.x;
	y_offset = rect.y;
	bitmask = bitmask_create(Width, Height);
	if (!bitmask){
		Log("[ERRO] Unable to create bitmask");
	}
	else
		SetBitmask(t, rect, pitch);
}

Mask::~Mask(){
	bitmask_free(bitmask);
}

bool Mask::Overlap(Mask* m, int xoffset, int yoffset){
	return bitmask_overlap(bitmask, m->GetBitmask(), xoffset, yoffset);
}

bitmask_t* Mask::GetBitmask(){
	return bitmask;
}

bool Mask::SetBitmask(SDL_Texture* tex, SDL_Rect r, int pitch){
	int pix, texw;
    void *pixelBuffer;
	SDL_QueryTexture(tex, NULL, NULL, &texw, NULL);
	SDL_LockTexture(tex, NULL, &pixelBuffer, &pitch);
	Uint32 *pixels = (Uint32*) pixelBuffer;
	for(int y=r.y; y < r.y+r.h; y++){
		int begin = y*texw;
		for(int x=r.x; x < r.x+r.w; x++){
			pix = begin+x;
			if(((pixels[pix]>>24) & 0xFF) >= 64)
				bitmask_setbit(bitmask, x-r.x, y-r.y);
		}
	}
	SDL_UnlockTexture(tex);
	return true;
}
