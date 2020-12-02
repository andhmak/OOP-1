/* File: kindergarten.cpp */

#include <iostream>
#include <string>
#include <cstdlib>
#include "kindergarten.h"

using namespace std;

// Συναρτήσεις της Pair

// επιστρέφει τον μαθητή του φύλου που δίνεται σαν όρισμα
Student* Sequence::Pair::get_student(bool male) const {
    if ((first != NULL) && (first->male == male)) {
        return first;
    }
    else if ((second != NULL) && (second->male == male)) {
        return second;
    }
    else {
        return NULL;
    }
}

// εφαρμόζεται σε μη πλήρες ζευγάρι και δέχεται μη πλήρες ζευγάρι, το δεύτερο ζευγάρι πρέπει να έχει δεσμευτεί στον σωρό 
// τα ενώνει και επιστρέφει δείκτη στο νέο, με τον μαθητή του πρώτου ζευγαριού να βρίσκεται στην πρώτη θέση του νέου ζευγαριού
// (οι προϋποθέσεις χρήσης της είναι σχετικά πολύπλοκες αλλά χρησιμοποιείται ελεγχόμενα από συναρτήσεις της Kindergarten, όχι από τον χρήστη)
Sequence::Pair* Sequence::Pair::merge(Pair* other) {
    if (this->first == NULL) {  // ο μαθητής του πρώτου ζευγαριού πρέπει να βρίσκεται στην πρώτη θέση
        this->first = this->second;
    }
    if (other->first != NULL) { // στην δεύτερη θέση θα μπει ο μαθητής του δεύτερου ζευγαριού
        this->second = other->first;
    }
    else {
        this->second = other->second;
    }
    delete other;   // απελευθέρωση μνήμης δεύτερου ζευγαριού
    return this;
}

// αντιμεταθέτει τους μαθητές του φίλου που ορίζεται, μεταξύ των ζευγαριών this και other
void Sequence::Pair::swap(Pair* other, bool male) {
    Student *temp, **first_to_swap, **second_to_swap;
    if (((this->first != NULL) && (this->first->male == male)) || ((this->first == NULL) && (this->second->male != male))) {
        first_to_swap = &this->first;
    }
    else {
        first_to_swap = &this->second;
    }
    if (((other->first != NULL) && (other->first->male == male)) || ((other->first == NULL) && (other->second->male != male))) {
        second_to_swap = &other->first;
    }
    else {
        second_to_swap = &other->second;
    }
    temp = *first_to_swap;
    *first_to_swap = *second_to_swap;
    *second_to_swap = temp;
}

