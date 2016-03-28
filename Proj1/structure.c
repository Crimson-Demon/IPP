//
// Created by marcin on 3/25/16.
//

#include "structure.h"
#include <stdlib.h>
#include <string.h>

/*---------------------------------------------------------------------------*/
//ILLNESS - METHODS
/*---------------------------------------------------------------------------*/
IllnessPtr IllnessConstruct(char* name, char* description) {
	if(name != NULL && description != NULL) {
		IllnessPtr illnessPtr = malloc(sizeof(IllnessPtr*));
		illnessPtr->name = malloc(sizeof(*name));
		illnessPtr->description = malloc(sizeof(*description)));
		illnessPtr->counter = 1;
		memcpy(&(illnessPtr->name), &name, sizeof(*name));
		memcpy(&(illnessPtr->description), &description, sizeof(*description));
		return illnessPtr;
	} else
		return NULL;
}

char* IllnessPrintDescr(IllnessPtr illnessPtr) {
	if(illnessPtr != NULL) {
		char* description = malloc(sizeof(*(illnessPtr->description)));
		memcpy(&description, &(illnessPtr->description), sizeof(*(illnessPtr->description)));
		return description;
	} else
		return NULL;
}

int IllnessGetCount(IllnessPtr illnessPtr) {
	if(illnessPtr != NULL)
		return illnessPtr->counter;
	else
		return -1;
}

void IllnessIncreaseCount(IllnessPtr illnessPtr) {
	if(illnessPtr != NULL) {
		illnessPtr->counter++;
	}
}

void IllnessDecreaseCount(IllnessPtr illnessPtr) {
	if(illnessPtr != NULL) {
		illnessPtr->counter--;
		if(illnessPtr->counter == 0)
			IllnessClear(illnessPtr);
	}
}

void IllnessClear(IllnessPtr illnessPtr) {
	if(illnessPtr != NULL) {
		if(illnessPtr->name != NULL) {
			free(illnessPtr->name);
			illnessPtr->name = NULL;
		}
		if(illnessPtr->description != NULL) {
			free(illnessPtr->description);
			illnessPtr->description = NULL;
		}
	}
}

void IllnessDelete(IllnessPtr illnessPtr) {
	if(illnessPtr != NULL) {
        IllnessClear(illnessPtr);
        free(illnessPtr);
        illnessPtr = NULL;
	}
}

/*---------------------------------------------------------------------------*/
//ILLNESS LIST - METHODS
/*---------------------------------------------------------------------------*/
IllnessList IListCreate(IllnessPtr illnessPtr) {
	if(illnessPtr != NULL) {
		IllnessList illnessList;
		illnessList = malloc(sizeof(*IllnessList));
		illnessList->illness = illnessPtr;
		illnessList->next = NULL;
		return illnessList;
	} else
		return NULL;
}

IllnessList IListGetNext(IllnessList illnessList) {
	if(illnessList != NULL) {
		return illnessList->next;
	} else
		return NULL;
}

void IListAdd(IllnessList illnessList, IllnessPtr illnessPtr) {
	if(illnessList != NULL) {
		if(illnessPtr != NULL) {
			IllnessList illnessListNew = malloc(sizeof(*IllnessList));
			illnessListNew->illness = illnessPtr;
			illnessListNew->next = NULL;
			IllnessList illnessListEnd = illnessList;
			while(illnessListEnd->next != NULL)
				illnessListEnd = IListGetNext(illnessListEnd);
			illnessListEnd->next = illnessListNew;
		}
	} else {
		if(illnessPtr != NULL) {
			illnessList = malloc(sizeof(*IllnessList));
			illnessList->illness = illnessPtr;
			illnessList->next = NULL;
		}
	}
}

int IListGetLength(IllnessList illnessList) {
	if(illnessList != NULL) {
		int i = 0;
		IllnessList illnessListTmp = illnessList;
		while(illnessListTmp != NULL) {
			illnessListTmp = IListGetNext(illnessListTmp);
			i++;
		}
		return i;
	} else {
		return 0;
	}
}

bool IListHas(IllnessList illnessList, IllnessPtr illnessPtr) {
	if(illnessList != NULL) {
		IllnessList illnessListTmp = illnessList;
		bool found = FALSE;
		while(illnessListTmp != NULL && !found) {
			if(illnessPtr == illnessListTmp->illness)
				found = TRUE;
			illnessListTmp = IListGetNext(illnessListTmp);
		}
		return found;
	} else
		return FALSE;
}

IllnessPtr IListChangeNthDescr(IllnessList illnessList, int n, char* descr) {
	if(illnessList != NULL) {
		if(!(IListGetLength(illnessList) < n)) {
			IllnessList illnessListTmp = IllnessList;
			while(n>0) {
				illnessListTmp = IListGetNext(illnessListTmp);
				n--;
			}
			IllnessPtr illnessPtr = IllnessConstruct(illnessListTmp->illness->name, descr);
			IllnessDecreaseCount(illnessListTmp->illness);
			illnessListTmp->illness = illnessPtr;
			return illnessPtr;
		} else
			return NULL;
	} else
		return NULL;
}

