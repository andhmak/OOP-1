#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include "names.h"

using namespace std;

class Student {
    string name;
    int classroom_id;
    bool male;
    public:
        Student(const char* init_name, int init_classroom_id, bool init_male)
        :   name(init_name), classroom_id(init_classroom_id), male(init_male) {
            cout << "New student " << name << (male ? " male" : " female") << endl;
        }
        bool is_male() const {
            return male;
        }
        void print() const {
            cout << name << ", class " << classroom_id + 1 << (male ? ", male" : ", female") << endl;
        }
};

class Pair {
    Student* first;
    Student* second;
    Pair* next;
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
                cout << "mistake" << endl;///////////////////remove later
                exit(-1);
            }
            delete other;
            return this;
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
        bool is_full() const {
            return (first != NULL) && (second != NULL);
        }
        void set_next(Pair* next_pair) {
            next = next_pair;
        }
        Pair* get_next() const {
            return next;
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

class Queue {
    int messiness;
    Pair *first_pair, *last_full;
    public:
        Queue(Student** students, int student_ammount)
        :   messiness(0) {
            int i, male_ammount = 0, size = (student_ammount + 1)/2;
            for (i = 0 ; i < student_ammount ; i++) {
                if (students[i]->is_male()) {
                    male_ammount++;
                }
            }
            if (male_ammount < (student_ammount/2) || male_ammount > ((student_ammount + 1)/2)) {
                cout << "Throw exception" << endl;
                exit(-1);
            }
            Student *first, *second, *temp;
            bool is_male = true;
            Pair *prev_pair, *curr_pair;
            int j = 0, k = 0;
            for (i = 0 ; i < size ; i++) {
                first = NULL;
                second = NULL;
                for ( ; j < student_ammount ; j++) {
                    if (students[j]->is_male()) {
                        first = students[j];
                        j++;
                        break;
                    }
                }
                for ( ; k < student_ammount ; k++) {
                    if (!students[k]->is_male()) {
                        second = students[k];
                        k++;
                        break;
                    }
                }
                if (i % 2) {
                    temp = first;
                    first = second;
                    second = temp;
                }
                if (i == 0) {
                    first_pair = new Pair(first, second);
                    prev_pair = first_pair;
                }
                else {
                    curr_pair = new Pair(first, second);
                    prev_pair->set_next(curr_pair);
                    curr_pair = prev_pair;
                }
                if (i >= size - 2) {
                    if (prev_pair->is_full()) {
                        last_full = prev_pair;
                    }
                }
            }
        }
        ~Queue() {
            Pair *next_pair, *prev_pair;
            for (prev_pair = first_pair, next_pair = first_pair->get_next() ; prev_pair != NULL ; prev_pair = next_pair, next_pair = next_pair->get_next()) {
                delete prev_pair;
            }
        }
        Pair* trim() {
            Pair* to_return = last_full->get_next();
            last_full->set_next(NULL);
            return to_return;
        }
        void append(Pair* extra_pairs) {
            last_full->set_next(extra_pairs);
        }
        bool excess_male() const {
            if ((last_full->get_next() != NULL) && last_full->get_next()->only_male()) {
                return true;
            }
            else {
                return false;
            }
        }
        bool excess_female() const {
            if ((last_full->get_next() != NULL) && last_full->get_next()->only_female()) {
                return true;
            }
            else {
                return false;
            }
        }
        Pair* get_last_full_pair() const {
            return last_full;
        }
        void print(int tquiet, int tmessy) const {
            Pair *next_pair, *prev_pair;
            int i = 0;
            for (prev_pair = first_pair, next_pair = first_pair->get_next() ; prev_pair != NULL ; prev_pair = next_pair, next_pair = next_pair->get_next(), i++) {
                prev_pair->print(i);
            }
            cout << ((messiness < tquiet) ? "What a quiet class!" : ((messiness <= tmessy) ? "Please, be quiet!" : "What a mess!")) << endl;
        }
};

class School {
    Queue** queues;
    int size;
    int tquiet, tmessy;
    public:
        School(Queue** init_queues, int queue_ammount, int init_tquiet, int init_messy)
        :   queues(init_queues), tquiet(init_tquiet), tmessy(init_tquiet), size(queue_ammount) {
            int extra_males = 0, extra_females = 0;
            for (int i = 0 ; i < queue_ammount ; i++) {
                if (queues[i]->excess_male()) {
                    extra_males++;
                }
                else if (queues[i]->excess_female()) {
                    extra_females++;
                }
            }
            int extra_pair_ammount = (extra_males < extra_females) ? extra_males : extra_females;
            if (extra_pair_ammount != 0) {
                Pair *extra_pairs_first, *extra_pairs_prev, *extra_pairs_next;
                Pair *male, *female;
                bool male_first = !queues[0]->get_last_full_pair()->male_first();
                int j = 0, k = 0;
                for (int i = 0 ; i < extra_pair_ammount ; i++, male_first = !male_first) {
                    for ( ; j < queue_ammount ; j++) {
                        if (queues[j]->excess_male()) {
                            male = queues[j]->trim();
                            j++;
                            break;
                        }
                    }
                    for ( ; k < queue_ammount ; k++) {
                        if (queues[k]->excess_female()) {
                            female = queues[k]->trim();
                            k++;
                            break;
                        }
                    }
                    if (i == 0) {
                        if (male_first) {
                            extra_pairs_first = male->merge(female);
                        }
                        else {
                            extra_pairs_first = female->merge(male);
                        }
                        extra_pairs_prev = extra_pairs_first;
                    }
                    else {
                        if (male_first) {
                            extra_pairs_next = male->merge(female);
                        }
                        else {
                            extra_pairs_next = female->merge(male);
                        }
                        extra_pairs_prev->set_next(extra_pairs_next);
                        extra_pairs_prev = extra_pairs_next;
                    }
                }
                queues[0]->append(extra_pairs_first);
            }
        }
        void print() const {
            for (int i = 0 ; i < size ; i++) {
                queues[i]->print(tquiet, tmessy);
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
    Queue* queues[k];
    for (int i = 0 ; i < k ; i++) {
        queues[i] = new Queue(students[i], 21);
    }
    School school(queues, k, tquiet, tmessy);
    school.print();
    srand(time(NULL));
/*    int messy_number;

    for (int i = 0 ; i < l ; i++) {
        messy_number = rand() % (student_num/5);
        school.mess
    }*/
    school.print();
    for (int i = 0 ; i < k ; i++) {
        for (int j = 0 ; j < 21 ; j++) {
            delete students[i][j];
        }
    }
    for (int i = 0 ; i < k ; i++) {
        delete queues[i];
    }
    return 0;
}