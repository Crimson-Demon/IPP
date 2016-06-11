/** @file
   Interface of parser.

*/

#ifndef PARSE_H
#define PARSE_H

#define null NULL

#include <stdbool.h>

/** Constant holding max acceptable length of line.
 */
extern const int MAX_COMMAND_LEN;

/** Structure of a command.
 Returns command with data points using 'command' structure.
 */
typedef struct def_command {
    char name[16];
    int data[7];
} command;

/** Checks line for correct structure.
  Checks if buffer is an initially correct input line.
  * @param[in] buffer[103] Input line buffer.
  * @param[in] start Index from which to start int parsing.
  * @param[in] num_of_spaces The expected number of spaces to be encountered.
  */
bool parse_ints(char buffer[103], int start, int num_of_spaces);

/** Reads a command.
  Returns command with data points using 'command' structure.
  */
command *parse_command();

#endif /* PARSE_H */
