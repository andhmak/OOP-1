/* File: school.h */

// Αναπαράσταση του χώρου όπου βρίσκεται ένας μαθητής
enum area {
    at_yard, at_stairs, at_corridor, at_class, outside
};

// Κλάση που αναπαριστά έναν μαθητή
class Student {
    std::string name;       // όνομα του μαθητή
    short floor_num;        // αριθμός οροόφου όπου βρίσκεται η τάξη/προορισμός του
    short class_num;        // αριθμός/θέση της τάξης/προορισμού του στον όροφο
    enum area position;     // χώρος στον οποίο βρίσκεται μια συγκεκριμένη στιγμή
    public:
        Student(const char* init_name, short init_floor_num, short init_class_num); // Constructor
        ~Student();                                                                 // Destructor (εκτυπώνει και τα δεδομένα του μαθητή)
        void set_position(enum area new_position) { position = new_position; }      // Mutator
        std::string get_name() const { return name; }                               // |
        short get_floor_num() const { return floor_num; }                           // | --> Accessors
        short get_class_num() const { return class_num; }                           // |
        void print() const { std::cout << name << std::endl; }                      // Συνάρτηση εκτύπωσης (εκτυπώνει το όνομα)
};

// Κλάση που αναπαριστά έναν δάσκαλο
class Teacher {
    std::string name;   // όνομα του δασκάλου
    short floor_num;    // αριθμός οροόφου όπου βρίσκεται η τάξη/προορισμός του
    short class_num;    // αριθμός/θέση της τάξης/προορισμού του στον όροφο
    bool in;            // αν βρίσκεται μέσα στην τάξη ή όχι
    public:
        Teacher(const char* init_name, short init_floor_num, short init_class_num);     // Constructor
        ~Teacher();                                                                     // Destructor (εκτυπώνει και τα δεδομένα του δασκάλου)
        void set_in() { in = true; }                                                    // Mutator
        short get_floor_num() const { return floor_num; }                               // |
        short get_class_num() const { return class_num; }                               // | --> Accessors
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
        Student* exit();                // Αφαιρεί τον τελευταίο μαθητή από την αυλή και επιστρέφει δείκτη σε αυτόν
        void print() const; // Συνάρτηση εκτύπωσης (εκτυπώνει τους μαθητές που βρίσκονται στην αυλή)
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
        Student* exit(short floor_num); // Αφαιρεί τον τελευταίο μαθητή του οποίου η τάξη βρίσκεται στον
                                        // όροφο/όρισμα από το κλιμακοστάσιο και επιστρέφει δείκτη σε αυτόν
        void print() const;             // Συνάρτηση εκτύπωσης (εκτυπώνει τους μαθητές που βρίσκονται στο κλιμακοστάσιο)
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
        Student* exit();                // Αφαιρεί τον τελευταίο μαθητή από τον διάδρομο και επιστρέφει δείκτη σε αυτόν
        void print() const; // Συνάρτηση εκτύπωσης (εκτυπώνει τους μαθητές που βρίσκονται στον διάδρομο)
};

// Κλάση που αναπαριστά μια τάξη
class Class {
    int capacity;       // χωρητικότητα σε μαθητές
    Student** students; // πίνακας μαθητών (δεικτών σε αντικείμενα μαθητών) που βρίσκονται στην τάξη
    Teacher* teacher;   // ο δάσκαλος που βρίσκεται στην τάξη (δείκτης στο αντικείμενο του δασκάλου, αν δεν έχει φτάσει NULL)
    int student_num;    // πλήθος μαθητών που βρίσκονται στην τάξη
    public:
        Class(int init_capacity);   // Constructor
        ~Class();                   // Destructor
        bool full() const { return (capacity == student_num) || (teacher != NULL); }    // Επιστρέφει αν είναι κορεσμένη η τάξη, είτε
                                                                                        // λόγω της ύπαρξης πολλών μαθητών ή δασκάλου
        void enter(Student& student);           // Βάζει τον μαθητή/όρισμα στην τάξη
        void place(Teacher& teacher_in);        // Θέτει τον δάσκαλο/όρισμα ως τον δάσκαλο της τάξης, ενημερώνοντάς τον πως εισήλθε
        void print(short class_number) const;   // Συνάρτηση εκτύπωσης (εκτυπώνει τους μαθητές και τον δάσκαλο που βρίσκονται στην τάξη)
};

// Κλάση που αναπαριστά έναν όροφο
class Floor {
    Class* classes[6];  // πίνακας τάξεων (δεικτών σε αντικείμενα τάξεων) του ορόφου 
    Corridor corridor;  // ο διάδρομος του ορόφου
    public:
        Floor(int cclass, int ccorr);       // Constructor
        ~Floor();                           // Destructor
        bool can_fit() const { return !corridor.full(); }   // Επιστρέφει αν μπορεί να μπει μαθητής στον όροφο (αν δεν είναι γεμάτος ο διάδρομος)
        void enter(Student& student);       // Βάζει τον μαθητή/όρισμα στον όροφο, βάζοντάς τον στον διάδρομο αν χωράει
        void place(Teacher& teacher) { classes[teacher.get_class_num()]->place(teacher); }  // Τοποθετεί τον δάσκαλο/όρισμα στον όροφό του,
                                                                                            // τοποθετώντας τον στην τάξη του
        void print(short floor_number) const;   // Συνάρτηση εκτύπωσης (εκτυπώνει τον διάδρομο και τις τάξεις του ορόφου)
};

// Κλάση που αναπαριστά ένα σχολείο
class School {
    Yard yard;          // η αυλή του σχολείου
    Stairs stairs;      // το κλιμακοστάσιο του σχολείου
    Floor* floors[3];   // πίνακας ορόφων (δεικτών σε αντικείμενα ορόφων) του σχολείου
    public:
        School(int cclass, int cyard, int cstair, int ccorr);   // Constructor
        ~School();      // Destructor
        bool enter(Student& student);   // Βάζει τον μαθητή/όρισμα στο σχολείο, πηγαίνοντάς τον όσο πιο κοντά γίνεται
                                        // στην τάξη του. Επιστρέφει το αν μπόρεσε να μπει τουλάχιστον στην αυλή ή όχι.
        bool enter(Student** students, int size);   // Βάζει τους μαθητές/όρισμα στο σχολείο, μετακινόντας τους σε "κύματα",
                                                    // πηγαίνοντάς τους τελικά όσο κοντά γίνεται στις τάξεις τους. Επιστρέφει
                                                    // το αν μπόρεσαν όλοι οι μαθητές να μπουν τουλάχιστον στην αυλή ή όχι.
        void place(Teacher& teacher) { floors[teacher.get_floor_num()]->place(teacher); }   // Τοποθετεί τον δάσκαλο/όρισμα . στο σχολείο,
                                                                                            // τοποθετώντας τον στο όροφό του
        void print() const; // Συνάρτηση εκτύπωσης (εκτυπώνει την αυλή, το κλιμακοστάσιο και τους ορόφους του σχολείου)
};