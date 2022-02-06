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
#define NUM_POTOION 12
#define NUM_WAR 100
bool saveandexit=false;
bool your_potion=false;
bool ai_potion=false;
int fps_potion[NUM_POTOION]={0};
int number_of_maps=0;
char number[50]="";
char number2[50]="";
char number3[50]="";
double Vsoldier=10;
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

//////////////////////////////////////////////
struct potion pot[NUM_POTOION];
struct warstatus wars[NUM_WAR]; //in 10000 kheili jaha 100 e dorostesh kon
int number_of_attack=0;
int number_of_block,number_of_player;
uint32_t *arr_of_colors;
struct block *arr_of_block;
long long counterFPS=0;
long long countai=0;
/////////////////////////////////////////////
int stringToNumber(char * j)
{
    int res=0;
    for(int i=0;i< strlen(j);i++)
    {
        res=res*10+((int)j[i]-48);
    }
    return res;
}
void how_many_maps()
{
    FILE* fptr;
    fptr= fopen("nummaps.txt","r");
    fscanf(fptr,"%d",&number_of_maps);
    fclose(fptr);
}
void write_number_of_maps()
{
    FILE* fptr;
    fptr= fopen("nummaps.txt","w");
    fprintf(fptr,"%d",number_of_maps);
    fclose(fptr);
}
void declareclr()
{
    clr[0] = color(0, 0, 0, 255);
    clr[1] = color(0, 255, 0, 255);
    clr[2] = color(0, 0, 255, 255);
    clr[3] = color(255, 0, 255, 255);
    clr[4] = color(255, 120, 0, 255);
    clr[5] = color(255, 255, 0, 255);
    clr[6] = color(255, 0, 0, 255);
    clr[7] = color(255, 255, 255, 255);
    clr[8] = color(0, 255, 255, 255);
    clr[9] = color(100, 100, 100, 255);
    ////
    for (int j=0;j<5;j++)
    {
        for (int i = 0; i < 9; i++)
        {
            all_block[j * 9 + i].xpos = 160 + i * 200;
            all_block[j * 9 + i].ypos = 110 + j * 200;
            all_block[j * 9 + i].index=-1;
            all_block[j * 9 + i].number_soldier=15;
            all_block[j * 9 + i].number_soldier2=15;
            all_block[j * 9 + i].nolimit=false;
            all_block[j * 9 + i].fastblock=false;
        }
    }
}
int which_block_clicked(struct block arr_of_valid_block[],int num_of_valiv_block,SDL_Event ev)
{
    if(ev.type==SDL_MOUSEBUTTONUP)
    {
        SDL_GetMouseState(&xCursor, &yCursor);
        for (int i = 0; i < num_of_valiv_block; i++)
            if( (arr_of_valid_block[i].xpos - xCursor <= 100 && -100 <= arr_of_valid_block[i].xpos - xCursor)  &&
                (arr_of_valid_block[i].ypos - yCursor <= 100 && -100 <= arr_of_valid_block[i].ypos - yCursor ))
                return i;
    }
    return -1;
}
void strrev(char *str1)
{
    // declare variable
    int i, len, temp;
    len = strlen(str1); // use strlen() to get the length of str string

    // use for loop to iterate the string
    for (i = 0; i < len/2; i++)
    {
        // temp variable use to temporary hold the string
        temp = str1[i];
        str1[i] = str1[len - i - 1];
        str1[len - i - 1] = temp;
    }
}
int number_to_string(int num)
{
    if (num==0)
    {
        temp_of_function_numberToString[0]='0';
        temp_of_function_numberToString[1]='\0';
        return 1;
    }
    int counter = 0;
    while( num > 0 )
    {
        temp_of_function_numberToString[counter]=(int)(num%10+48);
        counter++;
        num/=10;
    }
    temp_of_function_numberToString[counter]='\0';
    strrev(temp_of_function_numberToString);
    return counter;
}//return chand raghamie va string mire too temp_of_function_numberToString[10]
void soundplay(SDL_Event ev)
{
    SDL_GetMouseState(&xCursor,&yCursor);
    if(ev.type==SDL_MOUSEBUTTONDOWN && xCursor<=1828 && xCursor>=1720 &&yCursor<=138 && yCursor>=30)
    {
        sound=!sound;
    }
}
void showcursorandsound()
{
    if(sound)
    {
        SDL_Surface *img = SDL_LoadBMP("soundicon.bmp");
        if (!img)
            printf("ridi dar hitler %s", SDL_GetError());
        SDL_Rect place = {.x=1720, .y=30, .w=108, .h=108};
        SDL_Texture *texture_hitler = SDL_CreateTextureFromSurface(renderer, img);
        SDL_RenderCopy(renderer, texture_hitler, NULL, &place);
        SDL_FreeSurface(img);
        SDL_DestroyTexture(texture_hitler);
        SDL_RectEmpty(&place);
    }
    else
    {
        SDL_Surface *img = SDL_LoadBMP("muteicon.bmp");
        if (!img)
            printf("ridi dar hitler %s", SDL_GetError());
        SDL_Rect place = {.x=1720, .y=30, .w=108, .h=108};
        SDL_Texture *texture_hitler = SDL_CreateTextureFromSurface(renderer, img);
        SDL_RenderCopy(renderer, texture_hitler, NULL, &place);
        SDL_FreeSurface(img);
        SDL_DestroyTexture(texture_hitler);
        SDL_RectEmpty(&place);
    }
    SDL_GetMouseState(&xCursor,&yCursor);
    SDL_Surface *image_cursor= SDL_LoadBMP("cursor.bmp");
    if(!image_cursor)
        printf("ridi dar cursor %s",SDL_GetError());
    SDL_Rect cursor_place={.x=xCursor-50,.y=yCursor-40,.w=100,.h=80};
    SDL_Texture *texture_cursor= SDL_CreateTextureFromSurface(renderer,image_cursor);
    SDL_RenderCopy(renderer,texture_cursor,NULL,&cursor_place);
    if (!sound)
        Mix_PauseMusic();
    else
        Mix_ResumeMusic();
    SDL_RectEmpty(&cursor_place);
    SDL_FreeSurface(image_cursor);
    SDL_DestroyTexture(texture_cursor);
}
void show_text(SDL_Renderer *renderer,int x,int y,const char * text,int font_size,int R,int G,int B, int A)
{
    TTF_Init();
    SDL_Color text_color = { R, G, B, A};
    const char * font_address_01="font.ttf";
    const char * Font =NULL;
    Font = font_address_01;
    int mWidth = 0;
    int mHeight = 0;
    SDL_Rect* clip = NULL;
    TTF_Font *gFont = NULL;
    double angle = 0.0;
    SDL_Point* center = NULL;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    SDL_Texture* mTexture = NULL;
    gFont = TTF_OpenFont(Font, font_size );
    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont,text, text_color );

    mWidth = textSurface->w;
    mHeight = textSurface->h;
    mTexture = SDL_CreateTextureFromSurface( renderer, textSurface );

    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    SDL_RenderCopyEx( renderer, mTexture, clip, &renderQuad, angle, center, flip );
    SDL_FreeSurface( textSurface );
    SDL_DestroyTexture( mTexture );
    TTF_CloseFont(gFont);
}
void txtRGBA(SDL_Renderer *renderer,int x,int y,const char * text,int font_size,int R,int G,int B, int A)
{
    SDL_GetMouseState(&xCursor,&yCursor);
    roundedBoxRGBA(renderer,x-50,y-50,x+450,y+150,90,61,61,61,255);
    roundedBoxRGBA(renderer,x,y,x+400,y+100,90,78,78,78,255);
    x+=75;
    y+=20;
    TTF_Init();
    SDL_Color text_color = { R, G, B, A};
    const char * font_address_01="font.ttf";
    const char * Font =NULL;
    Font = font_address_01;
    int mWidth = 0;
    int mHeight = 0;
    SDL_Rect* clip = NULL;
    TTF_Font *gFont = NULL;
    double angle = 0.0;
    SDL_Point* center = NULL;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    SDL_Texture* mTexture = NULL;
    gFont = TTF_OpenFont(Font, font_size );

    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont,text, text_color );

    mWidth = textSurface->w;
    mHeight = textSurface->h;
    mTexture = SDL_CreateTextureFromSurface( renderer, textSurface );
    if (xCursor >= x && xCursor<=x+mWidth && yCursor>=y && yCursor<=y+mHeight)
    {
        SDL_Surface *image_hitler= SDL_LoadBMP("hitler.bmp");
        if(!image_hitler)
            printf("ridi dar hitler %s",SDL_GetError());
        SDL_Rect hitler_place={.x=900,.y=y-30,.w=320,.h=180};
        SDL_Texture *texture_hitler= SDL_CreateTextureFromSurface(renderer,image_hitler);
        SDL_RenderCopy(renderer,texture_hitler,NULL,&hitler_place);
        SDL_FreeSurface(image_hitler);
        SDL_DestroyTexture(texture_hitler);
        SDL_RectEmpty(&hitler_place);
    }
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    SDL_RenderCopyEx( renderer, mTexture, clip, &renderQuad, angle, center, flip );
    SDL_DestroyTexture( mTexture );
    SDL_FreeSurface( textSurface );
    TTF_CloseFont(gFont);
}
void check_exit_game(SDL_Event ev)
{
    const SDL_MessageBoxButtonData buttons[] = {
            { /* .flags, .buttonid, .text */        0, 0, "YES" },
            { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "NO" }
    };
    const SDL_MessageBoxColorScheme colorScheme = {
            { /* .colors (.r, .g, .b) */
                    /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
                    { 50,   50,   50 },
                    /* [SDL_MESSAGEBOX_COLOR_TEXT] */
                    {   255, 255,   255 },
                    /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
                    { 0,   0,   0 },
                    /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
                    {   0, 0, 200 },
                    /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
                    { 255,   0, 0 }
            }
    };
    const SDL_MessageBoxData messageboxdata = {
            SDL_MESSAGEBOX_INFORMATION, /* .flags */
            NULL, /* .window */
            "EXIT", /* .title */
            "Are you sure you want to exit ?", /* .message */
            SDL_arraysize(buttons), /* .numbuttons */
            buttons, /* .buttons */
            &colorScheme /* .colorScheme */
    };
    int buttonid=-1;
    if (ev.type==SDL_QUIT)
    {
        Mix_PauseMusic();
        SDL_ShowMessageBox(&messageboxdata, &buttonid);
        if(buttonid==0)
            game_is_running=false;
        else
            Mix_ResumeMusic();
    }
    else
    if (ev.type==SDL_KEYUP && ev.key.keysym.sym==SDLK_ESCAPE)
    {
        Mix_PauseMusic();
        SDL_ShowMessageBox(&messageboxdata, &buttonid);
        if(buttonid==0)
            game_is_running=false;
        else
            Mix_ResumeMusic();
    }

}
bool is_ok_to_run_game()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER |SDL_INIT_AUDIO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    if(Mix_Init(MIX_INIT_MP3) <0)
        return false;
    return true;
}
void render_blocks(int num_block,uint32_t arr[],struct block block[],SDL_Texture *block_khali,SDL_Texture *block_por)
{
    for(int i=0;i<num_block;i++)
    {
        if (block[i].index==-1)
        {
            SDL_Rect rect={.x=block[i].xpos-100, .y=block[i].ypos-100,.w=200,.h=200};
            SDL_RenderCopy(renderer,block_khali,NULL,&rect);
            if(number_to_string(block[i].number_soldier)==1)
                show_text(renderer,block[i].xpos-15,block[i].ypos+10,temp_of_function_numberToString,40,0,255,0,255);
            else if(number_to_string(block[i].number_soldier)==2)
                show_text(renderer,block[i].xpos-25,block[i].ypos+10,temp_of_function_numberToString,40,0,0,255,255);
            else if(number_to_string(block[i].number_soldier)==3)
                show_text(renderer,block[i].xpos-35,block[i].ypos+10,temp_of_function_numberToString,40,255,0,0,255);
        }
        else
        {
            SDL_Rect rect={.x=block[i].xpos-100, .y=block[i].ypos-100,.w=200,.h=200};
            filledCircleColor(renderer, block[i].xpos, block[i].ypos, 100, arr[block[i].index]);
            SDL_RenderCopy(renderer,block_por,NULL,&rect);
            if(number_to_string(block[i].number_soldier)==1)
                show_text(renderer,block[i].xpos-15,block[i].ypos+5,temp_of_function_numberToString,50,0,255,0,255);
            else if(number_to_string(block[i].number_soldier)==2)
                show_text(renderer,block[i].xpos-30,block[i].ypos+5,temp_of_function_numberToString,50,0,0,255,255);
            else if(number_to_string(block[i].number_soldier)==3)
                show_text(renderer,block[i].xpos-44,block[i].ypos+5,temp_of_function_numberToString,50,255,0,0,255);

        }
    }
}
void make_randomcolor(uint32_t arr[],int n)
{
    time_t t;
    int random_numbers[9];
    for(int i=0;i<9;i++)
        random_numbers[i]=-1;
    int count =0;
    srand((unsigned) time(&t));
    while(count <9)
    {
        int randNum =rand()%9;
        bool found =false;
        for (int i = 0; i < count; i++) {
            if(random_numbers[i] ==randNum) {
                found =true;
                break;
            }
        }
        if(!found) {
            random_numbers[count] =randNum;
            count++;
        }
    }
    for( int i = 0 ; i < n-1 ; i++ )
    {
        arr[i+1]=clr[random_numbers[i]+1];
    }
    arr[0]=clr[0];
}
bool click_new_game(SDL_Event ev)
{
    SDL_GetMouseState(&xCursor,&yCursor);
    if(ev.type==SDL_MOUSEBUTTONDOWN)
    {
        if(xCursor >= 1375 && xCursor <=1375+276 && yCursor>=270 && yCursor<=339 )
        {
            return true;
        }
    }
    return false;
}
bool click_continue(SDL_Event ev)
{
    SDL_GetMouseState(&xCursor,&yCursor);
    if(ev.type==SDL_MOUSEBUTTONDOWN)
    {
        if(xCursor >= 1375 && xCursor <=1375+276 && yCursor>=270+240 && yCursor<=339+240 )
        {
            return true;
        }
    }
    return false;
}
bool click_ranking(SDL_Event ev)
{
    SDL_GetMouseState(&xCursor,&yCursor);
    if(ev.type==SDL_MOUSEBUTTONDOWN)
    {
        if(xCursor >= 1375 && xCursor <=1375+276 && yCursor>=270+480 && yCursor<=339+480 )
        {
            return true;
        }
    }
    return false;
}
void render_soldier(struct warstatus war[],int number_of_war,SDL_Texture *texttemp[],uint32_t arr_color[],struct block blocks[])
{
    SDL_Texture *temp;
    for(int i=0;i<number_of_war;i++)
    {
        struct soldier * current = war[i].head;
        while(current->next!=NULL)
        {
            if ( arr_color[current->index] == clr[0])
                temp = texttemp[0];
            else if ( arr_color[current->index]  == clr[1])
                temp=texttemp[1];
            else if (arr_color[current->index] == clr[2])
                temp=texttemp[2];
            else if (arr_color[current->index] == clr[3])
                temp=texttemp[3];
            else if (arr_color[current->index] == clr[4])
                temp=texttemp[4];
            else if (arr_color[current->index] == clr[5])
                temp=texttemp[5];
            else if (arr_color[current->index] == clr[6])
                temp=texttemp[6];
            else if (arr_color[current->index] == clr[7])
                temp=texttemp[7];
            else if (arr_color[current->index] == clr[8])
                temp=texttemp[8];
            else if (arr_color[current->index] == clr[9])
                temp=texttemp[9];

            SDL_Rect texture_soldier={.x=current->x-25,.y=current->y-25,.w=50,.h=50};
            SDL_RenderCopy(renderer,temp,NULL,&texture_soldier);
            // filledCircleColor(renderer,current->x,current->y,15,arr_color[blocks[current->num_beg_block].index]);
            current=current->next;
        }
    }
}
char inputs_string(SDL_Event ev)
{
    char ch;
    if(ev.type==SDL_KEYUP)
    {
        ch = (char)ev.key.keysym.sym;
        return ch;
    }
}
void generate_one_soldier_end_of_list(struct soldier * head,struct block* att,struct block def,int number_of_dest_block,int number_of_beg_block)
{
    static long long temp=0;
    struct soldier * current = head;
    while(current->next!=NULL)
    {
        current=current->next;
    }
    att->number_soldier-=1;
    current->next=(struct soldier*)malloc(sizeof(struct soldier));
    if(temp%3==0) {
        current->x = att->xpos-20;
        current->y = att->ypos-20;
    }
    if(temp%3==1)
    {
        current->x = att->xpos;
        current->y = att->ypos;
    }
    if(temp%3==2)
    {
        current->x = att->xpos+20;
        current->y = att->ypos+20;
    }
    double vatar=sqrt( (def.xpos-att->xpos)*(def.xpos-att->xpos) + (def.ypos-att->ypos)*(def.ypos-att->ypos));
    current->vx=Vsoldier*(def.xpos-att->xpos)/vatar;
    current->vy=Vsoldier*(def.ypos-att->ypos)/vatar;
    current->destx=def.xpos;
    current->desty=def.ypos;
    current->index=att->index;
    current->num_dest_block=number_of_dest_block;
    current->num_beg_block=number_of_beg_block;
    current->stop=false;
    current->fast_run=false;
    current->next->next=NULL;
    temp++;
}
bool is_same_soldier(struct soldier a,struct soldier b)
{
    if(a.x==b.x && a.y==b.y && a.vx==b.vx && a.vy==b.vy)
        return true;
    else
        return false;
}
int delete_soldier(struct soldier dest_for_delete,struct soldier ** head)
{
    struct  soldier *current = (*head);
    if (is_same_soldier(*current,dest_for_delete))
    {
        (*head) = (*head)->next;
        return 1;
    }
    while(current->next!=NULL)
    {
        if (is_same_soldier(*(current->next),dest_for_delete))
        {
            current->next = current->next->next;
            return 1;
        }
        current=current->next;
    }
    return 0;//in sarbaz vojood nadasht
}
void moving_soldiers(struct warstatus war[],struct block arr_block[])
{
    for(int i=0;i<NUM_WAR;i++)
    {
        struct soldier * current= war[i].head;
        while(current->next!=NULL)
        {
            if(current->stop == true)
            {
            }
            else if(current->fast_run == true)
            {
                current->x += 3*current->vx;
                current->y += 3*current->vy;
            }
            else
            {
                current->x += current->vx;
                current->y += current->vy;
            }

            if( current->x  - current->destx <70
                &&  -70 < current->x  - current->destx
                &&  current->y  - current->desty <70
                &&    -70 < current->y  - current->desty
                    )
            {
                if (current->index == arr_block[current->num_dest_block].index )
                {
                    arr_block[current->num_dest_block].number_soldier += 1;
                    arr_block[current->num_dest_block].number_soldier2 += 1;
                }
                else
                {
                    if (arr_block[current->num_dest_block].number_soldier == 0 )
                    {
                        arr_block[current->num_dest_block].index=current->index;
                        arr_block[current->num_dest_block].number_soldier = 1;
                        arr_block[current->num_dest_block].number_soldier2 = 1;
                        for(int j=0;j<NUM_WAR;j++)
                            if(war[j].att==current->num_dest_block)
                                war[j].num_soldier=0;
                    }
                    else
                    {
                        arr_block[current->num_dest_block].number_soldier -= 1;
                        arr_block[current->num_dest_block].number_soldier2 -= 1;
                    }
                }
                delete_soldier(*current,&war[i].head);
            }
            for(int j=i+1;j<NUM_WAR;j++)
            {
                struct soldier * cur2= war[j].head;
                while(cur2->next!=NULL)
                {
                    if (sqrt((current->x - cur2->x)*(current->x - cur2->x) + (current->y - cur2->y)*(current->y - cur2->y)) < 50)
                    {
                        if(current->index != cur2->index)
                        {
                            delete_soldier(*current, &war[i].head);
                            delete_soldier(*cur2, &war[j].head);
                        }
                    }
                    cur2=cur2->next;
                }
            }
            current=current->next;
        }
    }
}
void generate_all_wars_soldiers(struct warstatus war[],int number_of_wars,struct block arr_of_blocks[])
{
    for(int i=0;i<number_of_wars;i++)
    {
        if( arr_of_blocks[war[i].att].number_soldier == 0)
        {
            war[i].num_soldier=0;
        }
        if (war[i].counter < war[i].num_soldier)
        {
            generate_one_soldier_end_of_list(war[i].head,&arr_of_blocks[war[i].att],arr_of_blocks[war[i].def],war[i].def,war[i].att);
            war[i].counter+=1;
        }
    }
}
struct axis generate_random_potion(struct block arr_block[],int num_block)
{
    time_t t;
    srand((unsigned) time(&t));
    int a=rand() % num_block;
    int b=rand() % num_block;
    while(b==a)
        b=rand() % num_block;
    ////
    double num;
    int k=rand()%100;
    num=k/(double)100;
    double num2=1-num;
    ///
    struct axis temp;
    int x;
    int y;

