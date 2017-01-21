//Author: Marcin Kania

#include "structure.h"
#include <stdlib.h>
#include <string.h>

/*---------------------------------------------------------------------------*/
// DISEASE - METHODS DEFINITION
/*---------------------------------------------------------------------------*/
DiseasePtr DiseaseCreate(char* description) {
	if(description != NULL) {
		DiseasePtr diseasePtr = malloc(sizeof(*diseasePtr));
		diseasePtr->description = malloc((strlen(description) + 1)*sizeof(char));
		diseasePtr->counter = 1;
		strcpy(diseasePtr->description, description);
		return diseasePtr;
	} else
		return NULL;
}

char* DiseasePrintDescription(DiseasePtr diseasePtr) {
	if(diseasePtr != NULL)
		return diseasePtr->description;
	else
		return NULL;
}

void DiseaseIncreaseCount(DiseasePtr diseasePtr) {
	if(diseasePtr != NULL) {
		diseasePtr->counter++;
	}
}

int DiseaseDecreaseCount(DiseasePtr diseasePtr) {
	if(diseasePtr != NULL) {
		diseasePtr->counter--;
		if(diseasePtr->counter == 0) {
			DiseaseDelete(diseasePtr);
			return DISEASE_DELETED;
		}
		return DISEASE_DECREASED_COUNT;
	}
	return DELETE_DISEASE_FAIL;
}

void DiseaseDelete(DiseasePtr diseasePtr) {
	if(diseasePtr != NULL) {
        if(diseasePtr->description != NULL) {
            free(diseasePtr->description);
            diseasePtr->description = NULL;
        }
        free(diseasePtr);
	}
}

/*---------------------------------------------------------------------------*/
// DISEASE LIST - METHODS DEFINITION
/*---------------------------------------------------------------------------*/
DiseaseList DListCreate1(char* description) {
	if(description != NULL) {
		DiseaseList diseaseList;
		diseaseList = malloc(sizeof(*diseaseList));
		DiseasePtr diseasePtr = DiseaseCreate(description);
		diseaseList->disease = diseasePtr;
		diseaseList->next = NULL;
		return diseaseList;
	}
	return NULL;
}

DiseaseList DListCreate2(DiseasePtr diseasePtr) {
	if(diseasePtr != NULL) {
		DiseaseList diseaseList;
		diseaseList = malloc(sizeof(*diseaseList));
		diseaseList->disease = diseasePtr;
		diseaseList->next = NULL;
		return diseaseList;
	}
	return NULL;
}

bool DListNewDisease(DiseaseList* diseaseList, char* description) {
	if(description != NULL) {
		if(*diseaseList != NULL) {
			DiseasePtr diseasePtr = DiseaseCreate(description);
			return DListAdd(diseaseList, diseasePtr);
		}
		*diseaseList = DListCreate1(description);
		return (*diseaseList != NULL);
	}
	return false;
}

DiseaseList DListGetNext(DiseaseList diseaseList) {
	if(diseaseList != NULL)
		return diseaseList->next;
	return NULL;
}

bool DListAdd(DiseaseList* diseaseList, DiseasePtr diseasePtr) {
	if(*diseaseList != NULL) {
        if (diseasePtr != NULL) {
            DiseaseList diseaseListNewElement = malloc(sizeof(*diseaseListNewElement));
            diseaseListNewElement->disease = diseasePtr;
            diseaseListNewElement->next = NULL;
            DListGetLatestElement(*diseaseList)->next = diseaseListNewElement;
        	return true;
        }
    } else
		if(diseasePtr != NULL) {
			*diseaseList = DListCreate2(diseasePtr);
			return true;
		}
	return false;
}

bool DListCopyDisease(DiseaseList* diseaseList, DiseasePtr diseasePtr) {
    if(DListAdd(diseaseList, diseasePtr)) {
        DiseaseIncreaseCount(diseasePtr);
        return true;
    }
    return false;
}

DiseaseList DListGetLatestElement(DiseaseList diseaseList) {
	if(diseaseList != NULL) {
        DiseaseList diseaseListTmp = diseaseList;
        while(DListGetNext(diseaseListTmp) != NULL)
            diseaseListTmp = DListGetNext(diseaseListTmp);
        return diseaseListTmp;
    }
    return NULL;
}

DiseasePtr DListGetLatestDisease(DiseaseList diseaseList) {
    return DListGetLatestElement(diseaseList)->disease;
}

