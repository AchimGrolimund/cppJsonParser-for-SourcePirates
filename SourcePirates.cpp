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
    std::string x_str = "";
    std::string y_str = "";
    for (auto &val1 : input["map"]) {
        x_str = std::to_string(x);
        for (auto &val : val1) {
            y_str = std::to_string(y);
            arrMap[y][x] = input["map"][y_str][x];
            y++;
        }
        x++;
        y = 0;
    }

    // Specials
    for (auto &val : input["specials"]["coin"]) {
        specials.coins.emplace_back(Cord(val["pos_x"], val["pos_y"]));
    }

    for (auto &val : input["specials"]["block"]) {
        specials.blocks.emplace_back(
                val["pos_x"],
                val["pos_y"],
                val["params"]["trigger"],
                val["params"]["value"]
        );
    }
    for (auto &enemy : input["specials"]["enemy"]) {
        specials.enemys.emplace_back(
                enemy["pos_x"],
                enemy["pos_y"],
                enemy["params"]["id"],
                enemy["params"]["health"],
                enemy["params"]["name"],
                enemy["params"]["color"]
        );
    }

    for (auto &val : input["specials"]["start"]) {
        specials.start.emplace_back(Cord(val["pos_x"], val["pos_y"]));
    }
    for (auto &val : input["specials"]["end"]) {
        specials.end.emplace_back(Cord(val["pos_x"], val["pos_y"]));
    }

/*
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
*/


    player.name = input["player"]["name"];
    player.color = input["player"]["color"];
    player.x = input["player"]["pos_x"];
    player.y = input["player"]["pos_y"];
    player.direction = input["player"]["direction"];
    player.id = input["player"]["id"];

    for (auto &ply : input["players"]) {
        players.emplace_back(ply["id"], ply["name"], ply["color"], ply["health"], ply["loads"], ply["direction"], ply["pos_x"], ply["pos_y"]);
    }
}

std::vector<Player> SourcePirates::getPlayers() {
    return players;
}

Player SourcePirates::getPlayer(std::string id) {
    for (auto &val : players) {
        if (val.id == id) {
            return val;
        }
    }
    return Player();
}

Player SourcePirates::getPlayerByCoords(int x, int y) {
    for (auto &val : players) {
        if (val.x == x && val.y == y) {
            return val;
        }
    }
    return Player();
}

Player SourcePirates::getMyPlayer() {
    return player;
}

Specials SourcePirates::getSpecials() {
    return specials;
}

std::vector<Cord> SourcePirates::getCoins() {
    return specials.coins;
}

std::vector<Blocks> SourcePirates::getBlocks() {
    return specials.blocks;
}

std::vector<Enemy> SourcePirates::getEnemys() {
    return specials.enemys;
}

std::vector<Cord> SourcePirates::getStarts() {
    return specials.start;
}

std::vector<Cord> SourcePirates::getEnds() {
    return specials.end;
}

void SourcePirates::actionMoveForward() {
    this->arrOutput["order"] = "MOVE_FORWARDS";
}

void SourcePirates::actionMoveBackwards() {
    this->arrOutput["order"] = "MOVE_BACKWARDS";
}

void SourcePirates::actionTurnLeft() {
    this->arrOutput["order"] = "TURN_LEFT";
}

void SourcePirates::actionTurnRight() {
    this->arrOutput["order"] = "TURN_RIGHT";
}

void SourcePirates::actionLoadCanon() {
    this->arrOutput["order"] = "LOAD_CANON";
}

void SourcePirates::actionFireCannon(std::string direction, int power) {
    if (direction == "left" || direction == "right") {
        if (power > 0 && power < 6) {
            auto jOut = R"(
                    {
                        "ORDER" : {
                            "FIRE_CANNON" : {
                                "cannon" : "right",
                                "power" : 1
                            }
                        }
                    }
                )"_json;
            jOut["ORDER"]["FIRE_CANNON"]["cannon"] = direction;
            jOut["ORDER"]["FIRE_CANNON"]["power"] = power;
            this->arrOutput = jOut;
        }
    }
}

void SourcePirates::executeOrders() {
    writeOutputFile();
}

