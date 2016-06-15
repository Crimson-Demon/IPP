/** @file
    Implementation of interface of parser.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "parse.h"

const int MAX_COMMAND_LEN = 101;

bool parse_ints(char buffer[103], int start, int num_of_spaces) {
    int buff_len = (int) strlen(buffer);
    bool was_space = false;
    int i = start;
    int space_counter = 0;
    while(i < buff_len) {
        if(isdigit(buffer[i])) {
            i++;
            if(was_space)
                was_space = false;
        } else if(buffer[i] == '\n')
            i++;
        else if(buffer[i] == ' ') {
            if(was_space)
                return false;
            else {
                was_space = true;
                space_counter++;
                i++;
            }
        } else
            return false;
    }
    if(buffer[i - 1] == ' ')
        return false;
    if(space_counter != num_of_spaces)
        return false;
    return true;
}

command* parse_command() {
    char buffer[MAX_COMMAND_LEN + 2];
    if(fgets(buffer, MAX_COMMAND_LEN + 2, stdin) == null) {
        command* new_command = (command*) malloc(sizeof(command));
        new_command->name[0] = '\0';
        return new_command;
    }
    if(strlen(buffer) > (size_t) MAX_COMMAND_LEN) {
        command* new_command = (command*) malloc(sizeof(command));
        new_command->name[0] = '\0';
        return new_command;
    }
    if(strncmp(buffer, "INIT", 4) == 0) {
        command* new_command = (command*) malloc(sizeof(command));
        if(!parse_ints(buffer, 4, 7)) {
            new_command->name[0] = '\0';
            return new_command;
        }
        sscanf(buffer, "%s %i %i %i %i %i %i %i",
               new_command->name,
               &(new_command->data[0]),
               &(new_command->data[1]),
               &(new_command->data[2]),
               &(new_command->data[3]),
               &(new_command->data[4]),
               &(new_command->data[5]),
               &(new_command->data[6]));
        new_command->data[3]--;
        new_command->data[4]--;
        new_command->data[5]--;
        new_command->data[6]--;
        return new_command;
    } else if(strncmp(buffer, "MOVE", 4) == 0) {
        command* new_command = (command*) malloc(sizeof(command));
        if(!parse_ints(buffer, 4, 4)) {
            new_command->name[0] = '\0';
            return new_command;
        }
        sscanf(buffer, "%s %i %i %i %i",
               new_command->name,
               &(new_command->data[3]),
               &(new_command->data[4]),
               &(new_command->data[5]),
               &(new_command->data[6]));
        new_command->data[3]--;
        new_command->data[4]--;
        new_command->data[5]--;
        new_command->data[6]--;
        return new_command;
    } else if(strncmp(buffer, "PRODUCE_KNIGHT", 14) == 0) {
        command* new_command = (command*) malloc(sizeof(command));
        if(!parse_ints(buffer, 14, 4)) {
            new_command->name[0] = '\0';
            return new_command;
        }
        sscanf(buffer, "%s %i %i %i %i",
               new_command->name,
               &(new_command->data[3]),
               &(new_command->data[4]),
               &(new_command->data[5]),
               &(new_command->data[6]));
        new_command->data[3]--;
        new_command->data[4]--;
        new_command->data[5]--;
        new_command->data[6]--;
        return new_command;
    } else if(strncmp(buffer, "PRODUCE_PEASANT", 15) == 0) {
        command* new_command = (command*) malloc(sizeof(command));
        if(!parse_ints(buffer, 15, 4)) {
            new_command->name[0] = '\0';
            return new_command;
        }
        sscanf(buffer, "%s %i %i %i %i",
               new_command->name,
               &(new_command->data[3]),
               &(new_command->data[4]),
               &(new_command->data[5]),
               &(new_command->data[6]));
        new_command->data[3]--;
        new_command->data[4]--;
        new_command->data[5]--;
        new_command->data[6]--;
        return new_command;
    } else if(strncmp(buffer, "END_TURN", 8) == 0) {
        command* new_command = (command*) malloc(sizeof(command));
        if(strlen(buffer) > strlen("END_TURN\n")) {
            new_command->name[0] = '\0';
            return new_command;
        }
        sscanf(buffer, "%s", new_command->name);
        return new_command;
    } else {
        command* new_command = (command*) malloc(sizeof(command));
        new_command->name[0] = '\0';
        return new_command;
    }
}
