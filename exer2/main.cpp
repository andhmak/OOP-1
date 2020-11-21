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
            else if (second == NULL) {
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
    int size;
    Pair** pairs;
    public:
        Queue(Student** students, int student_ammount)
        :   messiness(0), size((student_ammount + 1)/2) {
            int i, male_ammount = 0;
            for (i = 0 ; i < student_ammount ; i++) {
                if (students[i]->is_male()) {
                    male_ammount++;
                }
            }
            if (male_ammount < (student_ammount/2) || male_ammount > ((student_ammount + 1)/2)) {
                cout << "Throw exception" << endl;
                exit(-1);
            }
            bool positioned[student_ammount];
            for (i = 0 ; i < student_ammount ; i++) {
                positioned[i] = false;
            }
            pairs = new Pair*[size];
            Student *first, *second;
            bool is_male = true;
            for (i = 0 ; i < size ; i++) {
                first = NULL;
                second = NULL;
                for (int j = 0 ; j < student_ammount ; j++) {
                    if (!positioned[j]) {
                        if (students[j]->is_male() == is_male) {
                            first = students[j];
                            positioned[j] = true;
                            break;
                        }
                    }
                }
                is_male = !is_male;
                for (int j = 0 ; j < student_ammount ; j++) {
                    if (!positioned[j]) {
                        if (students[j]->is_male() == is_male) {
                            second = students[j];
                            positioned[j] = true;
                            break;
                        }
                    }
                }
                pairs[i] = new Pair(first, second);
            }
        }
        ~Queue() {
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
        void append(Pair** extra_pairs, int extra_ammount) {
            Pair** new_pairs = new Pair*[size + extra_ammount];
            for (int i = 0 ; i < size ; i++) {
                new_pairs[i] = pairs[i];
            }
            for (int i = 0 ; i < extra_ammount ; i++) {
                new_pairs[i + size] = extra_pairs[i];
            }
            delete[] pairs;
            pairs = new_pairs;
            size += extra_ammount;
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
        void print(int tquiet, int tmessy) const {
            for (int i = 0 ; i < size ; i++) {
                pairs[i]->print(i);
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
                Pair* extra_pairs[extra_pair_ammount];
                Pair *male, *female;
                bool male_first = !queues[0]->get_last_full_pair()->male_first();
                for (int i = 0 ; i < extra_pair_ammount ; i++, male_first = !male_first) {
                    for (int j = 0 ; j < queue_ammount ; j++) {
                        if (queues[j]->excess_male()) {
                            male = queues[j]->trim();
                            break;
                        }
                    }
                    for (int j = 0 ; j < queue_ammount ; j++) {
                        if (queues[j]->excess_female()) {
                            female = queues[j]->trim();
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
                queues[0]->append(extra_pairs, extra_pair_ammount);
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