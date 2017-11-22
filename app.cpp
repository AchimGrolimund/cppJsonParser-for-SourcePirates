#include <iostream>
#include "SourcePirates.h"

using namespace std;
using json = nlohmann::json;

int main() {
	SourcePirates gameObj("../test.json");


	//cout << gameObj.arrMap->at(32).at(32) << endl;

	gameObj.printMap();

	return 0;
}
