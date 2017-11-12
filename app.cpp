#include <iostream>
#include <fstream>
#include <string>
#include "json.hpp"



using namespace std;
using json = nlohmann::json;

int main()
{
	string line;
	ifstream file("../test.json");

	json j;
	j << file;

	setw(4);

	for (auto it = j["player"].begin(); it != j["player"].end(); ++it)
	{
		std::cout  << it.key() << " | " << it.value() << "\n";
	}


	//cout << j << endl<< endl<< endl;
	return 0;
}
