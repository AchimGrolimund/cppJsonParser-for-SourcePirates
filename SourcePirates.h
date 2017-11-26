#ifndef SOURCEPIRATES_H
#define SOURCEPIRATES_H

#include <iostream>
#include <fstream>
#include "json.hpp"
#include <vector>

using json = nlohmann::json;


struct Coin {
    int pos_x;
    int pos_y;

    Coin(int pos_x, int pos_y) : pos_x(pos_x), pos_y(pos_y) {};
};

struct Specials {
    std::vector<Coin> coins;
};


class SourcePirates {
private:

public:

    explicit SourcePirates(std::string strIoFolder);

    //int getMapFieldByCoords(int numX, int numY);
    Specials specials;
    int numTurn = 0;

    std::vector<std::vector<int>> *arrMap;

    std::vector<std::vector<int>> *getMap();

    std::string arrPlayer;
    std::string arrPlayers;
    std::string arrSpecials;
    std::string strIoFolder;
    std::string arrOutput;
    std::string arrLocalSession;

    void printMap();

};

#endif // SOURCEPIRATES_H


/**
 * @brief SourcePirates::SourcePirates Read Json
 * @param strIoFolder Path to input.JSON
 */
SourcePirates::SourcePirates(std::string strIoFolder) {

    std::ifstream jsonFile(strIoFolder);
    json input;
    jsonFile >> input;

    //Create Map Array
    // 0 = Frei // 1 = Gesperrt
    arrMap = new std::vector<std::vector<int>>(64, std::vector<int>(64));
    //Fill vector vector matrix => map
    unsigned int x(0), y(0);
    for (auto val1 : input["map"]) {
        for (auto val : val1) {
            arrMap->at(y).at(x) = val;
            y++;
        }
        x++;
        y = 0;
    }

    // Specials
    for (auto val : input["specials"]["coin"]) {
        specials.coins.emplace_back(Coin(val["pos_x"], val["pos_y"]));
    }
}

/**
 * @brief SourcePirates::getMap Return Map Matrix
 * @return vector<vector<int>>
 */
std::vector<std::vector<int>> *SourcePirates::getMap() {
    return arrMap;
}

/**
 * @brief SourcePirates::printMap
 * @brief Print Map into Console
 */
void SourcePirates::printMap() {
    for (unsigned int i(0); i < 64; i++) {
        std::cout << i << "\t";
        for (unsigned int j(0); j < 64; j++) {
            std::cout << arrMap->at(i).at(j) << "";
        }
        std::cout << "\n";

    }
}
