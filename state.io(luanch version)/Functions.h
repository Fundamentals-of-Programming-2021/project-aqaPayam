
#ifndef STATE_IO_FUNCTIONS_H
#define STATE_IO_FUNCTIONS_H
#pragma once

void write_name_to_file();

int readfileforleaderboardandsort(struct line lines[]);
void boxleaderboard(SDL_Renderer * renderer,int x,int y,struct line khat,int R,int G,int B, int A);
void delete_leaderboard_data();
bool check_delete_leaderboard(SDL_Event ev);

int which_map_selected(SDL_Event ev,int scrol);
void delete_all_maps();
bool check_delete_maps(SDL_Event ev);

bool is_on_hint();
void delete_work(SDL_Event ev);
void render_delet();


bool leaderboard();
bool map(int which);
bool random_map();
bool select_map();
bool new_game();
void menu();
void intro();
void first_page();

#endif //STATE_IO_FUNCTIONS_H