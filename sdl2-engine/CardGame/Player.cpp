#include "Player.h"


Player::Player(int n){
	
	id_cards.resize(n);
	for (int i = 0; i < n; i++)
		id_cards[i] = i;
}
	
void Player::create_deck(){
	deck_cards.resize(deck_cards.size() + 1);
	for (int i = 0; i < 60; i++)
		if (!add_card_deck(i))
			break;
	shuffle();
	show_deck();
}

int Player::add_card_deck(int id){
	int tam = deck_cards[actual].size();
	if (tam < deck_size){
		deck_cards[actual].resize(tam + 1);
		deck_cards[actual][tam] = id_cards[id];
		return 1;
	}
	//full deck
	return 0;
}

void Player::show_deck(){
	for (int i = 0; i < deck_cards[actual].size(); i++)
		printf("card %d in deck\n", deck_cards[actual][i]);
}

void Player::shuffle(){
	int x;
	int i;
	int aux;
	srand(time(NULL));
	for (i = 0; i< deck_size; i++){
		x = rand() % deck_size;
		aux = deck_cards[actual][i];
		deck_cards[actual][i] = deck_cards[actual][x];
		deck_cards[actual][x] = aux;
	}

}

void Player::draw_card(int n){
	
	if (!deck_cards[actual].size()){
		if (n > 0){
			deck_cards[actual].pop_back();
			Player::draw_card(n - 1);
			//function that add a card to hand
		}
	}
	else{
		//lose the game
		printf("You lose the game yeahhhh!\n");
		return;
	}

}
