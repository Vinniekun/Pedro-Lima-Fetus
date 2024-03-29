//==============================================================================
/*
	Primary application class

	3/11/2014
	SDLTutorials.com
	Tim Jones
*/
//==============================================================================
#ifndef __APP_H__
	#define __APP_H__

#include <SDL2/SDL.h>

#include "TextureBank.h"
#include "GameObject.h"

class App {
	private:
		static App Instance;

		bool Running = true;

		SDL_Window* Window = NULL;
		SDL_Renderer* Renderer = NULL;
		SDL_Surface* PrimarySurface = NULL;

		static const int WindowWidth = 1024;
		static const int WindowHeight = 600;

		// GameObjects
		GameObject* mario = NULL;

	private:
		App();

		// Capture SDL Events
		void OnEvent(SDL_Event* Event);

		// Logic loop
		void Loop();

		// Render loop (draw)
		void Render();

		// Free up resources
		void Cleanup();

	public:
		int Execute(int argc, char* argv[]);

	public:
		// Initialize our SDL game / app
		bool Init();
		SDL_Renderer* GetRenderer();

	public:
		static App* GetInstance();

		static int GetWindowWidth();
		static int GetWindowHeight();
};

#endif
