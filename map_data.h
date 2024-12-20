#ifndef DANGDGEON_MAP_DATA_H
#define DANGDGEON_MAP_DATA_H

#include <stdbool.h>

#define LENGTH 99
#define WIDTH 35
#define LAYER 50

/* Each map_layer is divided to one main-room_data and eight areas */
struct region_info {
    int north;
    int west;
    int south;
    int east;
};

/*Room size l1 = (rand() % (5 - 3 + 1) + 3) + 1;
            w1 = (rand() % (3 - 1 + 1) + 1) + 1; */
struct room_info {
    bool is_exist;
    struct room_map_info {
        int north;
        int south;
        int west;
        int east;
        struct connector {
            bool is_exist;
            int x;
            int y;
        }gate[4]; /*0 for north, 1 for west, 2 for south, 3 for east.*/

    }map_info;
};

extern char entity_layer[WIDTH][LENGTH];
extern int walkable_layer[WIDTH][LENGTH];
    // 0-8 for rooms
    // 9 for +
    // 10 for #
    // 11 for -
    // 12 for |
    // 13 for >
    // 14 for <
    // 15 for ^
    // -1 for none
extern int explored_layer[WIDTH][LENGTH];
extern int total_walkable_layer[LAYER][WIDTH][LENGTH];
extern int total_explored_layer[LAYER][WIDTH][LENGTH];
extern struct region_info regions[8];
extern struct room_info room_data[9];
extern struct region_info total_regions[LAYER][8];
extern struct room_info total_room_data[LAYER][9];
extern int layer;
extern int current_layer;
extern int upstairs_pos[50][2]; // 0 for x, 1 for y
extern int downstairs_pos[50][2];
extern bool up_or_down; // down for true, up for false
extern int layer_treasure[2];
extern bool amulet_not_taken;

#endif //DANGDGEON_MAP_DATA_H
