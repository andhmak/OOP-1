#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

enum area {
    at_yard, at_stairs, at_corridor, at_class, outside
};

class Class {
    int capacity;
    int student_num;
    public:
        Class(int init_capacity) : capacity(init_capacity) {
            cout << "A New Class has been created!" << endl;
        }
        ~Class() {
            cout << "A Class to be destroyed!" << endl;
        }
};

class Corridor {
    int capacity;
    int student_num;
    public:
        Corridor(int init_capacity) : capacity(init_capacity) {
            cout << "A New Corridor has been created!" << endl;
        }
        ~Corridor() {
            cout << "A Corridor to be destroyed!" << endl;
        }
};

class Yard {
    int capacity;
    int student_num;
    public:
        Yard(int init_capacity) : capacity(init_capacity) {
            cout << "A New Yard has been created!" << endl;
        }
        ~Yard() {
            cout << "A Yard to be destroyed!" << endl;
        }
};

class Stairs {
    int capacity;
    int student_num;
    public:
        Stairs(int init_capacity) : capacity(init_capacity) {
            cout << "New Stairs have been created!" << endl;
        }
        ~Stairs() {
            cout << "Stairs to be destroyed!" << endl;
        }
};

class Floor {
    Class* classes[6];
    Corridor corridor;
    public:
        Floor(int cclass, int ccorr) : corridor(ccorr) {
            for (int i = 0 ; i < 3 ; i++) {
                classes[i] = new Class(cclass);
            }
            cout << "A New Floor has been created!" << endl;
        }
        ~Floor() {
            cout << "A Floor to be destroyed!" << endl;
            for (int i = 0 ; i < 3 ; i++) {
                delete classes[i];
            }
        }
};

class School {
    Yard yard;
    Stairs stairs;
    Floor* floors[3];
    public:
        School(int cclass, int cyard, int cstair, int ccorr)
        :   yard(cyard), stairs(cstair)
        {
            for (int i = 0 ; i < 3 ; i++) {
                floors[i] = new Floor(cclass, ccorr);
            }
            cout << "A New School has been created!" << endl;
        }
        ~School() {
            cout << "A School to be destroyed!" << endl;
            for (int i = 0 ; i < 3 ; i++) {
                delete floors[i];
            }
        }
};

class Student {
    string name;
    int floor_num;
    int class_num;
    enum area position;
    public:
        Student(char* init_name, int init_floor_num, int init_class_num)
        :   name(init_name), floor_num(init_floor_num), class_num(init_class_num)
        {
            position = outside;
            cout << "A New Student has been created!" << endl;
            cout << name << endl;
            cout << "Floor " << floor_num  << ", class " << class_num << endl;
        }
        ~Student() {
            cout << "A Student to be destroyed!" << endl;
            cout << name << endl;
            cout << "Floor " << floor_num  << ", class " << class_num << endl;
            switch (position) {
                case at_yard:
                    cout << "Situated in the yard" << endl;
                    break;
                case at_stairs:
                    cout << "Situated on the stairs" << endl;
                    break;
                case at_corridor:
                    cout << "Situated in the corridor" << endl;
                    break;
                case at_class:
                    cout << "Situated in the class" << endl;
                    break;
                case outside:
                    cout << "Situated outside" << endl;
            }
        }
};

int main(int argc, char* argv[]) {
    if (argc != 5) {
        cerr << "Wrong number of arguments" << endl;
        return 1;
    }
    School school(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
    return 0;
}