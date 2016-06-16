/** @file
    Implementation of interface of game engine.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "engine.h"

#define max(a, b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

void start_game() {
    player_1.init = false;
    player_2.init = false;
    player_1.king = null;
    player_2.king = null;
    player_1_turn = true;
    board.size = 0;
    board.init = false;
    board.player_1_list = null;
    board.player_2_list = null;
    cur_turn = 1;
}

void end_game() {
    unit_list_elem_ptr unit_list_temp = board.player_1_list;
    while(unit_list_temp != null) {
        unit_list_elem_ptr unit_list_temp2 = unit_list_temp;
        if(unit_list_temp->unit != null) {
            free(unit_list_temp->unit);
            unit_list_temp->unit = null;
        }
        unit_list_temp = unit_list_temp2->next;
        free(unit_list_temp2);
    }
    unit_list_temp = board.player_2_list;
    while(unit_list_temp != null) {
        unit_list_elem_ptr unit_list_temp2 = unit_list_temp;
        if(unit_list_temp->unit != null) {
            free(unit_list_temp->unit);
            unit_list_temp->unit = null;
        }
        unit_list_temp = unit_list_temp2->next;
        free(unit_list_temp2);
    }
    player_1.king = null;
    player_2.king = null;
}

void print_unit(unit_ptr u_ptr) {
    switch(u_ptr->type) {
        case KING:
            if (u_ptr->owner == PLAYER_1)
                fprintf(stdout, "K");
            else
                fprintf(stdout, "k");
            break;
        case KNIGHT:
            if (u_ptr->owner == PLAYER_1)
                fprintf(stdout, "R");
            else
                fprintf(stdout, "r");
            break;
        case PEASANT:
            if (u_ptr->owner == PLAYER_1)
                fprintf(stdout, "C");
            else
                fprintf(stdout, "c");
            break;
        default:
            fprintf(stdout, "Epic fail");
            break;
    }
}
//TODO: Can eventually remake it so that it makes a temporary list to search through
void print_topleft() {
    int max_n;
    if(board.size > 10)
        max_n = 10;
    else
        max_n = board.size;
    for(int i = 0; i < max_n; i++) {
        for(int j = 0; j < max_n; j++) {
            bool found = false;
            unit_list_elem_ptr unit_list_temp = board.player_1_list;
            while(unit_list_temp != null && !found) {
                if(unit_list_temp->unit->x == j && unit_list_temp->unit->y == i) {
                    found = true;
                    print_unit(unit_list_temp->unit);
                }
                unit_list_temp = unit_list_temp->next;
            }
            unit_list_temp = board.player_2_list;
            while(unit_list_temp != null && !found) {
                if (unit_list_temp->unit->x == j && unit_list_temp->unit->y == i) {
                    found = true;
                    print_unit(unit_list_temp->unit);
                }
                unit_list_temp = unit_list_temp->next;
            }
            if(!found)
                fprintf(stdout, ".");
        }
        fprintf(stdout, "\n");
    }
    fprintf(stdout, "\n");
}

bool is_empty(int x1, int y1) {
    unit_list_elem_ptr unit_list_temp = board.player_1_list;
    while(unit_list_temp != null) {
        if(unit_list_temp->unit->x == x1 && unit_list_temp->unit->y == y1)
            return false;
        unit_list_temp = unit_list_temp->next;
    }
    unit_list_temp = board.player_2_list;
    while(unit_list_temp != null) {
        if (unit_list_temp->unit->x == x1 && unit_list_temp->unit->y == y1)
            return false;
        unit_list_temp = unit_list_temp->next;
    }
    return true;
}

unit_ptr get_unit(int x1, int y1) {
    unit_list_elem_ptr unit_list_temp = board.player_1_list;
    while(unit_list_temp != null) {
        if(unit_list_temp->unit->x == x1 && unit_list_temp->unit->y == y1)
            return unit_list_temp->unit;
        unit_list_temp = unit_list_temp->next;
    }
    unit_list_temp = board.player_2_list;
    while(unit_list_temp != null) {
        if (unit_list_temp->unit->x == x1 && unit_list_temp->unit->y == y1)
            return unit_list_temp->unit;
        unit_list_temp = unit_list_temp->next;
    }
    return null;
}

void erase_unit(unit_ptr u_ptr) {
    bool erased = false;
    unit_list_elem_ptr unit_list_elem_curr = board.player_1_list;
    unit_list_elem_ptr unit_list_elem_prev = null;
    while(unit_list_elem_curr != null && !erased) {
        if (unit_list_elem_curr->unit == u_ptr) {
            if(unit_list_elem_curr->next == null) {
                free(unit_list_elem_curr->unit);
                unit_list_elem_curr->unit = null;
                if(board.player_1_list->unit == null)
                    board.player_1_list = null;
                if(unit_list_elem_prev != null)
                    unit_list_elem_prev->next = null;
                free(unit_list_elem_curr);
            } else {
                free(unit_list_elem_curr->unit);
                unit_list_elem_curr->unit = unit_list_elem_curr->next->unit;
                unit_list_elem_curr->next->unit = null;
                unit_list_elem_ptr unit_list_elem_next = unit_list_elem_curr->next;
                unit_list_elem_curr->next = unit_list_elem_curr->next->next;
                //if(unit_list_elem_prev != null)
                //    unit_list_elem_prev->next = null;
                free(unit_list_elem_next);
            }
            erased = true;
        }
        unit_list_elem_prev = unit_list_elem_curr;
        unit_list_elem_curr = unit_list_elem_curr->next;
    }
    unit_list_elem_curr = board.player_2_list;
    unit_list_elem_prev = null;
    while(unit_list_elem_curr != null && !erased) {
        if (unit_list_elem_curr->unit == u_ptr) {
            if(unit_list_elem_curr->next == null) {
                free(unit_list_elem_curr->unit);
                unit_list_elem_curr->unit = null;
                if(board.player_2_list->unit == null)
                    board.player_2_list = null;
                if(unit_list_elem_prev != null)
                    unit_list_elem_prev->next = null;
                free(unit_list_elem_curr);
            } else {
                free(unit_list_elem_curr->unit);
                unit_list_elem_curr->unit = unit_list_elem_curr->next->unit;
                unit_list_elem_curr->next->unit = null;
                unit_list_elem_ptr unit_list_elem_next = unit_list_elem_curr->next;
                unit_list_elem_curr->next = unit_list_elem_curr->next->next;
                //if(unit_list_elem_prev != null)
                //    unit_list_elem_prev->next = null;
                free(unit_list_elem_next);
            }
            erased = true;
        }
        unit_list_elem_prev = unit_list_elem_curr;
        unit_list_elem_curr = unit_list_elem_curr->next;
    }
}

bool check_init(int n, int k, int x1, int y1, int x2, int y2) {
    if(board.init) {
        if (board.size != n)
            return false;
        else if (k < 1)
            return false;
        else if (is_empty(x1, y1))
            return false;
        else if (get_unit(x1, y1)->type != KING)
            return false;
        else if (get_unit(x1, y1)->owner != PLAYER_1)
            return false;
        else if (is_empty(x1, y1))
            return false;
        else if(get_unit(x2, y2)->type != KING)
            return false;
        else if(get_unit(x2, y2)->owner != PLAYER_2)
            return false;
        else
            return true;
    } else {
        if(n < 9 || k < 1)
            return false;
        else if(x1 < 0 || n - 3 < x1)
            return false;
        else if(y1 < 0 || n < y1)
            return false;
        else if(x2 < 0 || n - 3 < x2)
            return false;
        else if(y2 < 0 || n < y2)
            return false;
        else if(x1 == x2 && y1 == y2)
            return false;
        else if(max(abs(x1 - x2), abs(y1 - y2)) < 8) {
            return false;
        } else
            return true;
    }
}

void produce_unit(int x1, int y1, player_type p_type, unit_type u_type) {
    unit_ptr new_unit = (unit_ptr) malloc(sizeof(unit));
    new_unit->type = u_type;
    new_unit->owner = p_type;
    new_unit->x = x1;
    new_unit->y = y1;
    new_unit->last_move = max(cur_turn - 1, 0);
    unit_list_elem_ptr new_unit_list_elem = (unit_list_elem_ptr) malloc(sizeof(unit_list_elem));
    new_unit_list_elem->unit = new_unit;
    if(p_type == PLAYER_1) {
        new_unit_list_elem->next = board.player_1_list;
        board.player_1_list = new_unit_list_elem;
    } else {
        new_unit_list_elem->next = board.player_2_list;
        board.player_2_list = new_unit_list_elem;
    }

}

void allocate_board(int n, int x1, int y1, int x2, int y2) {
    board.size = n;
    produce_unit(x1, y1, PLAYER_1, KING);
    produce_unit(x1 + 2, y1, PLAYER_1, KNIGHT);
    produce_unit(x1 + 3, y1, PLAYER_1, KNIGHT);
    produce_unit(x1 + 1, y1, PLAYER_1, PEASANT);
    produce_unit(x2, y2, PLAYER_2, KING);
    produce_unit(x2 + 2, y2, PLAYER_2, KNIGHT);
    produce_unit(x2 + 3, y2, PLAYER_2, KNIGHT);
    produce_unit(x2 + 1, y2, PLAYER_2, PEASANT);
    player_1.king = get_unit(x1, y1);
    player_2.king = get_unit(x2, y2);
    board.init = true;
}

bool not_adjacent(int x1, int y1, int x2, int y2) {
    if(max(abs(x2 - x1), abs(y2 - y1)) > 1)
        return true;
    return false;
}

int init(int n, int k, int p, int x1, int y1, int x2, int y2) {
    if(p == 1 && !player_1.init) {
        if(!check_init(n, k, x1, y1, x2, y2))
            return INIT_ERROR;
        if(!board.init)
            allocate_board(n, x1, y1, x2, y2);
        player_1.init = true;
        player_1.turn_limit = k;
    } else if(p == 2 && !player_2.init) {
        if(!check_init(n, k, x1, y1, x2, y2))
            return INIT_ERROR;
        if(!board.init)
            allocate_board(n, x1, y1, x2, y2);
        player_2.init = true;
        player_2.turn_limit = k;
    } else
        return INIT_ERROR;
    return OK;
}

bool can_move(int x1, int y1, int x2, int y2) {
    if(x1 < 0 || x2 < 0 || y1 < 0 || y2 < 0)
        return false;
    else if(x1 > board.size - 1 || x2 > board.size - 1 || y1 > board.size - 1 || y2 > board.size - 1)
        return false;
    else if(is_empty(x1, y1))
        return false;
    else if((get_unit(x1, y1)->owner == PLAYER_1) != player_1_turn)
        return false;
    else if(!(is_empty(x2, y2)) && (get_unit(x2, y2)->owner == PLAYER_1) == player_1_turn)
        return false;
    else if(not_adjacent(x1, y1, x2, y2))
        return false;
    else if(get_unit(x1, y1)->last_move == cur_turn)
        return false;
    else
        return true;
}

int move(int x1, int y1, int x2, int y2) {
    /*fprintf(stderr, "coords = %d %d %d %d\n", x1, y1, x2, y2);
    fprintf(stderr, "x1 and board size = %d %d\n", x1, board.size - 1);
    fprintf(stderr, "x2 and board size = %d %d\n", x2, board.size - 1);
    fprintf(stderr, "y1 and board size = %d %d\n", y1, board.size - 1);
    fprintf(stderr, "y2 and board size = %d %d\n", y2, board.size - 1);
    fprintf(stderr, "empty = %d\n",is_empty(x1, y1));
    fprintf(stderr, "our unit = %d\n",(get_unit(x1, y1)->owner == PLAYER_1) != player_1_turn);
    fprintf(stderr, "unit owner = %d\n", get_unit(x1, y1)->owner);
    fprintf(stderr, "Player 1 = %d\n", PLAYER_1);
    fprintf(stderr, "unit owner is player 1 = %d\n", get_unit(x1, y1)->owner == PLAYER_1);
    fprintf(stderr, "player 1 turn = %d\n", player_1_turn);
    fprintf(stderr, "our turn = %d\n", our_turn);
    fprintf(stderr, "non empty theirs + their unit = %d\n",!(is_empty(x2, y2)) && (get_unit(x2, y2)->owner == PLAYER_1) == player_1_turn);
    fprintf(stderr, "not adjacent = %d\n", not_adjacent(x1, y1, x2, y2));
    fprintf(stderr, "cant move = %d\n", get_unit(x1, y1)->last_move == cur_turn);*/
    if(can_move(x1, y1, x2, y2)) {
        if(is_empty(x2, y2)) {
            unit_ptr unit_temp = get_unit(x1, y1);
            unit_temp->x = x2;
            unit_temp->y = y2;
            unit_temp->last_move = cur_turn;
        } else {
            unit_ptr my_unit = get_unit(x1, y1);
            unit_ptr their_unit = get_unit(x2, y2);
            if(their_unit->type < my_unit->type) {
                if(their_unit->type == KING) {
                    if(player_1_turn)
                        player_2.king = null;
                    else
                        player_1.king = null;
                }
                erase_unit(their_unit);
                my_unit->x = x2;
                my_unit->y = y2;
                my_unit->last_move = cur_turn;
            } else if(their_unit->type == my_unit->type) {
                if(their_unit->type == KING) {
                    player_1.king = null;
                    player_2.king = null;
                }
                erase_unit(their_unit);
                erase_unit(my_unit);
            } else {
                if(my_unit->type == KING) {
                    if(player_1_turn)
                        player_1.king = null;
                    else
                        player_2.king = null;
                }
                erase_unit(my_unit);
            }
        }
        return OK;
    } else
        return MOVE_ERROR;
}

