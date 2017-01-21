//Author: Marcin Kania

#ifndef HOSPITAL_PARSE_H
#define HOSPITAL_PARSE_H

#include <stdbool.h>
#include <stdio.h>

// Max line length
#define MAX_LINE_LEN 100000

// Helper variable that holds whether its the end of file or not
bool fileEnd;

// Helper variable to check if program is called with -v
bool isVe;

/*---------------------------------------------------------------------------*/
// INPUT MESSAGE - STRUCTURE STRUCTURE AND METHODS DECLARATION
/*---------------------------------------------------------------------------*/

// Enum for types of input
typedef enum {NewDisease, CopyDisease, ChangeDescription, PrintDescription, DeletePatient} InputType;

// Input message structure
// holds input type and strings that define arguments
struct IMessage {
    InputType inputType;
    char* arg1;
    char* arg2;
    char* arg3;
};

// Typedef for a input message pointer
typedef struct IMessage* IMessagePtr;

// Creates an input message based on input type and an array of argument strings
// returns an input message ptr
IMessagePtr IMessageCreate(InputType inputType, char* args[3]);

// Deletes data held by an input message pointer
void IMessageDelete(IMessagePtr iMessagePtr);

/*---------------------------------------------------------------------------*/
// OUTPUT MESSAGE - DATA STRUCTURE AND METHODS DECLARATION
/*---------------------------------------------------------------------------*/

// Enum for types of output
typedef enum {OK, IGNORED} OutputType;

// Output message structure
// holds output type and a string that defines an argument
struct OMessage {
    OutputType outputType;
    char* output2;
};

// typedef for an output message pointer
typedef struct OMessage* OMessagePtr;

// Creates an output message based on output type and a string
// returns an output message ptr
OMessagePtr OMessageCreate(OutputType outputType, char* args);

// Deletes data held by an output message pointer
void OMessageDelete(OMessagePtr oMessagePtr);

/*---------------------------------------------------------------------------*/
//PARSING FUNCTIONS
/*---------------------------------------------------------------------------*/

// Parses a surname string from stdin
// Returns said string
char* ReadName();

// Parses a description string from stdin
char* ReadDescription();

// Practically a copy of ReadName
char* ReadNumber();

// Parses one line of input from stdin
// Returns a input message pointer
IMessagePtr InputParse();

// Takes an output message pointer and outputs the appropriate value
// Returns if we should continue parsing, or not.
bool OutputParse(OMessagePtr oMessagePtr);

#endif //HOSPITAL_PARSE_H