char* IListPrintNthDescr(IllnessList illnessList, int n) {
	if(illnessList != NULL) {
		if(!(IListGetLength(illnessList) < n)) {
			IllnessList illnessListTmp = IllnessList;
			while(n>0) {
				illnessListTmp = IListGetNext(illnessListTmp);
				n--;
			}
			return IllnessPrintDescr(illnessListTmp->illness);
		} else
			return NULL;
	} else
		return NULL;
}

//TODO
void IListClear(IllnessList illnessList) {
	if(illnessList != NULL) {
		IllnessList illnessListTmp = illnessList;
		while(illnessListTmp != NULL) {
			IllnessDecreaseCount(illnessListTmp->illness);
			illnessListTmp = IListGetNext(illnessListTmp);
		}
	}
}

//TODO
void IListDelete(IllnessList illnessList) {
	if(illnessList != NULL) {
		IllnessList illnessListTmp = illnessList;
		IllnessList illnessListTmp2 = NULL;
		while(illnessListTmp != NULL) {
			illnessListTmp2 = illnessListTmp;
			illnessListTmp = IListGetNext(illnessListTmp);
			IllnessDelete(illnessListTmp2->illness);
		}
	}
}

/*---------------------------------------------------------------------------*/
//PATIENT - METHODS
/*---------------------------------------------------------------------------*/
PatientPtr PatientCreate(char* surname) {
	if(surname != NULL) {
		PatientPtr patientPtr = malloc(sizeof(PatientPtr*));
		patientPtr->surname = malloc(sizeof(*surname));
		patientPtr->history = NULL;
		memcpy(&(patientPtr->surname), &surname, sizeof(*surname));
		return patientPtr;
	} else
		return NULL;
}

void PatientAdd(PatientPtr patientPtr, IllnessPtr illnessPtr) {
	if(patientPtr != NULL) {
		if(patientPtr->history != NULL)
			IListAdd(patientPtr->history, illnessPtr);
	}
}

IllnessPtr PatientChangeNthDescr(PatientPtr patientPtr, int n, char* descr) {
	if(patientPtr != NULL) {
		return IListChangeNthDescr(patientPtr->history, n, descr);
	} else
		return NULL;
}

bool PatientHas(PatientPtr patientPtr, IllnessPtr illnessPtr) {
	if(patientPtr != NULL) {
		return IListHas(patientPtr->history, illnessPtr);
	} else
		return FALSE;
}

char* PatientPrintNthDescr(PatientPtr patientPtr, int n) {
	if(patientPtr != NULL) {
		return IListPrintNthDescr(patientPtr->history, n);
	} else
		return NULL;
}

bool PatientClearHistory(PatientPtr patientPtr) {
	if(patientPtr != NULL)
		return IListClear(patientPtr->history);
	else
		return FALSE;
}

/*---------------------------------------------------------------------------*/
//PATIENT LIST - METHODS
/*---------------------------------------------------------------------------*/
PatientList PListCreate(PatientPtr patientPtr) {
	if(patientPtr != NULL) {
		PatientList patientList;
		patientList = malloc(sizeof(*List));
		patientList->patient = patientPtr;
		patientList->next = NULL;
		return patientList;
	} else
		return NULL;
}

PatientList PListGetNext(PatientList patientList) {
	if(patientList != NULL) {
		return patientList->next;
	} else
		return NULL;
}

int PListGetLength(PatientList patientList) {
	if(patientList != NULL) {
		PatientList patientListTmp = PatientList;
		int i = 0;
		while(patientListTmp != NULL) {
			i++;
			patientListTmp = PListGetNext(patientListTmp);
		}
		return i;
	} else
		return 0;
}

bool PListAddPatient(PatientList patientList, PatientPtr patientPtr) {
	if(patientList != NULL) {
		if(patientPtr != NULL) {
			PatientList patientListTmp = patientList;
			while(patientListTmp->next != NULL)
				patientListTmp = PListGetNext(patientListTmp);
			PatientList patientListNew = PListCreate(patientPtr);
			patientListTmp->next = patientListNew;
			return TRUE;
		} else
			return FALSE;
	} else {
		if(patientPtr != NULL) {
			patientList = malloc(sizeof(*List));
			patientList->patient = patientPtr;
			patientList->next = NULL;
			return TRUE;
		} else
			return FALSE;
	}
}

char* PListPrintNthDescr(PatientList patientList, char* surname, int n) {
	if(illnessList != NULL) {
		if(!(IListGetLength(illnessList) < n)) {
			IllnessList illnessListTmp = IllnessList;
			while(n>0) {
				illnessListTmp = IListGetNext(illnessListTmp);
				n--;
			}
			return IllnessPrintDescr(illnessListTmp->illness);
		} else
			return NULL;
	} else
		return NULL;
}

//TODO
bool PListCopy(PatientList patientList, char* surname1, char* surname2) {
    if((PListHas(patientList, surname1)) && (PListHas(patientList, surname2))) {

    } else
        return FALSE;
}

bool PListHas(PatientList patientList, char* surname) {
    if(surname != NULL && patientList != NULL) {
        PatientList PatientListTmp = patientList;
        bool found = FALSE;
        while(patientListTmp != NULL && !found) {
            if(strcmp(surname, patientListTmp->surname) == 0)
                found = TRUE;
            patientListTmp = PListGetNext(patientListTmp);
        }
        return found;
    } else
        return FALSE;
}

bool PListModifyNthDescr(PatientList patientList, char* surname, int n, char* descr) {

}

bool PListClear(PatientList patientList) {

}
