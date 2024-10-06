#ifndef CALC_H
#define CALC_H

#include "spreadsheet.h"

// Function Prototypes
float calculateTotalGrade(Student *student);
char calculateLetterGrade(Student *student);
void calculateGrades(Student *students, int studentCount);
void displaySpreadsheet(Student *students, int studentCount);
void displayHistogram(Student *students, int studentCount);
void updateLastName(Student *students, int studentCount);
void updateExamGrade(Student *students, int studentCount);
void updateGradeMapping();
void removeStudent(Student *students, int *studentCount);
void cToContinue();

#endif // CALC_H
