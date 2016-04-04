#include <vector>
#include <stdio.h>
#ifndef __CREATE_DECK_H__
	#define __CREATE_DECK_H__



class Create_Deck{

	static std::vector <int> id_cards;

	public:
		static int Init();
		static void save_deck();
};

#endif