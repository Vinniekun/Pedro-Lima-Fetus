//==============================================================================
#include "Texture.h"
#include "Log.h"
#include <cstring>

//==============================================================================
Texture::Texture() {
}

//------------------------------------------------------------------------------
Texture::~Texture() {
	if(SDLTexture) {
		SDL_DestroyTexture(SDLTexture);
		SDLTexture = NULL;
	}
}

//==============================================================================
bool Texture::Load(SDL_Renderer* Renderer, std::string Filename) {
	if(Renderer == NULL) {
		Log("Bad SDL renderer passed");
		return false;
	}

	this->Renderer = Renderer;
	this->Filename = Filename;

	SDL_Surface* TempSurface = IMG_Load(Filename.c_str());
	if(TempSurface == NULL) {
		Log("Unable to load image : %s : %s", Filename.c_str(), IMG_GetError());
		return false;
	}

    // Convert SDL surface to a texture
	/*SDLTexture = SDL_CreateTextureFromSurface(Renderer, TempSurface);
	if(SDLTexture == NULL) {
		Log("Unable to create SDL Texture : %s : %s", Filename.c_str(), IMG_GetError());
		return false;
	}*/

	// Created to give STREAMING access to texture. This is needed to access
	// pixels to determine its masks
	SDLTexture = SDL_CreateTexture(Renderer, SDL_PIXELFORMAT_ABGR8888,
		SDL_TEXTUREACCESS_STREAMING, TempSurface->w, TempSurface->h);
	if(SDLTexture == NULL) {
		Log("Unable to create SDL Texture : %s : %s", Filename.c_str(), IMG_GetError());
		return false;
	}

	void* pixels;
	SDL_SetTextureBlendMode(SDLTexture, SDL_BLENDMODE_BLEND);
    SDL_LockTexture(SDLTexture, &TempSurface->clip_rect, &pixels, &TempSurface->pitch);
    memcpy(pixels, TempSurface->pixels, (TempSurface->w * TempSurface->h)<<2);
	SDL_UnlockTexture(SDLTexture);
    // Grab dimensions and pitch
	Width = TempSurface->w;
	Height = TempSurface->h;
	pitch = TempSurface->pitch;

	//SDL_QueryTexture(SDLTexture, NULL, NULL, &Width, &Height);
	//Log("Texture Dimensions: %s : %d %d", Filename.c_str(), Width, Height);

	SDL_FreeSurface(TempSurface);
	return true;
}

//------------------------------------------------------------------------------
void Texture::Render(int X, int Y) {
	Render(X, Y, Width, Height);
}

//------------------------------------------------------------------------------
void Texture::Render(int X, int Y, int Width, int Height) {
	SDL_Rect Destination = {X, Y, Width, Height};

	SDL_RenderCopy(Renderer, SDLTexture, NULL, &Destination);
}

//------------------------------------------------------------------------------
void Texture::Render(int X, int Y, int Width, int Height, int SX, int SY, int SWidth, int SHeight) {
	SDL_Rect Source = {SX, SY, SWidth, SHeight};
	SDL_Rect Destination = {X, Y, Width, Height};

	SDL_RenderCopy(Renderer, SDLTexture, &Source, &Destination);
}

//------------------------------------------------------------------------------
int Texture::GetWidth()  { return Width;  }
int Texture::GetHeight() { return Height; }
int Texture::GetPitch()  { return pitch;  }
//==============================================================================
