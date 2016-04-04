#include <string>
#include <stdlib.h>
#include <vector>
#include <iostream>
using namespace std;
#pragma once

class Card
{
private:
	int power, lt, res;
	int pri_cost, sec_cost;
	string name, type, color, desc;

public:
	Card(vector<string> &values);
	int id_card;
	int is_equal(char* ct, char* type);
	void print();
};

