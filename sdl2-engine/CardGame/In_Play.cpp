#include "In_Play.h"

//carrega baralho escolhido pelo player
In_Play::In_Play(int size, int* deck_list)
{
//	deck = (int*)malloc(sizeof(int)*size);
	//for (int i = 0; i < size; i++){
		//deck[i] = deck_list[i];
	//}

}

void In_Play::ini_heap(deck_t* d){
	d->top = -1;
	d->gap = deck_size;
	d->id_card = (int*)malloc(sizeof(int)*d->gap);

}

int In_Play::heap_is_empty(deck_t* d){
	if (d->top == -1)
		return 1;
	return 0;
}

void In_Play::push_heap(deck_t* d, int id){
	if (d->top + 1 >= deck_size){
		d->gap *= 2;
		d->id_card = (int*)malloc(sizeof(int)*d->gap);
	}
	d->id_card[++d->top] = id;
}

int In_Play::pop_heap(deck_t* d){
	int aux = d->id_card[d->top--];
	return aux;
}

int In_Play::top_deck(deck_t* d){
	return d->id_card[d->top];
}
