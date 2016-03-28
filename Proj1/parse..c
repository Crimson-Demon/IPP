//
// Created by marcin on 3/25/16.
//
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "parse.h"

IMessagePtr IMessageConstruct(InputType inputType, char* args[4]) {
    IMessagePtr iMessagePtr = malloc(sizeof(IMessagePtr*));
    iMessagePtr->arg1 = malloc(sizeof(args[0]));
    strcpy(iMessagePtr->arg1, args[0]);
    iMessagePtr->arg2 = malloc(sizeof(args[1]));
    strcpy(iMessagePtr->arg2, args[1]);
    iMessagePtr->arg3 = malloc(sizeof(args[2]));
    strcpy(iMessagePtr->arg3, args[2]);
    iMessagePtr->arg4 = malloc(sizeof(args[3]));
    strcpy(iMessagePtr->arg4, args[3]);
    return iMessagePtr;
}

void IMessageDestruct(IMessagePtr iMessagePtr) {
    if(iMessagePtr != NULL) {
        if(iMessagePtr->arg1 != NULL)
            free(iMessagePtr->arg1);
        if(iMessagePtr->arg2 != NULL)
        free(iMessagePtr->arg2);
        if(iMessagePtr->arg3 != NULL)
            free(iMessagePtr->arg3);
        if(iMessagePtr->arg4 != NULL)
            free(iMessagePtr->arg4);
        free(iMessagePtr);
    }
}

bool LineCheckValidity(char* input) {
    char* token = strtok(input, " ");
    char* validInputs[5];
    validInputs[0] = malloc(sizeof(char)*30);
    validInputs[0] = "NEW_DISEASE_ENTER_DESCRIPTION";
    validInputs[1] = malloc(sizeof(char)*30);
    validInputs[1] = "NEW_DISEASE_COPY_DESCRIPTION";
    validInputs[2] = malloc(sizeof(char)*30);
    validInputs[2] = "CHANGE_DESCRIPTION";
    validInputs[3] = malloc(sizeof(char)*30);
    validInputs[3] = "PRINT_DESCRIPTION";
    validInputs[4] = malloc(sizeof(char)*30);
    validInputs[4] = "DELETE_PATIENT_DATA";
    if(strcmp(token, validInputs[0]) == 0) {
        for(int i = 0; i < 3; i++) {
            token = strtok(NULL, input);
            if(token == NULL)
                return false;
        }
        return true;
    } else if(strcmp(token, validInputs[1]) == 0) {
        for(int i = 0; i < 2; i++) {
            token = strtok(NULL, input);
            if(token == NULL)
                return false;
        }
        return true;
    } else if(strcmp(token, validInputs[2]) == 0) {
        for(int i = 0; i < 4; i++) {
            token = strtok(NULL, input);
            if(token == NULL)
                return false;
            if(i == 1) {
                if(strlen(token) > 1)
                    return false;
                else {
                    int num = token[0];
                    if(num < 1)
                        return false;
                }
            }
        }
        return true;
    } else if(strcmp(token, validInputs[3]) == 0) {
        for(int i = 0; i < 2; i++) {
            token = strtok(NULL, input);
            if(token == NULL)
                return false;
            if(i == 1) {
                if(strlen(token) > 1)
                    return false;
                else {
                    int num = token[0];
                    if(num < 1)
                        return false;
                }
            }
        }
        return true;
    } else if(strcmp(token, validInputs[4]) == 0) {
        for(int i = 0; i < 1; i++) {
            token = strtok(NULL, input);
            if(token == NULL)
                return false;
        }
        return true;
    } else
        return false;
}


char* LineGet() {
    char* line = malloc(sizeof(char)*MAX_INPUT_LEN);
    char* linep = line;
    size_t length = 0;
    int c;

    if(line == NULL)
        return NULL;

    while(c!=EOF && c!=EOL)
        c = fgetc(stdin);

    if(--len == 0) {
    len = lenmax;
    char * linen = realloc(linep, lenmax *= 2);

    if(linen == NULL) {
    free(linep);
    return NULL;
    }
    line = linen + (line - linep);
    linep = linen;
    }

    if((*line++ = c) == '\n')
    break;
    }
    *line = '\0';
    return linep;
}

void InputParse() {
    while(!(EOF)) {

    }
}