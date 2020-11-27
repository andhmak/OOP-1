/* File: kindergarten.cpp */

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include "kindergarten.h"

using namespace std;

Student* Pair::get_student(bool male) const {
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

Pair* Pair::merge(Pair* other) {
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

void Pair::swap(Pair* other, bool male) {
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
    temp = *first_to_swap;
    *first_to_swap = *second_to_swap;
    *second_to_swap = temp;
}

void Pair::print(int position) const {
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


Sequence::Sequence(Student** students, int student_amount)
:   messiness(0), size((student_amount + 1)/2) {
    int male_amount = 0;
    for (int i = 0 ; i < student_amount ; i++) {
        if (students[i]->is_male()) {
            male_amount++;
        }
    }
    if (male_amount < (student_amount/2) || male_amount > ((student_amount + 1)/2)) {
        cout << "Throw exception" << endl;
        exit(-1);
    }
    pairs = new Pair*[size];
    int j = 0, k = 0;
    for (int i = 0 ; i < size ; i++) {
        Student *male = NULL, *female = NULL;
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

Sequence::~Sequence() {
    for (int i = 0 ; i < size ; i++) {
        delete pairs[i];
    }
    delete[] pairs;
}

Pair* Sequence::trim() {
    size--;
    return pairs[size];
}

void Sequence::append(Pair** extra_pairs, int extra_amount) {
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

void Sequence::print(double tquiet, double tmessy) const {
    double mess_percentage = messiness / (double) (2*size - (this->excess_male() || this->excess_female()));
    for (int i = 0 ; i < size ; i++) {
        pairs[i]->print(i);
    }
    cout << ((mess_percentage < tquiet) ? "What a quiet class!" : ((mess_percentage <= tmessy) ? "Please, be quiet!" : "What a mess!")) << endl;
}


Kindergarten::Kindergarten(Sequence** init_sequences, int sequence_amount, double init_tquiet, double init_messy)
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
        bool male_first = !sequences[0]->get_last_full_pair()->male_first();
        int j = 0, k = 0;
        for (int i = 0 ; i < extra_pair_amount ; i++, male_first = !male_first) {
            Pair *male, *female;
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

void Kindergarten::cause_mess() {
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
        int continuous_messy = 0;
        for (int j = 0 ; j < sequences[i]->get_size() ; j++) {
            if (!(rand() % messiness_chance)) {
                Pair* curr_pair = sequences[i]->get_pair(j);
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
        int sequence_size = sequences[i]->get_size();
        if (messy_amount[i] <= 2) {
            int other_pair_position;
            for (int j = 0 ; j < sequence_size ; j++) {
                Pair* curr_pair = sequences[i]->get_pair(j);
                Student* male = curr_pair->get_student(true);
                Student* female = curr_pair->get_student(false);
                if (((male != NULL) && male->get_messy()) || ((female != NULL) && female->get_messy())) {
                    cout << "Students being messy:" << endl;
                    if ((male != NULL) && male->get_messy()) {
                        male->set_messy(false);
                        sequences[male->get_classroom_id()]->increase_messiness(1);
                        male->print();
                    }
                    if ((female != NULL) && female->get_messy()) {
                        female->set_messy(false);
                        sequences[female->get_classroom_id()]->increase_messiness(1);
                        female->print();
                    }
                    while (true) {
                        other_pair_position = rand() % sequence_size;
                        if (other_pair_position != j) {
                            break;
                        }
                    }
                    Pair* other_pair = sequences[i]->get_pair(other_pair_position);
                    Student *other_male = other_pair->get_student(true), *other_female = other_pair->get_student(false);
                    if ((other_male != NULL) && (other_male->get_messy())) {
                        other_male->set_messy(false);
                        sequences[other_male->get_classroom_id()]->increase_messiness(1);
                        other_male->print();
                    }
                    if ((other_female != NULL) && (other_female->get_messy())) {
                        other_female->set_messy(false);
                        sequences[other_female->get_classroom_id()]->increase_messiness(1);
                        other_female->print();
                    }
                    curr_pair->swap(other_pair, true);
                    cout << "Sequence " << i + 1 << ":" << endl;
                    sequences[i]->print(tquiet, tmessy);
                }
            }
        }
        else if (!enough_continuous[i]) {
            int other_sequence_position = (i < (size - 1)) ? i + 1 : 0;
            int other_messiness = 1 + (messy_amount[other_sequence_position] > 2);
            int other_sequence_size = sequences[other_sequence_position]->get_size();
            for (int j = 0 ; j < sequence_size ; j++) {
                Pair* curr_pair = sequences[i]->get_pair(j);
                Student* male = curr_pair->get_student(true);
                Student* female = curr_pair->get_student(false);
                if (((male != NULL) && male->get_messy()) || ((female != NULL) && female->get_messy())) {
                    cout << "Students being messy:" << endl;
                    if ((male != NULL) && male->get_messy()) {
                        male->set_messy(false);
                        sequences[male->get_classroom_id()]->increase_messiness(2);
                        male->print();
                    }
                    if ((female != NULL) && female->get_messy()) {
                        female->set_messy(false);
                        sequences[female->get_classroom_id()]->increase_messiness(2);
                        female->print();
                    }
                    int other_pair_position = rand() % other_sequence_size;
                    Pair* other_pair = sequences[other_sequence_position]->get_pair(other_pair_position);
                    Student *other_male = other_pair->get_student(true), *other_female = other_pair->get_student(false);
                    if ((other_male != NULL) && (other_male->get_messy())) {
                        other_male->set_messy(false);
                        other_male->print();
                        sequences[other_male->get_classroom_id()]->increase_messiness(other_messiness);
                    }
                    if ((other_female != NULL) && (other_female->get_messy())) {
                        other_female->set_messy(false);
                        other_female->print();
                        sequences[other_female->get_classroom_id()]->increase_messiness(other_messiness);
                    }
                    curr_pair->swap(other_pair, true);
                    cout << "Sequence " << i + 1 << ":" << endl;
                    sequences[i]->print(tquiet, tmessy);
                    cout << "Sequence " << other_sequence_position + 1 << ":" << endl;
                    sequences[other_sequence_position]->print(tquiet, tmessy);
                }
            }
        }
        else {
            for (int j = 0 ; j < sequence_size ; j++) {
                Pair* curr_pair = sequences[i]->get_pair(j);
                Student* male = curr_pair->get_student(true);
                Student* female = curr_pair->get_student(false);
                if (((male != NULL) && male->get_messy()) || ((female != NULL) && female->get_messy())) {
                    cout << "Students being messy:" << endl;
                    if ((male != NULL) && male->get_messy()) {
                        male->set_messy(false);
                        sequences[male->get_classroom_id()]->increase_messiness(2);
                        male->print();
                    }
                    if ((female != NULL) && female->get_messy()) {
                        female->set_messy(false);
                        sequences[female->get_classroom_id()]->increase_messiness(2);
                        female->print();
                    }
                    int other_sequence_position;
                    while (true) {
                        other_sequence_position = rand() % size;
                        if (other_sequence_position != i) {
                            break;
                        }
                    }
                    int other_messiness = 1 + (messy_amount[other_sequence_position] > 2);
                    cout << other_messiness << "-----------------------------------------" << endl;
                    int other_pair_position = rand() % sequences[other_sequence_position]->get_size();
                    Pair* other_pair = sequences[other_sequence_position]->get_pair(other_pair_position);
                    Student *other_male = other_pair->get_student(true), *other_female = other_pair->get_student(false);
                    if ((other_male != NULL) && (other_male->get_messy())) {
                        other_male->set_messy(false);
                        other_male->print();
                        sequences[other_male->get_classroom_id()]->increase_messiness(other_messiness);
                    }
                    if ((other_female != NULL) && (other_female->get_messy())) {
                        other_female->set_messy(false);
                        other_female->print();
                        sequences[other_female->get_classroom_id()]->increase_messiness(other_messiness);
                    }
                    curr_pair->swap(other_pair, true);
                    cout << "Sequence " << i + 1 << ":" << endl;
                    sequences[i]->print(tquiet, tmessy);
                    cout << "Sequence " << other_sequence_position + 1 << ":" << endl;
                    sequences[other_sequence_position]->print(tquiet, tmessy);
                }
            }
        }
    }
}

void Kindergarten::print() const {
    for (int i = 0 ; i < size ; i++) {
        cout << "Sequence " << i + 1 << ":" << endl;
        sequences[i]->print(tquiet, tmessy);
    }
}

//    Pair* trim_space_efficient() {
//        Pair** new_pairs = new Pair*[size - 1];
//        for (int i = 0 ; i < size - 1 ; i++) {
//            new_pairs[i] = pairs[i];
//        }
//        Pair* excess = pairs[size - 1];
//        delete[] pairs;
//        pairs = new_pairs;
//        size--;
//        return excess;
//    }