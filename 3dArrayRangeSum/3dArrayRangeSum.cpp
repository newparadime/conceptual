#include <cmath>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cstddef>
#include <limits>

template<class T>
class Cube {
public:
    Cube() { }
    void append(int x, int y, int z, T v) {
        map[x][y][z] = v;
    }
    T sum(int x1, int y1, int z1, int x2, int y2, int z2) {
        T sum = 0;
        for (auto xit = map.lower_bound(x1); xit != map.upper_bound(x2); ++xit) {
            auto yz = xit->second;
            for (auto yit = yz.lower_bound(y1); yit != yz.upper_bound(y2); ++yit) {
                auto z = yit->second;
                for (auto zit = z.lower_bound(z1); zit != z.upper_bound(z2); ++zit) {
                    sum += zit->second;
                }
            }
        }
        return sum;
    }
private:
    std::map<int, std::map<int, std::map<int, T>>> map;
};

void cubeRange() {
    int n, m;
    std::cin >> n >> m;
    std::string op;
    int x1,y1,z1,x2,y2,z2;
    long long v;
    Cube<long long> cube;
    while(m--) {
        std::cin >> op;
        if (op == "UPDATE") {
            std::cin >> x1 >> y1 >> z1 >> v;
            cube.append(x1,y1,z1,v);
        }
        else {
            std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
            std::cout << cube.sum(x1,y1,z1,x2,y2,z2) << std::endl;
        }
    }
}



int main() {
    int runs;
    std::cin >> runs;
    while(runs--) cubeRange();
    return 0;
}
