#include <iostream>
#include <ostream>
#include "SourcePirates.h"
#include <string>

using namespace std;
using json = nlohmann::json;

struct Cords {
    int x;
    int y;

    Cords(int x, int y) : x(x), y(y) {};

    Cords &operator=(const Cords &obj) {
        this->x = obj.x;
        this->y = obj.y;
        return *this;
    }

    Cords &operator=(const Cord &obj) {
        this->x = (unsigned int) obj.x;
        this->y = (unsigned int) obj.y;
        return *this;
    }

    Cords operator-(const Cords &obj) {
        Cords result(this->x - obj.x, this->y - obj.y);
        return result;
    }

    Cords operator-(const Cord &obj) {
        Cords result(this->x - obj.x, this->y - obj.y);
        return result;
    }

    Cords operator+(const Cords &obj) {
        Cords result(this->x + obj.x, this->y + obj.y);
        return result;
    }

    bool operator==(const Cords &obj) {
        return (this->x == obj.x && this->y == obj.y);
    }

    bool operator==(const Cord &obj) {
        return (this->x == obj.x && this->y == obj.y);
    }

    bool operator!=(const Cords &obj) {
        return (this->x != obj.x || this->y != obj.y);
    }

    friend ostream &operator<<(ostream &stream, Cords &obj) {
        stream << obj.x << " : " << obj.y;
    }
};


vector<Cords> getNeighbours(array<array<int, 64>, 64> &map, Cords from) {
    vector<Cords> result;
    //cout << "GetNeighbours" << from.x << " : " << from.y << endl;
    //cout << "Map at : " << map->at(from.y).at(from.x) << endl;
    //cout << from.x << " : " << from.y << endl;

    if (map[from.x + 1][from.y] == 0) {
        result.emplace_back(Cords(from.x + 1, from.y));
    }
    if (map[from.x - 1][from.y] == 0) {
        result.emplace_back(Cords(from.x - 1, from.y));
    }
    if (map[from.x][from.y + 1] == 0) {
        result.emplace_back(Cords(from.x, from.y + 1));
    }
    if (map[from.x][from.y - 1] == 0) {
        result.emplace_back(Cords(from.x, from.y - 1));
    }
    if (map[from.x + 1][from.y + 1] == 0 && map[from.x + 1][from.y] == 0 && map[from.x][from.y + 1] == 0) {
        result.emplace_back(Cords(from.x + 1, from.y + 1));
    }
    if (map[from.x + 1][from.y - 1] == 0&& map[from.x + 1][from.y] == 0 && map[from.x][from.y - 1] == 0) {
        result.emplace_back(Cords(from.x + 1, from.y - 1));
    }
    if (map[from.x - 1][from.y + 1] == 0 && map[from.x - 1][from.y] == 0 && map[from.x][from.y + 1] == 0) {
        result.emplace_back(Cords(from.x - 1, from.y + 1));
    }
    if (map[from.x - 1][from.y - 1] == 0 && map[from.x - 1][from.y] == 0 && map[from.x][from.y - 1] == 0) {
        result.emplace_back(Cords(from.x - 1, from.y - 1));
    }

    return result;
}

struct Entry {
    int distance = -1;
    Cords cord = Cords(0, 0);
    Cords pre = Cords(-1, -1);
    bool marked = false;

    void setValues(Cords cord, bool marked = false) {
        this->cord = cord;
        this->marked = marked;
    }
};

