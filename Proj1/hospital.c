//Author: Marcin Kania

#include "parse.h"
#include "structure.h"
#include <string.h>

//Function
//given a string encoding a number
//returns said number as int
int StrToNumber(char* n) {
    int i = 0;
    int num = 0;
    while(n[i] != '\0') {
        int numTmp = n[i] - '0';
        num = 10*num + numTmp;
        i++;
    }
    return num;
}

//Main "main" function
//Take an input message and does the appropriate action
//Returns an output message
OMessagePtr ActionDo(Hospital* hospital, IMessagePtr iMessagePtr) {
    if(iMessagePtr == NULL)
        return OMessageCreate(IGNORED, NULL);
    else {
        char* name;
        char* description;
        char* name1;
        char* name2;
        int n;
        switch(iMessagePtr->inputType) {
            case NewDisease:
                name = iMessagePtr->arg1;
                description = iMessagePtr->arg2;
                if(HospitalNewDisease(hospital, name, description))
                    return OMessageCreate(OK, NULL);
                else
                    return OMessageCreate(IGNORED, NULL);
            case CopyDisease:
                name1 = iMessagePtr->arg1;
                name2 = iMessagePtr->arg2;
                if(HospitalCopyDisease(hospital, name1, name2))
                    return OMessageCreate(OK, NULL);
                else
                    return OMessageCreate(IGNORED, NULL);
            case ChangeDescription:
                name = iMessagePtr->arg1;
                n = StrToNumber(iMessagePtr->arg2);
                description = iMessagePtr->arg3;
                if(HospitalChangeDescription(hospital, name, n, description))
                    return OMessageCreate(OK, NULL);
                else
                    return OMessageCreate(IGNORED, NULL);
            case PrintDescription:
                name = iMessagePtr->arg1;
                n = StrToNumber(iMessagePtr->arg2);
                description = HospitalPrintDescription(hospital, name, n);
                if(description != NULL)
                    return OMessageCreate(OK, description);
                else
                    return OMessageCreate(IGNORED, NULL);
            case DeletePatient:
                name = iMessagePtr->arg1;
                if(HospitalDeletePatient(hospital, name))
                    return OMessageCreate(OK, NULL);
                else
                    return OMessageCreate(IGNORED, NULL);
            default:
                return OMessageCreate(IGNORED, NULL);
        }
    }
}

int main(int argc, char** argv) {
    Hospital* hospital = HospitalCreate();
    isVe = false;
    fileEnd = false;
    if(argc > 1) {
        if (strcmp(argv[0], "-v") && argc == 2)
            isVe = true;
        else {
            fprintf(stdout, "ERROR\n");
            return 1;
        }
    }
    while(!(fileEnd)) {
        IMessagePtr iMessagePtr = InputParse();
        OMessagePtr oMessagePtr = ActionDo(hospital, iMessagePtr);
        fileEnd = !OutputParse(oMessagePtr);
        if(isVe)
            fprintf(stderr, "DESCRIPTIONS: %i\n", HospitalGetDiseaseCounter(hospital));
        IMessageDelete(iMessagePtr);
        OMessageDelete(oMessagePtr);
    }
    HospitalDelete(hospital);
    return 0;
}