#include "Create_Deck.h"
#include "Card.h"

std::vector <int> Create_Deck::id_cards;

int Create_Deck::Init(){
	int id;
	printf ("Informe id das cartas que serao adicionadas ao baralho\n");
	printf ("Digite -1 para sair e -2 para salvar baralho\n");
	while (1){
		scanf ("%d", &id);
		if (id >= 0)	
			id_cards.push_back(id);
		if (id == -1)
			return -1;
		if (id == -2)
			if (id_cards.size() == SIZE_DECK)
				Create_Deck::save_deck();
	}
	
}

void Create_Deck::save_deck(){
	printf ("teste\n");

}