int DListChangeDescription(DiseaseList diseaseList, int n, char* description) {
	if(diseaseList != NULL) {
		DiseaseList diseaseListNth = DListGetNth(diseaseList, n);
		if(diseaseListNth == NULL)
			return CHANGE_DESCRIPTION_FAIL;
		int number = DiseaseDecreaseCount(diseaseListNth->disease);
		if(number < 0)
			return CHANGE_DESCRIPTION_FAIL;
		DiseasePtr diseasePtr = DiseaseCreate(description);
		diseaseListNth->disease = diseasePtr;
		return number;
	}
	return -1;
}

char* DListPrintDescription(DiseaseList diseaseList, int n) {
	if(diseaseList != NULL) {
		DiseaseList diseaseListNth = DListGetNth(diseaseList, n);
		if(diseaseListNth == NULL)
			return NULL;
		return DiseasePrintDescription(diseaseListNth->disease);
	}
	return NULL;
}

DiseaseList DListGetNth(DiseaseList diseaseList, int n) {
	if(diseaseList != NULL && n > 0) {
		DiseaseList diseaseListTmp = diseaseList;
        n--;
		while(n > 0) {
			diseaseListTmp = DListGetNext(diseaseListTmp);
			n--;
		}
		return diseaseListTmp;
	}
	return NULL;
}

int DListDelete(DiseaseList diseaseList) {
	DiseaseList diseaseListTmp;
	int decreasedCount = 0;
	int number = 0;
	while(diseaseList != NULL) {
		number = DiseaseDecreaseCount(diseaseList->disease);
		if(number < 0)
			return number;
		decreasedCount += number;
		diseaseList->disease = NULL;
        diseaseListTmp = DListGetNext(diseaseList);
        free(diseaseList);
        diseaseList = diseaseListTmp;
	}
	return decreasedCount;
}

/*---------------------------------------------------------------------------*/
// PATIENT - METHODS DEFINITION
/*---------------------------------------------------------------------------*/
PatientPtr PatientCreate(char* name) {
	if(name != NULL) {
		PatientPtr patientPtr = malloc(sizeof(*patientPtr));
		patientPtr->name = (char*) malloc((strlen(name) + 1)*sizeof(char));
		patientPtr->history = NULL;
		strcpy(patientPtr->name, name);
		return patientPtr;
	}
	return NULL;
}

bool PatientNewDisease(PatientPtr patientPtr, char* description) {
	if(patientPtr != NULL && description != NULL)
		return DListNewDisease(&(patientPtr->history), description);
	return false;
}

bool PatientCopyDisease(PatientPtr patientPtr1, PatientPtr patientPtr2) {
	DiseasePtr diseasePtr = PatientGetLatestDisease(patientPtr2);
	if(patientPtr1 != NULL && diseasePtr != NULL) {
		return DListCopyDisease(&(patientPtr1->history), diseasePtr);
	}
	return false;
}

int PatientChangeDescription(PatientPtr patientPtr, int n, char* description) {
	if(patientPtr != NULL)
		return DListChangeDescription(patientPtr->history, n, description);
	return CHANGE_DESCRIPTION_FAIL;
}

char* PatientPrintDescription(PatientPtr patientPtr, int n) {
	if(patientPtr != NULL)
		return DListPrintDescription(patientPtr->history, n);
	return NULL;
}

int PatientDeletePatient(PatientPtr patientPtr) {
	if(patientPtr != NULL) {
        int number = DListDelete(patientPtr->history);
        patientPtr->history = NULL;
        return number;
    }
	return -1;
}

void PatientDelete(PatientPtr patientPtr) {
    if(patientPtr != NULL) {
    	PatientDeletePatient(patientPtr);
        free(patientPtr->name);
        patientPtr->name = NULL;
        free(patientPtr);
    }
}

DiseasePtr PatientGetLatestDisease(PatientPtr patientPtr) {
	if(patientPtr != NULL)
		return DListGetLatestDisease(patientPtr->history);
	return NULL;
}

bool PatientCompare(PatientPtr patientPtr, char* name) {
	return (strcmp(name, patientPtr->name) == 0);
}

/*---------------------------------------------------------------------------*/
// PATIENT LIST - METHODS DEFINITION
/*---------------------------------------------------------------------------*/
PatientList PListCreate(PatientPtr patientPtr) {
	if(patientPtr != NULL) {
		PatientList patientList;
		patientList = malloc(sizeof(*patientList));
		patientList->patient = patientPtr;
		patientList->next = NULL;
		return patientList;
	}
	return NULL;
}

bool PListNewDisease(PatientList* patientList, char* name, char* description) {
    PatientPtr patientPtr = PListFind(*patientList, name);
    if(patientPtr != NULL)
        return PatientNewDisease(patientPtr, description);
    else {
        patientPtr = PatientCreate(name);
        if(PatientNewDisease(patientPtr, description))
        	return PListAddPatient(patientList, patientPtr);
    }
    return false;
}

