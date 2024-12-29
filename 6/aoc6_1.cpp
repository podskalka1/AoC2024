#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

vector<vector<char>> map;

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
    if(map.at(newY).at(newX) == '#'){
        return false;
    }
    return true;
}

void move(int &x, int &y, int dir){
    map.at(y).at(x) = 'X';
    x += deltaX(dir);
    y += deltaY(dir);
}

void rotate(int &dir){
    dir++;
    dir %= 4;
}



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
            map.at(line).push_back(ch);
        }
    }
    
    while(inBounds(x,y)){
        if(canMove(x,y,dir)){
            move(x,y,dir);
        }else{
            rotate(dir);
        }
    }
    
    int count = 0;
    for (auto line: map){
        for(auto pos: line){
            if(pos == 'X') count++;
        }
    }
    
    // cout<< "\nGuard is at " << x <<","<< y << "\n";

    for (const auto& linea: map) {
        for(char c:linea){
            cout << c;
        }
        cout << '\n';
    }
    
    cout << count << "\n";

    return 0;
}
