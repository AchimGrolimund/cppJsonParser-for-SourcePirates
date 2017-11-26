#ifndef SOURCEPIRATES_H
#define SOURCEPIRATES_H

#include <iostream>
#include <fstream>
#include "json.hpp"
#include <vector>
#include <array>
#include <ostream>

using json = nlohmann::json;

struct Param {
    std::string trigger;
    int value;
    Param() : value(0){};
};

struct EnemyParam{
    std::string id;
    int health;
    std::string name;
    std::string color;
    EnemyParam() : id(""), health(0), name(""), color(""){};
};

struct Coin {
    int x;
    int y;
    Coin(): x(0), y(0){};
    Coin(int pos_x, int pos_y) : x(pos_x), y(pos_y) {};
    friend std::ostream &operator<<(std::ostream &stream, Coin &obj){
        stream << "Coin: " << obj.x << " : " << obj.y;
        return stream;
    }
};

class Blocks : public Param {
public:
    int x;
    int y;
    Param param;
    Blocks(int x, int y, std::string trigger, int value) : x(x), y(y){
        param.trigger = trigger;
        param.value = value;
    };
    friend std::ostream &operator<<(std::ostream &stream, Blocks &obj){
        stream << "Param:" << std::endl;
        stream << "\t" << "Trigger: " << obj.param.trigger << std::endl;
        stream << "\t" << "Value: " << obj.param.value << std::endl;
        stream << "Position: " << std::endl;
        stream << "\t" << obj.x << " : " << obj.y << std::endl;
        return stream;
    }
};

struct Enemy : public EnemyParam{
    int x;
    int y;
    EnemyParam param;
    Enemy(int x, int y, std::string id, int health, std::string name, std::string color) : x(x), y(y){
        param.id = id;
        param.health = health;
        param.name = name;
        param.color = color;
    }
    friend std::ostream &operator<<(std::ostream &stream, Enemy &obj){
        stream << "Param: " << std::endl;
        stream << "\t" << "Id: " << obj.param.id << std::endl;
        stream << "\t" << "Health: " << obj.param.health << std::endl;
        stream << "\t" << "Name: " << obj.param.name << std::endl;
        stream << "\t" << "Color: " << obj.param.color << std::endl;
        stream << "Position: " << std::endl;
        stream << "\t" << obj.x << " : " << obj.y << std::endl;
        return stream;
    }
};

struct Specials {
    std::vector<Coin> coins;
    std::vector<Blocks> blocks;
    std::vector<Enemy> enemys;
    std::vector<Coin> start;
    std::vector<Coin> end;
    friend std::ostream &operator<<(std::ostream &stream, Specials &obj){
        int count = 0;
        stream << "Coins" << std::endl;
        stream << "===========" << std::endl;
        for(auto &val : obj.coins){
            stream << val << std::endl;
            count++;
        }
        stream << "===========" << std::endl;
        stream << "Blocks" << std::endl;
        stream << "===========" << std::endl;
        count = 0;
        for(auto &val : obj.blocks){
            stream << "Block: " << count << std::endl;
            stream << val << std::endl;
            count++;
        }
        stream << "===========" << std::endl;
        stream << "Enemys" << std::endl;
        stream << "===========" << std::endl;
        count = 0;
        for(auto &val : obj.enemys){
            stream << "Enemy: " << count << std::endl;
            stream << val << std::endl;
            count++;
        }
        stream << "===========" << std::endl;
        stream << "Start" << std::endl;
        for(auto &val : obj.start){
            stream << val.x << " : " << val.y << std::endl;
        }
        stream << "===========" << std::endl;
        stream << "End " << std::endl;
        for(auto &val : obj.end){
            stream << val.x << " : " << val.y << std::endl;
        }
        stream << "===========" << std::endl;

        return stream;
    }
};

struct Players {
    std::string id;
    std::string name;
    std::string color;
    int health;
    int loads;
    std::string direction;
    int x;
    int y;
    Players() : id(""), name(""), color(""), health(0), loads(0), direction(""), x(0), y(0){};
    Players(
            std::string id,
            std::string name,
            std::string color,
            int health,
            int loads,
            std::string direction,
            int x,
            int y
    ) :
            id(id),
            name(name),
            color(color),
            health(health),
            loads(loads),
            direction(direction),
            x(x),
            y(y)
    {};

    friend std::ostream &operator<<(std::ostream &stream, Players &obj){
        stream << "ID: " << obj.id << std::endl;
        stream << "Name: " << obj.name << std::endl;
        stream << "Color: " << obj.color << std::endl;
        stream << "Health: " << obj.health << std::endl;
        stream << "Loads: " << obj.loads << std::endl;
        stream << "Direction: " << obj.direction << std::endl;
        stream << "Position: " << obj.x << " : " << obj.y << std::endl;
        return stream;
    }
    friend std::ostream &operator<<(std::ostream &stream, std::vector<Players> &obj){
        stream << "Players" << std::endl;
        stream << "=====================" << std::endl;
        for(auto val : obj){
            stream << val;
        }
        stream << "=====================" << std::endl;
        return stream;
    }
};

struct Player : public Players{
    std::string lang;
    std::string executable;
    std::string iofolder;
    int score;
    bool qualified;
    std::string status;
    Player(){};

    Player(
            std::string &name,
            std::string &color,
            std::string &lang,
            std::string &executable,
            std::string &iofolder,
            int &score,
            bool &qualified,
            int &x,
            int &y,
            std::string &direction,
            std::string &status,
            std::string &id,
            int &health,
            int &loads
    ) :
            lang(lang),
            executable(executable),
            iofolder(iofolder),
            score(score),
            qualified(qualified),
            status(status)
    {
        this->name = name;
        this->color = color;
        this->direction = direction;
        this->id = id;
        this->health = health;
        this->loads = loads;
    }

    friend std::ostream &operator<<(std::ostream &stream, Player &obj){
        stream << "Player" << std::endl;
        stream << "=====================" << std::endl;
        stream << "Lang: " << obj.lang << std::endl;
        stream << "Executable: " << obj.executable << std::endl;
        stream << "Iofolder: " << obj.iofolder << std::endl;
        stream << "Score: " << obj.score << std::endl;
        stream << "Qualified: " << obj.qualified << std::endl;
        stream << "Status: " << obj.status << std::endl;
        stream << "ID: " << obj.id << std::endl;
        stream << "Name: " << obj.name << std::endl;
        stream << "Color: " << obj.color << std::endl;
        stream << "Health: " << obj.health << std::endl;
        stream << "Loads: " << obj.loads << std::endl;
        stream << "Direction: " << obj.direction << std::endl;
        stream << "Position: " << obj.x << " : " << obj.y << std::endl;
        stream << "=====================" << std::endl;
        return stream;
    }
};

class SourcePirates {
private:
    std::array<std::array<int, 64>, 64> arrMap;
public:
    int turn;
    explicit SourcePirates(std::string strIoFolder);
    std::array<std::array<int, 64>, 64> getMap() const;
    void printMap();
    int getMapFieldByCoords(int numX, int numY);
    Specials specials;
    Player player;
    std::vector<Players> players;
    int numTurn = 0;

    std::string arrLocalSession;
};

#endif // SOURCEPIRATES_H


