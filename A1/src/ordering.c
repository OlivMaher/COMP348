//-----------------------
//Sorting the SpreadSheet
//-----------------------
#include "ordering.h"

extern int sortChoice; // Defined in spreadsheet.c

int compare(const void *a, const void *b){
    Student *studentA = (Student*)a;
    Student *studentB = (Student*)b;
    if (sortChoice == 1){
        return studentA->studentID - studentB->studentID;
    }
    else if (sortChoice == 2){
        return strcmp(studentA->lastName, studentB->lastName);
    }
    else if (sortChoice == 3){
        return studentB->examGrade - studentA->examGrade;
    }
    else if (sortChoice == 4){
        if (studentB->totalGrade > studentA->totalGrade) {
            return 1;
        } else if (studentB->totalGrade < studentA->totalGrade) {
            return -1;
        } else {
            return 0;
        }
    }
    return 0;
}

void sortByColumn(Student *students, int studentCount){
    printf("Column Options");
    printf("\n--------------");
    printf("\n1. Student ID \n2. Last Name \n3. Exam \n4. Total \n");
    printf("\nSort Column: ");
    scanf("%d", &sortChoice);
    if(sortChoice < 1 || sortChoice > 4){
        printf("Invalid sort choice. Defaulting to Student ID.\n");
        sortChoice = 1;
    }
    qsort(students, studentCount, sizeof(Student), compare);
    printf("Students sorted successfully.\n");
}
