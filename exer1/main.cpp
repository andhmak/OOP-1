#include <iostream>
#include <ctime>
#include <cstdlib>
#include "names.h"
#include "school.h"

using namespace std;

void shuffle(Student* array[], int size) {
    int new_pos;
    Student* temp;
	for (int i = 0; i < size; i++) {
		new_pos = i + rand() / (RAND_MAX / (size - i) + 1);
		temp = array[new_pos];
		array[new_pos] = array[i];
		array[i] = temp;
	}
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        cerr << "Wrong number of arguments" << endl;
        return 1;
    }
    srand(time(NULL));
    int cclass = atoi(argv[1]), cyard = atoi(argv[2]), cstair = atoi(argv[3]), ccorr = atoi(argv[4]);
    School school(cclass, cyard, cstair, ccorr);
    int student_num = cclass*18;
    Student* students[student_num];
    Teacher* teachers[18];
    Teacher* to_be_placed;
    for (int i = 0 ; i < 3 ; i++) {
        for (int j = 0 ; j < 6 ; j++) {
            for (int k = 0 ; k < cclass ; k++) {
                students[cclass*6*i + cclass*j + k] = new Student(names[rand() % 36], i, j);
            }
        }
    }
    shuffle(students, student_num);
    for (int i = 0 ; i < 18 ; i++) {
        teachers[i] = new Teacher(names[rand() % 36], i / 6, i % 6);
    }
    int teacher_num;
    for (int i = 0 ; i < student_num ; i++) {
        if ((rand() % 2) || (i + student_num/9 > student_num)) {
            if (!school.enter(*students[i])) {
                break;
            }
        }
        else {
            school.enter(students + i, student_num/9);
            i += student_num/9 - 1;
        }
        if (!(rand() % (student_num/8))) {
            teacher_num = rand() % 4;
            for (int j = 0 ; j < teacher_num ; j++) {
                to_be_placed = teachers[rand() % 18];
                if (to_be_placed->is_in() == false) {
                    school.place(*to_be_placed);
                }
            }
        }
    }
    school.print();
    for (int i = 0 ; i < student_num ; i++) {
        students[i]->print();
        delete students[i];
    }
    for (int i = 0 ; i < 18 ; i++) {
        delete teachers[i];
    }
    return 0;
}