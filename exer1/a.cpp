#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

class Class {
    int capacity;
    int student_num;
    public:
        Class(int init_capacity) : capacity(init_capacity) {
            cout << "A New Class has been created!" << endl;
        }
};

class Corridor {
    int capacity;
    int student_num;
    public:
        Corridor(int init_capacity) : capacity(init_capacity) {
            cout << "A New Corridor has been created!" << endl;
        }
};

class Yard {
    int capacity;
    int student_num;
    public:
        Yard(int init_capacity) : capacity(init_capacity) {
            cout << "A New Yard has been created!" << endl;
        }
};

class Stairs {
    int capacity;
    int student_num;
    public:
        Stairs(int init_capacity) : capacity(init_capacity) {
            cout << "New Stairs have been created!" << endl;
        }
};

class Floor {
    Class classes;
    Corridor corridor;
    public:
        Floor(int cclass, int ccorr) : classes(cclass), corridor(ccorr) {
            cout << "A New Floor has been created!" << endl;
        }
};

class School {
    Yard yard;
    Stairs stairs;
    Floor floors;
    public:
        School(int cclass, int cyard, int cstair, int ccorr)
        :   yard(cyard), stairs(cstair), floors(cclass, ccorr)
        {
            cout << "A New School has been created!" << endl;
        }
};

class Student {
    string name;
};

int main(int argc, char* argv[]) {
    if (argc != 5) {
        cerr << "Wrong number of arguments" << endl;
        return 1;
    }
    School school(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
    return 0;
}