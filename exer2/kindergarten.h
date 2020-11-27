/* File: kindergarten.h */

#include <iostream>
#include <string>

class Student {
    std::string name;
    int classroom_id;
    bool male;
    bool messy;
    public:
        Student(const char* init_name, int init_classroom_id, bool init_male)
        :   name(init_name), classroom_id(init_classroom_id), male(init_male), messy(0) { }
        bool is_male() const { return male; }
        int get_classroom_id() const { return classroom_id; }
        bool get_messy() const { return messy; }
        void set_messy(bool to_be_messy) { messy = to_be_messy; }
        void print() const { std::cout << name << ", class " << classroom_id + 1 << (male ? ", male" : ", female") << std::endl; }
};

class Pair {
    Student* first;
    Student* second;
    public:
        Pair(Student* init_first, Student* init_second) : first(init_first), second(init_second) { }
        Pair* merge(Pair* other);
        void swap(Pair* other, bool male);
        Student* get_student(bool male) const;
        bool male_first() const { return first->is_male(); }
        bool only_male() const { return ((first == NULL) && ((second != NULL) && second->is_male())) || (((first != NULL) && first->is_male()) && (second == NULL)); }
        bool only_female() const { return ((first == NULL) && ((second != NULL) && !second->is_male())) || (((first != NULL) && !first->is_male()) && (second == NULL)); }
        void print(int position) const;
};

class Sequence {
    int messiness;
    int size;
    Pair** pairs;
    public:
        Sequence(Student** students, int student_amount);
        ~Sequence();
        Pair* trim();
        void append(Pair** extra_pairs, int extra_amount);
        void increase_messiness(int amount) { messiness += amount; }
        bool excess_male() const { return pairs[size - 1]->only_male(); }
        bool excess_female() const { return pairs[size - 1]->only_female(); }
        Pair* get_last_full_pair() const { return (pairs[size - 1]->only_female() || pairs[size - 1]->only_male()) ? pairs[size - 2] : pairs[size - 1]; }
        int get_size() const { return size; }
        Pair* get_pair(int i) const { return pairs[i]; }
        void print(int tquiet, int tmessy) const;
};

class Kindergarten {
    Sequence** sequences;
    int size;
    int tquiet, tmessy;
    public:
        Kindergarten(Sequence** init_sequences, int sequence_amount, int init_tquiet, int init_messy);
        void cause_mess();
        void print() const;
};