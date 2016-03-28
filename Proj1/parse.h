//
// Created by marcin on 3/24/16.
//

#ifndef HOSPITAL_PARSE_H
#define HOSPITAL_PARSE_H

#include <stdbool.h>
#include <stdio.h>

#define MAX_INPUT_LEN 100000

typedef enum {NewDisease, CopyDisease, ChangeDescription, PrintDescription, DeletePatient} InputType;

struct IMessage {
    InputType inputType;
    char* arg1;
    char* arg2;
    char* arg3;
    char* arg4;
};

typedef struct IMessage* IMessagePtr;

typedef enum {OK, IGNORED} OutputType;

struct OMessage {
    OutputType outputType;
    char* output1;
    char* output2;
};

typedef struct OMessage* OMessagePtr;

IMessagePtr IMessageConstruct(InputType inputType, char* args[4]);

void IMessageDestruct(IMessagePtr iMessagePtr);

bool LineCheckValidity(char* input);

void InputGet();

char* LineGet();

#endif //HOSPITAL_PARSE_H
