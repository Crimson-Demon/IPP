#ifndef "_HOSPITAL_H_"
#define "_HOSPITAL_H_"

/*TODO
1.Should methods return bool or define int codes to denote success or failure
2.Do I need to define boolean due to too old C standard
3.Should create methods return an object or should they return success/failure and the object should be an argument
4.Should I generalize all "classes" to constructor, copy constructor, comparison and destructor interfaces

IDEA:
    create methods take object as argument.
    If null then it creates the object, else it increases its count/doesnt do anything
    No need for increaseCounter or decreaseCounter methods
    Clear and Destructor
    Clear - deletes data held
    Destructor - decreases ptr and deletes

5.I need to look at the implementation of the smartPtr in C++
*/


#define ILLNESS_INCR_SUCC 2
#define ILLNESS_DECR_SUCC 3
#define ILLNESS_DELTE_SUCC 4
#define ILLNESS_CLEAR_SUCC 5

#define ILLNESS_INCR_FAIL -2
#define ILLNESS_DECR_FAIL -3
#define ILLNESS_DELTE_FAIL -4
#define ILLNESS_CLEAR_FAIL -5

/*---------------------------------------------------------------------------*/
//ILLNESS - STRUCTURE AND METHODS
/*---------------------------------------------------------------------------*/
//Illness data structure
//Works "like" a smartPtr in C++
//Holds a counter of references to it
//Dealocates the structure when the counter hits 0
struct Illness {
char* name;
char* description;
int counter;
};

//Typedef for a ptr to the Illness structure
typedef IllnessPtr Illness*;

//Function
//Creates an illness with name and description specified by args
//Returns ptr to data structure
IllnessPtr IllnessCreate(char* name, char* description);

//Function
//Returns the description of the illness specified by illnessPtr
char* IllnessPrintDescr(IllnessPtr illnessPtr);

//Function
//Returns the number of references to illnessPtr
int IllnessGetCount(IllnessPtr illnessPtr);

//Function
//Increases the number of references to illnessPtr
int IllnessIncreaseCount(IllnessPtr illnessPtr);

//Function
//Decreases the number of references to illnessPtr
//If it hits 0 then it calls IllnessDelete
int IllnessDecreaseCount(IllnessPtr illnessPtr);

//Function
//Dealocates data held by the ptr illnessPtr
int IllnessClear(IllnessPtr illnessPtr);

//Function
//Dealocates data held by the ptr illnessPtr and dealocates structure
int IllnessDelete(IllnessPtr illnessPtr);
/*---------------------------------------------------------------------------*/
//ILLNESS LIST - DATA STRUCTURE AND METHODS
/*---------------------------------------------------------------------------*/
//Prototype of Illness list element
struct IllnessListElem;

//Typedef for a ptr to a illness list element
typedef IllnessList IllnessListElem*;

//Illness list data structure
//Holds a ptr to the illness and a ptr to the next element of the list
struct IllnessListElem {
IllnessPtr illness;
IllnessList next;
};

IllnessList IListCreate(IllnessPtr illnessPtr);

IllnessList IListGetNext(IllnessList illnessList);

bool IListAdd(IllnessList illnessList, IllnessPtr illnessPtr);

int IListGetLength(IllnessList illnessList);

bool IListHas(IllnessList illnessList, IllnessPtr illnessPtr);

IllnessPtr IListChangeNthDescr(IllnessList illnessList, int n, char* descr);

char* IListPrintNthDescr(IllnessList illnessList, int n);

bool IListClear(IllnessList illnessList);

bool IListDelete(IllnessList illnessList);
/*---------------------------------------------------------------------------*/
//PATIENT - DATA STRUCTURE AND METHODS
/*---------------------------------------------------------------------------*/
//Patient data structure
//Holds the surname and illness history of patient
struct Patient {
char* surname;
IllnessList history;
};

typedef PatientPtr Patient*;

PatientPtr PatientCreate(char* surname);

bool PatientAdd(PatientPtr patientPtr, IllnessPtr illnessPtr);

IllnessPtr PatientChangeNthDescr(PatientPtr patientPtr, int n, char* descr);

bool PatientHas(PatientPtr patientPtr, IllnessPtr illnessPtr);

char* PatientPrintNthDescr(PatientPtr patientPtr, int n);

bool PatientClearHistory(PatientPtr patientPtr);
/*---------------------------------------------------------------------------*/
//PATIENT LIST - DATA STRUCTURE AND METHODS
/*---------------------------------------------------------------------------*/
//Patient list element structure prototype
struct PatientListElem;

//Typedef for a ptr to a patient list element
typedef PatientList PatientListElem*;

//Patient list element data structure
//Holds a ptr to the patient and a ptr to the next element of the list
struct PatientListElem {
PatientPtr patient;
PatientList next;
};

PatientList PListCreate(PatientPtr patientPtr);

PatientList PListGetNext(PatientList patientList);

int PListGetLength(PatientList patientList);

bool PListAddPatient(PalientListPtr patientListPtr, PatientPtr patientPtr);

char* PListPrintNthDescr(PatientList patientList, char* surname, int n);

bool PListCopy(PatientList patientList, char* surname1, char* surname2);

bool PListHas(PatientList patientList, char* surname);

bool PListModifyNthDescr(PatientList patientList, char* surname, int n, char* descr);

bool PListClear(PatientList patientList);

#endif
