/* File: kindergarten.h */

#include <iostream>
#include <string>

// Κλάση που αναπαριστά έναν μαθητή
class Student {
    std::string name;   // όνομα του μαθητή
    int classroom_id;   // index της τάξης του μαθητή
    bool male;          // φύλο του μαθητή/το αν είναι αρσενικός
    bool messy;         // το αν ο μαθητής κάνει αταξίες μια δεδομένη στιγμή
    public:
        Student(const char* init_name, int init_classroom_id, bool init_male)   // Constructor
        :   name(init_name), classroom_id(init_classroom_id), male(init_male), messy(0) { }
        void set_messy(bool to_be_messy) { messy = to_be_messy; }   // Mutator
        bool is_male() const { return male; }                       // +
        int get_classroom_id() const { return classroom_id; }       // |  Accessors
        bool get_messy() const { return messy; }                    // +
        void print() const {    // Συνάρτηση εκτύπωσης (εκτυπώνει το όνομα, την τάξη και το φύλο)
            std::cout << name << ", class " << classroom_id + 1 << (male ? ", male" : ", female") << std::endl;
        }
};

// Κλάση που αναπαριστά έναν ζαυγάρι μαθητών
class Pair {
    Student* first;
    Student* second;
    public:
        Pair(Student* init_first, Student* init_second) : first(init_first), second(init_second) { }    // Constructor
        Student* get_student(bool male) const;
        bool male_first() const { return first->is_male(); }
        bool only_male() const { return !((((first != NULL) && !first->is_male())) || (((second != NULL) && !second->is_male()))); }
        bool only_female() const { return !((((first != NULL) && first->is_male())) || (((second != NULL) && second->is_male()))); }
        Pair* merge(Pair* other);
        void swap(Pair* other, bool male);
        void print(int position) const;
};

// Κλάση που αναπαριστά την ακολουθία ενός τμήματος κατά μια μετακίνηση
class Sequence {
    int messiness;
    int size;
    Pair** pairs;
    public:
        Sequence(Student** students, int student_amount);   // Constructor
        ~Sequence();    // Destructor
        int get_size() const { return size; }
        Pair* get_pair(int i) const { return pairs[i]; }
        void increase_messiness(int amount) { messiness += amount; }
        bool excess_male() const { return pairs[size - 1]->only_male(); }
        bool excess_female() const { return pairs[size - 1]->only_female(); }
        Pair* get_last_full_pair() const { return (pairs[size - 1]->only_female() || pairs[size - 1]->only_male()) ? pairs[size - 2] : pairs[size - 1]; }
        Pair* trim();
        void append(Pair** extra_pairs, int extra_amount);
        void print(int tquiet, int tmessy) const;
};

// Κλάση που αναπαριστά το σύνολο των ακολουθιών ενός τμήματος κατά μια μετακίνηση
class Kindergarten {
    Sequence** sequences;
    int size;
    int tquiet, tmessy;
    public:
        Kindergarten(Sequence** init_sequences, int sequence_amount, int init_tquiet, int init_messy);  // Constructor
        void cause_mess();
        void print() const;
};