
#undef main
#include "App.h"
#include <vector>
#include "GameObject.h"
#include <stdio.h>
#include <iostream>
#include <string.h>
#include "CardGame/Card.h"
#include "CardGame/Player.h"
#include "CardGame/DataBase.h"
#include "CardGame/Create_Deck.h"
using namespace std;
//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//
const int SIZE_DECK = 40;
const int INI_CARDS = 40;

int main(int argc, char* argv[]) {
   DataBase:Init("cartas.db");

	if (App::GetInstance()->Init()){
		GameObject* vinnie = new GameObject("Test");
		std::vector<GameObject*> gebinha;
		gebinha.push_back(new GameObject("Test"));
		delete gebinha[0];
		gebinha.clear();
		return App::GetInstance()->Execute(argc, argv);
	}

}
