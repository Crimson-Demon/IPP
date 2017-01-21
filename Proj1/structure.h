// Author: Marcin Kania

#ifndef HOSPITAL_STRUCTURE_H
#define HOSPITAL_STRUCTURE_H

// For bool type, true and false macros
#include <stdbool.h>

// Defines for int return values for some methods
#define DELETE_DISEASE_FAIL -2;
#define CHANGE_DESCRIPTION_FAIL -1;
#define DISEASE_DECREASED_COUNT 0;
#define DISEASE_DELETED 1;

/*---------------------------------------------------------------------------*/
// ILLNESS - DATA STRUCTURE DEFINITION AND METHODS DECLARATION
/*---------------------------------------------------------------------------*/

// Disease data structure
// Works "like" a smartPtr in C++
// Holds a counter of references to it
// Dealocates the structure when the counter hits 0
struct Disease {
    char* description;
    int counter;
};

// Typedef for a ptr to the Disease structure
typedef struct Disease* DiseasePtr;

// Creates an disease with name and description specified by args
// Returns ptr to data structure
DiseasePtr DiseaseCreate(char* description);

// Returns the description of the disease specified by illnessPtr
char* DiseasePrintDescription(DiseasePtr diseasePtr);

// Increases the number of references to illnessPtr
void DiseaseIncreaseCount(DiseasePtr diseasePtr);

// Decreases the number of references to illnessPtr
// If it hits 0 then it calls DiseaseDelete
// Returns DELETE_DISEASE_FAIL if it failed at decreasing the count
// Returns DISEASE_DECREASED_COUNT if it succeeded in decreasing the count but didnt delete the disease
// Returns DISEASE_DELETED if it succeeded in decreasing and deleting the disease
int DiseaseDecreaseCount(DiseasePtr diseasePtr);

// unallocates data held by the ptr illnessPtr and dealocates structure
void DiseaseDelete(DiseasePtr diseasePtr);

/*---------------------------------------------------------------------------*/
// ILLNESS LIST - DATA STRUCTURE DEFINITION AND METHODS DECLARATION
/*---------------------------------------------------------------------------*/

// Prototype of Disease list element
struct DiseaseListElem;

// Typedef for a ptr to a disease list element
typedef struct DiseaseListElem* DiseaseList;

// Disease list data structure
// Holds a ptr to the disease and a ptr to the next element of the list
struct DiseaseListElem {
    DiseasePtr disease;
    DiseaseList next;
};

// Creates an disease list with a single disease in it using a description for a disease
DiseaseList DListCreate1(char* description);

// Creates an disease list with a single disease in it using a DiseasePtr
DiseaseList DListCreate2(DiseasePtr diseasePtr);

// Governs the process behind the NEW_DISEASE_ENTER_DESCRIPTION related operation
bool DListNewDisease(DiseaseList* diseaseList, char* description);

// Gets the next element of the disease list
DiseaseList DListGetNext(DiseaseList diseaseList);

// Adds an disease to the end of the disease list
bool DListAdd(DiseaseList* diseaseList, DiseasePtr diseasePtr);

// Governs the process behind the NEW_DISEASE_COPY_DESCRIPTION related operation
bool DListCopyDisease(DiseaseList* diseaseList, DiseasePtr diseasePtr);

// Gets the latest disease on the disease list
DiseaseList DListGetLatestElement(DiseaseList diseaseList);

// Gets the latest disease on the disease list
DiseasePtr DListGetLatestDisease(DiseaseList diseaseList);

// Modifies the description of the nth disease on the list
// Returns int corresponding to failure or global disease count change
int DListChangeDescription(DiseaseList diseaseList, int n, char* description);

// Returns the description of the nth disease on the list
char* DListPrintDescription(DiseaseList diseaseList, int n);

// Returns an disease list element that is the nth on the list or null
DiseaseList DListGetNth(DiseaseList diseaseList, int n);

// Empties the whole list
int DListDelete(DiseaseList diseaseList);

/*---------------------------------------------------------------------------*/
// PATIENT - DATA STRUCTURE DEFINITION AND METHODS DECLARATION
/*---------------------------------------------------------------------------*/