void getPath(array<array<int, 64>, 64> &map, vector<Entry> &visited, vector<Cord> &coins, vector<Cords> &visitedCoins, Cords cord, Cords &res, int lastSum = 0) {
    //cout << "GetPath 1 => " << cord.x << " : " << cord.y << endl;
    int i = 0;

    /*
    for(auto val : visited){
        i++;
        if(i == 64){
            cout << endl;
            i = 0;
        }
        cout << val.marked;
    }
    cout << endl;
    */
    visited[64 * cord.y + cord.x].setValues(cord, true);
    visited[64 * cord.y + cord.x].distance = lastSum;


    vector<Cord>::iterator it;
    vector<Cords>::iterator it2;
    auto check = coins.end();
    it2 = find(visitedCoins.begin(), visitedCoins.end(), cord);
    if (it2 == visitedCoins.end()) {
        for (it = coins.begin(); it != coins.end(); it++) {
            if (cord == *it) {
                res = *it;
                return;
            }
        }
    }

    if (res == cord) {
        return;
    }


    auto neighbours = getNeighbours(map, cord);
    if (neighbours.empty()) {
        return;
    };
    //cout << "Have Neighbors" << neighbours.size() << endl;
    for_each(neighbours.begin(), neighbours.end(), [&](const Cords &cords) {
        if (!visited[64 * cords.y + cords.x].marked) {
            if (visited[64 * cords.y + cords.x].distance == -1) {
                visited[64 * cords.y + cords.x].distance = lastSum + 1;
                visited[64 * cords.y + cords.x].pre = cord;
                visited[64 * cords.y + cords.x].cord = cords;
            } else {
                if (lastSum + 1 < visited[64 * cords.y + cords.x].distance) {
                    visited[64 * cords.y + cords.x].distance = lastSum + 1;
                    visited[64 * cords.y + cords.x].pre = cord;
                }
            }
        }
    });

    int min_dis = 0;
    bool first = true;
    Cords min_cord(0, 0);
    for_each(visited.begin(), visited.end(), [&first, &min_dis, &min_cord](const Entry &obj) {
        if (first && obj.distance != -1 && !obj.marked) {
            //cout << "First : " << obj.cord.x << " : " << obj.cord.y << endl;
            min_dis = obj.distance;
            min_cord = obj.cord;
            first = false;
        } else if (obj.distance < min_dis && obj.distance != -1 && !obj.marked) {
            //cout << "second : " << obj.cord.x << " : " << obj.cord.y << endl;
            min_dis = obj.distance;
            min_cord = obj.cord;
        }
    });
    //cout << min_cord.x << " : " << min_cord.y << endl;
    if (min_dis != 0) {
        //cout << "Get Path => Min: " << min_dis << " : " << min_cord.x << " - " << min_cord.y << endl;
        if (min_cord.x == 0 || min_cord.y == 0) return;
        getPath(map, visited, coins, visitedCoins, min_cord, res, min_dis);
    }

}

vector<Cords> getPath(array<array<int, 64>, 64> map, vector<Cord> &coins, vector<Cords> &visitedCoins, Cords from) {
    vector<Entry> visited(64 * 64);
    Cords start = from;
    Cords res(0, 0);
    getPath(map, visited, coins, visitedCoins, from, res);
    int i = 0;
    int y = 0;

    /*
    for (int x = 0; x < 64; x++) {
        for (int j = 0; j < 64; j++) {
            if (x == res.y && res.x == j) {
                cout << "X";
            } else if (x == from.y && j == from.x) {
                cout << "X";
            } else {
                cout << visited[64 * x + j].marked;
            }
        }
        cout << endl;
    }*/


    vector<Cords> result;
    if (visited[res.y * 64 + res.x].pre != (Cords(-1, -1))) {
        while (res != from) {
            result.push_back(res);
            res = visited[64 * res.y + res.x].pre;
        }
        result.push_back(from);
        reverse(result.begin(), result.end());
    }
    return result;
}

int directionToInt(string direction) {
    if (direction == "N") return 0;
    if (direction == "NE") return 1;
    if (direction == "E") return 2;
    if (direction == "SE") return 3;
    if (direction == "S") return 4;
    if (direction == "SW") return 5;
    if (direction == "W") return 6;
    return 7;
}

vector<int> changeDirection(int start, int target) {
    vector<int> res;
    int offset = (start - 4) * -1;
    start += offset;
    target += offset;
    if (target < 0) {
        target = 8 + target;
    }
    if (target > 7) {
        target = target % 8;
    }
    int result = start - target;
    int direction = result < 0 ? 1 : -1;
    if (result < 0) result *= -1;
    for (int i = 0; i < result; i++) {
        res.push_back(direction);
    }
    return res;
}

