#include <iostream>
#include "SourcePirates.h"

using namespace std;
using json = nlohmann::json;

int main() {
    SourcePirates gameObj("");

    cout << gameObj.arrMap->at(32).at(32) << endl;
    return 0;
}
