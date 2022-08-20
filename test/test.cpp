#include "../encoding.h"
#include <iostream>

int main(void) {
    int val;
    std::cin >> val;
    std::string s = Encoding::encode(val);
    std::cout << Encoding::decode(s);
    return 0;
}