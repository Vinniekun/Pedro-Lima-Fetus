#include "Card.h"

//int* atrib, int* cost, char* nam, char* typ, char* sec_typ, char* des

Card::Card(vector <string> &values){
		name = values[0];
		type = values[1];
		desc = values[2];
		color = values[3];
		pri_cost = atoi(values[4].c_str());
		sec_cost = atoi(values[5].c_str());
		power = atoi(values[6].c_str());
		lt = atoi(values[7].c_str());
		res = atoi(values[8].c_str());
}

void Card::print (){
	cout << "Nome " << name << endl;
	cout << "Tipo " << type << endl;
	cout << "Cor " << color << endl;
	cout << "Desc " << desc << endl;
	cout << "Pow " << power << endl;
	cout << "Lt " << lt << endl;
	cout << "Res " << res << endl;
	cout << "cost " << pri_cost << endl;
	cout << "carga " << sec_cost << endl;
}
