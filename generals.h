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

double Vsoldier=15;

bool saveandexit=false;
bool your_potion=false;
bool ai_potion=false;
int fps_potion[NUM_POTOION]={0};
int number_of_maps=0;
char number[50]="";
char number2[50]="";
char number3[50]="";
bool run_menu=false;
uint32_t color(int r,int g, int b, int a){return    ( (a << 24) + (b<< 16) + (g << 8) + r) ;}
uint32_t clr[10];
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
SDL_Event event;
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
struct block all_block[45];
int xCursor=0,yCursor=0;
Mix_Music *music=NULL;
SDL_Window *window=NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *texture=NULL;
SDL_Rect texture_rect={.x=0,.y=0,.w=1920,.h=1080};
SDL_Surface *image=NULL;
char name_used_in_menu[200]="welcome ";
char temp_of_function_numberToString[10]="";
const int FPS = 60;
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
bool game_is_running=true;
bool sound=true;
bool new_user=true;
char name[200]="";
char AIname[3][50]={"AI one","AI two","AI three"};
int temp1=-1;
int temp2=-1;
//////////////////////////////////////////////
struct potion pot[NUM_POTOION];
struct warstatus wars[NUM_WAR];
int number_of_attack=0;
int number_of_block,number_of_player;
uint32_t *arr_of_colors;
struct block *arr_of_block;
long long counterFPS=0;
long long countai=0;
/////////////////////////////////////////////
