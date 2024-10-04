#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STUDENTS 1000

void printMenu(){
    printf("Spreadsheet Menu");
    printf("\n----------------");
    printf("\n1. Display Spreadsheet");
    printf("\n2. Display Histogram");
    printf("\n3. Set sort column");
    printf("\n4. Update Last Name");
    printf("\n5. Update Exam Grade");
    printf("\n6. Update Grade Mapping");
    printf("\n7. Delete Student");
    printf("\n8. Exit");
    printf("\n\nSelection: ");
}
typedef struct{
    int studentID;
    char firstName[20];
    char lastName[20];
    int a1Grade;
    int a2Grade;
    int a3Grade;
    int midtermGrade;
    int examGrade;
    float totalGrade;
    char letterGrade;
}Student;

float calculateTotalGrade(Student *student){
    float assignmentContribution = ((student->a1Grade / 40.0) + (student->a2Grade / 40.0) + (student->a3Grade / 40.0)) * 0.25;
    float midtermContribution = (student->midtermGrade / 25.0) * 0.25;
    float finalExamContribution = (student->examGrade / 40.0) * 0.50;

    return assignmentContribution + midtermContribution + finalExamContribution;
}
char calculateLetterGrade(Student *student){
    if(student->totalGrade >= 80){
        return 'A';
    }
    else if (student->totalGrade >=70)
    {
        return 'B';
    }
    else if (student->totalGrade >= 60)
    {
        return 'C';
    }
    else if (student->totalGrade >= 50)
    {
        return 'D';
    }
    else if (student->totalGrade < 50)
    {
        return 'F';
    }
    
}

Student* readStudentTxtFile(int *studentCount){
    Student *students = malloc(MAX_STUDENTS * sizeof(Student));
     if (students == NULL) {
        printf("Memory allocation failed\n");
        return NULL; // Return NULL if memory allocation fails
    }

    FILE *fptr;
    fptr = fopen("students.txt", "r");

    if (fptr == NULL){
        printf("Unable to open file");
        return NULL;
    }

    while (*studentCount < MAX_STUDENTS && 
           fscanf(fptr, "%d|%20[^|]|%20[^|]|%d|%d|%d|%d|%d",
                  &students[*studentCount].studentID,
                  students[*studentCount].firstName,
                  students[*studentCount].lastName,
                  &students[*studentCount].a1Grade,
                  &students[*studentCount].a2Grade,
                  &students[*studentCount].a3Grade,
                  &students[*studentCount].midtermGrade,
                  &students[*studentCount].examGrade) == 8) {
        (*studentCount)++;
    }
    fclose(fptr);
    return students;
}
void displaySpreadsheet(Student *students, int *studentCount){
    printf("\nCOMP 348 GRADE SHEET\n");
    printf("%-10s %-10s %-10s %-5s %-5s %-5s %-8s %-5s %-5s %-5s\n", 
           "ID", "Last", "First", "A1", "A2", "A3", "Midterm", "Exam", "Total", "Grade");
    printf("%-10s %-10s %-10s %-5s %-5s %-5s %-8s %-5s %-5.2f %-5s\n", 
           "--", "----", "-----", "--", "--", "--", "-------", "----", "-----", "-----");
    for(int i = 0; i < studentCount; i++){
        printf("%-10d %-10s %-10s %-5d %-5d %-5d %-8d %-5d %-5d %-5c\n",students[i].studentID,students[i].lastName,students[i].firstName,students[i].a1Grade,
        students[i].a2Grade, students[i].a3Grade, students[i].midtermGrade, students[i].examGrade, students[i].totalGrade, students[i].letterGrade);
    }
}
void calculateGrades(Student *students, int *studentCount){
    for(int i = 0; i < studentCount; i++){
        students[i].totalGrade = calculateTotalGrade(&students[i]);
        students[i].letterGrade = calculateLetterGrade(&students[i]);
    }
}


int main(){
    int studentCount = 0;
    Student *students = readStudentTxtFile(&studentCount);
    calculateGrades(students, studentCount);
    int selection;
    do {
        printMenu();
        scanf("%d", &selection);
        switch(selection){
            case 1:
                displaySpreadsheet(students, studentCount);
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
        }
        system("cls"); //Change to clear prior to submitting (Doesnt show in VSCODE but runs in CMD)
    }
    while (selection != 8);
    return 0;
}