bool can_produce(int x1, int y1, int x2, int y2) {
    /*fprintf(stderr, "can produce = %d\n", get_unit(x1, y1)->last_move + 3 > cur_turn);
    fprintf(stderr, "last move = %d\n", get_unit(x1, y1)->last_move);
    fprintf(stderr, "current turn = %d\n", cur_turn);*/
    if(x1 < 0 || x2 < 0 || y1 < 0 || y2 < 0)
       return false;
    else if(x1 > board.size - 1 || x2 > board.size - 1 || y1 > board.size - 1 || y2 > board.size - 1)
        return false;
    else if(is_empty(x1, y1))
        return false;
    else if((get_unit(x1, y1)->owner == PLAYER_1) != player_1_turn)
        return false;
    else if(get_unit(x1, y1)->type != PEASANT)
        return false;
    else if(get_unit(x1, y1)->last_move + 3 > cur_turn)
        return false;
    else if(!is_empty(x2, y2))
        return false;
    else
        return true;
}

int produce_knight(int x1, int y1, int x2, int y2) {
    if(can_produce(x1, y1, x2, y2)) {
        produce_unit(x2, y2, player_1_turn ? PLAYER_1 : PLAYER_2, KNIGHT);
        get_unit(x1, y1)->last_move = cur_turn;
        return OK;
    } else
        return PRODUCE_ERROR;
}

