//=============================================================================
#include "TextureBank.h"
#include "App.h"
#include "FileManager.h"
#include "Log.h"
#include "Stringify.h"

//=============================================================================
std::map<std::string, Texture*> TextureBank::TexList;
std::map<std::string, std::vector<SDL_Rect>*> TextureBank::RectsList;
std::map<std::string, std::vector<Mask*>*> TextureBank::MasksList;

//=============================================================================
bool TextureBank::Init() {
	Cleanup();
	return LoadFolder("Textures");
}

//-----------------------------------------------------------------------------
void TextureBank::Cleanup() {
	if(TexList.size() <= 0) return;

	for(auto& Iterator : TexList){
		std::string ID = (std::string)Iterator.first;
		FreeTexture(ID);
	}

	TexList.clear();
	RectsList.clear();
	MasksList.clear();
	Log("[ OK ] TextureBank Cleaned up");
}

//-----------------------------------------------------------------------------
bool TextureBank::LoadFolder(std::string Folder){
	SDL_Renderer* Renderer = App::GetInstance()->GetRenderer();
	if(!Renderer) return false;

	std::vector<std::string> Files = FileManager::GetFilesInFolder(Folder); // Relative to CWD
	for(auto Filename : Files) {
        std::string Ext = FileManager::GetFilenameExt(Filename);
		std::string ID  = FileManager::GetFilenameWithoutExt(Filename);
        // Skip all non-png files
        if(Ext != "png") continue;

		AddTexture(Renderer, ID, Filename);
		AddRects(ID);
		AddMasks(ID);
	}
	return true;
}

//-----------------------------------------------------------------------------
void TextureBank::UnloadFolder(std::string Folder){
	std::vector<std::string> Files = FileManager::GetFilesInFolder(Folder); // Relative to CWD

	for(auto Filename : Files) {
        std::string ID  = FileManager::GetFilenameWithoutExt(Filename);
		if (TexList[ID])
			FreeTexture(ID);
	}
}

//=============================================================================
void TextureBank::AddTexture(SDL_Renderer* Renderer, std::string ID, std::string Filename) {
    if(ID == "") return;

    Texture* NewTexture = new Texture();
    if(NewTexture->Load(Renderer, Filename) == false) {
		Log("[ERRO] Unable to Load Texture: %s", ID.c_str());
		return;
	}
    TexList[ID] = NewTexture;
}

//-----------------------------------------------------------------------------
void TextureBank::FreeTexture(std::string ID){
	// free Texture
	delete TexList[ID];
	TexList.erase(ID);

	// free SDL_Rects
	RectsList[ID]->clear();
	delete RectsList[ID];
	RectsList.erase(ID);

	// free Masks
	for(Mask* m : *MasksList[ID])
		delete m;
	MasksList[ID]->clear();
	delete RectsList[ID];
	MasksList.erase(ID);
	Log ("[ OK ] Cleaned sprite: %s",ID.data());
}

//-----------------------------------------------------------------------------
Texture* TextureBank::Get(std::string ID) {
	if(TexList.find(ID) == TexList.end()) return 0;
	return TexList[ID];
}

//=============================================================================
void TextureBank::AddRects(std::string ID){
	std::vector<SDL_Rect> *NewRects = new std::vector<SDL_Rect>();
	std::string raw = FileManager::GetContents("Masks/"+ID);
	if (raw != ""){
		std::vector<std::string> rects_v = Stringify::Explode(raw, "\n");
		for (std::string rect_v : rects_v){
			if (rect_v == "") continue;
			SDL_Rect r;
			std::vector<std::string> values = Stringify::Explode(rect_v, " ");
			r.x = Stringify::ToInt(values[0]);
			r.y = Stringify::ToInt(values[1]);
			r.w = Stringify::ToInt(values[2]);
			r.h = Stringify::ToInt(values[3]);
			NewRects->push_back(r);
		}
	}
	else{
		Log("[INFO] Mask info from sprite \"%s\" not found.\
		Setting 1 mask with full sprite size.",ID.data());
		SDL_Texture* tex = TexList[ID]->Get();
		int h,w;
		SDL_QueryTexture(tex, 0, 0, &w, &h);
		SDL_Rect r = {0,0,w,h};
		NewRects->push_back(r);
	}
	RectsList[ID] = NewRects;
}

//-----------------------------------------------------------------------------
std::vector<SDL_Rect>* TextureBank::GetRects(std::string ID){
	return RectsList[ID];
}

//=============================================================================
void TextureBank::AddMasks(std::string ID){
	std::vector<Mask*> *NewMasks = new std::vector<Mask*>();
	Texture *tex = TexList[ID];
	for(SDL_Rect rect : *RectsList[ID])
		NewMasks->push_back(new Mask(tex->Get(), rect, tex->GetPitch()));
	MasksList[ID] = NewMasks;
}

//-----------------------------------------------------------------------------
std::vector<Mask*>* TextureBank::GetMasks(std::string ID){
	return MasksList[ID];
}
