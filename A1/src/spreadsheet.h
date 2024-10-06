#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 1000

// Global Variables (Default Values)
extern int sortChoice;
extern int aBaseline;
extern int bBaseline;
extern int cBaseline;
extern int dBaseline;

// Student Structure
typedef struct {
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
} Student;

// Function Prototypes
void printMenu();
Student* readStudentTxtFile(int *studentCount);
void displaySpreadsheet(Student *students, int studentCount);
void calculateGrades(Student *students, int studentCount);
void displayHistogram(Student *students, int studentCount);
int compare(const void *a, const void *b);
void sortByColumn(Student *students, int studentCount);
void cToContinue();
void updateLastName(Student *students, int studentCount);
void updateExamGrade(Student *students, int studentCount);
void updateGradeMapping();
void removeStudent(Student *students, int *studentCount);

#endif // SPREADSHEET_H
