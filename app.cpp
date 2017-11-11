#include <iostream>
#include <fstream>
#include "json.hpp"



using namespace std;
using json = nlohmann::json;

int main()
{

	ifstream file("test.json");

	json j;
	j << file;




	cout << j << endl;
	return 0;
}
