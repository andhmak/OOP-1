/* File: school.cpp */

#include <iostream>
#include "school.h"

using namespace std;

// Constructor της Student
Student::Student(const char* init_name, short init_floor_num, short init_class_num)
:   name(init_name), floor_num(init_floor_num), class_num(init_class_num)
{
    position = outside;
    cout << "A New Student has been created!" << endl;
    cout << name << endl;
    cout << "Floor " << floor_num + 1 << ", class " << class_num + 1 << endl;
}

// Destructor της Student
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

// Constructor της Teacher
Teacher::Teacher(const char* init_name, short init_floor_num, short init_class_num)
:   name(init_name), floor_num(init_floor_num), class_num(init_class_num)
{
    in = false;
    cout << "A New Teacher has been created!" << endl;
    cout << name << endl;
    cout << "Floor " << floor_num + 1  << ", class " << class_num + 1 << endl;
}

// Destructor της Teacher
Teacher::~Teacher() {
    cout << "A Teacher to be destroyed!" << endl;
    cout << name << endl;
    cout << "Floor " << floor_num + 1 << ", class " << class_num  + 1 << endl;
    cout << "Situated " << (in ? "in " : "outside ") << "the class" << endl;
}

// Constructor της Yard
Yard::Yard(int init_capacity) : capacity(init_capacity) {
    students = new Student*[init_capacity];
    student_num = 0;
    cout << "A New Yard has been created!" << endl;
}

// Destructor της Yard
Yard::~Yard() {
    cout << "A Yard to be destroyed!" << endl;
    delete[] students;
}

// Βάζει τον μαθητή/όρισμα στην αυλή
void Yard::enter(Student& student) {
    cout << student.get_name() << " enters schoolyard!" << endl;
    students[student_num] = &student;
    student_num++;
    student.set_position(at_yard);
}

// Αφαιρεί τον τελευταίο μαθητή από την αυλή και επιστρέφει δείκτη σε αυτόν
Student* Yard::exit() {
    if (student_num == 0) {
        return NULL;
    }
    cout << students[student_num - 1]->get_name() << " exits schoolyard!" << endl;
    student_num--;
    return students[student_num];
}

// Συνάρτηση εκτύπωσης της Yard
void Yard::print() const {
    cout << "People in schoolyard are: " << endl;
    for (int i = 0 ; i < student_num ; i++) {
        students[i]->print();
    }
}

// Constructor της Stairs
Stairs::Stairs(int init_capacity) : capacity(init_capacity) {
    students = new Student*[init_capacity];
    student_num = 0;
    cout << "New Stairs have been created!" << endl;
}

// Destructor της Stairs
Stairs::~Stairs() {
    cout << "Stairs to be destroyed!" << endl;
    delete[] students;
}

// Βάζει τον μαθητή/όρισμα στο κλιμακοστάσιο
void Stairs::enter(Student& student) {
    cout << student.get_name() << " enters stairs!" << endl;
    students[student_num] = &student;
    student_num++;
    student.set_position(at_stairs);
}

