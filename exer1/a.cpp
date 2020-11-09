#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include "names.h"

using namespace std;

enum area {
    at_yard, at_stairs, at_corridor, at_class, outside
};

class Student {
    string name;
    int floor_num;
    int class_num;
    enum area position;
    public:
        Student(const char* init_name, int init_floor_num, int init_class_num)
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
        string get_name() const {
            return name;
        }
        void print() {
            cout << name << endl;
        }
};

class Teacher {
    string name;
    int floor_num;
    int class_num;
    bool in;
    public:
        Teacher(const char* init_name, int init_floor_num, int init_class_num)
        :   name(init_name), floor_num(init_floor_num), class_num(init_class_num)
        {
            in = false;
            cout << "A New Teacher has been created!" << endl;
            cout << name << endl;
            cout << "Floor " << floor_num  << ", class " << class_num << endl;
        }
        ~Teacher() {
            cout << "A Teacher to be destroyed!" << endl;
            cout << name << endl;
            cout << "Floor " << floor_num  << ", class " << class_num << endl;
            cout << in ? "In" : "Out of" << "the class" << endl;
        }
        void print() {
            cout << "The teacher is: " << name << endl;
        }
        void set_in() {
            in = true;
        }
        int get_floor_num() const {
            return floor_num;
        }
        int get_class_num() const {
            return class_num;
        }
};

class Class {
    int capacity;
    Student** students;
    Teacher* teacher;
    int student_num;
    public:
        Class(int init_capacity) : capacity(init_capacity) {
            students = new Student*[init_capacity];
            student_num = 0;
            cout << "A New Class has been created!" << endl;
        }
        ~Class() {
            cout << "A Class to be destroyed!" << endl;
        }
        void enter(Student& student) {
            cout << student.get_name() << " enters class!" << endl;
            students[student_num] = &student;
            student_num++;
        }
        void print(int class_number) {
            cout << "People in class " << class_number << " are: " << endl;
            for (int i = 0 ; i < student_num ; i++) {
                students[i]->print();
            }
            teacher->print();
        }
        void place(Teacher& teacher_in) {
            teacher = &teacher_in;
            teacher_in.set_in();
        }
};

class Corridor {
    int capacity;
    Student** students;
    int student_num;
    public:
        Corridor(int init_capacity) : capacity(init_capacity) {
            students = new Student*[init_capacity];
            student_num = 0;
            cout << "A New Corridor has been created!" << endl;
        }
        ~Corridor() {
            cout << "A Corridor to be destroyed!" << endl;
        }
        void enter(Student& student) {
            cout << student.get_name() << " enters corridor!" << endl;
            students[student_num] = &student;
            student_num++;
        }
        void exit(Student& student) {
            cout << student.get_name() << " exits corridor!" << endl;
            student_num--;
            students[student_num] = NULL;   //unnecessary
        }
        void print() {
            cout << "People in corridor are: " << endl;
            for (int i = 0 ; i < student_num ; i++) {
                students[i]->print();
            }
        }
};

class Yard {
    int capacity;
    Student** students;
    int student_num;
    public:
        Yard(int init_capacity) : capacity(init_capacity) {
            students = new Student*[init_capacity];
            student_num = 0;
            cout << "A New Yard has been created!" << endl;
        }
        ~Yard() {
            cout << "A Yard to be destroyed!" << endl;
        }
        void enter(Student& student) {
            cout << student.get_name() << " enters schoolyard!" << endl;
            students[student_num] = &student;
            student_num++;
        }
        void exit(Student& student) {
            cout << student.get_name() << " exits schoolyard!" << endl;
            student_num--;
            students[student_num] = NULL;   //unnecessary
        }
        void print() {
            cout << "People in schoolyard are: " << endl;
            for (int i = 0 ; i < student_num ; i++) {
                students[i]->print();
            }
        }
};

class Stairs {
    int capacity;
    Student** students;
    int student_num;
    public:
        Stairs(int init_capacity) : capacity(init_capacity) {
            students = new Student*[init_capacity];
            student_num = 0;
            cout << "New Stairs have been created!" << endl;
        }
        ~Stairs() {
            cout << "Stairs to be destroyed!" << endl;
        }
        void enter(Student& student) {
            cout << student.get_name() << " enters stairs!" << endl;
            students[student_num] = &student;
            student_num++;
        }
        void exit(Student& student) {
            cout << student.get_name() << " exits stairs!" << endl;
            student_num--;
            students[student_num] = NULL;   //unnecessary
        }
        void print() {
            cout << "People in stairs are: " << endl;
            for (int i = 0 ; i < student_num ; i++) {
                students[i]->print();
            }
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
        void enter(Student& student) {
            cout << student.get_name() << " enters floor!" << endl;
            corridor.enter(student);
        }
        void print(int floor_number) {
            cout << "Floor number " << floor_number << " contains: " << endl;
            corridor.print();
            for (int i = 0 ; i < 6 ; i++) {
                classes[i]->print(i);
            }
        }
        void place(Teacher& teacher) {
            classes[teacher.get_class_num()]->place(teacher);
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
        void enter(Student& student) {
            cout << student.get_name() << " enters school!" << endl;
            yard.enter(student);
        }
        void print() {
            cout << "School life consists of: " << endl;
            yard.print();
            stairs.print();
            for (int i = 0 ; i < 3 ; i++) {
                floors[i]->print(i);
            }
        }
        void place(Teacher& teacher) {
            floors[teacher.get_floor_num()]->place(teacher);
        }
};

int main(int argc, char* argv[]) {
    if (argc != 5) {
        cerr << "Wrong number of arguments" << endl;
        return 1;
    }
    srand(time(NULL));
    School school(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
    Student student(names[rand() % 36], 1, 3);
    Teacher teacher(names[rand() % 36], 2, 5);
    school.enter(student);
    return 0;
}