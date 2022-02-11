//
// Created by payam on 2/10/22.
//

#ifndef STATE_IO_GENERALS_H
#define STATE_IO_GENERALS_H
#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#define max_sarbaz 50
#define NUM_POTOION 4
#define NUM_WAR 100
#define timeactivepotion 180
#define timeexistpotion 150
#define timeAIattack 30

extern double Vsoldier;

extern bool saveandexit;
extern bool your_potion;
extern bool ai_potion;
extern int fps_potion[];
extern int number_of_maps;
extern char number[50];
extern char number2[50];
extern char number3[50];
extern bool run_menu;
extern uint32_t clr[10];
struct potion
{
    int x;
    int y;
    bool exist;
    bool runnig;
    int index;
};
struct axis
{
    int x;
    int y;
};
struct person
{
    char name[200];
    int win;
    int lose;
};
struct line
{
    char place[50];
    char name[200];
    char win[50];
    char lose[50];
    char point[50];
};
extern SDL_Event event;
struct block
{
    bool nolimit;
    bool fastblock;
    int xpos;
    int ypos;
    int index;   //-1 yani khali baghie raghama motealegh be rangesh
    int number_soldier;
    int number_soldier2;
};
struct soldier
{
    double x;
    double y;
    double vx;
    double vy;
    int num_dest_block;
    int num_beg_block;
    int destx;
    int desty;
    int index;
    bool fast_run;
    bool stop;
    struct soldier * next;
};
struct warstatus
{
    int att;
    int def;
    int num_soldier;
    int counter;
    struct soldier * head;
};
extern struct block all_block[45];
extern int xCursor,yCursor;
extern Mix_Music *music;
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Texture *texture;
extern SDL_Rect texture_rect;
extern SDL_Surface *image;
extern char name_used_in_menu[200];
extern char temp_of_function_numberToString[10];
extern const int FPS;
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern bool game_is_running;
extern bool sound;
extern bool new_user;
extern char name[200];
extern char AIname[3][50];
extern int temp1;
extern int temp2;
//////////////////////////////////////////////
extern struct potion pot[NUM_POTOION];
extern struct warstatus wars[NUM_WAR];
extern int number_of_attack;
extern int number_of_block,number_of_player;
extern uint32_t *arr_of_colors;
extern struct block *arr_of_block;
extern long long counterFPS;
extern long long countai;
/////////////////////////////////////////////

#endif //STATE_IO_GENERALS_H
