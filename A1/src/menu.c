#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STUDENTS 1000

//------------
// Global Variables (Default Values)
//------------
int sortChoice = 1; 
//Default Grade Mapping
int aBaseline = 80; 
int bBaseline = 70;
int cBaseline = 60;
int dBaseline = 50;


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
    float assignmentContribution = (((student->a1Grade / 40.0) + 
                                     (student->a2Grade / 40.0) + 
                                     (student->a3Grade / 40.0)) / 3) * 0.25;
    float midtermContribution = (student->midtermGrade / 25.0) * 0.25;
    float finalExamContribution = (student->examGrade / 40.0) * 0.50;
    return (assignmentContribution + midtermContribution + finalExamContribution) * 100;
}
char calculateLetterGrade(Student *student){
    if(student->totalGrade >= aBaseline){
        return 'A';
    }
    else if (student->totalGrade >= bBaseline)
    {
        return 'B';
    }
    else if (student->totalGrade >= cBaseline)
    {
        return 'C';
    }
    else if (student->totalGrade >= dBaseline)
    {
        return 'D';
    }
    else{
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
                  students[*studentCount].lastName,
                  students[*studentCount].firstName,
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
void displaySpreadsheet(Student *students, int studentCount){
    printf("\nCOMP 348 GRADE SHEET\n");
    printf("%-10s %-10s %-10s %-5s %-5s %-5s %-8s %-5s %-5s %-5s\n", 
           "ID", "Last", "First", "A1", "A2", "A3", "Midterm", "Exam", "Total", "Grade");
    printf("%-10s %-10s %-10s %-5s %-5s %-5s %-8s %-5s %-5.2s %-5s\n", 
           "--", "----", "-----", "--", "--", "--", "-------", "----", "-----", "-----");
    for(int i = 0; i < studentCount; i++){
        printf("%-10d %-10s %-10s %-5d %-5d %-5d %-8d %-5d %-5.2f %-5c\n",students[i].studentID,students[i].lastName,students[i].firstName,students[i].a1Grade,
        students[i].a2Grade, students[i].a3Grade, students[i].midtermGrade, students[i].examGrade, students[i].totalGrade, students[i].letterGrade);
    }
}
void calculateGrades(Student *students, int studentCount){
    for(int i = 0; i < studentCount; i++){
        students[i].totalGrade = calculateTotalGrade(&students[i]);
        students[i].letterGrade = calculateLetterGrade(&students[i]);
    }
}
void displayHistogram(Student *students, int studentCount){
    printf("\nCOMP 348 Grade Distribution\n");
    int numOfA = 0, numOfB = 0, numOfC = 0, numOfD = 0, numOfF = 0;
    for(int i =0; i < studentCount; i++){
        if(students[i].letterGrade == 'A'){
            numOfA += 1;
        }
        else if (students[i].letterGrade == 'B'){
            numOfB += 1;
        }
        else if (students[i].letterGrade == 'C')
        {
            numOfC += 1;
        }
        else if(students[i].letterGrade == 'D'){
            numOfD += 1;
        }
        else{
            numOfF += 1;
        }
    }
    printf("\nA: ");
    for(int i =0; i < numOfA; i++){
        printf("*");
    }
    printf("\nB: ");
    for(int i =0; i < numOfB; i++){
        printf("*");
    }
    printf("\nC: ");
    for(int i =0; i < numOfC; i++){
        printf("*");
    }
    printf("\nD: ");
    for(int i =0; i < numOfD; i++){
        printf("*");
    }
    printf("\nF: ");
    for(int i =0; i < numOfF; i++){
        printf("*");
    }
}
int compare(const void *a, const void *b){
    Student *studentA = (Student*)a;
    Student *studentB = (Student*)b;
    if (sortChoice == 1){
        return studentA->studentID - studentB->studentID;
    }
    else if (sortChoice == 2){
        return strcmp(studentA->lastName,studentB->lastName);
    }
    else if (sortChoice == 3){
        return studentB->examGrade-studentA->examGrade;
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
    printf("\n1. Student ID \n 2. Last Name \n 3. Exam \n 4. Total \n");
    printf("\nSort Column: ");
    scanf(" %d", &sortChoice);
    qsort(students, studentCount, sizeof(Student), compare);
}

void cToContinue(){
    char choice;
    do{
        printf("\n\nPress 'c' or 'C' to continue: ");
        scanf(" %c", &choice);
    }
    while(choice != 'c' && choice != 'C');
}

void updateLastName(Student *students, int studentCount){
    int selectedID;
    char updatedLastName[20];
    printf("\nEnter Student ID: ");
    scanf("%d", &selectedID);
    printf("\nEnter updated Last Name: ");
    scanf("%s", updatedLastName);
    for(int i = 0; i < studentCount; i++){
        if(students[i].studentID == selectedID){
            strcpy(students[i].lastName,updatedLastName);
            printf("\nLast name updated");
        }
    }
}
void updateExamGrade(Student *students, int studentCount){
    int selectedID;
    int updatedExamGrade;
    printf("\nEnter Student ID: ");
    scanf("%d", &selectedID);
    printf("\nEnter updated exam grade: ");
    scanf("%d", &updatedExamGrade);
    for(int i = 0; i < studentCount; i++){
        if(students[i].studentID == selectedID){
            students[i].examGrade = updatedExamGrade;
            printf("\nExam grade updated"); 

            students[i].totalGrade = calculateTotalGrade(&students[i]);
            students[i].letterGrade = calculateLetterGrade(&students[i]);

            if (sortChoice == 3 || sortChoice == 4){
                qsort(students, studentCount, sizeof(Student), compare);
            }
            return;
        }
    }
    printf("\nStudent with ID %d not found", selectedID);
}
void updateGradeMapping(){
    int updatedABaseline;
    int updatedBBaseline;
    int updatedCBaseline;
    int updatedDBaseline;
    printf("Current Mapping:\n A: >= %d\n B: >= %d\n C: >= %d\n D: >= %d\n F: < %d", aBaseline, bBaseline, cBaseline, dBaseline, dBaseline);

    printf("\n\nEnter new A baseline: ");
    scanf("%d", &updatedABaseline);
    aBaseline = updatedABaseline;
    printf("Enter new B baseline: ");
    scanf("%d", &updatedBBaseline);
    bBaseline = updatedBBaseline;
    printf("Enter new C baseline: ");
    scanf("%d", &updatedCBaseline);
    cBaseline = updatedCBaseline;
    printf("Enter new D baseline: ");
    scanf("%d", &updatedDBaseline);
    dBaseline = updatedDBaseline;

    printf("Current Mapping:\n A: >= %d\n B: >= %d\n C: >= %d\n D: >= %d\n F: < %d", aBaseline, bBaseline, cBaseline, dBaseline, dBaseline);
}

void removeStudent(Student *students, int *studentCount){
    int studentToDelete;
    printf("\nEnter Student ID: ");
    scanf("%d", &studentToDelete);

    for(int i = 0; i < *studentCount; i++){
        if(students[i].studentID == studentToDelete){
            for(int j = i; j < *studentCount - 1; j++){
                students[j] = students[j+1];
            }
            (*studentCount)--;
            printf("Student sucessfully deleted");
            return;
        }
    }
    printf("Student with ID %d not found", studentToDelete);
}


int main(){
    int studentCount = 0;
    Student *students = readStudentTxtFile(&studentCount);
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
                //Display histogram
                displayHistogram(students, studentCount);
                break;
            case 3:
                //Sort
                sortByColumn(students, studentCount);
                break;
            case 4:
                //Update last name
                displaySpreadsheet(students, studentCount);
                updateLastName(students, studentCount);
                break;
            case 5:
                //Update exam grade
                displaySpreadsheet(students, studentCount);
                updateExamGrade(students, studentCount);
                break;
            case 6:
                //Adjust grade mappings
                updateGradeMapping();
                calculateGrades(students, studentCount);
                break;
            case 7:
                //Remove student
                displaySpreadsheet(students, studentCount);
                removeStudent(students, &studentCount);
                break;
        }
        cToContinue();
        system("cls"); //Change to clear prior to submitting (Doesnt show in VSCODE but runs in CMD)
    }
    while (selection != 8);
    return 0;
}