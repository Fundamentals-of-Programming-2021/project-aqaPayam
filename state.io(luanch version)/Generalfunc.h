

#ifndef STATE_IO_GENERALFUNC_H
#define STATE_IO_GENERALFUNC_H
#pragma once

bool is_ok_to_run_game();
uint32_t color(int r,int g, int b, int a);
int stringToNumber(char * j);
void strrev(char *str1);
void numberTOstring(int num,char ch[]);
int number_to_string(int num);

void how_many_maps();
void write_number_of_maps();

void declareclr();
void soundplay(SDL_Event ev);
void showcursorandsound();

bool click_new_game(SDL_Event ev);
bool click_continue(SDL_Event ev);
bool click_ranking(SDL_Event ev);

void show_text(SDL_Renderer *renderer,int x,int y,const char * text,int font_size,int R,int G,int B, int A);
void txtRGBA(SDL_Renderer *renderer,int x,int y,const char * text,int font_size,int R,int G,int B, int A);

void check_exit_game(SDL_Event ev);

char inputs_string(SDL_Event ev);

void showcursorandsoundLEADERBOARD();
void show_delete_leaderborad();
void show_save();
bool LEADERBOARDback(SDL_Event ev);

#endif //STATE_IO_GENERALFUNC_H