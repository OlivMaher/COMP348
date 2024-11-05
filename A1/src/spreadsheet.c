// spreadsheet.c
#include "spreadsheet.h"
#include "data.h"
#include "ordering.h"
#include "calc.h"

int sortChoice = 1; 
// Default Grade Mapping
int aBaseline = 80; 
int bBaseline = 70;
int cBaseline = 60;
int dBaseline = 50;

int main(){
    int studentCount = 0;
    Student *students = readStudentTxtFile(&studentCount);
    if (students == NULL) {
        return 1; // Exit if reading data failed
    }
    calculateGrades(students, studentCount);
    qsort(students, studentCount, sizeof(Student), compare);
    
    int selection;
    do {
        printMenu();
        scanf("%d", &selection);
        switch(selection){
            case 1:
                displaySpreadsheet(students, studentCount);
                break;
            case 2:
                displayHistogram(students, studentCount);
                break;
            case 3:
                sortByColumn(students, studentCount);
                break;
            case 4:
                displaySpreadsheet(students, studentCount);
                updateLastName(students, studentCount);
                break;
            case 5:
                displaySpreadsheet(students, studentCount);
                updateExamGrade(students, studentCount);
                break;
            case 6:
                updateGradeMapping();
                calculateGrades(students, studentCount);
                break;
            case 7:
                displaySpreadsheet(students, studentCount);
                removeStudent(students, &studentCount);
                break;
            case 8:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid selection. Please try again.\n");
        }
        if (selection != 8) {
            cToContinue();
            system("clear"); //Clears the screen
        }
    }
    while (selection != 8);
    
    free(students);
    return 0;
}