// εκτυπώνει την θέση στην ακολουθία (position) και τους μαθητές του ζεύγους
void Sequence::Pair::print(int position) const {
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

// Συναρτήσεις της Sequence

// Constructor
Sequence::Sequence(Student** students, int student_amount)
:   messiness(0), size((student_amount + 1)/2) {
    // (εφόσον δεν έχουμε διδαχθεί exceptions θεωρώ πώς πάντα τα φύλα των μαθητών είναι κατάλληλα για αν φτιαχθούν ζευγάρια)
    pairs = new Pair*[size];
    int j = 0, k = 0;
    for (int i = 0 ; i < size ; i++) {
        Student *male = NULL, *female = NULL;
        for ( ; j < student_amount ; j++) {
            if (students[j]->male) {
                male = students[j];
                j++;
                break;
            }
        }
        for ( ; k < student_amount ; k++) {
            if (students[k]->male == false) {
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

// Destructor
Sequence::~Sequence() {
    for (int i = 0 ; i < size ; i++) {
        delete pairs[i];
    }
    delete[] pairs;
}

// αφαιρεί το τελευταίο ζευγάρι από την ακολουθία και απιστρέφει δείκτη σε αυτό
// (δεν αντιγράφει τον πίνακα ζευγαριών, αλλά χαραμίζει τον χώρο ενός δείκτη,
// που θεωρώ αποδεκτό προκειμένουν να υπάρχει χρονική βελτίωση)
Sequence::Pair* Sequence::trim() {
    size--;
    return pairs[size];
}

// προσθέτει τα ζευγάρια που δίνονται στο τέλος της ακολουθίας
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

// εκτυπώνει τα ζευγάρια και το κατάλληλο μήνυμα ανάλογα με το ποσοστό αταξίας του τμήματος και τα κατόφλια tquiet και tmessy
void Sequence::print(double tquiet, double tmessy) const {
    double mess_percentage = messiness / (double) (2*size - (this->excess_male() || this->excess_female()));
    for (int i = 0 ; i < size ; i++) {
        pairs[i]->print(i);
    }
    cout << ((mess_percentage < tquiet) ? "What a quiet class!" : ((mess_percentage <= tmessy) ? "Please, be quiet!" : "What a mess!")) << endl;
}

// Συναρτήσεις της Kindergarten

// Constructor
Supersequence::Supersequence(Sequence** init_sequences, int sequence_amount, double init_tquiet, double init_messy)
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
        Sequence::Pair* extra_pairs[extra_pair_amount];
        bool male_first = !sequences[0]->get_last_full_pair()->male_first();
        int j = 0, k = 0;
        for (int i = 0 ; i < extra_pair_amount ; i++, male_first = !male_first) {
            Sequence::Pair *male, *female;
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

// επιλέγονται τυχαία μαθητές να κάνουν αταξίες, οπότε έπειτα γίνονται οι απαραίτητες διαδικασίες
void Supersequence::cause_mess() {
    const int messiness_chance = 5; // πιθανότητα αταξίας (1/messiness_chance)

    // αρχικοποίηση δομής που κρατά το πλήθος των ατάκτων ανά ακολουθία
    int messy_amount[size];
    for (int i = 0 ; i < size ; i++) {
        messy_amount[i] = 0;
    }

    // αρχικοποίηση δομής που κρατά το αν υπάρχουν πάνω από τρία διαδοχικά άττακτα ζευγάρια στην ακολουθία
    bool enough_continuous[size];
    for (int i = 0 ; i < size ; i++) {
        enough_continuous[i] = false;
    }

    // επιλογή τυχαίων μαθητών
    for (int i = 0 ; i < size ; i++) {
        int continuous_messy = 0;
        for (int j = 0 ; j < sequences[i]->size ; j++) {
            if (!(rand() % messiness_chance)) { // κάθε ζευγάρι έχει μια πιθανότητα να είναι άτακτο
                Sequence::Pair* curr_pair = sequences[i]->pairs[j];
                continuous_messy++;
                messy_amount[i]++;
                if (curr_pair->only_male()) {
                    curr_pair->get_student(true)->messy = true;
                }
                else if (curr_pair->only_female()) {
                    curr_pair->get_student(false)->messy = true;
                }
                else {
                    if (rand() % 2) {   // και 1/2 πιθανότητα να είναι και οι δύο μαθητές άτακτοι
                        curr_pair->get_student(true)->messy = true;
                        curr_pair->get_student(false)->messy = true;
                    }
                    else {
                        curr_pair->get_student(rand() % 2)->messy = true;
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

    // μετακίνηση και όλες οι σχετικές διαδικασίες
    for (int i = 0 ; i < size ; i++) {  // για κάθε ακολουθία
        int sequence_size = sequences[i]->size;
        if (messy_amount[i] <= 2) { // πρώτη περίπτωση
            for (int j = 0 ; j < sequence_size ; j++) { // για κάθε ζευγάρι
                Sequence::Pair* curr_pair = sequences[i]->pairs[j];
                Student* male = curr_pair->get_student(true);
                Student* female = curr_pair->get_student(false);
                if (((male != NULL) && male->messy) || ((female != NULL) && female->messy)) {   // αν υπάρχει άτακτος
                    cout << "Students being messy:" << endl;
                    // για το ίδιο το ζευγάρι
                    // αν είναι άτακτο το αγόρι γίνονται οι κατάλληλες διαδικασίες
                    if ((male != NULL) && male->messy) {
                        male->messy = false;     // σταματάει να είναι άτακτο
                        sequences[male->classroom_id]->messiness++; // αυξάνει κατά ένα την αταξία του τμήματός του
                        male->print();              // τυπώνεται
                    }
                    // και αν είναι το κορίτσι
                    if ((female != NULL) && female->messy) {
                        female->messy = false;
                        sequences[female->classroom_id]->messiness++;
                        female->print();
                    }

                    // για το άλλο ζευγάρι
                    int other_pair_position;
                    // επιλέγεται τυχαία ένα διαφορετικό ζευγάρι στην ίδια ακολουθία
                    while (true) {
                        other_pair_position = rand() % sequence_size;
                        if (other_pair_position != j) {
                            break;
                        }
                    }
                    Sequence::Pair* other_pair = sequences[i]->pairs[other_pair_position];
                    Student *other_male = other_pair->get_student(true), *other_female = other_pair->get_student(false);
                    // γίνονται οι διαδικασίες για το άλλο αγόρι αν είναι άτακτο
                    if ((other_male != NULL) && other_male->messy) {
                        other_male->messy = false;
                        sequences[other_male->classroom_id]->messiness++;
                        other_male->print();
                    }
                    // και για το άλλο κορίτσι
                    if ((other_female != NULL) && other_female->messy) {
                        other_female->messy = false;
                        sequences[other_female->classroom_id]->messiness++;
                        other_female->print();
                    }

                    curr_pair->swap(other_pair, true);  // γίνεται η αντιμετάθεση

                    // τυπώνεται η ακολουθία
                    cout << "Sequence " << i + 1 << ":" << endl;
                    sequences[i]->print(tquiet, tmessy);
                }
            }
        }
        else if (!enough_continuous[i]) {   // δεύτερη περίπτωση
            int other_sequence_position = (i < (size - 1)) ? i + 1 : 0;             // εντοπίζεται η επόμενη ακολουθία
            int other_messiness = 1 + (messy_amount[other_sequence_position] > 2);  // βρίσκεται ο τύπος αταξίας άλλης ακολουθίας
            for (int j = 0 ; j < sequence_size ; j++) { // για κάθε ζευγάρι
                Sequence::Pair* curr_pair = sequences[i]->pairs[j];
                Student* male = curr_pair->get_student(true);
                Student* female = curr_pair->get_student(false);
                if (((male != NULL) && male->messy) || ((female != NULL) && female->messy)) { // αν υπάρχει άτακτος
                    cout << "Students being messy:" << endl;
                    // για το ίδιο το ζευγάρι
                    // αν είναι άτακτο το αγόρι γίνονται οι κατάλληλες διαδικασίες
                    if ((male != NULL) && male->messy) {
                        male->messy = false;        // σταματάει να είναι άτακτο
                        sequences[male->classroom_id]->messiness += 2;  // αυξάνει κατά δύο την αταξία του τμήματός του
                        male->print();              // τυπώνεται
                    }
                    // και αν είναι το κορίτσι
                    if ((female != NULL) && female->messy) {
                        female->messy = false;
                        sequences[female->classroom_id]->messiness += 2;
                        female->print();
                    }

                    // για το άλλο ζευγάρι
                    // επιλέγεται τυχαία ένα ζευγάρι στην επόμενη ακολουθία
                    int other_pair_position = rand() % sequences[other_sequence_position]->size;
                    Sequence::Pair* other_pair = sequences[other_sequence_position]->pairs[other_pair_position];
                    Student *other_male = other_pair->get_student(true), *other_female = other_pair->get_student(false);
                    // γίνονται οι διαδικασίες για το άλλο αγόρι αν είναι άτακτο
                    if ((other_male != NULL) && other_male->messy) {
                        other_male->messy = false;
                        other_male->print();
                        sequences[other_male->classroom_id]->messiness += other_messiness;
                    }
                    // και για το άλλο κορίτσι
                    if ((other_female != NULL) && other_female->messy) {
                        other_female->messy = false;
                        other_female->print();
                        sequences[other_female->classroom_id]->messiness += other_messiness;
                    }

                    curr_pair->swap(other_pair, true);  // γίνεται η αντιμετάθεση

                    // τυπώνονται οι επηρεασμένες ακολουθίες
                    cout << "Sequence " << i + 1 << ":" << endl;
                    sequences[i]->print(tquiet, tmessy);
                    cout << "Sequence " << other_sequence_position + 1 << ":" << endl;
                    sequences[other_sequence_position]->print(tquiet, tmessy);
                }
            }
        }
        else {  // τρίτη περίπτωση
            for (int j = 0 ; j < sequence_size ; j++) { // για κάθε ζευγάρι
                Sequence::Pair* curr_pair = sequences[i]->pairs[j];
                Student* male = curr_pair->get_student(true);
                Student* female = curr_pair->get_student(false);
                if (((male != NULL) && male->messy) || ((female != NULL) && female->messy)) {   // αν υπάρχει άτακτος
                    cout << "Students being messy:" << endl;
                    // για το ίδιο το ζευγάρι
                    // αν είναι άτακτο το αγόρι γίνονται οι κατάλληλες διαδικασίες
                    if ((male != NULL) && male->messy) {
                        male->messy = false;     // σταματάει να είναι άτακτο
                        sequences[male->classroom_id]->messiness += 2;    // αυξάνει κατά δύο την αταξία του τμήματός του
                        male->print();              // τυπώνεται
                    }
                    // και αν είναι το κορίτσι
                    if ((female != NULL) && female->messy) {
                        female->messy = false;
                        sequences[female->classroom_id]->messiness += 2;
                        female->print();
                    }

                    // για το άλλο ζευγάρι
                    int other_sequence_position;
                    // επιλέγεται τυχαία μια ακολουθία διαφορετική από την τωρινή
                    while (true) {
                        other_sequence_position = rand() % size;
                        if (other_sequence_position != i) {
                            break;
                        }
                    }
                    int other_messiness = 1 + (messy_amount[other_sequence_position] > 2);  // βρίσκεται ο τύπος αταξίας άλλης ακολουθίας
                    int other_pair_position = rand() % sequences[other_sequence_position]->size;  // επιλέγεται τυχαία το άλλο ζευγάρι
                    Sequence::Pair* other_pair = sequences[other_sequence_position]->pairs[other_pair_position];
                    Student *other_male = other_pair->get_student(true), *other_female = other_pair->get_student(false);
                    // γίνονται οι διαδικασίες για το άλλο αγόρι αν είναι άτακτο
                    if ((other_male != NULL) && other_male->messy) {
                        other_male->messy = false;
                        other_male->print();
                        sequences[other_male->classroom_id]->messiness += other_messiness;
                    }
                    // και για το άλλο κορίτσι
                    if ((other_female != NULL) && other_female->messy) {
                        other_female->messy = false;
                        other_female->print();
                        sequences[other_female->classroom_id]->messiness += other_messiness;
                    }

                    curr_pair->swap(other_pair, true);  // γίνεται η αντιμετάθεση

                    // τυπώνονται οι επηρεασμένες ακολουθίες
                    cout << "Sequence " << i + 1 << ":" << endl;
                    sequences[i]->print(tquiet, tmessy);
                    cout << "Sequence " << other_sequence_position + 1 << ":" << endl;
                    sequences[other_sequence_position]->print(tquiet, tmessy);
                }
            }
        }
    }
}

// εκτυπώνει όλες τις ακολουθίες ζευγαριών στον παιδικό σταθμό
void Supersequence::print() const {
    for (int i = 0 ; i < size ; i++) {
        cout << "Sequence " << i + 1 << ":" << endl;
        sequences[i]->print(tquiet, tmessy);
    }
}