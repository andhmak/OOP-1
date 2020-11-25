#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include "names.h"
////say empty spaces can be moved
using namespace std;

class StudentListNode {
    int position;
    bool male;
    StudentListNode* next;
    public:
        StudentListNode(int init_position, bool init_male)
        :   position(init_position), male(init_male) { }
        void set_next(StudentListNode* to_be_next) {
            next = to_be_next;
        }
        StudentListNode* get_next() const {
            return next;
        }
        int get_position() const {
            return position;
        }
        bool is_male() const {
            return male;
        }
};

class StudentList {
    StudentListNode* first;
    int size;
    public:
        StudentList() : first(NULL), size(0) { }
        ~StudentList() {
            StudentListNode *curr_node, *next_node;
            for (curr_node = first ; curr_node != NULL ; curr_node = next_node) {
                next_node = curr_node->get_next();
                delete curr_node;
            }
        }
        void pushFront(int position, bool male) {
            StudentListNode* new_node = new StudentListNode(position, male);
            new_node->set_next(first);
            first = new_node;
            size++;
        }
        StudentListNode* get_first() const {
            return first;
        }
        int get_size() const {
            return size;
        }
};

class Student {
    string name;
    int classroom_id;
    bool male;
    public:
        Student(const char* init_name, int init_classroom_id, bool init_male)
        :   name(init_name), classroom_id(init_classroom_id), male(init_male) { }
        bool is_male() const {
            return male;
        }
        int get_classroom_id() const {
            return classroom_id;
        }
        void print() const {
            cout << name << ", class " << classroom_id + 1 << (male ? ", male" : ", female") << endl;
        }
};

class Pair {
    Student* first;
    Student* second;
    public:
        Pair(Student* init_first, Student* init_second) {
            first = init_first;
            second = init_second;
        }
        Pair* merge(Pair* other) {
            if (first == NULL) {
                first = second;
                second = NULL;////////simplify later
            }
            if (second == NULL) {
                if (other->first != NULL) {
                    second = other->first;
                }
                else {
                    second = other->second;
                }
            }
            else {
                return NULL;
            }
            delete other;
            return this;
        }
        void swap(Pair* other, bool male) {
            Student *temp, **first_to_swap, **second_to_swap;
            if (((this->first != NULL) && (this->first->is_male() == male)) || ((this->first == NULL) && (this->second->is_male() != male))) {
                first_to_swap = &this->first;
            }
            else {
                first_to_swap = &this->second;
            }
            if (((other->first != NULL) && (other->first->is_male() == male)) || ((other->first == NULL) && (other->second->is_male() != male))) {
                second_to_swap = &other->first;
            }
            else {
                second_to_swap = &other->second;
            }
            (*first_to_swap)->print();
            temp = *first_to_swap;
            *first_to_swap = *second_to_swap;
            *second_to_swap = temp;
        }
        Student* get_student(bool male) const {
            if ((first != NULL) && (first->is_male() == male)) {
                return first;
            }
            else if ((second != NULL) && (second->is_male() == male)) {
                return second;
            }
            else {
                return NULL;
            }
        }
        bool male_first() const {
            return first->is_male();
        }
        bool only_male() const {
            return ((first == NULL) && ((second != NULL) && second->is_male())) || (((first != NULL) && first->is_male()) && (second == NULL));
        }
        bool only_female() const {
            return ((first == NULL) && ((second != NULL) && !second->is_male())) || (((first != NULL) && !first->is_male()) && (second == NULL));
        }
        void print(int position) const {
            cout << "Position " << position + 1 << ":" << endl;
            if (first != NULL) {
                first->print();
            }
            else {
                cout << "Empty" << endl;
            }
            if (second != NULL) {
                second->print();
            }
            else {
                cout << "Empty" << endl;
            }
        }
};

