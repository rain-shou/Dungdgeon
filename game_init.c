#include <stdlib.h>
#include "game_init.h"
#include "dialogue.h"
#include "player_data.h"
#include "map_data.h"
#include "equipment_data.h"

void initialize_game(void) {
    initialize_player(&player);
    layer = 0;
    current_layer = 1;
    for (int i = 0; i < LAYER; i++) {
        for (int j = 0; j < WIDTH; ++j) {
            for (int k = 0; k < LENGTH; ++k) {
                total_walkable_layer[i][j][k] = -1;
                total_explored_layer[i][j][k] = 0;
            }
        }
    }
    dialogue = create_dialogue();
    up_or_down = true;
    assign_equipments_to_unique_floors();
    amulet_not_taken = true;
}

void initialize_player(struct player_data *p) {
    p->health = 100;
    p->max_health = 100;
    p->attack = 10;
    p->total_attack = p->attack;
    p->defense = 5;
    p->total_defense = p->defense;
    p->level = 1;
    p->gold = 0;
    p->experience = 0;
    p->armor = -1;
    p->weapon = -1;
    p->potion = 0;
    p->bag_number = 0;
}

void initialize_layer(void) {
    for (int i = 0; i < WIDTH; ++i) {
        for (int j = 0; j < LENGTH; ++j) {
            entity_layer[i][j] = ' ';
            walkable_layer[i][j] = -1;
            explored_layer[i][j] = 0;
        }
    }
    for (int i = 0; i <= 8; ++i) {
        room_data[i].is_exist = true;
        for (int j = 0; j < 4; ++j) {
            room_data[i].map_info.gate[j].is_exist = true;
        }
    }
    layer_treasure[0] = -1;
    layer_treasure[1] = -1;
    layer++;
}

void load_layer(int n) {
    for (int i = 0; i < WIDTH; ++i) {
        for (int j = 0; j < LENGTH; ++j) {
            walkable_layer[i][j] = total_walkable_layer[n][i][j];
            explored_layer[i][j] = total_explored_layer[n][i][j];
        }
    }
    for (int i = 0; i < 8; i++) {
        regions[i] = total_regions[n][i];
    }
    for (int i = 0; i < 9; i++) {
        room_data[i] = total_room_data[n][i];
    }
}

void save_current_layer(int n) {
    for (int i = 0; i < WIDTH; ++i) {
        for (int j = 0; j < LENGTH; ++j) {
            total_walkable_layer[n][i][j] = walkable_layer[i][j];
            total_explored_layer[n][i][j] = explored_layer[i][j];
        }
    }
    for (int i = 0; i < 8; i++) {
        total_regions[n][i] = regions[i];
    }
    for (int i = 0; i < 9; i++) {
        total_room_data[n][i] = room_data[i];
    }
}

void assign_equipments_to_unique_floors(void) {
    for (int i = 0; i < WEAPON_AMOUNT; i++) {
        weapon_list[i].floor = (int)(random() % (weapon_list[i].max_floor - weapon_list[i].min_floor)) + weapon_list[i].min_floor;
        do {
            armor_list[i].floor = (int)(random() % (armor_list[i].max_floor - armor_list[i].min_floor)) + armor_list[i].min_floor;
        } while (armor_list[i].floor == weapon_list[i].floor);
    }
}
