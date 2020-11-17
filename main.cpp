#include <iostream>
#include <vector>
#include "strategy.h"
#include <memory>
using namespace std;

int main() {
    shared_ptr<strategy> p = make_shared<heap>();
    context method(p);

    vector<int> num = {5,1,6,7,9,3,9,9,2};
    method.run(num);
    for(int n : num) {
        std::cout << n << '\n';
    }
    return 0;
}