int produce_peasant(int x1, int y1, int x2, int y2) {
    if(can_produce(x1, y1, x2, y2)) {
        produce_unit(x2, y2, player_1_turn ? PLAYER_1 : PLAYER_2, PEASANT);
        get_unit(x1, y1)->last_move = cur_turn;
        return OK;
    } else
        return PRODUCE_ERROR;
}

int end_turn() { ;
    if(!player_1_turn)
        cur_turn++;
    our_turn = !our_turn;
    player_1_turn = !player_1_turn;
    return OK;
}

int check_if_end() {
    if(player_1.init && player_2.init) {
        if (cur_turn > player_1.turn_limit || cur_turn > player_2.turn_limit || cur_turn == INT_MAX) {
            //fprintf(stderr, "draw\n");
            return TURN_LIMIT;
        } else if (player_1.king == null && player_2.king == null) {
            //fprintf(stderr, "draw\n");
            return DRAW;
        } else if(player_1.king == null) {
            //fprintf(stderr, "player 2 won\n");
            return PLAYER_2_WINS;
        } else if(player_2.king == null) {
            //fprintf(stderr, "player 1 won\n");
            return PLAYER_1_WINS;
        } else
            return OK;
    } else
        return END_BEFORE_INIT;
}

void king_acts() {
    unit_ptr king_temp = us.king;
    bool potential_moves[3][3];
    bool has_to_evade = false;
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            potential_moves[i][j] = true;
    unit_list_elem_ptr enemy_list = us.king == player_1.king ? board.player_2_list : board.player_1_list;
    fprintf(stderr, "our king = %d\n", us.king);
    fprintf(stderr, "player 1 king = %d\n", player_1.king);
    fprintf(stderr, "our king is player 1 king = %d\n", us.king == player_1.king);
    while(enemy_list != null) {
        int diff_x = enemy_list->unit->x - king_temp->x;
        int diff_y = enemy_list->unit->y - king_temp->y;
        if(abs(diff_x) <= 1 && abs(diff_y) <= 1) {
            has_to_evade = true;
            if(diff_x == 0 && diff_y == 0) {
                //you shouldn't be here!!! :x
            } else if(diff_x == 0) {
                potential_moves[0][diff_y + 1] = false;
                potential_moves[1][diff_y + 1] = false;
                potential_moves[2][diff_y + 1] = false;
                potential_moves[0][1] = false;
                potential_moves[1][1] = false;
                potential_moves[2][1] = false;
            } else if(diff_y == 0) {
                potential_moves[diff_x + 1][0] = false;
                potential_moves[diff_x + 1][1] = false;
                potential_moves[diff_x + 1][2] = false;
                potential_moves[1][0] = false;
                potential_moves[1][1] = false;
                potential_moves[1][2] = false;
            } else { //if(diff_y != 0 || diff_x != 0)
                potential_moves[diff_x + 1][diff_y + 1] = false;
                potential_moves[diff_x + 1 - 1*diff_x][diff_y + 1] = false;
                potential_moves[diff_x][diff_y + 1 - 1*diff_y] = false;
            }
        }
        enemy_list = enemy_list->next;
    }
    if(has_to_evade) {
        fprintf(stderr, "King has to evade!");
        bool has_evaded = false;
        for(int i = 0; i < 3 && !has_evaded; i++)
            for(int j = 0; j < 3 && !has_evaded; j++)
                if(potential_moves[i][j]) {
                    int x = king_temp->x;
                    int y = king_temp->y;
                    if(can_move(x, y, x + i + 1, y + j + 1)) {
                        move(x, y, x + i + 1, y + j + 1);
                        has_evaded = true;
                        fprintf(stdout, "MOVE %d %d %d %d\n", x + 1, y + 1, x + 1 + i + 1, y + 1 + j + 1);
                    }
                }
    }
}

