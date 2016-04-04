
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <cstdlib>

using namespace std;
const string types[] = { "nome carta: ", "tipo carta: ", 
"text: ", "card color: ", "primary cost: ",
 "carga: ", "power: ", "lifetime: ", "armor: " };

bool isSubSequence(string str1, string str2, int m, int n){
	// Base Cases
	if (m == 0) return true;
	if (n == 0) return false;

	// If last characters of two strings are matching
	if (str1[m - 1] == str2[n - 1])
		return isSubSequence(str1, str2, m - 1, n - 1);

	// If last characters are not matching
	return isSubSequence(str1, str2, m, n - 1);
}

int main (){

	vector<string> values;
	int character;
	int lines;
	ifstream file("cartas.txt", std::ios::binary);
	ofstream file2("test.txt", std::ofstream::out);
	//SEU BUCETA
	string str,aux;

	while (getline(file, str)){
		if (isSubSequence(types[0], str, types[0].size(), str.size())){
			values.push_back(str.erase(0, types[0].size() + 1));
			getline(file, str);
			values.push_back(str.erase(0, types[1].size() + 1));

			if (isSubSequence("Personagem", values[1], 10, values[1].size()))
				character = 1;
			else
				character = 0;

			getline(file,str);
			aux = str.erase(0, types[2].size() + 1);
			getline(file,str);
			while (!isSubSequence(types[3],str,types[3].size(), str.size())){
				aux += "\n" + str;
				getline(file,str);
			}
			values.push_back(aux);
			for (int i = 0; i < 2; i++){
				values.push_back(str.erase(0, types[3+i].size() + 1));
				getline(file, str);
			}
			if (isSubSequence(types[5], str, types[5].size(), str.size())){
				values.push_back(str.erase(0,types[5].size()+1));
				if (values[5] == "")
					values[5] = "NULL\n";
				getline(file,str);
			}
			else
				values.push_back("NULL\n");

			for (int i=0; i <3; i++){
				if (character)
					values.push_back(str.erase(0,types[6+i].size()+1));
				else
					values.push_back("-\n");
				getline(file,str);
			} 
			file2 << values[0] + values[1] + values[2] + values[3] + values[4] + values[5] + values[6] + values[7] + values[8] << endl;
			values.clear();
		}	
	}
	file2.close();
	return 0;
}