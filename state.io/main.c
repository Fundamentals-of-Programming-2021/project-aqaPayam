#include <SDL2/SDL.h>
//#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#define image_path "menu .bmp"
int xCursor=0,yCursor=0;
SDL_Window *window=NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *texture=NULL;
SDL_Rect texture_rect={.x=0,.y=0,.w=1920,.h=1080};
SDL_Surface *image=NULL;
const int FPS = 60;
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
bool game_is_running=true;
void showcursor()
{
    SDL_GetMouseState(&xCursor,&yCursor);
    SDL_Surface *image_cursor= SDL_LoadBMP("cursor.bmp");
    if(!image_cursor)
        printf("ridi dar cursor %s",SDL_GetError());
    SDL_Rect cursor_place={.x=xCursor-50,.y=yCursor-40,.w=100,.h=80};
    SDL_Texture *texture_cursor= SDL_CreateTextureFromSurface(renderer,image_cursor);
    SDL_RenderCopy(renderer,texture_cursor,NULL,&cursor_place);
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
    SDL_FreeSurface( textSurface );

    if (xCursor >= x && xCursor<=x+mWidth && yCursor>=y && yCursor<=y+mHeight)
    {
        SDL_Surface *image_hitler= SDL_LoadBMP("hitler.bmp");
        if(!image_hitler)
            printf("ridi dar hitler %s",SDL_GetError());
        SDL_Rect hitler_place={.x=900,.y=y-30,.w=320,.h=180};
        SDL_Texture *texture_hitler= SDL_CreateTextureFromSurface(renderer,image_hitler);
        SDL_RenderCopy(renderer,texture_hitler,NULL,&hitler_place);
    }
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    SDL_RenderCopyEx( renderer, mTexture, clip, &renderQuad, angle, center, flip );

    SDL_DestroyTexture( mTexture );

}

void check_exit_game()
{
    const SDL_MessageBoxButtonData buttons[] = {
            { /* .flags, .buttonid, .text */        0, 0, "no" },
            { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "yes" },
            { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "cancel" },
    };
    const SDL_MessageBoxColorScheme colorScheme = {
            { /* .colors (.r, .g, .b) */
                    /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
                    { 180,   100,   0 },
                    /* [SDL_MESSAGEBOX_COLOR_TEXT] */
                    {   0, 0,   0 },
                    /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
                    { 255,   255,   0 },
                    /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
                    {   0, 0, 180 },
                    /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
                    { 255,   0, 0 }
            }
    };
    const SDL_MessageBoxData messageboxdata = {
            SDL_MESSAGEBOX_INFORMATION, /* .flags */
            NULL, /* .window */
            "Are you sure you want to exit ?", /* .title */
            "select a button", /* .message */
            SDL_arraysize(buttons), /* .numbuttons */
            buttons, /* .buttons */
            &colorScheme /* .colorScheme */
    };
    int buttonid;
    //SDL_ShowMessageBox(&messageboxdata, &buttonid);
    SDL_Event event;
    if (SDL_PollEvent(&event))
        if (event.type==SDL_QUIT)
        {
            game_is_running=false;
        }
        else
            if (event.type==SDL_KEYUP && event.key.keysym.sym==SDLK_ESCAPE)
            {
                game_is_running=false;
            }

}
uint32_t color(int r,int g, int b, int a){return    ( (a << 24) + (b<< 16) + (g << 8) + r) ;}
bool is_ok_to_run_game()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER |SDL_INIT_AUDIO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    return true;
}
int main()
{
    if(!is_ok_to_run_game())
        return -1;
    window = SDL_CreateWindow("game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                             SCREEN_WIDTH,
                                             SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    SDL_SetWindowBordered(window,SDL_WINDOW_FULLSCREEN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    image= SDL_LoadBMP(image_path);
    if(!image)
        printf("ridi %s",SDL_GetError());
    texture= SDL_CreateTextureFromSurface(renderer,image);
    while(game_is_running)
    {
        check_exit_game();
        SDL_RenderCopy(renderer,texture,NULL,&texture_rect);
        txtRGBA(renderer,1300,200+50,"NEW GAME",50,160,13,10,255);
        txtRGBA(renderer,1300,440+50,"CONTINUE",50,160,13,10,255);
        txtRGBA(renderer,1300,680+50," RANKING",50,160,13,10,255);
        SDL_ShowCursor(SDL_DISABLE);
        showcursor();
        SDL_RenderPresent(renderer);
        SDL_Delay(1000/FPS);
    }
    SDL_Window *window=NULL;
    SDL_Renderer *renderer = NULL;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}