unit_ptr find_closest_unit(unit_ptr unit) {
    unit_list_elem_ptr enemy_list_head = us.king == player_1.king ? board.player_2_list : board.player_1_list;
    unit_list_elem_ptr enemy_list_temp = enemy_list_head;
    unit_ptr closest_unit = null;
    //Unit seek out closest units
    while(enemy_list_temp != null) {
        fprintf(stderr, "Enemy unit is = %d\n", enemy_list_temp->unit->type);
        if(closest_unit == null)
            closest_unit = enemy_list_temp->unit;
        else {
            //compare with previous closest unit and update if neccessary
            int x = unit->x;
            int y = unit->y;
            int x_old = closest_unit->x;
            int y_old = closest_unit->y;
            int x_new = enemy_list_temp->unit->x;
            int y_new = enemy_list_temp->unit->y;
            int old_dist = max(abs(x - x_old), abs(y - y_old));
            int new_dist = max(abs(x - x_new), abs(y - y_new));
            if(new_dist < old_dist)
                closest_unit = enemy_list_temp->unit;
        }
        enemy_list_temp = enemy_list_temp->next;
    }
    return closest_unit;
}

void move_towards(int x1, int y1, int x2, int y2) {
    int diff_x = x1 - x2;
    int diff_y = y1 - y2;
    fprintf(stderr, "Our position = %d %d\n", x1, y1);
    fprintf(stderr, "Closest enemy position = %d %d\n", x2, y2);
    fprintf(stderr, "Differences in x and y positions = %d %d\n", diff_x, diff_y);
    if (diff_x != 0 && diff_y != 0) {
        fprintf(stderr, "Moving diagonally\n");
        //we move diagonally until we are on the same line
        //if we can't move diagonally, then we move straight in the best direction.
        //if we cant' even do that, then dang.
        int sign_y = x1 > x2 ? -1 : 1;
        int sign_x = y1 > y2 ? -1 : 1;
        if(can_move(x1, y1, x1 + 1 * sign_x, y1 + 1 * sign_y)) {
            move(x1, y1, x1 + 1 * sign_x, y1 + 1 * sign_y);
            fprintf(stdout, "MOVE %d %d %d %d\n", x1 + 1, y1 + 1, x1 + 1 + 1 * sign_x, y1 + 1 + 1 * sign_y);
        } else {
            if(can_move(x1, y1, x1 + 1*sign_x, y1)) {
                move(x1, y1, x1 + 1 * sign_x, y1);
                fprintf(stdout, "MOVE %d %d %d %d\n", x1 + 1, y1 + 1, x1 + 1 + 1 * sign_x, y1 + 1);
            } else if(can_move(x1, y1, x1, y1 + 1*sign_y)) {
                move(x1, y1, x1, y1 + 1 * sign_y);
                fprintf(stdout, "MOVE %d %d %d %d\n", x1 + 1, y1 + 1, x1 + 1, y1 + 1 + 1 * sign_y);
            }
        }
    } else
        fprintf(stderr, "Moving forward!\n");
    //we move forward, deviating only, if we cant move straight forward
    //if there is no possibility to move forward, then we don't move
    if(x1 - x2 == 0) {
        int sign = y1 > y2 ? -1 : 1;
        if(can_move(x1, y1, x1, y1 + sign * 1)) {
            move(x1, y1, x1, y1 + sign * 1);
            fprintf(stdout, "MOVE %d %d %d %d\n", x1 + 1, y1 + 1, x1 + 1, y1 + 1 + sign * 1);
        } else
        if(can_move(x1, y1, x1 + 1, y1 + sign*1)) {
            move(x1, y1, x1 + 1, y1 + sign * 1);
            fprintf(stdout, "MOVE %d %d %d %d\n", x1 + 1, y1 + 1, x1 + 1 + 1, y1 + 1 + sign * 1);
        } else if(can_move(x1, y1, x1 - 1, y1 + sign*1)) {
            move(x1, y1, x1 - 1, y1 + sign * 1);
            fprintf(stdout, "MOVE %d %d %d %d\n", x1 + 1, y1 + 1, x1 - 1 + 1, y1 + 1 + sign * 1);
        }
    } else {
        int sign = x1 > x2 ? -1 : 1;
        if(can_move(x1, y1, x1 + sign*1, y1)) {
            move(x1, y1, x1 + sign * 1, y1);
            fprintf(stdout, "MOVE %d %d %d %d\n", x1 + 1, y1 + 1, x1 + 1 + sign * 1, y1 + 1);
        } else
        if(can_move(x1, y1, x1 + sign*1, y1 + 1)) {
            move(x1, y1, x1 + sign * 1, y1 + 1);
            fprintf(stdout, "MOVE %d %d %d %d\n", x1 + 1, y1 + 1, x1 + 1 + sign * 1, y1 + 1 + 1);
        } else if(can_move(x1, y1, x1 + sign*1, y1 - 1)) {
            move(x1, y1, x1 + sign * 1, y1 - 1);
            fprintf(stdout, "MOVE %d %d %d %d\n", x1 + 1, y1 + 1, x1 + 1 + sign * 1, y1 + 1 - 1);
        }
    }
}