// Patient data structure
// Holds the name and disease history of patient
struct Patient {
    char* name;
    DiseaseList history;
};

// Typedef for a pointer to a patient
typedef struct Patient* PatientPtr;

// Creates a patient with name and an empty disease list
PatientPtr PatientCreate(char* name);

// Adds an disease given by its ptr to a patient given by his ptr
bool PatientNewDisease(PatientPtr patientPtr, char* description);

// Adds an disease given by its ptr to a patient given by his ptr
bool PatientCopyDisease(PatientPtr patientPtr1, PatientPtr patientPtr2);

// Changes the description of the nth disease on the patients history
int PatientChangeDescription(PatientPtr patientPtr, int n, char* description);

// Gets the latest disease of the patient
DiseasePtr PatientGetLatestDisease(PatientPtr patientPtr);

// Retuns a string corresponding to the patients nth disease' description
char* PatientPrintDescription(PatientPtr patientPtr, int n);

// Clears the patients disease history
int PatientDeletePatient(PatientPtr patientPtr);

// Deletes the patient
void PatientDelete(PatientPtr patientPtr);

// Compares one patient with another based on name
bool PatientCompare(PatientPtr patientPtr, char* name);

/*---------------------------------------------------------------------------*/
// PATIENT LIST - DATA STRUCTURE DEFINITION AND METHODS DECLARATION
/*---------------------------------------------------------------------------*/

// Patient list element structure prototype
struct PatientListElem;

// Typedef for a ptr to a patient list element
typedef struct PatientListElem* PatientList;

// Patient list element data structure
// Holds a ptr to the patient and a ptr to the next element of the list
struct PatientListElem {
    PatientPtr patient;
    PatientList next;
};

// Creates a patient list with a single patient
PatientList PListCreate(PatientPtr patientPtr);

// Gets the next element on the patient list
PatientList PListGetNext(PatientList patientList);

// Finds a patient given by his name or returns NULL
PatientPtr PListFind(PatientList patientList, char* name);

bool PListNewDisease(PatientList* patientList, char* name, char* description);

// Adds a patient to the patient list
bool PListAddPatient(PatientList* patientList, PatientPtr patientPtr);

// Copies the disease from patient with name1 to patient with name2 in the patient list.
bool PListCopyDisease(PatientList* patientList, char* name1, char* name2);

// Changes the description of the nth disease for patient with name in the patient list.
int PListChangeDescription(PatientList patientList, char* name, int n, char* description);

// Returns a string corresponding to the description of the nth disease given by
// a patient whose name is name
char* PListPrintDescription(PatientList patientList, char* name, int n);

// Clears the disease history of a patient given by his name
// Returns a bool depending on if he was on the list
int PListDeletePatient(PatientList patientList, char* name);

// Deletes the patient list
void PListDelete(PatientList patientList);

/*---------------------------------------------------------------------------*/
// HOSPITAL - DATA STRUCTURE DEFINITION AND METHODS DECLARATION
/*---------------------------------------------------------------------------*/

// Hospital structure typedef and declaration
typedef struct HospitalStruct {
    int diseaseCounter;
    PatientList patientList;
} Hospital;

// Creates an empty hospital and returns the pointer to it
Hospital* HospitalCreate();

// Returns the count of different diseases in the hospital.
int HospitalGetDiseaseCounter(Hospital* hospital);

// Adds a patient to the hospital.
bool HospitalNewDisease(Hospital* hospital, char* name, char* description);

// Copies the disease from patient with name1 to patient with name2 in the hospital.
bool HospitalCopyDisease(Hospital* hospital, char* name1, char* name2);

// Changes the description of the nth disease for patient with name in the hospital.
bool HospitalChangeDescription(Hospital* hospital, char* name, int n, char* description);

// Prints the description of the nth disease for patient with name in the hospital.
char* HospitalPrintDescription(Hospital* hospital, char* name, int n);

// Clears the disease list of patient with name in the hospital.
bool HospitalDeletePatient(Hospital* hospital, char* name);

// Deletes all the patients, diseases associated etc and all memory in the hospital.
void HospitalDelete(Hospital* hospital);

#endif