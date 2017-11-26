#include <iostream>
#include <ostream>
#include "SourcePirates.h"

using namespace std;
using json = nlohmann::json;

struct Cord {
    int x;
    int y;

    Cord(int x, int y) : x(x), y(y) {};

    Cord &operator=(const Cord &obj) {
        this->x = obj.x;
        this->y = obj.y;
        return *this;
    }

    Cord &operator=(const Coin &obj) {
        this->x = (unsigned int) obj.x;
        this->y = (unsigned int) obj.y;
        return *this;
    }

    Cord operator-(const Cord &obj) {
        Cord result(this->x - obj.x, this->y - obj.y);
        return result;
    }

    Cord operator+(const Cord &obj) {
        Cord result(this->x + obj.x, this->y + obj.y);
        return result;
    }

    bool operator==(const Cord &obj) {
        return (this->x == obj.x && this->y == obj.y);
    }

    bool operator==(const Coin &obj) {
        return (this->x == obj.x && this->y == obj.y);
    }

    bool operator!=(const Cord &obj) {
        return (this->x != obj.x || this->y != obj.y);
    }

    friend ostream &operator<<(ostream &stream, Cord &obj) {
        stream << obj.x << " : " << obj.y;
    }
};


vector<Cord> getNeighbours(array<array<int, 64>, 64> &map, Cord from) {
    vector<Cord> result;
    //cout << "GetNeighbours" << from.x << " : " << from.y << endl;
    //cout << "Map at : " << map->at(from.y).at(from.x) << endl;
    //cout << from.x << " : " << from.y << endl;

    if (map[from.x + 1][from.y] == 0) {
        result.emplace_back(Cord(from.x + 1, from.y));
    }
    if (map[from.x - 1][from.y] == 0) {
        result.emplace_back(Cord(from.x - 1, from.y));
    }
    if (map[from.x][from.y + 1] == 0) {
        result.emplace_back(Cord(from.x, from.y + 1));
    }
    if (map[from.x][from.y - 1] == 0) {
        result.emplace_back(Cord(from.x, from.y - 1));
    }
    if (map[from.x + 1][from.y + 1] == 0) {
        result.emplace_back(Cord(from.x + 1, from.y + 1));
    }
    if (map[from.x + 1][from.y - 1] == 0) {
        result.emplace_back(Cord(from.x + 1, from.y - 1));
    }
    if (map[from.x - 1][from.y + 1] == 0) {
        result.emplace_back(Cord(from.x - 1, from.y + 1));
    }
    if (map[from.x - 1][from.y - 1] == 0) {
        result.emplace_back(Cord(from.x - 1, from.y - 1));
    }

    return result;
}

struct Entry {
    int distance = -1;
    Cord cord = Cord(0, 0);
    Cord pre = Cord(-1, -1);
    bool marked = false;

    void setValues(Cord cord, bool marked = false) {
        this->cord = cord;
        this->marked = marked;
    }
};

void getPath(array<array<int, 64>, 64> &map, vector<Entry> &visited, vector<Coin> &coins, Cord cord, Cord &res, int lastSum = 0) {
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


    vector<Coin>::iterator it;
    auto check = coins.end();
    if(cord == Cord(42, 28)){
        cout << "Found" << endl;
    }
    for(it = coins.begin(); it != coins.end(); it++){
        if(cord == *it){
            res = *it;
        }
    }

    if(res == cord){
        return;
    }

    auto neighbours = getNeighbours(map, cord);
    if (neighbours.empty()) {
        return;
    };
    //cout << "Have Neighbors" << neighbours.size() << endl;
    for_each(neighbours.begin(), neighbours.end(), [&](const Cord &cords) {
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
    Cord min_cord(0, 0);
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
        getPath(map, visited, coins, min_cord, res, min_dis);
    }
}

vector<Cord> getPath(array<array<int, 64>, 64> map, vector<Coin> &coins, Cord from) {
    vector<Entry> visited(64 * 64);
    Cord res(0, 0);
    getPath(map, visited, coins, from, res);
    int i = 0;
    int y = 0;


    vector<Cord> result;
    if (visited[res.y * 64 + res.x].pre != (Cord(-1, -1))) {
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

void buildDrivePath(vector<Cord> Path, Cord myCords, int direct) {
    /*for (auto val : Path) {
        cout << val << ",";
    }
    cout << endl;
     */
    if (Path.empty()) {
        //cout << "Target erreicht" << endl;
        //cout << myCords.x << " : " << myCords.y << endl;
        return;
    }
    if (Path[0] == myCords) {
        //cout << "same cord" << endl;
        // Reached target
        Path.erase(Path.begin());
    } else {
        Cord difference = Path[0] - myCords;
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
            cout << "[forward]" << ",";
            myCords = myCords + difference;
            Path.erase(Path.begin());
        } else {
            for (auto val : dir) {
                if (val == -1) {
                    cout << "[left]" << ",";
                    direct--;
                } else {
                    cout << "[right]" << ",";
                    direct++;
                }
            }
            if (direct < 0) {
                direct = 8 - direct;
            } else if (direct > 7) {
                direct = direct % 8;
            }
            cout << "[forward]" << ",";
            myCords = myCords + difference;
            Path.erase(Path.begin());
        }
    }
    buildDrivePath(Path, myCords, direct);
}


int main() {
    SourcePirates gameObj("../test.json");
    auto map = gameObj.getMap();

    //auto coins = gameObj.specials.coins;
    Cord myCord(26, 24);
    /*for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64; j++) {
            if (i == 26 && j == 24) {
                cout << "X";
            } else {
                cout << map->at(j).at(i);
            }
        }
        cout << endl;
    }*/

    cout << gameObj.specials << endl;
    cout << gameObj.player << endl;
    cout << gameObj.players << endl;

    gameObj.actionFireCannon("right", 3);
    gameObj.executeOrders();
    //auto res = getPath(map, coins, myCord);

    //buildDrivePath(res, myCord, directionToInt("W"));

    return 0;
}
