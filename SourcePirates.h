#ifndef SOURCEPIRATES_H
#define SOURCEPIRATES_H

#include <iostream>
#include <fstream>
#include "json.hpp"
#include <vector>

using json = nlohmann::json;

class SourcePirates {
public:
    explicit SourcePirates(std::string strIoFolder);

    int **getMap() {};

    int getMapFieldByCoords(int numX, int numY) {};
    int numTurn = 0;
    std::string arrPlayer;
    std::string arrPlayers;
    std::vector<std::vector<int>> *arrMap;
    std::string arrSpecials;
    std::string strIoFolder;
    std::string arrOutput;
    std::string arrLocalSession;

};

#endif // SOURCEPIRATES_H


SourcePirates::SourcePirates(std::string strIoFolder) {

    std::ifstream jsonFile("../test.json");
    json input;
    jsonFile >> input;


    //Create Map Array
    arrMap = new std::vector<std::vector<int>>(64, std::vector<int>(64));
    //Fill vector vector matrix => map
    int x(0), y(0);
    for (auto val1 : input["map"]) {
        for (auto val : val1) {
            arrMap->at(x).at(y) = val;
            y++;
        }
        x++;
        y = 0;
    }
};
