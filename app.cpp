#include <iostream>
#include "SourcePirates.h"

using namespace std;
using json = nlohmann::json;

int main() {
	SourcePirates gameObj("");


	//cout << gameObj.arrMap->at(32).at(32) << endl;

	for(int i(0); i<64;i++){
		cout<<i<<"\t";
		for(int j(0);j<64;j++){
			cout<<gameObj.arrMap->at(i).at(j)<<"";
		}
				   cout<<"\n";

		}
		return 0;
	}
