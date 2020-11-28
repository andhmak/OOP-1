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
        void print() const {    // εκτυπώνει το όνομα, την τάξη και το φύλο
            std::cout << name << ", class " << classroom_id + 1 << (male ? ", male" : ", female") << std::endl;
        }
};

// Κλάση που αναπαριστά έναν ζαυγάρι μαθητών
class Pair {
    Student* first;     // δείκτης στον πρώτο μαθητή του ζεύγους
    Student* second;    // δείκτης στον δεύτερο μαθητή του ζεύγους
    public:
        Pair(Student* init_first, Student* init_second) : first(init_first), second(init_second) { }    // Constructor
        Student* get_student(bool male) const;                  // επιστρέφει τον μαθητή του φύλου που δίνεται σαν όρισμα
        bool male_first() const { return first->is_male(); }    // επιστρέφει αν ο πρώτος μαθητής στο ζευγάρι είναι αρσενικός
        // επιστρέφει αν το ζευγάρι περιέχει μόνο αρσενικό μαθητή
        bool only_male() const { return !((((first != NULL) && !first->is_male())) || (((second != NULL) && !second->is_male()))); }
        // επιστρέφει αν το ζευγάρι περιέχει μόνο θηλυκό μαθητή
        bool only_female() const { return !((((first != NULL) && first->is_male())) || (((second != NULL) && second->is_male()))); }
        Pair* merge(Pair* other);           // εφαρμόζεται σε μη πλήρες ζευγάρι και δέχεται μη πλήρες ζευγάρι, τα ενώνει και επιστρέφει δείκτη στο νέο
        void swap(Pair* other, bool male);  // αντιμεταθέτει τους μαθητές του φίλου που ορίζεται, μεταξύ των ζευγαριών this και other
        void print(int position) const;     // εκτυπώνει την θέση στην ακολουθία (position) και τους μαθητές του ζεύγους
};

// Κλάση που αναπαριστά την ακολουθία ενός τμήματος κατά μια μετακίνηση
class Sequence {
    Pair** pairs;   // πίνακας ζευγαριών (δεικτών σε αντικείμενα ζευγαριών) της ακολουθίας
    int size;       // πλήθος ζευγαριών στην ακολουθία
    int messiness;  // βαθμός αταξίας του τμήματος
    public:
        Sequence(Student** students, int student_amount);   // Constructor
        ~Sequence();    // Destructor
        int get_size() const { return size; }   // επιστρέφει το πλήθος ζευγαριών στην ακολουθία
        Pair* get_pair(int i) const { return pairs[i]; }    // επιστρέφει το ζευγάρι στην θέση i της ακολουθίας
        void increase_messiness(int amount) { messiness += amount; }            // αυξάνει τον βαθμό αταξίας κατά amount
        bool excess_male() const { return pairs[size - 1]->only_male(); }       // επιστρέφει το αν η ακολουθία έχει παραπάνω αγόρια από κορίτσια
        bool excess_female() const { return pairs[size - 1]->only_female(); }   // επιστρέφει το αν η ακολουθία έχει παραπάνω κορίτσια από αγόρια
        // επιστρέφει το τελευταίο πλήρες ζευγάρι της ακολουθίας
        Pair* get_last_full_pair() const { return (pairs[size - 1]->only_female() || pairs[size - 1]->only_male()) ? pairs[size - 2] : pairs[size - 1]; }
        Pair* trim();       // αφαιρεί το τελευταίο ζευγάρι από την ακολουθία και απιστρέφει δείκτη σε αυτό
        void append(Pair** extra_pairs, int extra_amount);  // προσθέτει τα ζευγάρια που δίνονται στο τέλος της ακολουθίας
        // εκτυπώνει τα ζευγάρια και το κατάλληλο μήνυμα ανάλογα με το ποσοστό αταξίας του τμήματος και τα κατόφλια tquiet και tmessy
        void print(double tquiet, double tmessy) const;
                                                        
};

// Κλάση που αναπαριστά το σύνολο των ακολουθιών ενός παιδικού σταθμού κατά μια μετακίνηση
class Kindergarten {
    Sequence** sequences;   // πίνακας ακολουθιών (δεικτών σε αντικείμενα ακολουθιών) του παιδικού σταθμού
    int size;               // πλήθος ακολουθιών στον παιδικό σταθμό
    double tquiet, tmessy;  // κατόφλια ησυχίας/αταξίας (ποσοστού αταξίας προς το πλήθος των μαθητών ενός τμήματος)
    public:
        Kindergarten(Sequence** init_sequences, int sequence_amount, double init_tquiet, double init_messy);  // Constructor
        void cause_mess();  // επιλέγονται τυχαία μαθητές να κάνουν αταξίες, οπότε έπειτα γίνονται οι απαραίτητες διαδικασίες
        void print() const; // εκτυπώνει όλες τις ακολουθίες ζευγαριών στον παιδικό σταθμό
};