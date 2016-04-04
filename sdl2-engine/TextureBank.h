//==============================================================================
/*
	Texture Bank class for loading multiple textures

	3/18/2014
    SDLTutorials.com
    Tim Jones
*/
//==============================================================================
#ifndef __TEXTUREBANK_H__
	#define __TEXTUREBANK_H__

#include <map>
#include <string>
#include <vector>
#include <SDL2/SDL.h>

#include "Texture.h"
#include "Mask.h"

class TextureBank {
	private:
		static std::map<std::string, Texture*> TexList;
		static std::map<std::string, std::vector<SDL_Rect>*> RectsList;
		static std::map<std::string, std::vector<Mask*>*> MasksList;

	public:
		static bool Init();
		static void Cleanup();
		static bool LoadFolder(std::string Folder);
		static void UnloadFolder(std::string Folder);

    private:
        static void AddTexture(SDL_Renderer* Renderer, std::string ID, std::string Filename);
		static void AddRects(std::string ID);
		static void AddMasks(std::string ID);
		static void FreeTexture(std::string ID);

	public:
		static Texture* Get(std::string ID);
		static std::vector<SDL_Rect>* GetRects(std::string ID);
		static std::vector<Mask*>* GetMasks(std::string ID);
		static TextureBank* GetInstance();
};

#endif
