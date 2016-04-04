#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include <time.h>

using std::vector;
const int deck_size = 50;




#pragma once
class Player
{
	vector<vector<int>> deck_cards;
	vector<int> id_cards;
	vector<int>::iterator it;
	int actual;
	

	void shuffle();
public:
	Player(int n);
	int add_card_deck(int id);
	void show_deck();
	void create_deck();
	void draw_card(int n);

};

