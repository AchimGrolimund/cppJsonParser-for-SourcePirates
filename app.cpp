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

//	if (file.is_open())
//	  {
//		while ( getline (file,line) )
//		{
//		  cout << line << '\n';
//		}
//		file.close();
//	  }
//	  else cout << "Unable to open file";
//	return 0;


	json j;
	j << file;




	cout << j << endl<< endl<< endl;
	return 0;
}
