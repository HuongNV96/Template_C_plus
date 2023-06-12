#include "SingletonTemplate.hpp"
#include <iostream>
class Test {
private :
    int a;
public :
    void setA(int a) { this->a = a; }
    int getA() { return a; }
};

int main() {
   auto singleton = SingletonTemplate<Test>::getInstance();
   singleton.setA(4);
   std::cout << singleton.getA() << std::endl;
}