#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <unordered_set>

using namespace std;

struct position{
    char type;
    set<int> access_directions = {};
    
    char draw(){
        bool vert = access_directions.contains(0) || access_directions.contains(2);
        bool hori = access_directions.contains(1) || access_directions.contains(3);
        if(vert && hori) return '+';
        if(vert) return '|';
        if(hori) return '-';
        return type;
    }
};

struct coords{
    int x,y;
    
    bool operator==(const coords& other) const {
        return x == other.x && y == other.y;
    }
};

namespace std {
    template <>
    struct hash<coords> {
        size_t operator()(const coords& c) const {
            // Combine hashes of x and y (simple example)
            return std::hash<int>()(c.x) ^ (std::hash<int>()(c.y) << 1);
        }
    };
}

vector<vector<position>> map;

bool inBounds(int x, int y){
    if (x < 0 || y < 0 || x >= map.at(0).size() || y >= map.size()){
        return false;
    }
    return true;
}

int deltaX(int dir){
    switch (dir){
    case 1:
        return 1;
    case 3:
        return -1;
    default:
        return 0;
    }
}

int deltaY(int dir){
    switch (dir){
    case 0:
        return -1;
    case 2:
        return 1;
    default:
        return 0;
    }
}

bool canMove(int x, int y, int dir){
    int newX = x + deltaX(dir);
    int newY = y + deltaY(dir);
    if(!inBounds(newX,newY)){
        return true;
    }
    if(map.at(newY).at(newX).type == '#'){
        return false;
    }
    return true;
}

bool move(int &x, int &y, int dir){   // može byť treba zmeniť poradie ak bude robiť bordel
    if(map.at(y).at(x).access_directions.contains(dir)) return true;
    map.at(y).at(x).access_directions.insert(dir);
    x += deltaX(dir);
    y += deltaY(dir);
    return false;
}

void rotate(int &dir){
    dir++;
    dir %= 4;
}

/*
battleplan:
    turn polička into structs 
        wait no, sets of direction are enough. I don't really need to include...
            wait no, I need to check whether they are block and in that case I can as well make them structs
                oof, this will basically make this shit n^4 in worst case...


 */


int main() {
    
    ifstream file("input.txt");

    map.emplace_back();
    
    int x,y;
    int dir = 0;
    
    char ch;
    int line = 0;
    while(file.get(ch)){
        if(ch=='\n'){
            map.emplace_back();
            line++;
        }else {
            if(ch=='^'){
                ch = '.';
                x = map.at(line).size();
                y = map.size()-1;
            }
            map.at(line).push_back({ch,{}});
        }
    }
    
    int xBackUp = x;
    int yBackUp = y;
    vector<vector<position>> mapBackUp = map;
    unordered_set<coords> visited_locations;
    
    while(inBounds(x,y)){
        if(canMove(x,y,dir)){
            visited_locations.insert({x,y});
            move(x,y,dir);
        }else{
            map.at(y).at(x).access_directions.insert(dir);
            rotate(dir);
        }
    }
    
    
    int i = 0;
    int count = 0;
    for(auto loc: visited_locations){
        // cout << i++ <<": "<< loc.x <<" " << loc.y << endl;
        map = mapBackUp;
        x = xBackUp;
        y = yBackUp;
        dir = 0;
        map.at(loc.y).at(loc.x).type='#';
        
        //if(loc.x!=xBackUp&&loc.y!=yBackUp){
            while(inBounds(x,y)){
                if(canMove(x,y,dir)){
                    if(move(x,y,dir)){
                        count++;
                        // cout << "loop\n";
                        break;
                    }//45236
                }else{
                    map.at(y).at(x).access_directions.insert(dir);
                    rotate(dir);
                }
            }
            // for (const auto& linea: map) {
            //     for(auto c:linea){
            //         cout << c.draw();
            //     }
            //     cout << '\n';
            // }
            // cout << "\n";
        //}
    }
    
    // 
    // for (auto line: map){
    //     for(auto pos: line){
    //         if(pos.access_directions.size() > 0) count++;
    //     }
    // }
    
    // cout<< "\nGuard is at " << x <<","<< y << "\n";
    
    // for (const auto& linea: map) {
    //     for(auto c:linea){
    //         cout << c.draw();
    //     }
    //     cout << '\n';
    // }
    cout << count << "\n";
    
    
    return 0;
}