    //
     x= (arr_block[a].xpos*num +arr_block[b].xpos*num2);
     y= (arr_block[a].ypos*num +arr_block[b].ypos*num2);
    //
    temp.x=x;
    temp.y=y;
    return temp;
}
void render_potion(struct potion all[],SDL_Texture *arrdeactive[4],SDL_Texture *arractive[4])
{
    for(int i=0;i<NUM_POTOION;i++)
    {
        if(all[i].exist==true && all[i].runnig==false)
        {
            SDL_Rect temp={.x=all[i].x-60,.y=all[i].y-60,.h=120,.w=120};
            SDL_RenderCopy(renderer,arrdeactive[i%4],NULL,&temp);
        }
        if(all[i].exist==true && all[i].runnig==true)
        {
            SDL_Rect temp={.x=all[i].x-60,.y=all[i].y-60,.h=120,.w=120};
            SDL_RenderCopy(renderer,arractive[i%4],NULL,&temp);
        }
    }
}
void check_to_active_potion(struct potion all[],struct  warstatus war[])
{
    for(int i=0;i<NUM_POTOION;i++)
    {
        if(all[i].exist==true && all[i].runnig==false)
        {
            for (int j = 0; j < NUM_WAR; j++)
            {
                struct soldier *current = war[j].head;
                while (current->next != NULL)
                {
                    double R = sqrt((current->x - all[i].x) * (current->x - all[i].x) +
                                    (current->y - all[i].y) * (current->y - all[i].y));
                    if (R <= 85)
                    {
                        all[i].runnig = true;
                        all[i].index = current->index;
                        fps_potion[i]=0;
                        if(current->index==0)
                            your_potion=true;
                        else
                            ai_potion=true;
                        break;
                    }
                    current = current->next;
                }
            }
        }
    }
}
void run_potion(struct potion potions[],struct warstatus wars[],struct block arr_block[],int numBlock)
{
    for(int i=0;i<NUM_POTOION;i++)
    {
        if(potions[i].runnig == true && potions[i].exist==true)
        {
            switch (i%4)
            {
                case 0:
                    for (int j = 0; j < NUM_WAR; j++)
                    {
                        struct soldier *current = wars[j].head;
                        while (current->next != NULL)
                        {
                            if(current->index==potions[i].index)
                                current->fast_run=true;
                            current=current->next;
                        }
                    }
                    break;
                case 1:
                    for (int j = 0; j < NUM_WAR; j++)
                    {
                        struct soldier *current = wars[j].head;
                        while (current->next != NULL)
                        {
                            if(current->index != potions[i].index)
                                current->stop=true;
                            current=current->next;
                        }
                    }
                    break;
                case 2:
                    for (int j = 0; j < numBlock; j++)
                    {
                        if(arr_block[j].index == potions[i].index)
                            arr_block[j].nolimit=true;
                    }
                    break;
                case 3:
                    for (int j = 0; j < numBlock; j++)
                    {
                        if(arr_block[j].index == potions[i].index)
                            arr_block[j].fastblock=true;
                    }
                    break;

            }
        }
    }
}
void deactive_potion(struct potion potions,int i,struct warstatus wars[],struct block arr_block[],int numBlock)
{
    if(potions.runnig==true && potions.exist==true)
    {
        switch (i % 4)
        {
            case 0:
                for (int j = 0; j < NUM_WAR; j++) {
                    struct soldier *current = wars[j].head;
                    while (current->next != NULL) {
                        if (current->index == potions.index)
                            current->fast_run = false;
                        current = current->next;
                    }
                }
                break;
            case 1:
                for (int j = 0; j < NUM_WAR; j++) {
                    struct soldier *current = wars[j].head;
                    while (current->next != NULL) {
                        if (current->index != potions.index)
                            current->stop = false;
                        current = current->next;
                    }
                }
                break;
            case 2:
                for (int j = 0; j < numBlock; j++) {
                    if (arr_block[j].index == potions.index)
                        arr_block[j].nolimit = false;
                }
                break;
            case 3:
                for (int j = 0; j < numBlock; j++) {
                    if (arr_block[j].index == potions.index)
                        arr_block[j].fastblock = false;
                }
                break;
        }
    }
}
void make_game_easy(struct block arr[])
{
 for(int i=0;i<number_of_block;i++)
     if(arr[i].index==-1)
     {
         arr[i].index=0;
         break;
     }
 for(int i=0;i<number_of_block;i++)
        if(arr[i].index==0)
        {
            arr[i].number_soldier=30;
            arr[i].number_soldier2=30;
        }

}
struct axis AI1(struct block arr[],int numblock)
{
    struct axis temp;
    time_t t;
    double R;
    double Rmin=5000;
    bool found=false;
    int random_numbers[numblock];
    {
        for (int i = 0; i < numblock; i++)
            random_numbers[i] = -1;
        int count = 0;
        srand((unsigned) time(&t));
        while (count < numblock) {
            int randNum = rand() % numblock;
            bool found = false;
            for (int i = 0; i < count; i++) {
                if (random_numbers[i] == randNum) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                random_numbers[count] = randNum;
                count++;
            }
        }
    }
    for(int i = 0 ;i<numblock;i++)
    {
        if( arr[random_numbers[i]].index != 0 && arr[random_numbers[i]].index !=-1)
        {
            for (int j = 0; j < numblock; j++)
            {
                if (arr[random_numbers[i]].number_soldier2 > arr[random_numbers[j]].number_soldier2 + 1 &&
                    arr[random_numbers[i]].index!=arr[random_numbers[j]].index)
                {
                    //printf("n %d %d\n",random_numbers[i],random_numbers[j]);
                    R=sqrt(( (arr[random_numbers[i]].xpos-arr[random_numbers[j]].xpos)
                             *(arr[random_numbers[i]].xpos-arr[random_numbers[j]].xpos)) +
                           ((arr[random_numbers[i]].ypos-arr[random_numbers[j]].ypos) *
                            (arr[random_numbers[i]].ypos-arr[random_numbers[j]].ypos)));
                    if (R < Rmin)
                    {
                        temp.x=random_numbers[i];
                        temp.y=random_numbers[j];
                        Rmin=R;
                        found=true;
                    }
                }
            }
            if(found)
                return temp;
        }
    }
    struct axis p;
    p.x=-1;
    p.y=-1;
    return p;
} //nazdik tarini ke ghabel hamle ast
struct axis AI2(struct block arr[],int numblock)
{
    struct axis temp;
    time_t t;
    int soldier;
    double smin=1000;
    bool found=false;
    int random_numbers[numblock];{
        for (int i = 0; i < numblock; i++)
            random_numbers[i] = -1;
        int count = 0;
        srand((unsigned) time(&t));
        while (count < numblock) {
            int randNum = rand() % numblock;
            bool found = false;
            for (int i = 0; i < count; i++) {
                if (random_numbers[i] == randNum) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                random_numbers[count] = randNum;
                count++;
            }
        }
    }
    for(int i = 0 ;i<numblock;i++)
    {
        if( arr[random_numbers[i]].index != 0 && arr[random_numbers[i]].index !=-1)
        {
            for (int j = 0; j < numblock; j++)
            {
                if (arr[random_numbers[i]].number_soldier2 > arr[random_numbers[j]].number_soldier2 + 1)
                {
                    soldier=arr[random_numbers[j]].number_soldier2;
                    if (soldier < smin)
                    {
                        temp.x=random_numbers[i];
                        temp.y=random_numbers[j];
                        smin=soldier;
                        found=true;
                    }
                }
            }
            if(found)
                return temp;
        }
    }
    struct axis p;
    p.x=-1;
    p.y=-1;
    return p;
} // be oon badbakhti ke kamtarin sarbazo dare hamle mikone
struct axis AI3(struct block arr[],int numblock)
{
    struct axis temp;
    time_t t;
    int soldier;
    double smin=1000;
    bool found=false;
    int random_numbers[numblock];{
        for (int i = 0; i < numblock; i++)
            random_numbers[i] = -1;
        int count = 0;
        srand((unsigned) time(&t));
        while (count < numblock) {
            int randNum = rand() % numblock;
            bool found = false;
            for (int i = 0; i < count; i++) {
                if (random_numbers[i] == randNum) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                random_numbers[count] = randNum;
                count++;
            }
        }
    }
    for(int i = 0 ;i<numblock;i++)
    {
        if( arr[random_numbers[i]].index != 0 && arr[random_numbers[i]].index !=-1)
        {
            for (int j = 0; j < numblock; j++)
            {
                if (arr[random_numbers[i]].number_soldier2 > arr[random_numbers[j]].number_soldier2 + 1
                    && arr[random_numbers[j]].index==0 )
                {
                    soldier=arr[random_numbers[j]].number_soldier2;
                    if (soldier < smin)
                    {
                        temp.x=random_numbers[i];
                        temp.y=random_numbers[j];
                        smin=soldier;
                        found=true;
                    }
                }
            }
            if(found)
                return temp;
        }
    }
    struct axis p;
    p.x=-1;
    p.y=-1;
    return p;
} //ta hamle koni jaei miad zaneto pare mikone
struct axis AI4(struct block arr[],int numblock)
{
    struct axis temp;
    time_t t;
    int soldier;
    int random_numbers[numblock];{
        for (int i = 0; i < numblock; i++)
            random_numbers[i] = -1;
        int count = 0;
        srand((unsigned) time(&t));
        while (count < numblock) {
            int randNum = rand() % numblock;
            bool found = false;
            for (int i = 0; i < count; i++) {
                if (random_numbers[i] == randNum) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                random_numbers[count] = randNum;
                count++;
            }
        }
    }
    for(int i = 0 ;i<numblock;i++)
    {
        if( arr[random_numbers[i]].index != 0 && arr[random_numbers[i]].index !=-1)
        {
            for (int j = 0; j < numblock; j++)
            {
                if (arr[random_numbers[i]].number_soldier > arr[random_numbers[j]].number_soldier2 + 1)
                {
                        temp.x=random_numbers[i];
                        temp.y=random_numbers[j];
                        return temp;
                }
            }
        }
    }
    struct axis p;
    p.x=-1;
    p.y=-1;
    return p;
}//2 ta khoone random ro hamle mide
bool win(struct block arr[],int numblock)
{
    bool youwin=true;
    for(int i=0;i<numblock;i++)
    {
        if(arr[i].index!=0 && arr[i].index!=-1)
            youwin=false;
    }
    return youwin;
}
bool lose(struct block arr[],int numblock)
{
    bool youlose=true;
    for(int i=0;i<numblock;i++)
    {
        if(arr[i].index == 0 )
            youlose=false;
    }
    return youlose;
}
bool LEADERBOARDback(SDL_Event ev)
{
    SDL_GetMouseState(&xCursor,&yCursor);
    if(ev.type==SDL_MOUSEBUTTONDOWN && xCursor<=1828 && xCursor>=1720 &&yCursor<=138 && yCursor>=30)
    {
        return true;
    } else
        return false;
}
void write_win_to_file()
{
    FILE *fptr2;
    if ( (fptr2 = fopen("names2.txt","w")) == NULL)
    {
        printf("Error! opening file");
        return ;
    }
    FILE *fptr;
    if ( (fptr = fopen("names.txt","r")) == NULL)
    {
        printf("Error! opening file");
        return ;
    }
    char tempname[200];
    char c;
    int win=0;
    int lose=0;
    while(fscanf(fptr,"%c",&c)==1)
    {
        if(c=='\n')
            continue;
        int counter=0;
        while(c != '\n')
        {
            tempname[counter]=c;
            counter++;
            fscanf(fptr,"%c",&c);
        }
        tempname[counter]='\0';
        fscanf(fptr," %d %d",&win,&lose);
        fscanf(fptr,"%c",&c); /// for enter

        if(!strcmp(tempname,name))
        {
            fprintf(fptr2,"%s\n",tempname);
            fprintf(fptr2,"%d %d\n",win+1,lose);
        }
        else
        {
            fprintf(fptr2, "%s\n", tempname);
            fprintf(fptr2, "%d %d\n", win, lose);
        }
    }
    remove("names.txt");
    rename("names2.txt","names.txt");
    fclose(fptr);
    fclose(fptr2);
    return ;
}
void write_lose_to_file()
{
    FILE *fptr2;
    if ( (fptr2 = fopen("names2.txt","w")) == NULL)
    {
        printf("Error! opening file");
        return ;
    }
    FILE *fptr;
    if ( (fptr = fopen("names.txt","r")) == NULL)
    {
        printf("Error! opening file");
        return ;
    }
    char tempname[200];
    char c;
    int win=0;
    int lose=0;
    while(fscanf(fptr,"%c",&c)==1)
    {
        if(c=='\n')
            continue;
        int counter=0;
        while(c != '\n')
        {
            tempname[counter]=c;
            counter++;
            fscanf(fptr,"%c",&c);
        }
        tempname[counter]='\0';
        fscanf(fptr," %d %d",&win,&lose);
        fscanf(fptr,"%c",&c); /// for enter

        if(!strcmp(tempname,name))
        {
            fprintf(fptr2,"%s\n",tempname);
            fprintf(fptr2,"%d %d\n",win,lose+1);
        }
        else
        {
            fprintf(fptr2, "%s\n", tempname);
            fprintf(fptr2, "%d %d\n", win, lose);
        }
    }
    remove("names.txt");
    rename("names2.txt","names.txt");
    fclose(fptr);
    fclose(fptr2);
    return ;
}
void write_name_to_file()
{
    FILE *fptr2;
    if ( (fptr2 = fopen("names2.txt","w")) == NULL)
    {
        printf("Error! opening file");
        return ;
    }
    FILE *fptr;
    if ( (fptr = fopen("names.txt","r")) == NULL)
    {
        printf("Error! opening file");
        return ;
    }
    char tempname[200];
    char c;
    int win=0;
    int lose=0;
    while(fscanf(fptr,"%c",&c)==1)
    {
        if(c=='\n')
            continue;
        int counter=0;
        while(c != '\n')
        {
            tempname[counter]=c;
            counter++;
            fscanf(fptr,"%c",&c);
        }
        tempname[counter]='\0';
        fscanf(fptr," %d %d",&win,&lose);
        fscanf(fptr,"%c",&c); /// for enter

        if(!strcmp(tempname,name))
        {
            new_user = false;
        }
        fprintf(fptr2,"%s\n",tempname);
        fprintf(fptr2,"%d %d\n",win,lose);
    }
    if(new_user)
    {
        fprintf(fptr2,"%s\n",name);
        fprintf(fptr2,"%d %d\n",0,0);
    }
    remove("names.txt");
    rename("names2.txt","names.txt");
    fclose(fptr);
    fclose(fptr2);
    return ;
}
void write_loseAI_to_file(int i)
{
    FILE *fptr2;
    if ( (fptr2 = fopen("names2.txt","w")) == NULL)
    {
        printf("Error! opening file");
        return ;
    }
    FILE *fptr;
    if ( (fptr = fopen("names.txt","r")) == NULL)
    {
        printf("Error! opening file");
        return ;
    }
    char tempname[200];
    char c;
    int win=0;
    int lose=0;
    while(fscanf(fptr,"%c",&c)==1)
    {
        if(c=='\n')
            continue;
        int counter=0;
        while(c != '\n')
        {
            tempname[counter]=c;
            counter++;
            fscanf(fptr,"%c",&c);
        }
        tempname[counter]='\0';
        fscanf(fptr," %d %d",&win,&lose);
        fscanf(fptr,"%c",&c); /// for enter

        if(!strcmp(tempname,AIname[i]))
        {
            fprintf(fptr2,"%s\n",tempname);
            fprintf(fptr2,"%d %d\n",win,lose+1);
        }
        else
        {
            fprintf(fptr2, "%s\n", tempname);
            fprintf(fptr2, "%d %d\n", win, lose);
        }
    }
    remove("names.txt");
    rename("names2.txt","names.txt");
    fclose(fptr);
    fclose(fptr2);
    return ;
}
void write_winAI_to_file(int i)
{
    FILE *fptr2;
    if ( (fptr2 = fopen("names2.txt","w")) == NULL)
    {
        printf("Error! opening file");
        return ;
    }
    FILE *fptr;
    if ( (fptr = fopen("names.txt","r")) == NULL)
    {
        printf("Error! opening file");
        return ;
    }
    char tempname[200];
    char c;
    int win=0;
    int lose=0;
    while(fscanf(fptr,"%c",&c)==1)
    {
        if(c=='\n')
            continue;
        int counter=0;
        while(c != '\n')
        {
            tempname[counter]=c;
            counter++;
            fscanf(fptr,"%c",&c);
        }
        tempname[counter]='\0';
        fscanf(fptr," %d %d",&win,&lose);
        fscanf(fptr,"%c",&c); /// for enter

        if(!strcmp(tempname,AIname[i]))
        {
            fprintf(fptr2,"%s\n",tempname);
            fprintf(fptr2,"%d %d\n",win+1,lose);
        }
        else
        {
            fprintf(fptr2, "%s\n", tempname);
            fprintf(fptr2, "%d %d\n", win, lose);
        }
    }
    remove("names.txt");
    rename("names2.txt","names.txt");
    fclose(fptr);
    fclose(fptr2);
    return ;
}
void delete_leaderboard_data()
{
    remove("names.txt");
    FILE *fptr;
    fptr= fopen("names.txt","w");
    fprintf(fptr,"AI one\n0 0\n");
    fprintf(fptr,"AI two\n0 0\n");
    fprintf(fptr,"AI three\n0 0\n");
    fprintf(fptr,"%s\n0 0\n",name);
    fclose(fptr);
}
void showcursorandsoundLEADERBOARD()
{
    SDL_Surface *img = SDL_LoadBMP("back.bmp");
    if (!img)
        printf("ridi dar back %s", SDL_GetError());
    SDL_Rect place = {.x=1720, .y=30, .w=108, .h=108};
    SDL_Texture *texture_hitler = SDL_CreateTextureFromSurface(renderer, img);
    SDL_RenderCopy(renderer, texture_hitler, NULL, &place);
    SDL_FreeSurface(img);
    SDL_DestroyTexture(texture_hitler);

    SDL_GetMouseState(&xCursor,&yCursor);
    SDL_Surface *image_cursor= SDL_LoadBMP("cursor.bmp");
    if(!image_cursor)
        printf("ridi dar cursor %s",SDL_GetError());
    SDL_Rect cursor_place={.x=xCursor-50,.y=yCursor-40,.w=100,.h=80};
    SDL_Texture *texture_cursor= SDL_CreateTextureFromSurface(renderer,image_cursor);
    SDL_RenderCopy(renderer,texture_cursor,NULL,&cursor_place);
    if (!sound)
        Mix_PauseMusic();
    else
        Mix_ResumeMusic();
    SDL_FreeSurface(image_cursor);
    SDL_DestroyTexture(texture_cursor);
}
bool check_delete_leaderboard(SDL_Event ev)
{
    SDL_GetMouseState(&xCursor,&yCursor);
    if(xCursor >= 1720 && xCursor<=1830 &&yCursor>=150 && yCursor<=260 && ev.type==SDL_MOUSEBUTTONUP)
    {
        const SDL_MessageBoxButtonData buttons[] = {
                { /* .flags, .buttonid, .text */        0, 0, "YES" },
                { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "NO" }
        };
        const SDL_MessageBoxColorScheme colorScheme = {
                { /* .colors (.r, .g, .b) */
                        /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
                        { 50,   50,   50 },
                        /* [SDL_MESSAGEBOX_COLOR_TEXT] */
                        {   255, 255,   255 },
                        /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
                        { 0,   0,   0 },
                        /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
                        {   0, 0, 200 },
                        /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
                        { 255,   0, 0 }
                }
        };
        const SDL_MessageBoxData messageboxdata = {
                SDL_MESSAGEBOX_INFORMATION, /* .flags */
                NULL, /* .window */
                "DELETE", /* .title */
                "Are you sure you want to delete leaderboard fata ?", /* .message */
                SDL_arraysize(buttons), /* .numbuttons */
                buttons, /* .buttons */
                &colorScheme /* .colorScheme */
        };
        int buttonid=-1;
        SDL_ShowMessageBox(&messageboxdata, &buttonid);
        if(buttonid==0)
        {
            delete_leaderboard_data();
            return true;
        }
    }
    return false;
}
void show_delete_leaderborad()
{
    SDL_Surface *img = IMG_Load("delicon.png");
    if (!img)
        printf("ridi  %s\n", SDL_GetError());
    SDL_Rect place = {.x=1720, .y=150, .w=110, .h=110};
    SDL_Texture *texture_hitler = SDL_CreateTextureFromSurface(renderer, img);
    SDL_RenderCopy(renderer, texture_hitler, NULL, &place);
    SDL_FreeSurface(img);
    SDL_DestroyTexture(texture_hitler);
}
void boxleaderboard(SDL_Renderer * renderer,int x,int y,struct line khat,int R,int G,int B, int A)
{
    roundedBoxRGBA(renderer,x,y,x+1600,y+100,80,80,80,80,255);
    x+=75;
    y+=20;
    show_text(renderer,x+10,y-20,khat.place,70,255,0,0,255);
    show_text(renderer,x+350,y,khat.name,50,255,255,255,255);
    show_text(renderer,x+800,y,khat.win,50,0,255,0,255);
    show_text(renderer,x+1050,y,khat.lose,50,0,0,255,255);
    show_text(renderer,x+1300,y,khat.point,50,0,0,255,255);

}
void numberTOstring(int num,char ch[])
{
    if (num==0)
    {
        ch[0]='0';
        ch[1]='\0';
        return ;
    }
    if(num>0) {
        int counter = 0;
        while (num > 0) {
            ch[counter] = (int) (num % 10 + 48);
            counter++;
            num /= 10;
        }
        ch[counter] = '\0';
        strrev(ch);
        return;
    }
    if(num<0)
    {
        num*=-1;
        int counter = 0;
        while (num > 0) {
            ch[counter] = (int) (num % 10 + 48);
            counter++;
            num /= 10;
        }
        ch[counter]='-';
        ch[counter+1] = '\0';
        strrev(ch);
        return;
    }
}
void show_save()
{
    SDL_Surface *img = SDL_LoadBMP("save.bmp");
    if (!img)
        printf("ridi dar save %s", SDL_GetError());
    SDL_Rect place = {.x=30, .y=30, .w=128, .h=128};
    SDL_Texture *texture_hitler = SDL_CreateTextureFromSurface(renderer, img);
    SDL_RenderCopy(renderer, texture_hitler, NULL, &place);
    SDL_FreeSurface(img);
    SDL_DestroyTexture(texture_hitler);
}
void save(SDL_Event ev)
{
    SDL_GetMouseState(&xCursor,&yCursor);
    if(ev.type==SDL_MOUSEBUTTONUP && xCursor>30 && xCursor<158 && yCursor>30 && yCursor < 158)
    {
    const SDL_MessageBoxButtonData buttons[] ={
            { /* .flags, .buttonid, .text */        0, 0, "YES" },
            { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "NO" }
    };
    const SDL_MessageBoxColorScheme colorScheme = {
            { /* .colors (.r, .g, .b) */
                    /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
                    { 50,   50,   50 },
                    /* [SDL_MESSAGEBOX_COLOR_TEXT] */
                    {   255, 255,   255 },
                    /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
                    { 0,   0,   0 },
                    /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
                    {   0, 0, 200 },
                    /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
                    { 255,   0, 0 }
            }
    };
    const SDL_MessageBoxData messageboxdata = {
            SDL_MESSAGEBOX_INFORMATION, /* .flags */
            NULL, /* .window */
            "SAVE", /* .title */
            "Are you sure you want to save the game ?", /* .message */
            SDL_arraysize(buttons), /* .numbuttons */
            buttons, /* .buttons */
            &colorScheme /* .colorScheme */
    };
    int buttonid=-1;
    SDL_ShowMessageBox(&messageboxdata, &buttonid);
        if (buttonid == 0)
        {
            saveandexit=true;
            return ;
        }
    }

}
bool is_on_hint()
{
    SDL_Surface *img = SDL_LoadBMP("hint_icon.bmp");
    if (!img)
        printf("ridi  %s", SDL_GetError());
    SDL_Rect place = {.x=30, .y=100, .w=108, .h=135};
    SDL_Texture *texture_hitler = SDL_CreateTextureFromSurface(renderer, img);
    SDL_RenderCopy(renderer, texture_hitler, NULL, &place);
    SDL_FreeSurface(img);
    SDL_DestroyTexture(texture_hitler);
    SDL_GetMouseState(&xCursor,&yCursor);
    if(xCursor >= 30 && xCursor<=138 &&yCursor>=100 && yCursor<=235)
    {
        SDL_Surface *img = SDL_LoadBMP("hint.bmp");
        if (!img)
            printf("ridi  %s", SDL_GetError());
        SDL_Rect place = {.x=-150, .y=130, .w=960*1.5, .h=540*1.5};
        SDL_Texture *texture_hitler = SDL_CreateTextureFromSurface(renderer, img);
        SDL_RenderCopy(renderer, texture_hitler, NULL, &place);
        SDL_FreeSurface(img);
        SDL_DestroyTexture(texture_hitler);
    }
}
bool leaderboard()
{
    SDL_Surface* iimage = SDL_LoadBMP("leaderboard.bmp");
    if (!iimage)
        printf("ridi %s", SDL_GetError());
    SDL_Texture *ttexture = SDL_CreateTextureFromSurface(renderer, iimage);

    int scroll=100;
    struct person all[500];
    int number_player=0;
    char temp[5];
    {
        FILE *fptr;
        if ( (fptr = fopen("names.txt","r")) == NULL)
        {
            printf("Error! opening file");
        }
        char tempname[200];
        char c;
        int win=0;
        int lose=0;

        while(fscanf(fptr,"%c",&c)==1)
        {
            if(c=='\n')
                continue;
            int counter=0;
            while(c != '\n')
            {
                tempname[counter]=c;
                counter++;
                fscanf(fptr,"%c",&c);
            }
            tempname[counter]='\0';
            fscanf(fptr," %d %d",&win,&lose);
            fscanf(fptr,"%c",&c); /// for enter


            strcpy(all[number_player].name,tempname);
            all[number_player].win=win;
            all[number_player].lose=lose;

            number_player++;
        }

        fclose(fptr);
    }  // read file
    {
        for(int i=0;i<number_player;i++)
        {
            for(int j=i+1;j<number_player;j++)
            {
                if( (all[i].win*3-all[i].lose < all[j].win*3-all[j].lose)  ||
                        (all[i].win*3-all[i].lose == all[j].win*3-all[j].lose) && all[i].win<all[j].win)
                {
                    struct person temp=all[i];
                    all[i]=all[j];
                    all[j]=temp;
                }
            }
        }
    }  // sort
    struct line lines[number_player];
    {
        for(int i=0;i<number_player;i++)
        {
            numberTOstring(all[i].win,lines[i].win);
            numberTOstring(all[i].lose,lines[i].lose);
            strcpy(lines[i].name,all[i].name);
            numberTOstring(i+1,lines[i].place);
            numberTOstring(3*all[i].win-all[i].lose,lines[i].point);
        }
    }  // line ha amade shodand va hamegik string hasstand
    struct line first;
    strcpy(first.place,"PLACE");
    strcpy(first.name,"NAME");
    strcpy(first.win,"WINS");
    strcpy(first.lose,"LOSES");
    strcpy(first.point,"POINT");
    while (game_is_running)
    {
        SDL_RenderCopy(renderer, ttexture, NULL, &texture_rect);
        boxleaderboard(renderer,50,scroll,first,255,0,0,255);
        for(int i=0;i<number_player;i++)
        {
            boxleaderboard(renderer,50,scroll+(i+1)*200,lines[i],255,0,0,255);
        }
        while(SDL_PollEvent(&event))
        {
            if(LEADERBOARDback(event))
            {
                SDL_DestroyTexture(ttexture);
                SDL_FreeSurface(iimage);
                return true;
            }
            if(check_delete_leaderboard(event))
            {
                sound=!sound;
                SDL_DestroyTexture(ttexture);
                SDL_FreeSurface(iimage);
                return true;
            }
            check_exit_game(event);
            if(event.type == SDL_MOUSEWHEEL)
            {
                if(event.wheel.y<0 && scroll <100)
                {
                    scroll+=20;
                }
                if(event.wheel.y>0)
                {
                    scroll-=20;
                }
            }
        }
        SDL_ShowCursor(SDL_DISABLE);
        show_delete_leaderborad();
        showcursorandsoundLEADERBOARD();
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / FPS);
        SDL_RenderClear(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    Mix_FreeMusic(music);
    window = NULL;
    renderer = NULL;
    texture=NULL;
    image=NULL;
    music=NULL;
    return false ;
}
void delete_work(SDL_Event ev)
{
    SDL_GetMouseState(&xCursor,&yCursor);
    if(xCursor >= 10 && xCursor<=300 &&yCursor>=750 && yCursor<=950 && ev.type==SDL_MOUSEBUTTONUP)
    {
        const SDL_MessageBoxButtonData buttons[] = {
                { /* .flags, .buttonid, .text */        0, 0, "YES" },
                { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "NO" }
        };
        const SDL_MessageBoxColorScheme colorScheme = {
                { /* .colors (.r, .g, .b) */
                        /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
                        { 50,   50,   50 },
                        /* [SDL_MESSAGEBOX_COLOR_TEXT] */
                        {   255, 255,   255 },
                        /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
                        { 0,   0,   0 },
                        /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
                        {   0, 0, 200 },
                        /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
                        { 255,   0, 0 }
                }
        };
        const SDL_MessageBoxData messageboxdata = {
                SDL_MESSAGEBOX_INFORMATION, /* .flags */
                NULL, /* .window */
                "DELETE", /* .title */
                "Are you sure you want to delete saved game ?", /* .message */
                SDL_arraysize(buttons), /* .numbuttons */
                buttons, /* .buttons */
                &colorScheme /* .colorScheme */
        };
        int buttonid=-1;
        SDL_ShowMessageBox(&messageboxdata, &buttonid);
        if(buttonid==0)
        {
            remove("saved.txt");
            remove("arr_colors.txt");
        }   ///delete game
    }
}
void render_delet()
{
    SDL_Surface *img = SDL_LoadBMP("delete.bmp");
    if (!img)
        printf("ridi  %s", SDL_GetError());
    SDL_Rect place = {.x=10, .y=750, .w=200, .h=200};
    SDL_Texture *texture_hitler = SDL_CreateTextureFromSurface(renderer, img);
    SDL_RenderCopy(renderer, texture_hitler, NULL, &place);
    SDL_FreeSurface(img);
    SDL_DestroyTexture(texture_hitler);
}
void delete_last_map_save()
{

    const SDL_MessageBoxButtonData buttons[] = {
            { /* .flags, .buttonid, .text */        0, 0, "YES" },
            { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "NO" }
    };
    const SDL_MessageBoxColorScheme colorScheme = {
            { /* .colors (.r, .g, .b) */
                    /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
                    { 50,   50,   50 },
                    /* [SDL_MESSAGEBOX_COLOR_TEXT] */
                    {   255, 255,   255 },
                    /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
                    { 0,   0,   0 },
                    /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
                    {   0, 0, 200 },
                    /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
                    { 255,   0, 0 }
            }
    };
    const SDL_MessageBoxData messageboxdata = {
            SDL_MESSAGEBOX_INFORMATION, /* .flags */
            NULL, /* .window */
            "saving", /* .title */
            "Do you want to save this map ?", /* .message */
            SDL_arraysize(buttons), /* .numbuttons */
            buttons, /* .buttons */
            &colorScheme /* .colorScheme */
    };
    int buttonid=-1;
    Mix_PauseMusic();
    SDL_ShowMessageBox(&messageboxdata, &buttonid);
    if(buttonid==1)
        {
            how_many_maps();
            char ch[5];
            numberTOstring(number_of_maps-1,ch);
            char temp1[20]="arr_colors";
            char temp2[20]="saved";
            strcat(temp1,ch);
            strcat(temp1,".txt");
            strcat(temp2,ch);
            strcat(temp2,".txt");
            remove(temp1);
            remove(temp2);
            number_of_maps--;
            write_number_of_maps();
        }
        else
            Mix_ResumeMusic();

}
bool map(int which)
{
    int blockclicked1=-1;
    int blockclicked2=-1;
    if (which==-1)
    {
       // scanf("%d %d",&number_of_block,&number_of_player);
        arr_of_block=(struct block *)malloc(number_of_block*sizeof (struct block));
        arr_of_colors=(uint32_t *)malloc(number_of_player*sizeof (uint32_t));
        make_randomcolor(arr_of_colors,number_of_player);
        {
            time_t t;
            int random_numbers[number_of_block];
            for(int i=0;i<number_of_block;i++)
                random_numbers[i]=-1;
            int count =0;
            srand((unsigned) time(&t));
            while(count <number_of_block) {
                int randNum =rand()%45;
                if (randNum==8 || randNum==0)
                    continue;
                bool found =false;
                for (int i = 0; i < count; i++) {
                    if(random_numbers[i] ==randNum) {
                        found =true;
                        break;
                    }
                }
                if(!found) {
                    random_numbers[count] =randNum;
                    count++;
                }
            }

            for(int i=0;i<number_of_block;i++) {
                arr_of_block[i] = all_block[random_numbers[i]];
                if (i < number_of_player)
                    arr_of_block[i].index=i;
            }
//            printf("%d ",random_numbers[i]);
            make_game_easy(arr_of_block);

        }  //inja miad arr_of_block ro random tarif mikone az all block


        how_many_maps();

        char endname[10];
        numberTOstring(number_of_maps,endname);
        char mamad[50]="arr_colors";
        strcat(mamad,endname);
        strcat(mamad,".txt");
                /////
            FILE * fptr;

            fptr= fopen(mamad,"w");
            fprintf(fptr,"%d\n",number_of_player);
            for(int i=1;i<number_of_player;i++)
                for(int j=0;j<10;j++)
                    if(arr_of_colors[i]==clr[j])
                        fprintf(fptr,"%d ",j);

            strcpy(mamad,"saved");
            strcat(mamad,endname);
            strcat(mamad,".txt");

            fclose(fptr);

            fptr=fopen(mamad,"w");
            fprintf(fptr,"%d\n",number_of_block);
            for(int i=0;i<number_of_block;i++)
            {
                fprintf(fptr,"%d ",arr_of_block[i].index);
                fprintf(fptr,"%d ",arr_of_block[i].xpos);
                fprintf(fptr,"%d ",arr_of_block[i].ypos);
                fprintf(fptr,"%d ",arr_of_block[i].number_soldier);
                fprintf(fptr,"%d ",arr_of_block[i].number_soldier2);
                fprintf(fptr,"%d ",arr_of_block[i].nolimit);
                fprintf(fptr,"%d\n",arr_of_block[i].fastblock);
            }

            fprintf(fptr,"%d\n",number_of_attack);
            for(int i=0;i<number_of_attack;i++)
            {
                fprintf(fptr,"%d ",wars[i].att);
                fprintf(fptr,"%d ",wars[i].def);
                fprintf(fptr,"%d ",wars[i].num_soldier);
                fprintf(fptr,"%d\n",wars[i].counter);
                struct soldier *current=wars[i].head;
                while(current->next!=NULL)
                {
                    fprintf(fptr,"%lf ",current->x);
                    fprintf(fptr,"%lf ",current->y);
                    fprintf(fptr,"%lf ",current->vx);
                    fprintf(fptr,"%lf ",current->vy);
                    fprintf(fptr,"%d ",current->num_dest_block);
                    fprintf(fptr,"%d ",current->num_beg_block);
                    fprintf(fptr,"%d ",current->index);
                    fprintf(fptr,"%d ",current->fast_run);
                    fprintf(fptr,"%d ",current->stop);
                    fprintf(fptr,"%d ",current->destx);
                    fprintf(fptr,"%d\n",current->desty);
                    current=current->next;
                }
                fprintf(fptr,"%lf ",0.0);
                fprintf(fptr,"%lf ",0.0);
                fprintf(fptr,"%lf ",0.0);
                fprintf(fptr,"%lf ",0.0);
                fprintf(fptr,"%d ",0);
                fprintf(fptr,"%d ",0);
                fprintf(fptr,"%d ",0);
                fprintf(fptr,"%d ",0);
                fprintf(fptr,"%d ",0);
                fprintf(fptr,"%d ",0);
                fprintf(fptr,"%d\n",0);

            }

            fprintf(fptr,"%d\n",NUM_POTOION);
            for(int i=0;i<NUM_POTOION;i++)
            {
                fprintf(fptr,"%d ",pot[i].x);
                fprintf(fptr,"%d ",pot[i].y);
                fprintf(fptr,"%d ",pot[i].index);
                fprintf(fptr,"%d ",pot[i].exist);
                fprintf(fptr,"%d\n",pot[i].runnig);
            }
            fprintf(fptr,"%d ",your_potion);
            fprintf(fptr,"%d ",ai_potion);
            fprintf(fptr,"%lld ",countai);
            fprintf(fptr,"%lld\n",counterFPS);
            for(int i=0;i<NUM_POTOION;i++)
                fprintf(fptr,"%d ",fps_potion[i]);

            fclose(fptr);
           // printf("new map saved\n");
            number_of_maps++;
            write_number_of_maps();

    } ///voroodi begire random bede
    else if(which==-2) ///load az ghabl
        {
            int temp;
            FILE * fptr;
            fptr=fopen("arr_colors.txt","r");
            fscanf(fptr," %d",&number_of_player);
            arr_of_colors=(uint32_t *)malloc(number_of_player*sizeof (uint32_t));
            for(int i=1;i<number_of_player;i++)
            {
                fscanf(fptr," %d",&temp);
                arr_of_colors[i]=clr[temp];
            }
            arr_of_colors[0]=clr[0];
            fclose(fptr);
            //////////////////////////////////////////
            fptr=fopen("saved.txt","r");
            fscanf(fptr," %d",&number_of_block);
            arr_of_block=(struct block *)malloc(number_of_block*sizeof (struct block));
            for(int i=0;i<number_of_block;i++)
            {
                fscanf(fptr," %d",&arr_of_block[i].index);
                fscanf(fptr," %d",&arr_of_block[i].xpos);
                fscanf(fptr," %d",&arr_of_block[i].ypos);
                fscanf(fptr," %d",&arr_of_block[i].number_soldier);
                fscanf(fptr," %d",&arr_of_block[i].number_soldier2);
                fscanf(fptr," %d",&temp);
                if(temp==1)
                    arr_of_block[i].nolimit=true;
                else
                    arr_of_block[i].nolimit=false;
                fscanf(fptr," %d",&temp);
                if(temp==1)
                    arr_of_block[i].fastblock=true;
                else
                    arr_of_block[i].fastblock=false;

            }

            fscanf(fptr," %d",&number_of_attack);
            for(int i=0;i<number_of_attack;i++)
            {
                fscanf(fptr," %d",&wars[i].att);
                fscanf(fptr," %d",&wars[i].def);
                fscanf(fptr," %d",&wars[i].num_soldier);
                fscanf(fptr," %d",&wars[i].counter);
                struct soldier sarbaz;
                while(1)
                {
                    fscanf(fptr," %lf",&sarbaz.x);
                    fscanf(fptr," %lf",&sarbaz.y);
                    fscanf(fptr," %lf",&sarbaz.vx);
                    fscanf(fptr," %lf",&sarbaz.vy);
                    fscanf(fptr," %d",&sarbaz.num_dest_block);
                    fscanf(fptr," %d",&sarbaz.num_beg_block);
                    fscanf(fptr," %d",&sarbaz.index);
                    fscanf(fptr," %d",&temp);
                    if(temp==1)
                        sarbaz.fast_run=true;
                    else
                        sarbaz.fast_run=false;
                    fscanf(fptr," %d",&temp);
                    if(temp==1)
                        sarbaz.stop=true;
                    else
                        sarbaz.stop=false;
                    fscanf(fptr," %d",&sarbaz.destx);
                    fscanf(fptr," %d",&sarbaz.desty);
                    if(sarbaz.x==0 && sarbaz.y==0)
                        break;
                    else
                    {
                        struct soldier *current=wars[i].head;
                        while(current->next!=NULL)
                        {
                            current=current->next;
                        }
                        sarbaz.next=(struct soldier*)malloc(sizeof(struct soldier));
                        *current=sarbaz;
                        current->next->next=NULL;
                    }
                }
            }
            fscanf(fptr," %d",&temp);
            for(int i=0;i<NUM_POTOION;i++)
            {
                fscanf(fptr," %d",&pot[i].x);
                fscanf(fptr," %d",&pot[i].y);
                fscanf(fptr," %d",&pot[i].index);
                fscanf(fptr," %d",&temp);
                if(temp==1)
                    pot[i].exist=true;
                else
                    pot[i].exist=false;

                fscanf(fptr," %d",&temp);
                if(temp==1)
                    pot[i].runnig=true;
                else
                    pot[i].runnig=false;
            }


            fscanf(fptr," %d",&temp);
            if(temp==1)
                your_potion=true;
            else
                your_potion=false;
            fscanf(fptr," %d",&temp);
            if(temp==1)
                ai_potion=true;
            else
                ai_potion=false;
            fscanf(fptr," %lld",&countai);
            fscanf(fptr," %lld",&counterFPS);
            for(int i=0;i<NUM_POTOION;i++)
                fscanf(fptr," %d",&fps_potion[i]);

            fclose(fptr);
         //   printf("loaded\n");
        }
    else    ///map az ghabl sakhte shode
    {
        int temp;
        FILE * fptr;
        char name_color[50]="arr_colors";
        char ch[5];
        numberTOstring(which,ch);
        strcat(name_color,ch);
        strcat(name_color,".txt");
        fptr=fopen(name_color,"r");
        if(fptr==NULL)
        {
            printf("file vojood nadare \n");
            return false;
        }
        fscanf(fptr," %d",&number_of_player);
        arr_of_colors=(uint32_t *)malloc(number_of_player*sizeof (uint32_t));
        for(int i=1;i<number_of_player;i++)
        {
            fscanf(fptr," %d",&temp);
            arr_of_colors[i]=clr[temp];
        }
        arr_of_colors[0]=clr[0];
        fclose(fptr);
        //////////////////////////////////////////
        char namegame[50]="saved";
        strcat(namegame,ch);
        strcat(namegame,".txt");
        fptr=fopen(namegame,"r");
        if(fptr==NULL)
        {
            printf("file vojood nadare \n");
            return false ;
        }

        fscanf(fptr," %d",&number_of_block);
        arr_of_block=(struct block *)malloc(number_of_block*sizeof (struct block));
        for(int i=0;i<number_of_block;i++)
        {
            fscanf(fptr," %d",&arr_of_block[i].index);
            fscanf(fptr," %d",&arr_of_block[i].xpos);
            fscanf(fptr," %d",&arr_of_block[i].ypos);
            fscanf(fptr," %d",&arr_of_block[i].number_soldier);
            fscanf(fptr," %d",&arr_of_block[i].number_soldier2);
            fscanf(fptr," %d",&temp);
            if(temp==1)
                arr_of_block[i].nolimit=true;
            else
                arr_of_block[i].nolimit=false;
            fscanf(fptr," %d",&temp);
            if(temp==1)
                arr_of_block[i].fastblock=true;
            else
                arr_of_block[i].fastblock=false;

        }

        fscanf(fptr," %d",&number_of_attack);
        for(int i=0;i<number_of_attack;i++)
        {
            fscanf(fptr," %d",&wars[i].att);
            fscanf(fptr," %d",&wars[i].def);
            fscanf(fptr," %d",&wars[i].num_soldier);
            fscanf(fptr," %d",&wars[i].counter);
            struct soldier sarbaz;
            while(1)
            {
                fscanf(fptr," %lf",&sarbaz.x);
                fscanf(fptr," %lf",&sarbaz.y);
                fscanf(fptr," %lf",&sarbaz.vx);
                fscanf(fptr," %lf",&sarbaz.vy);
                fscanf(fptr," %d",&sarbaz.num_dest_block);
                fscanf(fptr," %d",&sarbaz.num_beg_block);
                fscanf(fptr," %d",&sarbaz.index);
                fscanf(fptr," %d",&temp);
                if(temp==1)
                    sarbaz.fast_run=true;
                else
                    sarbaz.fast_run=false;
                fscanf(fptr," %d",&temp);
                if(temp==1)
                    sarbaz.stop=true;
                else
                    sarbaz.stop=false;
                fscanf(fptr," %d",&sarbaz.destx);
                fscanf(fptr," %d",&sarbaz.desty);
                if(sarbaz.x==0 && sarbaz.y==0)
                    break;
                else
                {
                    struct soldier *current=wars[i].head;
                    while(current->next!=NULL)
                    {
                        current=current->next;
                    }
                    sarbaz.next=(struct soldier*)malloc(sizeof(struct soldier));
                    *current=sarbaz;
                    current->next->next=NULL;
                }
            }
        }
        fscanf(fptr," %d",&temp);
        for(int i=0;i<NUM_POTOION;i++)
        {
            fscanf(fptr," %d",&pot[i].x);
            fscanf(fptr," %d",&pot[i].y);
            fscanf(fptr," %d",&pot[i].index);
            fscanf(fptr," %d",&temp);
            if(temp==1)
                pot[i].exist=true;
            else
                pot[i].exist=false;

            fscanf(fptr," %d",&temp);
            if(temp==1)
                pot[i].runnig=true;
            else
                pot[i].runnig=false;
        }


        fscanf(fptr," %d",&temp);
        if(temp==1)
            your_potion=true;
        else
            your_potion=false;
        fscanf(fptr," %d",&temp);
        if(temp==1)
            ai_potion=true;
        else
            ai_potion=false;
        fscanf(fptr," %lld",&countai);
        fscanf(fptr," %lld",&counterFPS);
        for(int i=0;i<NUM_POTOION;i++)
            fscanf(fptr," %d",&fps_potion[i]);

        fclose(fptr);
        printf("loaded\n");
    }

    ///berim hala karaye rendering
    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,2,2048) < 0)
        printf("%s",Mix_GetError());
    music = Mix_LoadMUS("music_war2.mp3");
    Mix_Music *warningmusic=Mix_LoadMUS("potionmusic.mp3");

    if (!is_ok_to_run_game())
        return false ;

    window = SDL_CreateWindow("game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    SDL_SetWindowBordered(window, SDL_WINDOW_FULLSCREEN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    image = SDL_LoadBMP("map_war2.bmp");
    if (!image)
        printf("ridi %s", SDL_GetError());
    texture = SDL_CreateTextureFromSurface(renderer, image);

    SDL_Surface* warningimg = SDL_LoadBMP("warning  .bmp");
    if (!warningimg)
        printf("ridi %s", SDL_GetError());
    SDL_Texture  *warningtxt = SDL_CreateTextureFromSurface(renderer, warningimg);
    //  SDL_SetTextureAlphaMod(warningtxt,150);


    SDL_Surface *image_block_por = SDL_LoadBMP("block_por.bmp");
    if (!image_block_por)
        printf("ridi %s", SDL_GetError());
    SDL_Texture *texture_block_por = SDL_CreateTextureFromSurface(renderer, image_block_por);

    SDL_Surface *image_block_khali = SDL_LoadBMP("block_khali.bmp");
    if (!image_block_khali)
        printf("ridi %s", SDL_GetError());
    SDL_Texture *texture_block_khali = SDL_CreateTextureFromSurface(renderer, image_block_khali);

    SDL_Surface *image_soldier[10];
    image_soldier[0] = SDL_LoadBMP("s0.bmp");
    image_soldier[1] = SDL_LoadBMP("s1.bmp");
    image_soldier[2] = SDL_LoadBMP("s2.bmp");
    image_soldier[3] = SDL_LoadBMP("s3.bmp");
    image_soldier[4] = SDL_LoadBMP("s4.bmp");
    image_soldier[5] = SDL_LoadBMP("s5.bmp");
    image_soldier[6] = SDL_LoadBMP("s6.bmp");
    image_soldier[7] = SDL_LoadBMP("s7.bmp");
    image_soldier[8] = SDL_LoadBMP("s8.bmp");
    image_soldier[9] = SDL_LoadBMP("s9.bmp");

    SDL_Texture *texture_soldier[10] ;
    texture_soldier[0]= SDL_CreateTextureFromSurface(renderer, image_soldier[0]);
    texture_soldier[1]= SDL_CreateTextureFromSurface(renderer, image_soldier[1]);
    texture_soldier[2]= SDL_CreateTextureFromSurface(renderer, image_soldier[2]);
    texture_soldier[3]= SDL_CreateTextureFromSurface(renderer, image_soldier[3]);
    texture_soldier[4]= SDL_CreateTextureFromSurface(renderer, image_soldier[4]);
    texture_soldier[5]= SDL_CreateTextureFromSurface(renderer, image_soldier[5]);
    texture_soldier[6]= SDL_CreateTextureFromSurface(renderer, image_soldier[6]);
    texture_soldier[7]= SDL_CreateTextureFromSurface(renderer, image_soldier[7]);
    texture_soldier[8]= SDL_CreateTextureFromSurface(renderer, image_soldier[8]);
    texture_soldier[9]= SDL_CreateTextureFromSurface(renderer, image_soldier[9]);

    SDL_Surface *image_potionD[4];
    image_potionD[0]= SDL_LoadBMP("p0.bmp");
    image_potionD[1]= SDL_LoadBMP("p1.bmp");
    image_potionD[2]= SDL_LoadBMP("p2.bmp");
    image_potionD[3]= SDL_LoadBMP("p3.bmp");
    SDL_Texture *texture_potionD[4];
    texture_potionD[0]= SDL_CreateTextureFromSurface(renderer,image_potionD[0]);
    texture_potionD[1]= SDL_CreateTextureFromSurface(renderer,image_potionD[1]);
    texture_potionD[2]= SDL_CreateTextureFromSurface(renderer,image_potionD[2]);
    texture_potionD[3]= SDL_CreateTextureFromSurface(renderer,image_potionD[3]);

    SDL_Surface *image_potionA[4];
    image_potionA[0]= SDL_LoadBMP("Ap0.bmp");
    image_potionA[1]= SDL_LoadBMP("Ap1.bmp");
    image_potionA[2]= SDL_LoadBMP("Ap2.bmp");
    image_potionA[3]= SDL_LoadBMP("Ap3.bmp");
    SDL_Texture *texture_potionA[4];
    texture_potionA[0]= SDL_CreateTextureFromSurface(renderer,image_potionA[0]);
    texture_potionA[1]= SDL_CreateTextureFromSurface(renderer,image_potionA[1]);
    texture_potionA[2]= SDL_CreateTextureFromSurface(renderer,image_potionA[2]);
    texture_potionA[3]= SDL_CreateTextureFromSurface(renderer,image_potionA[3]);

    SDL_Surface *img_waiting= SDL_LoadBMP("waiting.bmp");
    SDL_Texture *textture_waiting= SDL_CreateTextureFromSurface(renderer,img_waiting);

    Mix_PlayMusic(music,-1);

    while (game_is_running)
    {
        if (counterFPS == 9223372036854775807)
            counterFPS = 0;
        if (countai == 9223372036854775807)
            countai = 0;
        counterFPS++;
        SDL_RenderCopy(renderer, texture, NULL, &texture_rect);
        SDL_ShowCursor(SDL_DISABLE);
        render_blocks(number_of_block, arr_of_colors, arr_of_block, texture_block_khali, texture_block_por);

        while (SDL_PollEvent(&event))
        {
            blockclicked2 = which_block_clicked(arr_of_block, number_of_block, event);
            soundplay(event);
            check_exit_game(event);
            save(event);
        }
        moving_soldiers(wars, arr_of_block);
        check_to_active_potion(pot, wars);

        if (ai_potion == true)
        {
            SDL_RenderCopy(renderer, warningtxt, NULL, &texture_rect);
            SDL_RenderPresent(renderer);
            SDL_Delay(1000);
        }
        ai_potion = false;

        if (your_potion == true) {
            Mix_PlayMusic(warningmusic, 1);
        }
        your_potion = false;

        if (!Mix_PlayingMusic())
            Mix_PlayMusic(music, -1);

        run_potion(pot, wars, arr_of_block, number_of_block);
        render_potion(pot, texture_potionD, texture_potionA);
        render_soldier(wars, number_of_attack, texture_soldier, arr_of_colors, arr_of_block);
        show_save();
        showcursorandsound();
        if(saveandexit)
        {
           // if(which==-1)
           //  delete_last_map_save();
            FILE * fptr;
            fptr= fopen("arr_colors.txt","w");
            fprintf(fptr,"%d\n",number_of_player);
            for(int i=1;i<number_of_player;i++)
                for(int j=0;j<10;j++)
                    if(arr_of_colors[i]==clr[j])
                        fprintf(fptr,"%d ",j);
            fclose(fptr);
            fptr=fopen("saved.txt","w");
            fprintf(fptr,"%d\n",number_of_block);
            for(int i=0;i<number_of_block;i++)
            {
                fprintf(fptr,"%d ",arr_of_block[i].index);
                fprintf(fptr,"%d ",arr_of_block[i].xpos);
                fprintf(fptr,"%d ",arr_of_block[i].ypos);
                fprintf(fptr,"%d ",arr_of_block[i].number_soldier);
                fprintf(fptr,"%d ",arr_of_block[i].number_soldier2);
                fprintf(fptr,"%d ",arr_of_block[i].nolimit);
                fprintf(fptr,"%d\n",arr_of_block[i].fastblock);
            }

            fprintf(fptr,"%d\n",number_of_attack);
            for(int i=0;i<number_of_attack;i++)
            {
                fprintf(fptr,"%d ",wars[i].att);
                fprintf(fptr,"%d ",wars[i].def);
                fprintf(fptr,"%d ",wars[i].num_soldier);
                fprintf(fptr,"%d\n",wars[i].counter);
                struct soldier *current=wars[i].head;
                while(current->next!=NULL)
                {
                    fprintf(fptr,"%lf ",current->x);
                    fprintf(fptr,"%lf ",current->y);
                    fprintf(fptr,"%lf ",current->vx);
                    fprintf(fptr,"%lf ",current->vy);
                    fprintf(fptr,"%d ",current->num_dest_block);
                    fprintf(fptr,"%d ",current->num_beg_block);
                    fprintf(fptr,"%d ",current->index);
                    fprintf(fptr,"%d ",current->fast_run);
                    fprintf(fptr,"%d ",current->stop);
                    fprintf(fptr,"%d ",current->destx);
                    fprintf(fptr,"%d\n",current->desty);
                    current=current->next;
                }
                fprintf(fptr,"%lf ",0.0);
                fprintf(fptr,"%lf ",0.0);
                fprintf(fptr,"%lf ",0.0);
                fprintf(fptr,"%lf ",0.0);
                fprintf(fptr,"%d ",0);
                fprintf(fptr,"%d ",0);
                fprintf(fptr,"%d ",0);
                fprintf(fptr,"%d ",0);
                fprintf(fptr,"%d ",0);
                fprintf(fptr,"%d ",0);
                fprintf(fptr,"%d\n",0);

            }

            fprintf(fptr,"%d\n",NUM_POTOION);
            for(int i=0;i<NUM_POTOION;i++)
            {
                fprintf(fptr,"%d ",pot[i].x);
                fprintf(fptr,"%d ",pot[i].y);
                fprintf(fptr,"%d ",pot[i].index);
                fprintf(fptr,"%d ",pot[i].exist);
                fprintf(fptr,"%d\n",pot[i].runnig);
            }
            fprintf(fptr,"%d ",your_potion);
            fprintf(fptr,"%d ",ai_potion);
            fprintf(fptr,"%lld ",countai);
            fprintf(fptr,"%lld\n",counterFPS);
            for(int i=0;i<NUM_POTOION;i++)
                fprintf(fptr,"%d ",fps_potion[i]);

            fclose(fptr);

            SDL_RenderCopy(renderer,textture_waiting,NULL,&texture_rect);
            SDL_RenderPresent(renderer);
            SDL_Delay(1000);
            {
                SDL_DestroyTexture(texture);
                SDL_FreeSurface(image);
                Mix_FreeMusic(music);

                SDL_DestroyTexture(warningtxt);
                SDL_FreeSurface(warningimg);
                Mix_FreeMusic(warningmusic);

                SDL_DestroyTexture(texture_block_por);
                SDL_FreeSurface(image_block_por);

                SDL_DestroyTexture(texture_block_khali);
                SDL_FreeSurface(image_block_khali);
                for(int i=0;i<10;i++)
                {
                    SDL_DestroyTexture(texture_soldier[i]);
                    SDL_FreeSurface(image_soldier[i]);
                }
                for(int i=0;i<4;i++)
                {
                    SDL_DestroyTexture(texture_potionD[i]);
                    SDL_FreeSurface(image_potionD[i]);
                }
                for(int i=0;i<4;i++)
                {
                    SDL_DestroyTexture(texture_potionA[i]);
                    SDL_FreeSurface(image_potionA[i]);
                }

                SDL_DestroyTexture(textture_waiting);
                SDL_FreeSurface(img_waiting);

                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                window = NULL;
                renderer = NULL;
                texture=NULL;
                image=NULL;
                music=NULL;

            }
           // printf("saved\n");
            run_menu=true;
            return true;
        }  //inja bayad bazi save va baste beshe
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / FPS);
        SDL_RenderClear(renderer);
        if (counterFPS % 60 == 0)  //har 1 sanie ba ehtemal 50%
        {
            time_t t;
            srand((unsigned) time(&t));
            int pp=rand()%2;
            if (pp!=0)   //generate potion
            {
                bool tekrari = false;
                struct axis temp = generate_random_potion(arr_of_block, number_of_block);
                for (int i = 0; i < NUM_POTOION; i++)
                    if (temp.x == pot[i].x && temp.y == pot[i].y && pot[i].exist == true)
                        tekrari = true;
                int tmp = rand() % NUM_POTOION;
                if (!pot[tmp].exist && !tekrari) {
                    fps_potion[tmp] = 0;
                    pot[tmp].x = temp.x;
                    pot[tmp].y = temp.y;
                    pot[tmp].exist = true;
                    pot[tmp].runnig = false;
                }
            }
        }
        if (counterFPS % 60 == 0) {
            for (int i = 0; i < number_of_block; i++) {
                if (arr_of_block[i].index != -1) {
                    if (arr_of_block[i].nolimit == true && arr_of_block[i].fastblock == true) {
                        arr_of_block[i].number_soldier += 2;
                        arr_of_block[i].number_soldier2 += 2;
                    } else if (arr_of_block[i].nolimit == true && arr_of_block[i].fastblock == false) {
                        arr_of_block[i].number_soldier++;
                        arr_of_block[i].number_soldier2++;
                    } else if (arr_of_block[i].nolimit == false && arr_of_block[i].fastblock == true) {
                        if (arr_of_block[i].number_soldier < max_sarbaz) {
                            arr_of_block[i].number_soldier += 2;
                            arr_of_block[i].number_soldier2 += 2;
                        }

                    } else if (arr_of_block[i].nolimit == false && arr_of_block[i].fastblock == false) {
                        if (arr_of_block[i].number_soldier < max_sarbaz) {
                            arr_of_block[i].number_soldier++;
                            arr_of_block[i].number_soldier2++;
                        }
                    }
                }
            }
        } //afzayesh sarbaz
        if (counterFPS % 5 == 0) {
            generate_all_wars_soldiers(wars, number_of_attack, arr_of_block);
        }  //generate sarbaz
        if (blockclicked2 != -1 )
        {
            if (blockclicked1 == -1)
            {
                if (arr_of_block[blockclicked2].index != 0)
                    blockclicked2 = -1;
                else
                {
                    blockclicked1 = blockclicked2;
                    blockclicked2 = -1;
                }
            } else  //bayad jang start beshe
            {
                if (blockclicked2 != blockclicked1) {
                    wars[number_of_attack%NUM_WAR].def = blockclicked2;
                    wars[number_of_attack%NUM_WAR].att = blockclicked1;
                    wars[number_of_attack%NUM_WAR].num_soldier = arr_of_block[blockclicked1].number_soldier2;
                    arr_of_block[blockclicked1].number_soldier2 = 0;
                    wars[number_of_attack%NUM_WAR].counter = 0;
                    number_of_attack++;
                }
                blockclicked2 = -1;
                blockclicked1 = -1;
            }
        }  //hamle baazikon
        for (int i = 0; i < NUM_POTOION; i++)
        {
            if (pot[i].exist == true)
                fps_potion[i]++;
            if (fps_potion[i] > 150 && pot[i].runnig == false)
            {
                pot[i].exist = false;
                pot[i].runnig = false;
            }
            if (fps_potion[i] > 300 && pot[i].runnig == true)
            {
                if (pot[i].index == 0)
                    your_potion = false;
                else
                    ai_potion = false;
                deactive_potion(pot[i], i, wars, arr_of_block, number_of_block);
                pot[i].exist = false;
                pot[i].runnig = false;
            }
        } //zaman bandi az bein bordan potion
        struct axis AIatack ;
        if (counterFPS % 100==0 )
        {
            countai++;
            if(countai%4==0)
                AIatack = AI1(arr_of_block, number_of_block);
            else if(countai %4==1)
                AIatack = AI2(arr_of_block, number_of_block);
            else if(countai %4==2)
                AIatack = AI3(arr_of_block, number_of_block);
            else if(countai %4==3)
                AIatack = AI4(arr_of_block, number_of_block);
            if (AIatack.x != -1 && AIatack.y != -1)
            {
              //  printf("%d %d\n", AIatack.x, AIatack.y);
                wars[number_of_attack%NUM_WAR].def = AIatack.y;
                wars[number_of_attack%NUM_WAR].att = AIatack.x;
                wars[number_of_attack%NUM_WAR].num_soldier = arr_of_block[AIatack.x].number_soldier2;
                arr_of_block[AIatack.x].number_soldier2 = 0;
                wars[number_of_attack%NUM_WAR].counter = 0;
                number_of_attack++;
            }
        }  //AI
        if (win(arr_of_block,number_of_block))
        {
     //       if(which==-1)
     //           delete_last_map_save();
            write_win_to_file();
            for(int i=0;i<3;i++)
                write_loseAI_to_file(i);

            image= IMG_Load("win.jpg");
            texture= SDL_CreateTextureFromSurface(renderer,image);
            SDL_RenderCopy(renderer,texture,NULL,&texture_rect);
            if(strcmp(name,""))
                show_text(renderer,50,50,name,120,0,255,0,255);
            show_text(renderer,50,170,"WIN",120,0,255,0,255);
           // printf("win");
            SDL_RenderPresent(renderer);
            SDL_Delay(3000);
            run_menu=true;
            {
                SDL_DestroyTexture(texture);
                SDL_FreeSurface(image);
                Mix_FreeMusic(music);

                SDL_DestroyTexture(warningtxt);
                SDL_FreeSurface(warningimg);
                Mix_FreeMusic(warningmusic);

                SDL_DestroyTexture(texture_block_por);
                SDL_FreeSurface(image_block_por);

                SDL_DestroyTexture(texture_block_khali);
                SDL_FreeSurface(image_block_khali);
                for(int i=0;i<10;i++)
                {
                    SDL_DestroyTexture(texture_soldier[i]);
                    SDL_FreeSurface(image_soldier[i]);
                }
                for(int i=0;i<4;i++)
                {
                    SDL_DestroyTexture(texture_potionD[i]);
                    SDL_FreeSurface(image_potionD[i]);
                }
                for(int i=0;i<4;i++)
                {
                    SDL_DestroyTexture(texture_potionA[i]);
                    SDL_FreeSurface(image_potionA[i]);
                }

                SDL_DestroyTexture(textture_waiting);
                SDL_FreeSurface(img_waiting);

                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                window = NULL;
                renderer = NULL;
                texture=NULL;
                image=NULL;
                music=NULL;

            }
            return true;
        }
        if(lose(arr_of_block,number_of_block))
        {
        //    if(which==-1)
        //      delete_last_map_save();
            time_t t;
            srand((unsigned) time(&t));
            write_winAI_to_file(rand()%3);
            write_lose_to_file();
            image= IMG_Load("lose.jpg");
            texture= SDL_CreateTextureFromSurface(renderer,image);
            SDL_RenderCopy(renderer,texture,NULL,&texture_rect);
            if(strcmp(name,""))
             show_text(renderer,50,50,name,120,255,0,0,255);
            show_text(renderer,50,170,"LOST",120,255,0,0,255);
            SDL_RenderPresent(renderer);
            SDL_Delay(3000);
           // printf("lose");
            run_menu=true;
            {
                SDL_DestroyTexture(texture);
                SDL_FreeSurface(image);
                Mix_FreeMusic(music);

                SDL_DestroyTexture(warningtxt);
                SDL_FreeSurface(warningimg);
                Mix_FreeMusic(warningmusic);

                SDL_DestroyTexture(texture_block_por);
                SDL_FreeSurface(image_block_por);

                SDL_DestroyTexture(texture_block_khali);
                SDL_FreeSurface(image_block_khali);
                for(int i=0;i<10;i++)
                {
                    SDL_DestroyTexture(texture_soldier[i]);
                    SDL_FreeSurface(image_soldier[i]);
                }
                for(int i=0;i<4;i++)
                {
                    SDL_DestroyTexture(texture_potionD[i]);
                    SDL_FreeSurface(image_potionD[i]);
                }
                for(int i=0;i<4;i++)
                {
                    SDL_DestroyTexture(texture_potionA[i]);
                    SDL_FreeSurface(image_potionA[i]);
                }

                SDL_DestroyTexture(textture_waiting);
                SDL_FreeSurface(img_waiting);

                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                window = NULL;
                renderer = NULL;
                texture=NULL;
                image=NULL;
                music=NULL;

            }
            return true;
        }
    }
 //   if(which==-1)
 //     delete_last_map_save();
    {
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(image);
        Mix_FreeMusic(music);

        SDL_DestroyTexture(warningtxt);
        SDL_FreeSurface(warningimg);
        Mix_FreeMusic(warningmusic);

        SDL_DestroyTexture(texture_block_por);
        SDL_FreeSurface(image_block_por);

        SDL_DestroyTexture(texture_block_khali);
        SDL_FreeSurface(image_block_khali);
        for(int i=0;i<10;i++)
        {
            SDL_DestroyTexture(texture_soldier[i]);
            SDL_FreeSurface(image_soldier[i]);
        }
        for(int i=0;i<4;i++)
        {
            SDL_DestroyTexture(texture_potionD[i]);
            SDL_FreeSurface(image_potionD[i]);
        }
        for(int i=0;i<4;i++)
        {
            SDL_DestroyTexture(texture_potionA[i]);
            SDL_FreeSurface(image_potionA[i]);
        }

        SDL_DestroyTexture(textture_waiting);
        SDL_FreeSurface(img_waiting);

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        window = NULL;
        renderer = NULL;
        texture=NULL;
        image=NULL;
        music=NULL;

    }
    return false;
}   // save ya win ya lose return true end game ya eror return false
bool random_map()
{
    bool first_number=true;
    while (game_is_running)
    {
        SDL_RenderCopy(renderer, texture, NULL, &texture_rect);
        show_text(renderer,0,0,name_used_in_menu,60,255,0,0,255);
        show_text(renderer,820,470,"number of all blocks (max43)=",50,255,0,0,255);
        show_text(renderer,820,550,"number of AI (max9)=",50,255,0,0,255);
        SDL_ShowCursor(SDL_DISABLE);
        showcursorandsoundLEADERBOARD();
        if(strcmp(number,""))
            show_text(renderer,1570,470,number,50,255,255,255,255);
        if(strcmp(number2,""))
            show_text(renderer,1360,550,number2,50,255,255,255,255);
        while(SDL_PollEvent(&event))
        {
            if(first_number)
            {
                char ch = inputs_string(event);
                if (('0' <= ch && ch <= '9') || ch == ' ')
                    strncat(number, &ch, 1);
                if (ch == SDLK_BACKSPACE && strlen(number) >= 1)
                    number[strlen(number) - 1] = '\0';
                if (ch == SDLK_RETURN) {
                    first_number = false;
                }
            }
            else
            {
                char ch = inputs_string(event);
                if (('0' <= ch && ch <= '9') || ch == ' ')
                    strncat(number2, &ch, 1);
                if (ch == SDLK_BACKSPACE && strlen(number2) >= 1)
                    number2[strlen(number2) - 1] = '\0';
                if (ch == SDLK_RETURN)
                {
                    int num1= stringToNumber(number);
                    int num2=stringToNumber(number2);
                    if(num1 > 43)
                        num1=43;
                    if(num2>9)
                        num2=9;
                    number_of_block=num1;
                    number_of_player=num2+1;
                    SDL_DestroyRenderer(renderer);
                    SDL_DestroyWindow(window);
                    SDL_DestroyTexture(texture);
                    SDL_FreeSurface(image);
                    Mix_FreeMusic(music);
                    window = NULL;
                    renderer = NULL;
                    texture=NULL;
                    image=NULL;
                    map(-1);
                    return false;
                }
            }
            if(LEADERBOARDback(event))
            {
                strcpy(number,"");
                strcpy(number2,"");
                strcpy(number3,"");
                return true;
            }
            check_exit_game(event);
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / FPS);
        SDL_RenderClear(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    Mix_FreeMusic(music);
    window = NULL;
    renderer = NULL;
    texture=NULL;
    image=NULL;
    music=NULL;
    return false ;
}    //true vaqti bargashti ghabl false vaqti bazi baste shod
bool select_map()
{
    while (game_is_running)
    {
        SDL_RenderCopy(renderer, texture, NULL, &texture_rect);
        SDL_ShowCursor(SDL_DISABLE);

        char temp[10]="";
        char nahaei[50]="NUMBER OF MAPS SAVED = ";
        how_many_maps();
        numberTOstring(number_of_maps,temp);
        strcat(nahaei,temp);
        show_text(renderer,0,0,name_used_in_menu,60,255,0,0,255);

        show_text(renderer,820,200,nahaei,60,0,240,0,255);
        show_text(renderer,820,470,"number of map you want =",50,255,0,0,255);
        if(strcmp(number3,""))
            show_text(renderer,1520,470,number3,50,255,0,0,255);

        while(SDL_PollEvent(&event))
        {
            char ch = inputs_string(event);
            if (('0' <= ch && ch <= '9') || ch == ' ')
                strncat(number3, &ch, 1);
            if (ch == SDLK_BACKSPACE && strlen(number3) >= 1)
                number3[strlen(number3) - 1] = '\0';
            if (ch == SDLK_RETURN)
            {
                int num= stringToNumber(number3);
                num--;
                if(num < number_of_maps)
                {
                    SDL_DestroyRenderer(renderer);
                    SDL_DestroyWindow(window);
                    SDL_DestroyTexture(texture);
                    SDL_FreeSurface(image);
                    Mix_FreeMusic(music);
                    window = NULL;
                    renderer = NULL;
                    texture=NULL;
                    image=NULL;
                    map(num);
                    return false;
                }
            }
            if(LEADERBOARDback(event))
            {
                strcpy(number,"");
                strcpy(number2,"");
                strcpy(number3,"");
                return true;
            }
            check_exit_game(event);
        }
        showcursorandsoundLEADERBOARD();
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / FPS);
        SDL_RenderClear(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    Mix_FreeMusic(music);
    window = NULL;
    renderer = NULL;
    texture=NULL;
    image=NULL;
    music=NULL;
    return false ;
}
bool new_game()
{
    while (game_is_running)
    {
        SDL_RenderCopy(renderer, texture, NULL, &texture_rect);
        show_text(renderer,0,0,name_used_in_menu,60,255,0,0,255);
        txtRGBA(renderer, 1300, 200 + 50, "  Random", 50, 160, 13, 10, 255);
        txtRGBA(renderer, 1300, 440 + 50, "   Select", 50, 160, 13, 10, 255);
        SDL_ShowCursor(SDL_DISABLE);
        showcursorandsoundLEADERBOARD();
        while(SDL_PollEvent(&event))
        {
            if(LEADERBOARDback(event))
            {
                return true;
            }
            if(click_new_game(event))
            {
                if(!random_map())
                {
                    return false;
                }
            }
            if(click_continue(event))
            {
                if(!select_map())
                {
                    return false;
                }
            }
            check_exit_game(event);
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / FPS);
        SDL_RenderClear(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    Mix_FreeMusic(music);
    window = NULL;
    renderer = NULL;
    texture=NULL;
    image=NULL;
    music=NULL;
    Mix_Quit();
    SDL_Quit();
    return false ;
}
void menu(){
    strcat(name_used_in_menu,name);
    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,2,2048) < 0)
        printf("%s",Mix_GetError());
    music= Mix_LoadMUS("music.mp3");
    if (!is_ok_to_run_game())
        return ;
    window = SDL_CreateWindow("menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    SDL_SetWindowBordered(window, SDL_WINDOW_FULLSCREEN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    image = SDL_LoadBMP("menu .bmp");
    if (!image)
        printf("ridi %s", SDL_GetError());
    texture = SDL_CreateTextureFromSurface(renderer, image);
    Mix_PlayMusic(music,-1);
    while (game_is_running)
    {
        while(SDL_PollEvent(&event))
        {
            if(click_new_game(event))
            {
                if (!new_game())
                {
                    return;
                } //close the game
                sound = !sound;
            }
            if(click_continue(event))
            {
                FILE * fptr;
                fptr=fopen("arr_colors.txt","r");
                if(fptr==NULL)
                {
                        SDL_RenderCopy(renderer, texture, NULL, &texture_rect);
                        show_text(renderer,0,0,name_used_in_menu,60,255,0,0,255);
                        show_text(renderer, 880, 470, "NO GAME SAVED BEFORE", 80, 0, 255, 0, 255);
                        SDL_ShowCursor(SDL_DISABLE);
                        SDL_RenderPresent(renderer);
                        SDL_Delay(2000);
                        SDL_RenderClear(renderer);
                }
                   // fclose(fptr);
                else
                {
                    fclose(fptr);
                    SDL_DestroyRenderer(renderer);
                    SDL_DestroyWindow(window);
                    SDL_DestroyTexture(texture);
                    SDL_FreeSurface(image);
                    Mix_FreeMusic(music);
                    window = NULL;
                    renderer = NULL;
                    texture = NULL;
                    image = NULL;
                    music = NULL;
                    map(-2);
                    return ;
                }
            }
            if(click_ranking(event))
            {
                if(!leaderboard())
                {
                    return ;
                } //close the game
                sound=!sound;
            }
            soundplay(event);
            check_exit_game(event);
            delete_work(event);
        }
        SDL_RenderCopy(renderer, texture, NULL, &texture_rect);
        show_text(renderer,0,0,name_used_in_menu,60,255,0,0,255);
        txtRGBA(renderer, 1300, 200 + 50, "NEW GAME", 50, 160, 13, 10, 255);
        txtRGBA(renderer, 1300, 440 + 50, "CONTINUE", 50, 160, 13, 10, 255);
        txtRGBA(renderer, 1300, 680 + 50, " RANKING", 50, 160, 13, 10, 255);
        SDL_ShowCursor(SDL_DISABLE);
        is_on_hint();
        render_delet();
        showcursorandsound();
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / FPS);
        SDL_RenderClear(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    Mix_FreeMusic(music);
    window = NULL;
    renderer = NULL;
    texture=NULL;
    image=NULL;
    return ;
}
void intro()
{
    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,2,2048) < 0)
        printf("%s",Mix_GetError());
    music= Mix_LoadMUS("m3.mp3");
    if (!is_ok_to_run_game())
        return ;
    window = SDL_CreateWindow("intro", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    SDL_SetWindowBordered(window, SDL_WINDOW_FULLSCREEN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    char ch[20]="";
    char namep[30]="";
    Mix_PlayMusic(music,1);
    for (int i = 1; i <= 855; i++) {
        strcpy(namep, "t/");
        numberTOstring(i, ch);
        strcat(ch, ".png");
        strcat(namep, ch);
        image = IMG_Load(namep);
        if (!image) {
            printf("ridi");
            return;
        }
        texture = SDL_CreateTextureFromSurface(renderer, image);
        SDL_RenderCopy(renderer, texture, NULL, &texture_rect);
        SDL_ShowCursor(SDL_DISABLE);
        while (SDL_PollEvent(&event)) {
        //    soundplay(event);
            check_exit_game(event);
        }
      //  showcursorandsound();
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / 52);
        SDL_RenderClear(renderer);
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(image);
        if(!game_is_running)
            break;
    }
    for (int i = 1; i <= 255; i++)
    {
        if(!game_is_running)
            break;
        while (SDL_PollEvent(&event))
        {
            check_exit_game(event);
        }
        show_text(renderer,120,200,"STATE.IO",400,200,0,0,i);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / FPS);
        SDL_RenderClear(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_FreeMusic(music);
    window = NULL;
    renderer = NULL;
    texture=NULL;
    image=NULL;
    music=NULL;
    return;
}
void first_page()
{
    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,2,2048) < 0)
        printf("%s",Mix_GetError());
    music= Mix_LoadMUS("music_first.mp3");
    if (!is_ok_to_run_game())
        return ;
    window = SDL_CreateWindow("HELLO", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    SDL_SetWindowBordered(window, SDL_WINDOW_FULLSCREEN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    image = SDL_LoadBMP("bf4.bmp");
    if (!image)
        printf("ridi %s", SDL_GetError());
    texture = SDL_CreateTextureFromSurface(renderer, image);

    SDL_Surface *imagegame = SDL_LoadBMP("gamename.bmp");
    if (!imagegame)
        printf("ridi %s", SDL_GetError());
    SDL_Texture *texturegame = SDL_CreateTextureFromSurface(renderer, imagegame);
    int tool=imagegame->w / 4;
    int arz=imagegame->h  / 4;
    int temp99=0,temp98=0;
    int centerx=960;
    int centery=650;

    SDL_Rect temp_rect;
    SDL_Surface * war_first= SDL_LoadBMP("first_warning.bmp");
    SDL_Texture * txt = SDL_CreateTextureFromSurface(renderer,war_first);
    for(int i=0;i<=255;i++)
    {
        SDL_SetTextureAlphaMod(txt,i);
        SDL_RenderCopy(renderer,txt,NULL,&texture_rect);
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        SDL_Delay(1000/FPS);
    }
    SDL_SetTextureAlphaMod(txt,255);
    SDL_RenderCopy(renderer,txt,NULL,&texture_rect);
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
    SDL_Delay(3000);
    Mix_PlayMusic(music,-1);
    for(int i=255;i>=0;i--)
    {
        SDL_SetTextureAlphaMod(txt,i);
        SDL_RenderCopy(renderer,txt,NULL,&texture_rect);
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        SDL_Delay(1000/FPS);
    }
    SDL_FreeSurface(war_first);
    SDL_DestroyTexture(txt);
    while(tool < imagegame->w /2 && game_is_running)
    {
        SDL_ShowCursor(SDL_DISABLE);
        SDL_RenderCopy(renderer, texture, NULL, &texture_rect);
        show_text(renderer,30,30,"LOADING PLEASE WAIT ..",60,0,0,0,255);
        temp_rect.x=centerx-tool/2;
        temp_rect.y=centery-arz/2;
        temp_rect.w=tool;
        temp_rect.h=arz;
        tool+=1;
        arz+=1;
        SDL_RenderCopy(renderer, texturegame, NULL, &temp_rect);
        while(SDL_PollEvent(&event))
        {
            soundplay(event);
            check_exit_game(event);
        }
        showcursorandsound();
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
    }   //loading aval
    while(game_is_running && temp99<255)
    {
        SDL_ShowCursor(SDL_DISABLE);
        SDL_RenderCopy(renderer, texture, NULL, &texture_rect);
        show_text(renderer, 30, 30, "PLEASE ENTER YOUR NAME THEN PRESS ENTER :", 50, 255, 0, 90, temp99);
        SDL_RenderCopy(renderer, texturegame, NULL, &temp_rect);
        SDL_ShowCursor(SDL_DISABLE);

        while(SDL_PollEvent(&event))
        {
            soundplay(event);
            check_exit_game(event);
        }

        showcursorandsound();
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        temp99+=5;
    }  //neveshtan enter name

    while(game_is_running)
    {
        SDL_ShowCursor(SDL_DISABLE);
        SDL_RenderCopy(renderer, texture, NULL, &texture_rect);
        SDL_RenderCopy(renderer, texturegame, NULL, &temp_rect);
        show_text(renderer, 30, 30, "PLEASE ENTER YOUR NAME THEN PRESS ENTER :", 50, 255, 0, 90, 255);
        if(name[0]=='\0')
            show_text(renderer,50,150," ",40,0,0,0,255);
        else
            show_text(renderer,50,150,name,40,0,0,0,255);
        while(SDL_PollEvent(&event))
        {
            soundplay(event);
            check_exit_game(event);
            char ch=inputs_string(event);
            if(('a'<=ch && ch <= 'z') || ch==' ')
                strncat(name,&ch,1);
            if(ch==SDLK_BACKSPACE && strlen(name)>=1)
                name[strlen(name)-1]='\0';
            if(ch==SDLK_RETURN)
            {
                write_name_to_file();
               /// printf("\n%s",name);
                if(new_user)
                {
                    SDL_DestroyRenderer(renderer);
                    SDL_DestroyWindow(window);
                    SDL_DestroyTexture(texture);
                    SDL_FreeSurface(image);
                    SDL_DestroyTexture(texturegame);
                    SDL_DestroyTexture(txt);
                    Mix_FreeMusic(music);
                    window = NULL;
                    renderer = NULL;
                    texture=NULL;
                    image=NULL;
                    music=NULL;
                    intro();
                }
                else {
                    SDL_DestroyRenderer(renderer);
                    SDL_DestroyWindow(window);
                    SDL_DestroyTexture(texture);
                    SDL_FreeSurface(image);
                    SDL_DestroyTexture(texturegame);
                    SDL_DestroyTexture(txt);
                    Mix_FreeMusic(music);
                    window = NULL;
                    renderer = NULL;
                    texture = NULL;
                    image = NULL;
                    music = NULL;
                }
                menu();
                return;
            }
            event.key.keysym.sym = NULL;
            event.type = NULL;
        }
        showcursorandsound();
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / FPS);
        SDL_RenderClear(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    Mix_FreeMusic(music);
    Mix_Quit();
    SDL_Quit();
    window = NULL;
    renderer = NULL;
    texture=NULL;
    image=NULL;
    music=NULL;
}