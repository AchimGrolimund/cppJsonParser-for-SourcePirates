#ifndef SOURCEPIRATES_H
#define SOURCEPIRATES_H

#include <iostream>
#include <fstream>
#include "json.hpp"
#include <vector>
#include <array>
#include <ostream>
#include <utility>

using json = nlohmann::json;

/**
 * Parameter struct with "trigger" and "value"
 */
struct Param {
    std::string trigger;
    int value;
    Param() : value(0) {};
};

/**
 * EnemyParam struct for params of enemys
 */
struct EnemyParam {
    std::string id;
    int health;
    std::string name;
    std::string color;
    EnemyParam();
};

/**
 * Struct to save coordinats;
 */
struct Cord {
    int x;
    int y;
    Cord() : x(0), y(0) {};
    Cord(int pos_x, int pos_y);
    friend std::ostream &operator<<(std::ostream &stream, Cord &obj);
};

/**
 * Struct to Save the blocks
 */
class Blocks : public Param {
public:
    int x;
    int y;
    Param param;
    Blocks(int x, int y, std::string trigger, int value);
    friend std::ostream &operator<<(std::ostream &stream, Blocks &obj);
};

/**
 * Struct to save Enemys
 */
struct Enemy : public EnemyParam {
    int x;
    int y;
    EnemyParam param;
    Enemy(int x, int y, std::string id, int health, std::string name, std::string color);
    friend std::ostream &operator<<(std::ostream &stream, Enemy &obj);
};

/**
 * Struct with all specials inside
 */
struct Specials {
    std::vector<Cord> coins;
    std::vector<Blocks> blocks;
    std::vector<Enemy> enemys;
    std::vector<Cord> start;
    std::vector<Cord> end;
    friend std::ostream &operator<<(std::ostream &stream, Specials &obj);
};

/**
 * Player struct -> same for player and players
 */
struct Player {
    std::string id;
    std::string name;
    std::string color;
    int health;
    int loads;
    std::string direction;
    int x;
    int y;
    Player();
    Player(std::string id, std::string name, std::string color, int health, int loads, std::string direction, int x, int y);
    friend std::ostream &operator<<(std::ostream &stream, Player &obj);
    friend std::ostream &operator<<(std::ostream &stream, std::vector<Player> &obj);
};

/**
 * SourcePirates Class
 */
class SourcePirates {
private:
    json arrOutput;
    std::array<std::array<int, 64>, 64> arrMap;
    int turn;
    Player player;
    std::vector<Player> players;
    std::string arrLocalSession;
    Specials specials;
    void writeOutputFile() ;
public:

    explicit SourcePirates(std::string strIoFolder);

    std::array<std::array<int, 64>, 64> getMap() const;

    void printMap();

    int getMapFieldByCoords(int numX, int numY);

    int numTurn = 0;

    std::vector<Player> getPlayers() ;

    Player getPlayer(std::string id) ;

    Player getPlayerByCoords(int x, int y) ;

    Player getMyPlayer() ;

    Specials getSpecials() ;

    std::vector<Cord> getCoins() ;

    std::vector<Blocks> getBlocks() ;

    std::vector<Enemy> getEnemys() ;

    std::vector<Cord> getStarts() ;

    std::vector<Cord> getEnds() ;

    void actionMoveForward() ;

    void actionMoveBackwards() ;

    void actionTurnLeft() ;

    void actionTurnRight() ;

    void actionLoadCanon() ;

    void actionFireCannon(std::string direction, int power) ;

    void executeOrders() ;
};

#endif // SOURCEPIRATES_H


