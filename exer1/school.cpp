#include <iostream>
#include "school.h"

using namespace std;

Student::Student(const char* init_name, int init_floor_num, int init_class_num)
:   name(init_name), floor_num(init_floor_num), class_num(init_class_num)
{
    position = outside;
    cout << "A New Student has been created!" << endl;
    cout << name << endl;
    cout << "Floor " << floor_num + 1 << ", class " << class_num + 1 << endl;
}

Student::~Student() {
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

string Student::get_name() const {
    return name;
}

void Student::set_position(enum area new_position) {
    position = new_position;
}

void Student::print() const {
    cout << name << endl;
}

int Student::get_floor_num() const {
    return floor_num;
}

int Student::get_class_num() const {
    return class_num;
}

Teacher::Teacher(const char* init_name, int init_floor_num, int init_class_num)
:   name(init_name), floor_num(init_floor_num), class_num(init_class_num)
{
    in = false;
    cout << "A New Teacher has been created!" << endl;
    cout << name << endl;
    cout << "Floor " << floor_num + 1  << ", class " << class_num + 1 << endl;
}
Teacher::~Teacher() {
    cout << "A Teacher to be destroyed!" << endl;
    cout << name << endl;
    cout << "Floor " << floor_num + 1 << ", class " << class_num  + 1 << endl;
    cout << "Situated " << (in ? "in " : "outside ") << "the class" << endl;
}
void Teacher::print() const {
    cout << "The teacher is: " << name << endl;
}
void Teacher::set_in() {
    in = true;
}
int Teacher::get_floor_num() const {
    return floor_num;
}
int Teacher::get_class_num() const {
    return class_num;
}
bool Teacher::is_in() const {
    return in;
}

Yard::Yard(int init_capacity) : capacity(init_capacity) {
    students = new Student*[init_capacity];
    student_num = 0;
    cout << "A New Yard has been created!" << endl;
}

Yard::~Yard() {
    cout << "A Yard to be destroyed!" << endl;
    delete[] students;
}

void Yard::enter(Student& student) {
    cout << student.get_name() << " enters schoolyard!" << endl;
    students[student_num] = &student;
    student_num++;
    student.set_position(at_yard);
}

Student* Yard::exit() {
    if (student_num == 0) {
        return NULL;
    }
    cout << students[student_num - 1]->get_name() << " exits schoolyard!" << endl;
    student_num--;
    return students[student_num];
}

void Yard::print() const {
    cout << "People in schoolyard are: " << endl;
    for (int i = 0 ; i < student_num ; i++) {
        students[i]->print();
    }
}

bool Yard::full() const {
    return capacity == student_num;
}


Stairs::Stairs(int init_capacity) : capacity(init_capacity) {
    students = new Student*[init_capacity];
    student_num = 0;
    cout << "New Stairs have been created!" << endl;
}

Stairs::~Stairs() {
    cout << "Stairs to be destroyed!" << endl;
    delete[] students;
}

void Stairs::enter(Student& student) {
    cout << student.get_name() << " enters stairs!" << endl;
    students[student_num] = &student;
    student_num++;
    student.set_position(at_stairs);
}

Student* Stairs::exit(int floor_num) {
    Student* temp;
    for (int i = student_num - 1 ; i >= 0 ; i--) {
        if (students[i]->get_floor_num() == floor_num) {
            temp = students[i];
            students[i] = students[student_num - 1];
            students[student_num - 1] = temp;
            cout << students[student_num - 1]->get_name() << " exits stairs!" << endl;
            student_num--;
            return students[student_num];
        }
    }
    return NULL;
}

void Stairs::print() const {
    cout << "People in stairs are: " << endl;
    for (int i = 0 ; i < student_num ; i++) {
        students[i]->print();
    }
}

bool Stairs::full() const {
    return capacity == student_num;
}

Class::Class(int init_capacity) : capacity(init_capacity) {
    students = new Student*[init_capacity];
    student_num = 0;
    teacher = NULL;
    cout << "A New Class has been created!" << endl;
}

Class::~Class() {
    cout << "A Class to be destroyed!" << endl;
    delete[] students;
}

void Class::enter(Student& student) {
    cout << student.get_name() << " enters class!" << endl;
    students[student_num] = &student;
    student_num++;
    student.set_position(at_class);
}

void Class::print(int class_number) const {
    cout << "People in class " << class_number + 1 << " are: " << endl;
    for (int i = 0 ; i < student_num ; i++) {
        students[i]->print();
    }
    if (teacher != NULL) {
        teacher->print();
    }
}

void Class::place(Teacher& teacher_in) {
    teacher = &teacher_in;
    teacher_in.set_in();
}

bool Class::full() const {
    return (capacity == student_num) || (teacher != NULL);
}

Corridor::Corridor(int init_capacity) : capacity(init_capacity) {
    students = new Student*[init_capacity];
    student_num = 0;
    cout << "A New Corridor has been created!" << endl;
}
Corridor::~Corridor() {
    cout << "A Corridor to be destroyed!" << endl;
    delete[] students;
}

void Corridor::enter(Student& student) {
    cout << student.get_name() << " enters corridor!" << endl;
    students[student_num] = &student;
    student_num++;
    student.set_position(at_corridor);
}

Student* Corridor::exit() {
    if (student_num == 0) {
        return NULL;
    }
    cout << students[student_num - 1]->get_name() << " exits corridor!" << endl;
    student_num--;
    return students[student_num];
}

void Corridor::print() const {
    cout << "People in corridor are: " << endl;
    for (int i = 0 ; i < student_num ; i++) {
        students[i]->print();
    }
}

bool Corridor::full() const {
    return capacity == student_num;
}

Floor::Floor(int cclass, int ccorr) : corridor(ccorr) {
    for (int i = 0 ; i < 6 ; i++) {
        classes[i] = new Class(cclass);
    }
    cout << "A New Floor has been created!" << endl;
}

Floor::~Floor() {
    cout << "A Floor to be destroyed!" << endl;
    for (int i = 0 ; i < 6 ; i++) {
        delete classes[i];
    }
}

void Floor::enter(Student& student) {
    cout << student.get_name() << " enters floor!" << endl;
    corridor.enter(student);
    if (classes[student.get_class_num()]->full() == false) {
        corridor.exit();
        classes[student.get_class_num()]->enter(student);
    }
}

void Floor::print(int floor_number) const {
    cout << "Floor number " << floor_number + 1 << " contains: " << endl;
    corridor.print();
    for (int i = 0 ; i < 6 ; i++) {
        classes[i]->print(i);
    }
}

void Floor::place(Teacher& teacher) {
    classes[teacher.get_class_num()]->place(teacher);
}

bool Floor::can_fit() const {
    return !corridor.full();
}

School::School(int cclass, int cyard, int cstair, int ccorr)
:   yard(cyard), stairs(cstair)
{
    for (int i = 0 ; i < 3 ; i++) {
        floors[i] = new Floor(cclass, ccorr);
    }
    cout << "A New School has been created!" << endl;
}

School::~School() {
    cout << "A School to be destroyed!" << endl;
    for (int i = 0 ; i < 3 ; i++) {
        delete floors[i];
    }
}

bool School::enter(Student& student) {
    cout << student.get_name() << " enters school!" << endl;
    if (yard.full()) {
        return false;
    }
    yard.enter(student);
    if (stairs.full()) {
        return true;
    }
    yard.exit();
    stairs.enter(student);
    if (floors[student.get_floor_num()]->can_fit()) {
        stairs.exit(student.get_floor_num());
        floors[student.get_floor_num()]->enter(student);
    }
    return true;
}

bool School::enter(Student** students, int size) {
    for (int i = 0 ; i < size ; i++) {
        cout << students[i]->get_name() << " enters school!" << endl;
    }
    int ammount_in = 0;
    bool stagnated;
    Student* to_enter;
    while(true) {
        stagnated = true;
        for ( ; (yard.full() == false) && (ammount_in != size) ; ammount_in++) {
            yard.enter(*students[ammount_in]);
        }
        while (stairs.full() == false) {
            to_enter = yard.exit();
            if (to_enter == NULL) {
                break;
            }
            stairs.enter(*to_enter);
            stagnated = false;
        }
        for (int i = 0 ; i < 3 ; i++) {
            while (floors[i]->can_fit()) {
                to_enter = stairs.exit(i);
                if (to_enter == NULL) {
                    break;
                }
                floors[i]->enter(*to_enter);
                stagnated = false;
            }
        }
        if (stagnated) {
            return ammount_in == size;
        }
    }
}

void School::print() const {
    cout << "School life consists of: " << endl;
    yard.print();
    stairs.print();
    for (int i = 0 ; i < 3 ; i++) {
        floors[i]->print(i);
    }
}

void School::place(Teacher& teacher) {
    floors[teacher.get_floor_num()]->place(teacher);
}