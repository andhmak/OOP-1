enum area {
    at_yard, at_stairs, at_corridor, at_class, outside
};

class Student {
    std::string name;
    int floor_num;
    int class_num;
    enum area position;
    public:
        Student(const char* init_name, int init_floor_num, int init_class_num);
        ~Student();
        std::string get_name() const { return name; }
        void set_position(enum area new_position) { position = new_position; }
        void print() const { std::cout << name << std::endl; }
        int get_floor_num() const { return floor_num; }
        int get_class_num() const { return class_num; }
};

class Teacher {
    std::string name;
    int floor_num;
    int class_num;
    bool in;
    public:
        Teacher(const char* init_name, int init_floor_num, int init_class_num);
        ~Teacher();
        void print() const { std::cout << "The teacher is: " << name << std::endl; }
        void set_in() { in = true; }
        int get_floor_num() const { return floor_num; }
        int get_class_num() const { return class_num; }
        bool is_in() const { return in; }
};

class Yard {
    int capacity;
    Student** students;
    int student_num;
    public:
        Yard(int init_capacity);
        ~Yard();
        void enter(Student& student);
        Student* exit();
        void print() const;
        bool full() const { return capacity == student_num; }
};

class Stairs {
    int capacity;
    Student** students;
    int student_num;
    public:
        Stairs(int init_capacity);
        ~Stairs();
        void enter(Student& student);
        Student* exit(int floor_num);
        void print() const;
        bool full() const { return capacity == student_num; }
};

class Class {
    int capacity;
    Student** students;
    Teacher* teacher;
    int student_num;
    public:
        Class(int init_capacity);
        ~Class();
        void enter(Student& student);
        void print(int class_number) const;
        void place(Teacher& teacher_in);
        bool full() const { return (capacity == student_num) || (teacher != NULL); }
};

class Corridor {
    int capacity;
    Student** students;
    int student_num;
    public:
        Corridor(int init_capacity);
        ~Corridor();
        void enter(Student& student);
        Student* exit();
        void print() const;
        bool full() const { return capacity == student_num; }
};

class Floor {
    Class* classes[6];
    Corridor corridor;
    public:
        Floor(int cclass, int ccorr);
        ~Floor();
        void enter(Student& student);
        void print(int floor_number) const;
        void place(Teacher& teacher) { classes[teacher.get_class_num()]->place(teacher); }
        bool can_fit() const { return !corridor.full(); }
};

class School {
    Yard yard;
    Stairs stairs;
    Floor* floors[3];
    public:
        School(int cclass, int cyard, int cstair, int ccorr);
        ~School();
        bool enter(Student& student);
        bool enter(Student** students, int size);
        void print() const;
        void place(Teacher& teacher) { floors[teacher.get_floor_num()]->place(teacher); }
};