// Αφαιρεί τον τελευταίο μαθητή του οποίου η τάξη βρίσκεται στον
// όροφο/όρισμα από το κλιμακοστάσιο και επιστρέφει δείκτη σε αυτό
Student* Stairs::exit(short floor_num) {
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

// Συνάρτηση εκτύπωσης της Stairs
void Stairs::print() const {
    cout << "People in stairs are: " << endl;
    for (int i = 0 ; i < student_num ; i++) {
        students[i]->print();
    }
}

// Constructor της Corridor
Corridor::Corridor(int init_capacity) : capacity(init_capacity) {
    students = new Student*[init_capacity];
    student_num = 0;
    cout << "A New Corridor has been created!" << endl;
}

// Destructor της Corridor
Corridor::~Corridor() {
    cout << "A Corridor to be destroyed!" << endl;
    delete[] students;
}

// Βάζει τον μαθητή/όρισμα στον διάδρομο
void Corridor::enter(Student& student) {
    cout << student.get_name() << " enters corridor!" << endl;
    students[student_num] = &student;
    student_num++;
    student.set_position(at_corridor);
}

// Αφαιρεί τον τελευταίο μαθητή από τον διάδρομο και επιστρέφει δείκτη σε αυτόν
Student* Corridor::exit() {
    if (student_num == 0) {
        return NULL;
    }
    cout << students[student_num - 1]->get_name() << " exits corridor!" << endl;
    student_num--;
    return students[student_num];
}

// Συνάρτηση εκτύπωσης της Corridor
void Corridor::print() const {
    cout << "People in corridor are: " << endl;
    for (int i = 0 ; i < student_num ; i++) {
        students[i]->print();
    }
}

// Constructor της Class
Class::Class(int init_capacity) : capacity(init_capacity) {
    students = new Student*[init_capacity];
    student_num = 0;
    teacher = NULL;
    cout << "A New Class has been created!" << endl;
}

// Destructor της Class
Class::~Class() {
    cout << "A Class to be destroyed!" << endl;
    delete[] students;
}

// Βάζει τον μαθητή/όρισμα στην τάξη
void Class::enter(Student& student) {
    cout << student.get_name() << " enters class!" << endl;
    students[student_num] = &student;
    student_num++;
    student.set_position(at_class);
}

// Τοποθετεί τον δάσκαλο/όρισμα στην τάξη
void Class::place(Teacher& teacher_in) {
    teacher = &teacher_in;
    teacher_in.set_in();
}

// Συνάρτηση εκτύπωσης της Class
void Class::print(short class_number) const {
    cout << "People in class " << class_number + 1 << " are: " << endl;
    for (int i = 0 ; i < student_num ; i++) {
        students[i]->print();
    }
    if (teacher != NULL) {
        teacher->print();
    }
}

// Constructor της Floor
Floor::Floor(int cclass, int ccorr) : corridor(ccorr) {
    for (char i = 0 ; i < 6 ; i++) {
        classes[i] = new Class(cclass);
    }
    cout << "A New Floor has been created!" << endl;
}

// Destructor της Floor
Floor::~Floor() {
    cout << "A Floor to be destroyed!" << endl;
    for (char i = 0 ; i < 6 ; i++) {
        delete classes[i];
    }
}

// Βάζει τον μαθητή/όρισμα στον όροφο, βάζοντάς τον στον διάδρομο αν χωράει
void Floor::enter(Student& student) {
    cout << student.get_name() << " enters floor!" << endl;
    corridor.enter(student);
    if (classes[student.get_class_num()]->full() == false) {
        corridor.exit();
        classes[student.get_class_num()]->enter(student);
    }
}

// Συνάρτηση εκτύπωσης της Floor
void Floor::print(short floor_number) const {
    cout << "Floor number " << floor_number + 1 << " contains: " << endl;
    corridor.print();
    for (char i = 0 ; i < 6 ; i++) {
        classes[i]->print(i);
    }
}

// Constructor της School
School::School(int cclass, int cyard, int cstair, int ccorr)
:   yard(cyard), stairs(cstair)
{
    for (char i = 0 ; i < 3 ; i++) {
        floors[i] = new Floor(cclass, ccorr);
    }
    cout << "A New School has been created!" << endl;
}

// Destructor της School
School::~School() {
    cout << "A School to be destroyed!" << endl;
    for (char i = 0 ; i < 3 ; i++) {
        delete floors[i];
    }
}

// Βάζει τον μαθητή/όρισμα στο σχολείο, πηγαίνοντάς τον όσο πιο κοντά γίνεται
// στην τάξη του. Επιστρέφει το αν μπόρεσε να μπει τουλάχιστον στην αυλή ή όχι.
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

// Βάζει τους μαθητές/όρισμα στο σχολείο, μετακινόντας τους σε "κύματα",
// πηγαίνοντάς τους τελικά όσο κοντά γίνεται στις τάξεις τους. Επιστρέφει
// το αν μπόρεσαν όλοι οι μαθητές να μπουν τουλάχιστον στην αυλή ή όχι.
bool School::enter(Student** students, int size) {
    for (int i = 0 ; i < size ; i++) {
        cout << students[i]->get_name() << " enters school!" << endl;
    }
    int ammount_in = 0;
    bool stagnated;
    Student* to_enter;
    while (true) {
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

// Συνάρτηση εκτύπωσης της School
void School::print() const {
    cout << "School life consists of: " << endl;
    yard.print();
    stairs.print();
    for (char i = 0 ; i < 3 ; i++) {
        floors[i]->print(i);
    }
}