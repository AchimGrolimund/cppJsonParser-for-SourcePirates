//
// Created by Michel on 17.11.2017.
//

#include "SourcePirates.h"


/**
 * @brief SourcePirates::SourcePirates Read Json
 * @param strIoFolder Path to input.JSON
 */
SourcePirates::SourcePirates(std::string strIoFolder) {

    std::ifstream jsonFile(strIoFolder);
    json input;
    jsonFile >> input;
    turn = input["general"]["turn"];

    unsigned int x(0), y(0);
    for (auto val1 : input["map"]) {
        for (auto &val : val1) {
            arrMap[y][x] = val;
            y++;
        }
        x++;
        y = 0;
    }

    // Specials
    for (auto &val : input["specials"]["coin"]) {
        specials.coins.emplace_back(Coin(val["pos_x"], val["pos_y"]));
    }

    for (auto &val : input["specials"]["block"]) {
        specials.blocks.emplace_back(
                val["pos_x"],
                val["pos_y"],
                val["params"]["trigger"],
                val["params"]["value"]
        );
    }
    for(auto &enemy : input["specials"]["enemy"]){
        specials.enemys.emplace_back(
                enemy["pos_x"],
                enemy["pos_y"],
                enemy["params"]["id"],
                enemy["params"]["health"],
                enemy["params"]["name"],
                enemy["params"]["color"]
        );
    }

    for(auto &val : input["specials"]["start"]){
        specials.start.emplace_back(Coin(val["pos_x"], val["pos_y"]));
    }
    for(auto &val : input["specials"]["end"]){
        specials.end.emplace_back(Coin(val["pos_x"], val["pos_y"]));
    }


    player.name = input["player"]["name"];
    player.color = input["player"]["color"];
    player.lang = input["player"]["lang"];
    player.executable = input["player"]["executable"];
    player.iofolder = input["player"]["iofolder"];
    player.score = input["player"]["score"];
    player.qualified = input["player"]["qualified"];
    player.x = input["player"]["pos_x"];
    player.y = input["player"]["pos_y"];
    player.direction = input["player"]["direction"];
    player.status = input["player"]["status"];
    player.id = input["player"]["id"];

    for(auto ply : input["players"]){
    players.emplace_back(ply["id"], ply["name"], ply["color"], ply["health"], ply["loads"], ply["direction"], ply["pos_x"], ply["pos_y"]);
    }
}

/**
 *
 * @return
 */
std::array<std::array<int, 64>, 64> SourcePirates::getMap() const {
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
            std::cout << arrMap[i][j] << "";
        }
        std::cout << "\n";

    }
}

int SourcePirates::getMapFieldByCoords(int numX, int numY) {
    return arrMap[numY][numX];
}