void knights_act() {
    unit_list_elem_ptr our_list = us.king == player_1.king ? board.player_1_list : board.player_2_list;
    while(our_list != null) {
        if(our_list->unit->type == KNIGHT) {
            unit_ptr closest_unit = find_closest_unit(our_list->unit);
            //Move in the direction of the closest unit and fight
            if(closest_unit != null) {
                int x = our_list->unit->x;
                int y = our_list->unit->y;
                int x_closest = closest_unit->x;
                int y_closest = closest_unit->y;
                move_towards(x, y, x_closest, y_closest);
            } else {
                fprintf(stderr, "there is no closest unit! WTF?!");
            }
        }
        our_list = our_list->next;
    }
}

void peasants_act() {
    unit_list_elem_ptr our_list = us.king == player_1.king ? board.player_1_list : board.player_2_list;
    unit_ptr peasants[2];
    int count = 0;
    while(our_list != null) {
        if(our_list->unit->type == PEASANT) {
            peasants[count] = our_list->unit;
            count++;
        }
        our_list = our_list->next;
    }
    if(count == 1) {
        fprintf(stderr, "Only one peasant! Indeed, %d\n", count);
        int x = peasants[0]->x;
        int y = peasants[0]->y;
        bool has_produced = false;
        for(int i = 0; i < 3 && !has_produced; i++)
            for(int j = 0; j < 3 && !has_produced; j++) {
                fprintf(stderr, "We are interested in producing on %d %d\n", x + 1 - 1 + i, y + 1 - 1 + j);
                if (can_produce(x, y, x - 1 + i, y - 1 + j)) {
                    fprintf(stderr, "We can produce!");
                    produce_peasant(x, y, x - 1 + i, y - 1 + j);
                    fprintf(stdout, "PRODUCE_PEASANT %d %d %d %d\n", x + 1, y + 1, x + 1 - 1 + i, y + 1 - 1 + j);
                    has_produced = true;
                }
            }
    } else if(count == 2) {
        fprintf(stderr, "We have a whole two peasants! Indeed, %d\n", count);
        int x = peasants[0]->x;
        int y = peasants[0]->y;
        bool has_produced = false;
        for(int i = 0; i < 3 && !has_produced; i++)
            for(int j = 0; j < 3 && !has_produced; j++)
                if(can_produce(x, y, x - 1 + i, y - 1 + j)) {
                    produce_knight(x, y, x - 1 + i, y - 1 + j);
                    fprintf(stdout, "PRODUCE_KNIGHT %d %d %d %d\n", x + 1, y + 1, x + 1 - 1 + i, y + 1 - 1 + j);
                    has_produced = true;
                }
        x = peasants[1]->x;
        y = peasants[1]->y;
        has_produced = false;
        for(int i = 0; i < 3 && !has_produced; i++)
            for(int j = 0; j < 3 && !has_produced; j++)
                if(can_produce(x, y, x - 1 + i, y - 1 + j)) {
                    produce_knight(x, y, x - 1 + i, y - 1 + j);
                    fprintf(stdout, "PRODUCE_KNIGHT %d %d %d %d\n", x + 1, y + 1, x + 1 - 1 + i, y + 1 - 1 + j);
                    has_produced = true;
                }
    } else {
        fprintf(stderr, "You shouldn't be here! Indeed, %d\n", count);
    }
}

void do_actions() {
    peasants_act();
    fprintf(stderr, "Peasants have acted\n");
    king_acts();
    fprintf(stderr, "King has acted\n");
    knights_act();
    fprintf(stderr, "Knights have acted\n");
}