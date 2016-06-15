/** @file
    Main file harnessing both parser and game engine functionalities.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "parse.h"
#include "engine.h"

int main() {
    start_game();
    command* new_command;
    while(EOF) {
        new_command = parse_command();
        if(!player_1.init || !player_2.init) {
            if(strcmp(new_command->name, "INIT") == 0) {
                int code = init(new_command->data[0],
                                new_command->data[1],
                                new_command->data[2],
                                new_command->data[3],
                                new_command->data[4],
                                new_command->data[5],
                                new_command->data[6]);
                if(code == INIT_ERROR) {
                    //fprintf(stderr, "input error\n");
                    free(new_command);
                    end_game();
                    return 42;
                }
                init(new_command->data[0],
                     new_command->data[1],
                     new_command->data[2] == 1 ? 2 : 1,
                     new_command->data[3],
                     new_command->data[4],
                     new_command->data[5],
                     new_command->data[6]);
                if(new_command->data[2] == 1) {
                    us = player_1;
                    our_turn = true;
                    do_actions();
                    end_turn();
                    fprintf(stdout, "END_TURN\n");
                    fflush(stdout);
                    if(check_if_end() != OK) {
                        break;
                    }
                } else {
                    us = player_2;
                    our_turn = false;
                }
            } else {
                //fprintf(stderr, "input error\n");
                free(new_command);
                end_game();
                return 42;
            }
        } else {
            if(strcmp(new_command->name, "MOVE") == 0) {
                int code = move(new_command->data[3],
                                new_command->data[4],
                                new_command->data[5],
                                new_command->data[6]);
                if(code == MOVE_ERROR) {
                    //fprintf(stderr, "input error\n");
                    free(new_command);
                    end_game();
                    return 42;
                }
                if(check_if_end() != OK) {
                    //print_topleft();
                    break;
                }
            } else if(strcmp(new_command->name, "PRODUCE_KNIGHT") == 0) {
                int code = produce_knight(new_command->data[3],
                                          new_command->data[4],
                                          new_command->data[5],
                                          new_command->data[6]);
                if(code == PRODUCE_ERROR) {
                    //fprintf(stderr, "input error\n");
                    free(new_command);
                    end_game();
                    return 42;
                }
                if(check_if_end() != OK) {
                    break;
                }
            } else if(strcmp(new_command->name, "PRODUCE_PEASANT") == 0) {
                int code = produce_peasant(new_command->data[3],
                                           new_command->data[4],
                                           new_command->data[5],
                                           new_command->data[6]);
                if(code == PRODUCE_ERROR) {
                    //fprintf(stderr, "input error\n");
                    free(new_command);
                    end_game();
                    return 42;
                }
                if(check_if_end() != OK) {
                    break;
                }
            } else if(strcmp(new_command->name, "END_TURN") == 0) {
                do_actions();
                end_turn();
                fprintf(stdout, "END_TURN\n");
                fflush(stdout);
                if(check_if_end() != OK) {
                    break;
                }
            } else {
                //fprintf(stderr, "input error\n");
                free(new_command);
                end_game();
                return 42;
            }
        }
        if(strcmp(new_command->name, "END_TURN") != 0)
            //print_topleft();
        free(new_command);
    }
    int code;
    int check = check_if_end();
    switch(check) {
        case PLAYER_1_WINS:
            if(us.king != null)
                code = 0;
            else
                code = 2;
            break;
        case PLAYER_2_WINS:
            if(us.king != null)
                code = 0;
            else
                code = 2;
            break;
        case TURN_LIMIT:
            code = 1;
            break;
        case DRAW:
            code = 1;
            break;
        default:
            code = 42;
            break;
    }
    free(new_command);
    end_game();
    //fprintf(stderr, "the code is=%i\n", code);
    return code;
}
