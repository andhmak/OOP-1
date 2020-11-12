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
            cout << "Floor " << floor_num + 1 << ", class " << class_num + 1 << endl;
        }
        ~Student() {
            cout << "A Student to be destroyed!" << endl;
            cout << name << endl;
            cout << "Floor " << floor_num + 1 << ", class " << class_num + 1<< endl;
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
        void set_position(enum area new_position) {
            position = new_position;
        }
        void print() const {
            cout << name << endl;
        }
        int get_floor_num() const {
            return floor_num;
        }
        int get_class_num() const {
            return class_num;
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
            cout << "Floor " << floor_num + 1  << ", class " << class_num + 1 << endl;
        }
        ~Teacher() {
            cout << "A Teacher to be destroyed!" << endl;
            cout << name << endl;
            cout << "Floor " << floor_num + 1 << ", class " << class_num  + 1 << endl;
            cout << "Situated " << (in ? "in " : "outside ") << "the class" << endl;
        }
        void print() const {
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
        bool is_in() const {
            return in;
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
            teacher = NULL;
            cout << "A New Class has been created!" << endl;
        }
        ~Class() {
            cout << "A Class to be destroyed!" << endl;
            delete students;
        }
        void enter(Student& student) {
            cout << student.get_name() << " enters class!" << endl;
            students[student_num] = &student;
            student_num++;
            student.set_position(at_class);
        }
        void print(int class_number) const {
            cout << "People in class " << class_number + 1 << " are: " << endl;
            for (int i = 0 ; i < student_num ; i++) {
                students[i]->print();
            }
            if (teacher != NULL) {
                teacher->print();
            }
        }
        void place(Teacher& teacher_in) {
            teacher = &teacher_in;
            teacher_in.set_in();
        }
        bool full() const {
            return (capacity == student_num) || (teacher != NULL);
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
            delete students;
        }
        void enter(Student& student) {
            cout << student.get_name() << " enters corridor!" << endl;
            students[student_num] = &student;
            student_num++;
            student.set_position(at_corridor);
        }
        void exit(Student& student) {
            cout << student.get_name() << " exits corridor!" << endl;
            student_num--;
        }
        void print() const {
            cout << "People in corridor are: " << endl;
            for (int i = 0 ; i < student_num ; i++) {
                students[i]->print();
            }
        }
        bool full() const {
            return capacity == student_num;
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
            delete students;
        }
        void enter(Student& student) {
            cout << student.get_name() << " enters schoolyard!" << endl;
            students[student_num] = &student;
            student_num++;
            student.set_position(at_yard);
        }
        void exit(Student& student) {
            cout << student.get_name() << " exits schoolyard!" << endl;
            student_num--;
        }
        void print() const {
            cout << "People in schoolyard are: " << endl;
            for (int i = 0 ; i < student_num ; i++) {
                students[i]->print();
            }
        }
        bool full() const {
            return capacity == student_num;
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
            delete students;
        }
        void enter(Student& student) {
            cout << student.get_name() << " enters stairs!" << endl;
            students[student_num] = &student;
            student_num++;
            student.set_position(at_stairs);
        }
        void exit(Student& student) {
            cout << student.get_name() << " exits stairs!" << endl;
            student_num--;
        }
        void print() const {
            cout << "People in stairs are: " << endl;
            for (int i = 0 ; i < student_num ; i++) {
                students[i]->print();
            }
        }
        bool full() const {
            return capacity == student_num;
        }
};

class Floor {
    Class* classes[6];
    Corridor corridor;
    public:
        Floor(int cclass, int ccorr) : corridor(ccorr) {
            for (int i = 0 ; i < 6 ; i++) {
                classes[i] = new Class(cclass);
            }
            cout << "A New Floor has been created!" << endl;
        }
        ~Floor() {
            cout << "A Floor to be destroyed!" << endl;
            for (int i = 0 ; i < 6 ; i++) {
                delete classes[i];
            }
        }
        void enter(Student& student) {
            cout << student.get_name() << " enters floor!" << endl;
            corridor.enter(student);
            if (classes[student.get_class_num()]->full() == false) {
                corridor.exit(student);
                classes[student.get_class_num()]->enter(student);
            }
        }
        void print(int floor_number) const {
            cout << "Floor number " << floor_number + 1 << " contains: " << endl;
            corridor.print();
            for (int i = 0 ; i < 6 ; i++) {
                classes[i]->print(i);
            }
        }
        void place(Teacher& teacher) {
            classes[teacher.get_class_num()]->place(teacher);
        }
        bool can_fit() const {
            return !corridor.full();
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
        bool enter(Student& student) {
            cout << student.get_name() << " enters school!" << endl;
            if (yard.full()) {
                return false;
            }
            yard.enter(student);
            if (stairs.full()) {
                return true;
            }
            yard.exit(student);
            stairs.enter(student);
            if (floors[student.get_floor_num()]->can_fit()) {
                stairs.exit(student);
                floors[student.get_floor_num()]->enter(student);
            }
            return true;
        }
        void print() const {
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
    int cclass = atoi(argv[1]), cyard = atoi(argv[2]), cstair = atoi(argv[3]), ccorr = atoi(argv[4]);
    School school(cclass, cyard, cstair, ccorr);
    int student_num = cclass*18 + cyard + cstair + ccorr*3 + 5;
    Student* students[student_num];
    Teacher* teachers[18];
    Teacher* to_be_placed;
    for (int i = 0 ; i < student_num ; i++) {
        students[i] = new Student(names[rand() % 36], rand() % 3, rand() % 6);
    }
    for (int i = 0 ; i < 18 ; i++) {
        teachers[i] = new Teacher(names[rand() % 36], i / 6, i % 6);
    }
    int teacher_num;
    for (int i = 0 ; i < student_num ; i++) {
        if (!school.enter(*students[i])) {
            break;
        }
        if (!(rand() % (cclass*18))) {
            teacher_num = rand() % 18;
            for (int j = 0 ; j < teacher_num ; j++) {
                to_be_placed = teachers[rand() % 18];
                if (to_be_placed->is_in() == false) {
                    school.place(*to_be_placed);
                }
            }
        }
    }
    school.print();
    for (int i = 0 ; i < student_num ; i++) {
        delete students[i];
    }
    for (int i = 0 ; i < 18 ; i++) {
        delete teachers[i];
    }
    return 0;
}