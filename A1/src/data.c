#include "data.h"

Student* readStudentTxtFile(int *studentCount){
    Student *students = malloc(MAX_STUDENTS * sizeof(Student));
    if (students == NULL) {
        printf("Memory allocation failed\n");
        return NULL; // Return NULL if memory allocation fails
    }

    FILE *fptr = fopen("students.txt", "r");
    if (fptr == NULL){
        printf("Unable to open file\n");
        free(students);
        return NULL;
    }

    while (*studentCount < MAX_STUDENTS && 
           fscanf(fptr, "%d|%19[^|]|%19[^|]|%d|%d|%d|%d|%d",
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