class Sequence {
    int messiness;
    int size;
    Pair** pairs;
    public:
        Sequence(Student** students, int student_amount)
        :   messiness(0), size((student_amount + 1)/2) {
            int i, male_amount = 0;
            for (i = 0 ; i < student_amount ; i++) {
                if (students[i]->is_male()) {
                    male_amount++;
                }
            }
            if (male_amount < (student_amount/2) || male_amount > ((student_amount + 1)/2)) {
                cout << "Throw exception" << endl;
                exit(-1);
            }
            pairs = new Pair*[size];
            Student *male, *female;
            bool is_male = true;
            int j = 0, k = 0;
            for (i = 0 ; i < size ; i++) {
                male = NULL;
                female = NULL;
                for ( ; j < student_amount ; j++) {
                    if (students[j]->is_male()) {
                        male = students[j];
                        j++;
                        break;
                    }
                }
                for ( ; k < student_amount ; k++) {
                    if (!students[k]->is_male()) {
                        female = students[k];
                        k++;
                        break;
                    }
                }
                if (i % 2) {
                    pairs[i] = new Pair(male, female);
                }
                else {
                    pairs[i] = new Pair(female, male);
                }
            }
        }
        ~Sequence() {
            for (int i = 0 ; i < size ; i++) {
                delete pairs[i];
            }
            delete[] pairs;
        }
        Pair* trim() {
            Pair** new_pairs = new Pair*[size - 1];
            for (int i = 0 ; i < size - 1 ; i++) {
                new_pairs[i] = pairs[i];
            }
            Pair* excess = pairs[size - 1];
            delete[] pairs;
            pairs = new_pairs;
            size--;
            return excess;
        }
        Pair* trim_time_efficient() {
            size--;
            return pairs[size];
        }
        void append(Pair** extra_pairs, int extra_amount) {
            Pair** new_pairs = new Pair*[size + extra_amount];
            for (int i = 0 ; i < size ; i++) {
                new_pairs[i] = pairs[i];
            }
            for (int i = 0 ; i < extra_amount ; i++) {
                new_pairs[i + size] = extra_pairs[i];
            }
            delete[] pairs;
            pairs = new_pairs;
            size += extra_amount;
        }
        void increase_messiness(int amount) {
            messiness += amount;
        }
        bool excess_male() const {
            if (pairs[size - 1]->only_male()) {
                return true;
            }
            else {
                return false;
            }
        }
        bool excess_female() const {
            if (pairs[size - 1]->only_female()) {
                return true;
            }
            else {
                return false;
            }
        }
        Pair* get_last_full_pair() const {
            return (pairs[size - 1]->only_female() || pairs[size - 1]->only_male()) ? pairs[size - 2] : pairs[size - 1];
        }
        int get_size() const {
            return size;
        }
        Pair* get_ith(int i) const {
            return pairs[i];
        }
        void print(int tquiet, int tmessy) const {
            for (int i = 0 ; i < size ; i++) {
                pairs[i]->print(i);
            }
            cout << ((messiness < tquiet) ? "What a quiet class!" : ((messiness <= tmessy) ? "Please, be quiet!" : "What a mess!")) << endl;
        }
};

