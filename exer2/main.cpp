/* File: main.cpp */

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include "names.h"
#include "kindergarten.h"

using namespace std;

int main(int argc, char* argv[]) {
    // αρχικοποίηση με ορίσματα από γραμμή εντολής
    if (argc != 5) {
        cerr << "Wrong number of arguments" << endl;
        return 1;
    }
    int k = atoi(argv[1]), l = atoi(argv[2]);
    double tquiet = atof(argv[3]), tmessy = atof(argv[4]);
    if (tquiet > tmessy) {
        cerr << "Quiet threshold (third argument) should be lower than messy threshold (fourth argument)" << endl;
        return 2;
    }
    if (k < 2) {
        cerr << "There must be at least two classes (first argument)" << endl;
        return 3;
    }

    // αρχικοποίηση της rand()
    srand(time(NULL));

    // δημιουργία 21 μαθητών σε κάθε ένα από τα k τμήματα, με τυχαία ονόματα
    const int student_num = 21*k;
    Student* students[k][21];
    for (int i = 0 ; i < k ; i++) {
        if (i % 2) {    // εναλλάξ σε κάθε τμήμα υπάρχει ένα παραπάνω κορίτσι
            for (int j = 0 ; j < 10 ; j++) {
                students[i][j] = new Student(male_names[rand() % 24], i, true);
            }
            for (int j = 10 ; j < 21 ; j++) {
                students[i][j] = new Student(female_names[rand() % 24], i, false);
            }
        }
        else {          // ή ένα παραπάνω αγόρι
            for (int j = 0 ; j < 11 ; j++) {
                students[i][j] = new Student(male_names[rand() % 24], i, true);
            }
            for (int j = 11 ; j < 21 ; j++) {
                students[i][j] = new Student(female_names[rand() % 24], i, false);
            }
        }
    }

    // τοποθέτηση των μαθητών των τμημάτων σε ακολουθίες
    Sequence* sequences[k];
    for (int i = 0 ; i < k ; i++) {
        sequences[i] = new Sequence(students[i], 21);
    }

    // τοποθέτηση των ακολουθιών σε μια υπερακολουθία
    Supersequence supersequence(sequences, k, tquiet, tmessy);

    // εκτύπωση της υπερακολουθίας
    supersequence.print();

    // l φορές επιλογή τυχαίων μαθητών να κάνουν αταξίες, και έπειτα να γίνονται οι απαραίτητες διαδικασίες
    for (int i = 0 ; i < l ; i++) {
        supersequence.cause_mess();
    }

    // επανεκτύπωση της υπερακολουθίας
    supersequence.print();

    // απελευθέρωση μνήμης μαθητών
    for (int i = 0 ; i < k ; i++) {
        for (int j = 0 ; j < 21 ; j++) {
            delete students[i][j];
        }
    }

    // απελευθέρωση μνήμης ακολουθιών
    for (int i = 0 ; i < k ; i++) {
        delete sequences[i];
    }
    
    return 0;
}