bool PListCopyDisease(PatientList* patientList, char* name1, char* name2) {
    PatientPtr patientPtr1 = PListFind(*patientList, name1);
    PatientPtr patientPtr2 = PListFind(*patientList, name2);
    if((patientPtr2 != NULL)) {
        if(patientPtr1 == NULL) {
            patientPtr1 = PatientCreate(name1);
            PListAddPatient(patientList, patientPtr1);
        }
        return PatientCopyDisease(patientPtr1, patientPtr2);
    }
    return false;
}

int PListChangeDescription(PatientList patientList, char* name, int n, char* description) {
    PatientPtr patientPtr = PListFind(patientList, name);
    if (patientPtr == NULL)
        return CHANGE_DESCRIPTION_FAIL;
    return PatientChangeDescription(patientPtr, n, description);
}

char* PListPrintDescription(PatientList patientList, char* name, int n) {
    PatientPtr patientPtr = PListFind(patientList, name);
    if (patientPtr == NULL)
        return NULL;
    return PatientPrintDescription(patientPtr, n);
}

int PListDeletePatient(PatientList patientList, char* name) {
    PatientPtr patientPtr = PListFind(patientList, name);
    if (patientPtr == NULL)
        return -1;
    int number = PatientDeletePatient(patientPtr);
    patientPtr->history = NULL;
    return number;
}

void PListDelete(PatientList patientList) {
	PatientList patientListTmp;
    while(patientList != NULL) {
        PatientDelete(patientList->patient);
        patientList->patient = NULL;
        patientListTmp = PListGetNext(patientList);
        free(patientList);
        patientList = patientListTmp;
    }
}

bool PListAddPatient(PatientList* patientList, PatientPtr patientPtr) {
	if(*patientList != NULL) {
		if(patientPtr != NULL) {
			PatientList patientListTmp = *patientList;
			while(patientListTmp->next != NULL)
				patientListTmp = PListGetNext(patientListTmp);
			PatientList patientListNew = PListCreate(patientPtr);
			patientListTmp->next = patientListNew;
			return true;
		}
	} else
		if(patientPtr != NULL) {
            *patientList = PListCreate(patientPtr);
			return true;
		}
	return false;
}

PatientList PListGetNext(PatientList patientList) {
	if(patientList != NULL)
		return patientList->next;
	return NULL;
}

PatientPtr PListFind(PatientList patientList, char* name) {
    if(name != NULL && patientList != NULL) {
        PatientList patientListTmp = patientList;
        while(patientListTmp != NULL) {
            if(PatientCompare(patientListTmp->patient, name))
                break;
            else
                patientListTmp = PListGetNext(patientListTmp);
        }
        if(patientListTmp != NULL)
        	return patientListTmp->patient;
    }
    return NULL;
}

/*---------------------------------------------------------------------------*/
// HOSPITAL - METHODS DEFINITION
/*---------------------------------------------------------------------------*/
Hospital* HospitalCreate() {
	Hospital* hospital = malloc(sizeof(*hospital));
	hospital->patientList = NULL;
	hospital->diseaseCounter = 0;
	return hospital;
}

bool HospitalNewDisease(Hospital* hospital, char* name, char* description) {
	if(PListNewDisease(&(hospital->patientList), name, description)) {
		hospital->diseaseCounter++;
		return true;
	}
	return false;
}

bool HospitalCopyDisease(Hospital* hospital, char* name1, char* name2) {
	return PListCopyDisease(&(hospital->patientList), name1, name2);
}

bool HospitalChangeDescription(Hospital* hospital, char* name, int n, char* description) {
	int number = PListChangeDescription(hospital->patientList, name, n, description);
	if(number < 0)
		return false;
	if(number == 0) {
		hospital->diseaseCounter++;
		return true;
	}
	return true;
}

char* HospitalPrintDescription(Hospital* hospital, char* name, int n) {
	return PListPrintDescription(hospital->patientList, name, n);
}

bool HospitalDeletePatient(Hospital* hospital, char* name) {
	int number = PListDeletePatient(hospital->patientList, name);
	if(number > -1) {
		hospital->diseaseCounter -= number;
		return true;
	}
	return false;
}

void HospitalDelete(Hospital* hospital) {
	if(hospital->patientList != NULL)
		PListDelete(hospital->patientList);
	hospital->patientList = NULL;
	free(hospital);
}

int HospitalGetDiseaseCounter(Hospital* hospital) {
	return hospital->diseaseCounter;
}