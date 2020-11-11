#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

class Class;

class Student {
    string name;
    Class* classroom;
    bool male;
    Student(char* init_name, Class* init_classroom, bool init_male)
    :   name(init_name), classroom(init_classroom), male(init_male) {
        cout << "New student " << name << (male ? "male" : "female") <<  endl;
    }
};

class Pair {
    Student* first;
    Student* second;
    Pair(Student* init_first, Student* init_second) {
        first = init_first;
        second = init_second;
    }
};

class Class {
    int messiness;
};

class School {
    Class* classes;
};

int main(int argc, char* argv[]) {
    if (argc != 5) {
        cerr << "Wrong number of arguments" << endl;
        return 1;
    }
    srand(time(NULL));
    return 0;
}