class School {
    Sequence** sequences;
    int size;
    int tquiet, tmessy;
    public:
        School(Sequence** init_sequences, int sequence_amount, int init_tquiet, int init_messy)
        :   sequences(init_sequences), tquiet(init_tquiet), tmessy(init_messy), size(sequence_amount) {
            int extra_males = 0, extra_females = 0;
            for (int i = 0 ; i < sequence_amount ; i++) {
                if (sequences[i]->excess_male()) {
                    extra_males++;
                }
                else if (sequences[i]->excess_female()) {
                    extra_females++;
                }
            }
            int extra_pair_amount = (extra_males < extra_females) ? extra_males : extra_females;
            if (extra_pair_amount != 0) {
                Pair* extra_pairs[extra_pair_amount];
                Pair *male, *female;
                bool male_first = !sequences[0]->get_last_full_pair()->male_first();
                int j = 0, k = 0;
                for (int i = 0 ; i < extra_pair_amount ; i++, male_first = !male_first) {
                    for ( ; j < sequence_amount ; j++) {
                        if (sequences[j]->excess_male()) {
                            male = sequences[j]->trim();
                            j++;
                            break;
                        }
                    }
                    for ( ; k < sequence_amount ; k++) {
                        if (sequences[k]->excess_female()) {
                            female = sequences[k]->trim();
                            k++;
                            break;
                        }
                    }
                    if (male_first) {
                        extra_pairs[i] = male->merge(female);
                    }
                    else {
                        extra_pairs[i] = female->merge(male);
                    }
                }
                sequences[0]->append(extra_pairs, extra_pair_amount);
            }
        }
        void mess() {
            const int messiness_chance = 5;
            StudentList* list;
            for (int i = 0 ; i < size ; i++) {
                list = new StudentList;
                int continuous_messy = 0;
                bool enough_continuous = false;
                for (int j = 0 ; j < sequences[i]->get_size() ; j++) {
                    if (!(rand() % messiness_chance)) {
                        continuous_messy++;
                        if (sequences[i]->get_ith(j)->only_male()) {
                            list->pushFront(j, true);
                        }
                        else if (sequences[i]->get_ith(j)->only_female()) {
                            list->pushFront(j, false);
                        }
                        else {
                            if (rand() % 2) {
                                list->pushFront(j, true);
                                list->pushFront(j, false);
                            }
                            else {
                                list->pushFront(j, rand() % 2);
                            }
                        }
                    }
                    else {
                        continuous_messy = 0;
                    }
                    if (continuous_messy == 3) {
                        enough_continuous = true;
                    }
                }
                if (list->get_size() <= 2) {
                    int other_pair_position;
                    Pair *messy_pair, *other_pair;
                    for
                    (StudentListNode* messy_student = list->get_first() ;
                    messy_student != NULL ;
                    messy_student = messy_student->get_next())
                    {   
                        messy_pair = sequences[i]->get_ith(messy_student->get_position());
                        sequences[messy_pair->get_student(messy_student->is_male())->get_classroom_id()]->increase_messiness(1);
                    }
                    for
                    (StudentListNode* messy_student = list->get_first() ;
                    messy_student != NULL ;
                    messy_student = messy_student->get_next())
                    {
                        while (true) {
                            other_pair_position = rand() % sequences[i]->get_size();
                            if (other_pair_position != messy_student->get_position()) {
                                break;
                            }
                        }
                        messy_pair = sequences[i]->get_ith(messy_student->get_position());
                        other_pair = sequences[i]->get_ith(other_pair_position);
                        cout << "Student being moved:" << endl;
                        messy_pair->swap(other_pair, messy_student->is_male());
                        cout << "Sequence " << i + 1 << ":" << endl;
                        sequences[i]->print(tquiet, tmessy);
                    }
                }
                else if (!enough_continuous) {
                    int other_pair_position;
                    int other_sequence = (i < (size - 1)) ? i + 1 : 0;
                    Pair *messy_pair, *other_pair;
                    for
                    (StudentListNode* messy_student = list->get_first() ;
                    messy_student != NULL ;
                    messy_student = messy_student->get_next())
                    {
                        messy_pair = sequences[i]->get_ith(messy_student->get_position());
                        other_pair_position = rand() % sequences[other_sequence]->get_size();
                        other_pair = sequences[other_sequence]->get_ith(other_pair_position);
                        sequences[messy_pair->get_student(messy_student->is_male())->get_classroom_id()]->increase_messiness(2);
                        messy_pair->swap(other_pair, messy_student->is_male());
                        cout << "Sequence " << i + 1 << ":" << endl;
                        sequences[i]->print(tquiet, tmessy);
                        cout << "Sequence " << other_sequence + 1 << ":" << endl;
                        sequences[other_sequence]->print(tquiet, tmessy);
                    }
                }
                else {
                    int other_pair_position;
                    int other_sequence;
                    Pair *messy_pair, *other_pair;
                    for
                    (StudentListNode* messy_student = list->get_first() ;
                    messy_student != NULL ;
                    messy_student = messy_student->get_next())
                    {
                        while (true) {
                            other_sequence = rand() % size;
                            if (other_sequence != i) {
                                break;
                            }
                        }
                        messy_pair = sequences[i]->get_ith(messy_student->get_position());
                        other_pair_position = rand() % sequences[other_sequence]->get_size();
                        other_pair = sequences[other_sequence]->get_ith(other_pair_position);
                        sequences[messy_pair->get_student(messy_student->is_male())->get_classroom_id()]->increase_messiness(2);
                        messy_pair->swap(other_pair, messy_student->is_male());
                        cout << "Sequence " << i + 1 << ":" << endl;
                        sequences[i]->print(tquiet, tmessy);
                        cout << "Sequence " << other_sequence + 1 << ":" << endl;
                        sequences[other_sequence]->print(tquiet, tmessy);
                    }
                }
                delete list;
            }
        }
        void print() const {
            for (int i = 0 ; i < size ; i++) {
                cout << "Sequence " << i + 1 << ":" << endl;
                sequences[i]->print(tquiet, tmessy);
            }
        }
};

int main(int argc, char* argv[]) {
    if (argc != 5) {
        cerr << "Wrong number of arguments" << endl;
        return 1;
    }
    int k = atoi(argv[1]), l = atoi(argv[2]), tquiet = atoi(argv[3]), tmessy = atoi(argv[4]);
    if (tquiet > tmessy) {
        cerr << "Quiet threshold (third argument) should be lower than messy threshold (fourth argument)" << endl;
        return 2;
    }
    if (k < 2) {
        cerr << "There must be at least two classes (first argument)" << endl;
        return 3;
    }
    int student_num = 21*k;
    Student* students[k][21];
    for (int i = 0 ; i < k ; i++) {
        if (i % 2) {
            for (int j = 0 ; j < 10 ; j++) {
                students[i][j] = new Student(male_names[rand() % 18], i, true);
            }
            for (int j = 10 ; j < 21 ; j++) {
                students[i][j] = new Student(female_names[rand() % 18], i, false);
            }
        }
        else {
            for (int j = 0 ; j < 11 ; j++) {
                students[i][j] = new Student(male_names[rand() % 18], i, true);
            }
            for (int j = 11 ; j < 21 ; j++) {
                students[i][j] = new Student(female_names[rand() % 18], i, false);
            }
        }
    }
    Sequence* sequences[k];
    for (int i = 0 ; i < k ; i++) {
        sequences[i] = new Sequence(students[i], 21);
    }
    School school(sequences, k, tquiet, tmessy);
    school.print();
    srand(time(NULL));
    for (int i = 0 ; i < l ; i++) {
        school.mess();
    }
    school.print();
    for (int i = 0 ; i < k ; i++) {
        for (int j = 0 ; j < 21 ; j++) {
            delete students[i][j];
        }
    }
    for (int i = 0 ; i < k ; i++) {
        delete sequences[i];
    }
    return 0;
}