void buildDrivePath(vector<Cords> Path, Cords myCords, int direct, json &output, vector<Cords> &visitedCoins) {
    /*for (auto val : Path) {
        cout << val << ",";
    }
    cout << endl;
     */
    if (Path.empty()) {
        //cout << "Target erreicht" << endl;
        //cout << myCordss.x << " : " << myCordss.y << endl;
        return;
    }
    if (myCords == Path[0]) {
        //cout << "same cord" << endl;
        // Reached target
        Path.erase(Path.begin());
    } else {
        Cords difference = Path[0] - myCords;
        string target;
        if (difference.x == 1 && difference.y == 0) {
            // Move to east
            target = "E";
        } else if (difference.x == 1 && difference.y == 1) {
            // Move to south east
            target = "SE";
        } else if (difference.x == 0 && difference.y == 1) {
            // Move to south
            target = "S";
        } else if (difference.x == -1 && difference.y == 1) {
            // Move to south west
            target = "SW";
        } else if (difference.x == -1 && difference.y == 0) {
            // Move to west
            target = "W";
        } else if (difference.x == -1 && difference.y == -1) {
            // Move to north west
            target = "NW";
        } else if (difference.x == 0 && difference.y == -1) {
            // Move to north
            target = "N";
        } else if (difference.x == 1 && difference.y == -1) {
            // Move to north east
            target = "NE";
        }
        vector<int> dir = changeDirection(direct, directionToInt(target));
        if (dir.empty()) {
            output.push_back("f");
            cout << "[forward]" << ",";
            myCords = myCords + difference;
            Path.erase(Path.begin());
        } else {
            for (auto val : dir) {
                if (val == -1) {
                    output.push_back("l");
                    cout << "[left]" << ",";
                    direct--;
                } else {
                    output.push_back("r");
                    cout << "[right]" << ",";
                    direct++;
                }
            }
            if (direct < 0) {
                direct = 8 - direct;
            } else if (direct > 7) {
                direct = direct % 8;
            }
            output.push_back("f");
            cout << "[forward]" << ",";
            myCords = myCords + difference;
            Path.erase(Path.begin());
        }
    }
    buildDrivePath(Path, myCords, direct, output, visitedCoins);
}


int main() {
    bool debug = false;
    string inputPath = "../Wrapper/PHP/io/input.json";
    string outputPath = "../Wrapper/PHP/cheat.json";
    string tempPath = "../Wrapper/PHP/temp.json";
    if (debug) {
        inputPath = "../test1.json";
        outputPath = "../cheat.json";
        tempPath = "../temp.json";
    }


    SourcePirates gameObj(inputPath);
    auto map = gameObj.getMap();

    vector<Cords> visitedCoins;
    ifstream inp(tempPath);
    json j;
    inp >> j;
    for (auto &val : j) {
        cout << val << endl;
        visitedCoins.emplace_back(Cords(val["x"], val["y"]));
    }


    //auto coins = gameObj.specials.coins;
    Cords myCords(0, 0);
    auto me = gameObj.getMyPlayer();
    auto specials = gameObj.getSpecials();
    myCords.x = me.x;
    myCords.y = me.y;
    string dir = me.direction;
    auto coins = specials.coins;

    /*
    for (int i = 0; i < 64; i++) {
        cout << setw(3) << i << ": ";
        for (int j = 0; j < 64; j++) {
            if (i == 26 && j == 31) {
                cout << "X";
            } else {
                cout << map[j][i];
            }
        }
        cout << endl;
    }*/

    //cout << gameObj.specials << endl;
    //cout << gameObj.player << endl;
    //cout << gameObj.players << endl;
    auto res = getPath(map, coins, visitedCoins, myCords);
    if(res.empty()){
        visitedCoins.push_back(myCords);
    }

    json result = R"([])"_json;
    buildDrivePath(res, myCords, directionToInt(dir), result, visitedCoins);
    std::ofstream out2(outputPath);
    out2 << result << endl;

    json temp = R"([])"_json;
    json temp2;
    for (auto val : visitedCoins) {
        temp2["x"] = val.x;
        temp2["y"] = val.y;
        temp.push_back(temp2);
    }
    std::ofstream out1(tempPath);
    out1 << temp << endl;

    return 0;
}
