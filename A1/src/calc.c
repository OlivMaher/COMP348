//-------------------
// Logic of the menu
//------------------

// calc.c
#include "calc.h"

extern int aBaseline;
extern int bBaseline;
extern int cBaseline;
extern int dBaseline;
extern int sortChoice;

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
    else if (student->totalGrade >= bBaseline){
        return 'B';
    }
    else if (student->totalGrade >= cBaseline){
        return 'C';
    }
    else if(student->totalGrade >= dBaseline){
        return 'D';
    }
    else{
        return 'F';
    }
}

void calculateGrades(Student *students, int studentCount){
    for(int i = 0; i < studentCount; i++){
        students[i].totalGrade = calculateTotalGrade(&students[i]);
        students[i].letterGrade = calculateLetterGrade(&students[i]);
    }
}

void displaySpreadsheet(Student *students, int studentCount){
    printf("\nCOMP 348 GRADE SHEET\n");
    printf("%-10s %-10s %-10s %-5s %-5s %-5s %-8s %-5s %-7s %-5s\n", 
           "ID", "Last", "First", "A1", "A2", "A3", "Midterm", "Exam", "Total", "Grade");
    printf("%-10s %-10s %-10s %-5s %-5s %-5s %-8s %-5s %-7s %-5s\n", 
           "--", "----", "-----", "--", "--", "--", "-------", "----", "-----", "-----");
    for(int i = 0; i < studentCount; i++){
        printf("%-10d %-10s %-10s %-5d %-5d %-5d %-8d %-5d %-7.2f %-5c\n",
               students[i].studentID,
               students[i].lastName,
               students[i].firstName,
               students[i].a1Grade,
               students[i].a2Grade,
               students[i].a3Grade,
               students[i].midtermGrade,
               students[i].examGrade,
               students[i].totalGrade,
               students[i].letterGrade);
    }
}

void displayHistogram(Student *students, int studentCount){
    printf("\nCOMP 348 Grade Distribution\n");
    int numOfA = 0, numOfB = 0, numOfC = 0, numOfD = 0, numOfF = 0;
    for(int i =0; i < studentCount; i++){
        switch(students[i].letterGrade){
            case 'A': numOfA++; break;
            case 'B': numOfB++; break;
            case 'C': numOfC++; break;
            case 'D': numOfD++; break;
            case 'F': numOfF++; break;
            default: break;
        }
    }
    printf("\nA: ");
    for(int i =0; i < numOfA; i++) printf("*");
    printf("\nB: ");
    for(int i =0; i < numOfB; i++) printf("*");
    printf("\nC: ");
    for(int i =0; i < numOfC; i++) printf("*");
    printf("\nD: ");
    for(int i =0; i < numOfD; i++) printf("*");
    printf("\nF: ");
    for(int i =0; i < numOfF; i++) printf("*");
    printf("\n");
}

void updateLastName(Student *students, int studentCount){
    int selectedID;
    char updatedLastName[20];
    printf("\nEnter Student ID: ");
    scanf("%d", &selectedID);
    printf("Enter updated Last Name: ");
    scanf("%19s", updatedLastName);
    for(int i = 0; i < studentCount; i++){
        if(students[i].studentID == selectedID){
            strcpy(students[i].lastName, updatedLastName);
            printf("\nLast name updated successfully.\n");
            return;
        }
    }
    printf("\nStudent with ID %d not found.\n", selectedID);
}

void updateExamGrade(Student *students, int studentCount){
    int selectedID;
    int updatedExamGrade;
    printf("\nEnter Student ID: ");
    scanf("%d", &selectedID);
    printf("Enter updated exam grade: ");
    scanf("%d", &updatedExamGrade);
    for(int i = 0; i < studentCount; i++){
        if(students[i].studentID == selectedID){
            students[i].examGrade = updatedExamGrade;
            students[i].totalGrade = calculateTotalGrade(&students[i]);
            students[i].letterGrade = calculateLetterGrade(&students[i]);
            printf("\nExam grade updated successfully.\n");
            // Re-sort if necessary
            if (sortChoice == 3 || sortChoice == 4){
                sortByColumn(students, studentCount);
            }
            return;
        }
    }
    printf("\nStudent with ID %d not found.\n", selectedID);
}

void updateGradeMapping(){
    int updatedABaseline;
    int updatedBBaseline;
    int updatedCBaseline;
    int updatedDBaseline;
    printf("Current Mapping:\n A: >= %d\n B: >= %d\n C: >= %d\n D: >= %d\n F: < %d\n", 
           aBaseline, bBaseline, cBaseline, dBaseline, dBaseline);
    
    printf("\nEnter new A baseline: ");
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
    
    printf("\nUpdated Mapping:\n A: >= %d\n B: >= %d\n C: >= %d\n D: >= %d\n F: < %d\n", 
           aBaseline, bBaseline, cBaseline, dBaseline, dBaseline);
}

void removeStudent(Student *students, int *studentCount){
    int studentToDelete;
    printf("\nEnter Student ID to delete: ");
    scanf("%d", &studentToDelete);

    for(int i = 0; i < *studentCount; i++){
        if(students[i].studentID == studentToDelete){
            for(int j = i; j < *studentCount - 1; j++){
                students[j] = students[j+1];
            }
            (*studentCount)--;
            printf("Student successfully deleted.\n");
            return;
        }
    }
    printf("Student with ID %d not found.\n", studentToDelete);
}

void cToContinue(){
    char choice;
    do{
        printf("\n\nPress 'c' or 'C' to continue: ");
        scanf(" %c", &choice);
    }
    while(choice != 'c' && choice != 'C');
}



