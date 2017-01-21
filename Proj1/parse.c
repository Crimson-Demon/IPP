//Author: Marcin Kania

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "parse.h"

IMessagePtr IMessageCreate(InputType inputType, char* args[3]) {
    IMessagePtr iMessagePtr = malloc(sizeof(*iMessagePtr));
    iMessagePtr->inputType = inputType;
    if(args[0] != NULL) {
        iMessagePtr->arg1 = malloc((strlen(args[0]) + 1)*sizeof(char));
        strcpy(iMessagePtr->arg1, args[0]);
    } else
        iMessagePtr->arg1 = NULL;
    if(args[1] != NULL) {
        iMessagePtr->arg2 = malloc((strlen(args[1]) + 1)*sizeof(char));
        strcpy(iMessagePtr->arg2, args[1]);
    } else
        iMessagePtr->arg2 = NULL;
    if(args[2] != NULL) {
        iMessagePtr->arg3 = malloc((strlen(args[2]) + 1)*sizeof(char));
        strcpy(iMessagePtr->arg3, args[2]);
    } else
        iMessagePtr->arg3 = NULL;
    return iMessagePtr;
}

void IMessageDelete(IMessagePtr iMessagePtr) {
    if(iMessagePtr != NULL) {
        if(iMessagePtr->arg1 != NULL)
            free(iMessagePtr->arg1);
        if(iMessagePtr->arg2 != NULL)
            free(iMessagePtr->arg2);
        if(iMessagePtr->arg3 != NULL)
            free(iMessagePtr->arg3);
        free(iMessagePtr);
    }
}

OMessagePtr OMessageCreate(OutputType outputType, char* args) {
    OMessagePtr oMessagePtr = malloc(sizeof(*oMessagePtr));
    oMessagePtr->outputType = outputType;
    if(args != NULL) {
        oMessagePtr->output2 = malloc((strlen(args) + 1)*sizeof(char));
        strcpy(oMessagePtr->output2, args);
    } else
        oMessagePtr->output2 = NULL;
    return oMessagePtr;
}

void OMessageDelete(OMessagePtr oMessagePtr) {
    if(oMessagePtr != NULL) {
        if(oMessagePtr->output2 != NULL)
            free(oMessagePtr->output2);
        free(oMessagePtr);
    }
}

char* ReadName() {
    char* initialRead = malloc(sizeof(char)*(MAX_LINE_LEN + 1));
    scanf("%s", initialRead);
    size_t charsRead = strlen(initialRead);
    getchar(); // space;
    char* finalRead = malloc(sizeof(char)*(charsRead + 1));
    strncpy(finalRead, initialRead, charsRead + 1);
    free(initialRead);
    return finalRead;
}

char* ReadDescription() {
    char* initialRead = malloc(sizeof(char)*(MAX_LINE_LEN + 1));
    char c = (char) getchar();
    initialRead[0] = c;
    int counter = 0;
    while(c != EOF && c != '\n') {
        c = (char) getchar();
        if(c != EOF && c != '\n') {
            counter++;
            initialRead[counter] = c;
        }
    }
    initialRead[++counter] ='\0';
    char* finalRead = malloc(sizeof(char)*counter);
    strcpy(finalRead, initialRead);
    free(initialRead);
    return finalRead;
}

char* ReadNumber() {
    char* initialRead = malloc(sizeof(char)*(MAX_LINE_LEN + 1));
    scanf("%s", initialRead);
    size_t charsRead = strlen(initialRead);
    getchar();
    char* finalRead = malloc(sizeof(char)*(charsRead + 1));
    strncpy(finalRead, initialRead, charsRead + 1);
    free(initialRead);
    return finalRead;
}

IMessagePtr InputParse() {
    const char* validInputs[5];
    validInputs[0] = "NEW_DISEASE_ENTER_DESCRIPTION";
    validInputs[1] = "NEW_DISEASE_COPY_DESCRIPTION";
    validInputs[2] = "CHANGE_DESCRIPTION";
    validInputs[3] = "PRINT_DESCRIPTION";
    validInputs[4] = "DELETE_PATIENT_DATA";
    char inputTypeStr[31];
    fscanf(stdin, "%s", inputTypeStr);
    if(strcmp(inputTypeStr, validInputs[0]) == 0) {
        InputType inputType = NewDisease;
        char* args[3];
        char* name = ReadName();
        char* description = ReadDescription();
        if(name == NULL || description == NULL)
            return NULL;
        args[0] = name;
        args[1] = description;
        args[2] = NULL;
        IMessagePtr iMessagePtr = IMessageCreate(inputType, args);
        free(name);
        free(description);
        return iMessagePtr;
    } else if(strcmp(inputTypeStr, validInputs[1]) == 0) {
        InputType inputType = CopyDisease;
        char* args[3];
        char* name1 = ReadName();
        char* name2 = ReadName();
        if(name1 == NULL || name2 == NULL)
            return NULL;
        args[0] = name1;
        args[1] = name2;
        args[2] = NULL;
        IMessagePtr iMessagePtr = IMessageCreate(inputType, args);
        free(name1);
        free(name2);
        return iMessagePtr;
    } else if(strcmp(inputTypeStr, validInputs[2]) == 0) {
        InputType inputType = ChangeDescription;
        char* args[3];
        char* name = ReadName();
        char* n = ReadNumber();
        char* description = ReadDescription();
        if(name == NULL || n == NULL || description == NULL)
            return NULL;
        args[0] = name;
        args[1] = n;
        args[2] = description;
        IMessagePtr iMessagePtr = IMessageCreate(inputType, args);
        free(name);
        free(n);
        free(description);
        return iMessagePtr;
    } else if(strcmp(inputTypeStr, validInputs[3]) == 0) {
        InputType inputType = PrintDescription;
        char* args[3];
        char* name = ReadName();
        char* n = ReadNumber();
        if(name == NULL || n == NULL)
            return NULL;
        args[0] = name;
        args[1] = n;
        args[2] = NULL;
        IMessagePtr iMessagePtr = IMessageCreate(inputType, args);
        free(name);
        free(n);
        return iMessagePtr;
    } else if(strcmp(inputTypeStr, validInputs[4]) == 0) {
        InputType inputType = DeletePatient;
        char* args[3];
        char* name = ReadName();
        if(name == NULL)
            return NULL;
        args[0] = name;
        args[1] = NULL;
        args[2] = NULL;
        IMessagePtr iMessagePtr = IMessageCreate(inputType, args);
        free(name);
        return iMessagePtr;
    } else
        return NULL;
}

bool OutputParse(OMessagePtr oMessagePtr) {
    fileEnd = (feof(stdin) > 0);
    if(oMessagePtr == NULL) {
        fprintf(stdout, "oMessage NULL exception");
        return false;
    } else {
        if(oMessagePtr->output2 != NULL) {
            fprintf(stdout, "%s\n", oMessagePtr->output2);
            return !(fileEnd);
        } else {
            switch(oMessagePtr->outputType) {
                case OK:
                    fprintf(stdout, "OK\n");
                    return !(fileEnd);
                case IGNORED:
                    fprintf(stdout, "IGNORED\n");
                    return !(fileEnd);
                default:
                    fprintf(stdout, "Output value error\n");
                    return false;
            }
        }
    }
}