void SourcePirates::writeOutputFile() {
    std::ofstream str("output.json");
    str << this->arrOutput;
}


EnemyParam::EnemyParam() : id(""), health(0), name(""), color("") {};

Cord::Cord(int pos_x, int pos_y) : x(pos_x), y(pos_y) {};

Blocks::Blocks(int x, int y, std::string trigger, int value) : x(x), y(y) {
    param.trigger = trigger;
    param.value = value;
};

Enemy::Enemy(int x, int y, std::string id, int health, std::string name, std::string color) : x(x), y(y) {
    param.id = id;
    param.health = health;
    param.name = name;
    param.color = color;
}

Player::Player() : id(""), name(""), color(""), health(0), loads(0), direction(""), x(0), y(0) {};

Player::Player(std::string id, std::string name, std::string color, int health, int loads, std::string direction, int x, int y) :
        id(id),
        name(name),
        color(color),
        health(health),
        loads(loads),
        direction(direction),
        x(x),
        y(y) {};


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


std::ostream &operator<<(std::ostream &stream, Cord &obj) {
    stream << "Cord: " << obj.x << " : " << obj.y;
    return stream;
}

std::ostream &operator<<(std::ostream &stream, Blocks &obj) {
    stream << "Param:" << std::endl;
    stream << "\t" << "Trigger: " << obj.param.trigger << std::endl;
    stream << "\t" << "Value: " << obj.param.value << std::endl;
    stream << "Position: " << std::endl;
    stream << "\t" << obj.x << " : " << obj.y << std::endl;
    return stream;
}

std::ostream &operator<<(std::ostream &stream, Enemy &obj) {
    stream << "Param: " << std::endl;
    stream << "\t" << "Id: " << obj.param.id << std::endl;
    stream << "\t" << "Health: " << obj.param.health << std::endl;
    stream << "\t" << "Name: " << obj.param.name << std::endl;
    stream << "\t" << "Color: " << obj.param.color << std::endl;
    stream << "Position: " << std::endl;
    stream << "\t" << obj.x << " : " << obj.y << std::endl;
    return stream;
}

std::ostream &operator<<(std::ostream &stream, Specials &obj) {
    int count = 0;
    stream << "Coins" << std::endl;
    stream << "===========" << std::endl;
    for (auto &val : obj.coins) {
        stream << val << std::endl;
        count++;
    }
    stream << "===========" << std::endl;
    stream << "Blocks" << std::endl;
    stream << "===========" << std::endl;
    count = 0;
    for (auto &val : obj.blocks) {
        stream << "Block: " << count << std::endl;
        stream << val << std::endl;
        count++;
    }
    stream << "===========" << std::endl;
    stream << "Enemys" << std::endl;
    stream << "===========" << std::endl;
    count = 0;
    for (auto &val : obj.enemys) {
        stream << "Enemy: " << count << std::endl;
        stream << val << std::endl;
        count++;
    }
    stream << "===========" << std::endl;
    stream << "Start" << std::endl;
    for (auto &val : obj.start) {
        stream << val.x << " : " << val.y << std::endl;
    }
    stream << "===========" << std::endl;
    stream << "End " << std::endl;
    for (auto &val : obj.end) {
        stream << val.x << " : " << val.y << std::endl;
    }
    stream << "===========" << std::endl;

    return stream;
}

std::ostream &operator<<(std::ostream &stream, Player &obj) {
    stream << "ID: " << obj.id << std::endl;
    stream << "Name: " << obj.name << std::endl;
    stream << "Color: " << obj.color << std::endl;
    stream << "Health: " << obj.health << std::endl;
    stream << "Loads: " << obj.loads << std::endl;
    stream << "Direction: " << obj.direction << std::endl;
    stream << "Position: " << obj.x << " : " << obj.y << std::endl;
    return stream;
}

std::ostream &operator<<(std::ostream &stream, std::vector<Player> &obj) {
    stream << "Players" << std::endl;
    stream << "=====================" << std::endl;
    for (auto val : obj) {
        stream << val;
    }
    stream << "=====================" << std::endl;
    return stream;
}