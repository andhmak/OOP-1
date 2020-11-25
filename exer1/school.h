/* File: school.h */

// Αναπαράσταση του χώρου όπου βρίσκεται ένας μαθητής
enum area {
    at_yard, at_stairs, at_corridor, at_class, outside
};

// Κλάση που αναπαριστά έναν μαθητή
class Student {
    std::string name;       // όνομα του μαθητή
    int floor_num;          // αριθμός οροόφου όπου βρίσκεται η τάξη/προορισμός του
    int class_num;          // αριθμός/θέση της τάξης/προορισμού του στον όροφο
    enum area position;     // χώρος στον οποίο βρίσκεται μια συγκεκριμένη στιγμή
    public:
        Student(const char* init_name, int init_floor_num, int init_class_num); // Constructor
        ~Student();                                                             // Destructor
        void set_position(enum area new_position) { position = new_position; }  // Mutator
        std::string get_name() const { return name; }                           // |
        int get_floor_num() const { return floor_num; }                         // | --> Accessors
        int get_class_num() const { return class_num; }                         // |
        void print() const { std::cout << name << std::endl; }                  // Συνάρτηση εκτύπωσης (εκτυπώνει το όνομα)
};

// Κλάση που αναπαριστά έναν δάσκαλο
class Teacher {
    std::string name;   // όνομα του δασκάλου
    int floor_num;      // αριθμός οροόφου όπου βρίσκεται η τάξη/προορισμός του
    int class_num;      // αριθμός/θέση της τάξης/προορισμού του στον όροφο
    bool in;            // αν βρίσκεται μέσα στην τάξη ή όχι
    public:
        Teacher(const char* init_name, int init_floor_num, int init_class_num);         // Constructor
        ~Teacher();                                                                     // Destructor
        void set_in() { in = true; }                                                    // Mutator
        int get_floor_num() const { return floor_num; }                                 // |
        int get_class_num() const { return class_num; }                                 // | --> Accessors
        bool is_in() const { return in; }                                               // |
        void print() const { std::cout << "The teacher is: " << name << std::endl; }    // Συνάρτηση εκτύπωσης (εκτυπώνει το όνομα)
};

// Κλάση που αναπαριστά μια αυλή
class Yard {
    int capacity;       // χωρητικότητα σε μαθητές
    Student** students; // πίνακας μαθητών (δεικτών σε αντικείμενα μαθητών) στην αυλή
    int student_num;    // πλήθος μαθητών στην αυλή
    public:
        Yard(int init_capacity);        // Constructor
        ~Yard();                        // Destructor
        bool full() const { return capacity == student_num; }   // Επιστρέφει το αν είναι γεμάτη η αυλή
        void enter(Student& student);   // Βάζει τον μαθητή/όρισμα στην αυλή
        Student* exit();                // 
        void print() const; // Συνάρτηση εκτύπωσης ...
};

// Κλάση που αναπαριστά ένα κλιμακοστάσιο
class Stairs {
    int capacity;       // χωρητικότητα σε μαθητές
    Student** students; // πίνακας μαθητών (δεικτών σε αντικείμενα μαθητών) στο κλιμακοστάσιο
    int student_num;    // πλήθος μαθητών στο κλιμακοστάσιο
    public:
        Stairs(int init_capacity);  // Constructor
        ~Stairs();                  // Destructor
        bool full() const { return capacity == student_num; }   // Επιστρέφει το αν είναι γεμάτο το κλιμακοστάσιο
        void enter(Student& student);   // Βάζει τον μαθητή/όρισμα στο κλιμακοστάσιο
        Student* exit(int floor_num);   //
        void print() const; // Συνάρτηση εκτύπωσης ...
};

// Κλάση που αναπαριστά έναν διάδρομο
class Corridor {
    int capacity;       // χωρητικότητα σε μαθητές
    Student** students; // πίνακας μαθητών (δεικτών σε αντικείμενα μαθητών) στον διάδρομο
    int student_num;    // πλήθος μαθητών στον διάδρομο
    public:
        Corridor(int init_capacity);    // Constructor
        ~Corridor();                    // Destructor
        bool full() const { return capacity == student_num; }   // Επιστρέφει το αν είναι γεμάτος ο διάδρομος
        void enter(Student& student);   // Βάζει τον μαθητή/όρισμα στον διάδρομο
        Student* exit();                // 
        void print() const; // Συνάρτηση εκτύπωσης ...
};

// Κλάση που αναπαριστά μια τάξη
class Class {
    int capacity;       // χωρητικότητα σε μαθητές
    Student** students; // πίνακας μαθητών (δεικτών σε αντικείμενα μαθητών) που βρίσκονται στην τάξη
    Teacher* teacher;   // ο δάσκαλος που βρίσκεται στην τάξη (δείκτης στο αντικείμενο του δασκάλου, αν δεν έχει φτάσει NULL)
    int student_num;    // πλήθος μαθητών που βρίσκονται στην τάξη
    public:
        Class(int init_capacity);           // Constructor
        ~Class();                           // Destructor
        bool full() const { return (capacity == student_num) || (teacher != NULL); }    // Επιστρέφει αν είναι κορεσμένη η τάξη, είτε
                                                                                        // λόγω της ύπαρξης πολλών μαθητών ή δασκάλου
        void enter(Student& student);       // Βάζει τον μαθητή/όρισμα στην τάξη
        void place(Teacher& teacher_in);    // Θέτει τον δάσκαλο/όρισμα ως τον δάσκαλο της τάξης, ενημερώνοντάς τον πως εισήλθε
        void print(int class_number) const; // Συνάρτηση εκτύπωσης ...
};

// Κλάση που αναπαριστά έναν όροφο
class Floor {
    Class* classes[6];  // πίνακας τάξεων (δεικτών σε αντικείμενα τάξεων) του ορόφου 
    Corridor corridor;  // ο διάδρομος του ορόφου
    public:
        Floor(int cclass, int ccorr);       // Constructor
        ~Floor();                           // Destructor
        bool can_fit() const { return !corridor.full(); }   // Επιστρέφει αν μπορεί να μπει μαθητής στον όροφο (αν δεν είναι γεμάτος ο διάδρομος)
        void enter(Student& student);   // 
        void place(Teacher& teacher) { classes[teacher.get_class_num()]->place(teacher); }  // Τοποθετεί τον δάσκαλο/όρισμα στον όροφό του,
                                                                                            // τοποθετώντας τον στην τάξη του
        void print(int floor_number) const; // Συνάρτηση εκτύπωσης ...
};

// Κλάση που αναπαριστά ένα σχολείο
class School {
    Yard yard;          // η αυλή του σχολείου
    Stairs stairs;      // το κλιμακοστάσιο του σχολείου
    Floor* floors[3];   // πίνακας ορόφων (δεικτών σε αντικείμενα ορόφων) του σχολείου
    public:
        School(int cclass, int cyard, int cstair, int ccorr);   // Constructor
        ~School();          // Destructor
        bool enter(Student& student);   //
        bool enter(Student** students, int size);   //
        void place(Teacher& teacher) { floors[teacher.get_floor_num()]->place(teacher); }   // Τοποθετεί τον δάσκαλο/όρισμα στο σχολείο,
                                                                                            // τοποθετώντας τον στο όροφό του
        void print() const; // Συνάρτηση εκτύπωσης ...
};