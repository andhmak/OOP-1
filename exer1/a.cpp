#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

class Student {
    string name;
};

int main(int argc, char* argv[]) {
    if (argc != 5) {
        cerr << "Wrong number of arguments" << endl;
        return 1;
    }
    return 0;
}