#include <stdlib.h>
#pragma once
const int deck_size = 50;
class In_Play
{
	typedef struct deck{
		int top;
		int* id_card;
		int gap;
	}deck_t;

public:
	int* hand;


	In_Play(int size, int* deck_list);
	void ini_heap(deck_t* d);
	int heap_is_empty(deck_t* d);
	void push_heap(deck_t* d, int id);
	int top_deck(deck_t* d);
	int pop_heap(deck_t* d);
};
