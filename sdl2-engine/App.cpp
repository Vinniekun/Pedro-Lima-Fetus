//==============================================================================
#include "App.h"
#include "Log.h"

App App::Instance;

//==============================================================================
App::App() {
}

//------------------------------------------------------------------------------
void App::OnEvent(SDL_Event* Event) {
}

//------------------------------------------------------------------------------
bool App::Init() {
	Log("[ .. ] Initializing sdl2-engine...")
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		Log("[ERRO] Unable to Init SDL: %s", SDL_GetError());
		return false;
	}

	if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		Log("[ERRO] Unable to Init hinting: %s", SDL_GetError());
		return false;
	}

	if((Window = SDL_CreateWindow(
		"My SDL Game",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WindowWidth, WindowHeight, SDL_WINDOW_SHOWN)
	) == NULL) {
		Log("[ERRO] Unable to create SDL Window: %s", SDL_GetError());
		return false;
	}

	PrimarySurface = SDL_GetWindowSurface(Window);

	if((Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED)) == NULL) {
	    Log("[ERRO] Unable to create renderer");
	    return false;
	}

	SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	// Initialize image loading for PNGs
	if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		Log("[ERRO] Unable to init SDL_image: %s", IMG_GetError());
		return false;
	}

	// Load all of our Textures (see TextureBank class for expected folder)
	if(TextureBank::Init() == false) {
		Log("[ERRO] Unable to init TextureBank");
		return false;
	}
	Log("[ OK ] sdl2-engine initialized.");

	mario = new GameObject("Test");
	mario->SetPos((WindowWidth>>1)-140,(WindowHeight>>1)-160);

	return true;
}

//------------------------------------------------------------------------------
void App::Loop() {
}

//------------------------------------------------------------------------------
void App::Render() {
	SDL_RenderClear(Renderer);

	//TextureBank::Get("Test")->Render(0, 0); // You should really check your pointers
	mario->Render();

	SDL_RenderPresent(Renderer);
}

//------------------------------------------------------------------------------
void App::Cleanup() {
	TextureBank::Cleanup();

	if(Renderer) {
		SDL_DestroyRenderer(Renderer);
		Renderer = NULL;
	}

	if(Window) {
		SDL_DestroyWindow(Window);
		Window = NULL;
	}

	if (mario){
		delete mario;
		mario = NULL;
	}

	IMG_Quit();
	SDL_Quit();
	Log("[ OK ] App cleaned");
}

//------------------------------------------------------------------------------
int App::Execute(int argc, char* argv[]) {
	//if(!Initialized) return 0;
	//if(!Init()) return 0;

	SDL_Event Event;

	while(Running) {
		while(SDL_PollEvent(&Event) != 0) {
			OnEvent(&Event);

			if(Event.type == SDL_QUIT) Running = false;
		}

		Loop();
		Render();

		SDL_Delay(1); // Breath
	}

	Cleanup();

	return 1;
}

//==============================================================================
SDL_Renderer* App::GetRenderer() { return Renderer; }

//==============================================================================
App* App::GetInstance() { return &App::Instance; }

int App::GetWindowWidth()  { return WindowWidth; }
int App::GetWindowHeight() { return WindowHeight; }

//==============================================================================
