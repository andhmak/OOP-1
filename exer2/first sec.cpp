#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include "names.h"
////say empty spaces can be moved
using namespace std;

class Student {
    string name;
    int classroom_id;
    bool male;
    bool messy;
    public:
        Student(const char* init_name, int init_classroom_id, bool init_male)
        :   name(init_name), classroom_id(init_classroom_id), male(init_male), messy(0) { }
        bool is_male() const {
            return male;
        }
        int get_classroom_id() const {
            return classroom_id;
        }
        bool get_messy() const {
            return messy;
        }
        void set_messy(bool to_be_messy) {
            messy = to_be_messy;
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
        void swap(Pair* other, bool first) {
            Student *temp, **to_swap_with;
            bool maleness = this->first->is_male();
            if (((other->first != NULL) && (other->first->is_male() == maleness)) || ((other->first == NULL) && (other->second->is_male() != maleness))) {
                to_swap_with = &other->first;
            }
            else {
                to_swap_with = &other->second;
            }
            temp = this->first;
            this->first = *to_swap_with;
            *to_swap_with = temp;
        }
        Student* get_student(bool first_one) const {
            if (first_one) {
                return first;
            }
            else {
                return second;
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
            int messy_amount[size];
            for (int i = 0 ; i < size ; i++) {
                messy_amount[i] = 0;
            }
            bool enough_continuous[size];
            for (int i = 0 ; i < size ; i++) {
                enough_continuous[i] = false;
            }
            for (int i = 0 ; i < size ; i++) {
                cout << i << endl;
                int continuous_messy = 0;
                for (int j = 0 ; j < sequences[i]->get_size() ; j++) {
                    if (!(rand() % messiness_chance)) {
                        cout << "   " << j << endl;
                        Pair* curr_pair = sequences[i]->get_ith(j);
                        continuous_messy++;
                        messy_amount[i]++;
                        if (curr_pair->only_male()) {
                            curr_pair->get_student(true)->set_messy(true);
                        }
                        else if (curr_pair->only_female()) {
                            curr_pair->get_student(false)->set_messy(true);
                        }
                        else {
                            if (rand() % 2) {
                                curr_pair->get_student(true)->set_messy(true);
                                curr_pair->get_student(false)->set_messy(true);
                            }
                            else {
                                curr_pair->get_student(rand() % 2)->set_messy(true);
                            }
                        }
                    }
                    else {
                        continuous_messy = 0;
                    }
                    if (continuous_messy == 3) {
                        enough_continuous[i] = true;
                    }
                }
            }
            for (int i = 0 ; i < size ; i++) {
                cout << i << endl;
                int sequence_size = sequences[i]->get_size();
                if (messy_amount[i] <= 2) {
                    cout << "case 1" << endl;
                    int other_pair_position;
                    Pair *curr_pair, *other_pair;
                    Student *male, *female;
                    for (int j = 0 ; j < sequence_size ; j++) {
                        cout << "   " << j << endl;
                        curr_pair = sequences[i]->get_ith(j);
                        male = curr_pair->get_student(true);
                        female = curr_pair->get_student(false);
                        if ((male != NULL) && male->get_messy()) {
                            male->set_messy(false);
                            while (true) {
                                other_pair_position = rand() % sequence_size;
                                if (other_pair_position != j) {
                                    break;
                                }
                            }
                            other_pair = sequences[i]->get_ith(other_pair_position);
                            sequences[male->get_classroom_id()]->increase_messiness(1);
                            if ((female != NULL) && female->get_messy()) {
                                female->set_messy(false);
                                sequences[female->get_classroom_id()]->increase_messiness(1);
                                cout << "Students being messy:" << endl;
                                male->print();
                                female->print();
                            }
                            else {
                                cout << "Students being messy:" << endl;
                                male->print();
                            }
                            Student *other_male = other_pair->get_student(true), *other_female = other_pair->get_student(false);
                            if ((other_male != NULL) && (other_male->get_messy())) {
                                other_male->set_messy(false);
                                other_male->print();
                                sequences[other_male->get_classroom_id()]->increase_messiness(1);
                            }
                            if ((other_female != NULL) && (other_female->get_messy())) {
                                other_female->set_messy(false);
                                other_female->print();
                                sequences[other_female->get_classroom_id()]->increase_messiness(1);
                            }
                            curr_pair->swap(other_pair, true);
                            cout << "Sequence " << i + 1 << ":" << endl;
                            sequences[i]->print(tquiet, tmessy);
                        }
                        else {
                            if ((female != NULL) && female->get_messy()) {
                                female->set_messy(false);
                                while (true) {
                                    other_pair_position = rand() % sequence_size;
                                    if (other_pair_position != j) {
                                        break;
                                    }
                                }
                                other_pair = sequences[i]->get_ith(other_pair_position);
                                sequences[female->get_classroom_id()]->increase_messiness(1);
                                cout << "Students being messy:" << endl;
                                female->print();
                                Student *other_male = other_pair->get_student(true), *other_female = other_pair->get_student(false);
                                if ((other_male != NULL) && (other_male->get_messy())) {
                                    other_male->set_messy(false);
                                    other_male->print();
                                    sequences[other_male->get_classroom_id()]->increase_messiness(1);
                                }
                                if ((other_female != NULL) && (other_female->get_messy())) {
                                    other_female->set_messy(false);
                                    other_female->print();
                                    sequences[other_female->get_classroom_id()]->increase_messiness(1);
                                }
                                curr_pair->swap(other_pair, false);
                                cout << "Sequence " << i + 1 << ":" << endl;
                                sequences[i]->print(tquiet, tmessy);
                            }
                        }
                    }
                }
                else if (!enough_continuous[i]) {
                    cout << "case 2" << endl;
                    int other_sequence = (i < (size - 1)) ? i + 1 : 0;
                    int other_sequence_size = sequences[other_sequence]->get_size();
                    int other_pair_position;
                    Pair *curr_pair, *other_pair;
                    Student *male, *female;
                    for (int j = 0 ; j < sequence_size ; j++) {
                        cout << "   " << j << endl;
                        curr_pair = sequences[i]->get_ith(j);
                        male = curr_pair->get_student(true);
                        female = curr_pair->get_student(false);
                        if ((male != NULL) && male->get_messy()) {
                            male->set_messy(false);
                            other_pair_position = rand() % other_sequence_size;
                            other_pair = sequences[other_sequence]->get_ith(other_pair_position);
                            sequences[male->get_classroom_id()]->increase_messiness(2);
                            if ((female != NULL) && female->get_messy()) {
                                female->set_messy(false);
                                sequences[female->get_classroom_id()]->increase_messiness(2);
                                cout << "Students being messy:" << endl;
                                male->print();
                                female->print();
                            }
                            else {
                                cout << "Students being messy:" << endl;
                                male->print();
                            }
                            Student *other_male = other_pair->get_student(true), *other_female = other_pair->get_student(false);
                            if ((other_male != NULL) && (other_male->get_messy())) {
                                other_male->set_messy(false);
                                other_male->print();
                                sequences[other_male->get_classroom_id()]->increase_messiness(1);
                            }
                            if ((other_female != NULL) && (other_female->get_messy())) {
                                other_female->set_messy(false);
                                other_female->print();
                                sequences[other_female->get_classroom_id()]->increase_messiness(1);
                            }
                            curr_pair->swap(other_pair, true);
                            cout << "Sequence " << i + 1 << ":" << endl;
                            sequences[i]->print(tquiet, tmessy);
                            cout << "Sequence " << other_sequence + 1 << ":" << endl;
                            sequences[other_sequence]->print(tquiet, tmessy);
                        }
                        else {
                            if ((female != NULL) && female->get_messy()) {
                                female->set_messy(false);
                                other_pair_position = rand() % other_sequence_size;
                                other_pair = sequences[other_sequence]->get_ith(other_pair_position);
                                sequences[female->get_classroom_id()]->increase_messiness(2);
                                cout << "Students being messy:" << endl;
                                female->print();
                                Student *other_male = other_pair->get_student(true), *other_female = other_pair->get_student(false);
                                if ((other_male != NULL) && (other_male->get_messy())) {
                                    other_male->set_messy(false);
                                    other_male->print();
                                    sequences[other_male->get_classroom_id()]->increase_messiness(1);
                                }
                                if ((other_female != NULL) && (other_female->get_messy())) {
                                    other_female->set_messy(false);
                                    other_female->print();
                                    sequences[other_female->get_classroom_id()]->increase_messiness(1);
                                }
                                curr_pair->swap(other_pair, false);
                                cout << "Sequence " << i + 1 << ":" << endl;
                                sequences[i]->print(tquiet, tmessy);
                                cout << "Sequence " << other_sequence + 1 << ":" << endl;
                                sequences[other_sequence]->print(tquiet, tmessy);
                            }
                        }
                    }
                }
                else {
                    cout << "case 3" << endl;
                    int other_sequence;
                    int other_sequence_size;
                    int other_pair_position;
                    Pair *curr_pair, *other_pair;
                    Student *male, *female;
                    for (int j = 0 ; j < sequence_size ; j++) {
                        cout << "   " << j << endl;
                        curr_pair = sequences[i]->get_ith(j);
                        male = curr_pair->get_student(true);
                        female = curr_pair->get_student(false);
                        if ((male != NULL) && male->get_messy()) {
                            male->set_messy(false);
                            while (true) {
                                other_sequence = rand() % size;
                                if (other_sequence != i) {
                                    break;
                                }
                            }
                            other_sequence_size = sequences[other_sequence]->get_size();
                            other_pair_position = rand() % other_sequence_size;
                            other_pair = sequences[other_sequence]->get_ith(other_pair_position);
                            sequences[male->get_classroom_id()]->increase_messiness(1);
                            if ((female != NULL) && female->get_messy()) {
                                female->set_messy(false);
                                sequences[female->get_classroom_id()]->increase_messiness(1);
                                cout << "Students being messy:" << endl;
                                male->print();
                                female->print();
                            }
                            else {
                                cout << "Students being messy:" << endl;
                                male->print();
                            }
                            Student *other_male = other_pair->get_student(true), *other_female = other_pair->get_student(false);
                            if ((other_male != NULL) && (other_male->get_messy())) {
                                other_male->set_messy(false);
                                other_male->print();
                                sequences[other_male->get_classroom_id()]->increase_messiness(1);
                            }
                            if ((other_female != NULL) && (other_female->get_messy())) {
                                other_female->set_messy(false);
                                other_female->print();
                                sequences[other_female->get_classroom_id()]->increase_messiness(1);
                            }
                            curr_pair->swap(other_pair, true);
                            cout << "Sequence " << i + 1 << ":" << endl;
                            sequences[i]->print(tquiet, tmessy);
                            cout << "Sequence " << other_sequence + 1 << ":" << endl;
                            sequences[other_sequence]->print(tquiet, tmessy);
                        }
                        else {
                            if ((female != NULL) && female->get_messy()) {
                                female->set_messy(false);
                                while (true) {
                                    other_sequence = rand() % size;
                                    if (other_sequence != i) {
                                        break;
                                    }
                                }
                                other_sequence_size = sequences[other_sequence]->get_size();
                                other_pair_position = rand() % other_sequence_size;
                                other_pair = sequences[other_sequence]->get_ith(other_pair_position);
                                sequences[female->get_classroom_id()]->increase_messiness(1);
                                cout << "Students being messy:" << endl;
                                female->print();
                                Student *other_male = other_pair->get_student(true), *other_female = other_pair->get_student(false);
                                if ((other_male != NULL) && (other_male->get_messy())) {
                                    other_male->set_messy(false);
                                    other_male->print();
                                    sequences[other_male->get_classroom_id()]->increase_messiness(1);
                                }
                                if ((other_female != NULL) && (other_female->get_messy())) {
                                    other_female->set_messy(false);
                                    other_female->print();
                                    sequences[other_female->get_classroom_id()]->increase_messiness(1);
                                }
                                curr_pair->swap(other_pair, false);
                                cout << "Sequence " << i + 1 << ":" << endl;
                                sequences[i]->print(tquiet, tmessy);
                                cout << "Sequence " << other_sequence + 1 << ":" << endl;
                                sequences[other_sequence]->print(tquiet, tmessy);
                            }
                        }
                    }
                }
            }
            cout << "end" << endl;
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
    int student_num = 5*k;
    Student* students[k][5];
    for (int i = 0 ; i < k ; i++) {
        if (i % 2) {
            for (int j = 0 ; j < 2 ; j++) {
                students[i][j] = new Student(male_names[rand() % 18], i, true);
            }
            for (int j = 2 ; j < 5 ; j++) {
                students[i][j] = new Student(female_names[rand() % 18], i, false);
            }
        }
        else {
            for (int j = 0 ; j < 3 ; j++) {
                students[i][j] = new Student(male_names[rand() % 18], i, true);
            }
            for (int j = 3 ; j < 5 ; j++) {
                students[i][j] = new Student(female_names[rand() % 18], i, false);
            }
        }
    }
    Sequence* sequences[k];
    for (int i = 0 ; i < k ; i++) {
        sequences[i] = new Sequence(students[i], 5);
    }
    School school(sequences, k, tquiet, tmessy);
    school.print();
    cout << "---------------------------------------------------------------" << endl;
    srand(time(NULL));
    for (int i = 0 ; i < l ; i++) {
        school.mess();
    }
    school.print();
    for (int i = 0 ; i < k ; i++) {
        for (int j = 0 ; j < 5 ; j++) {
            delete students[i][j];
        }
    }
    for (int i = 0 ; i < k ; i++) {
        delete sequences[i];
    }
    return 0;
}