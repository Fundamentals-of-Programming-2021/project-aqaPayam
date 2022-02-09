
int stringToNumber(char * j)
{
    int res=0;
    for(int i=0;i< strlen(j);i++)
    {
        res=res*10+((int)j[i]-48);
    }
    return res;
}///general
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
}///general
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
}///general
int number_to_string(int num){
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
}//return chand raghamie va string mire too temp_of_function_numberToString[10]///general

void how_many_maps()
{
    FILE* fptr;
    fptr= fopen("nummaps.txt","r");
    fscanf(fptr,"%d",&number_of_maps);
    fclose(fptr);
}///general
void write_number_of_maps()
{
    FILE* fptr;
    fptr= fopen("nummaps.txt","w");
    fprintf(fptr,"%d",number_of_maps);
    fclose(fptr);
}///general

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
}///general
void soundplay(SDL_Event ev){
    SDL_GetMouseState(&xCursor,&yCursor);
    if(ev.type==SDL_MOUSEBUTTONDOWN && xCursor<=1828 && xCursor>=1720 &&yCursor<=138 && yCursor>=30)
    {
        sound=!sound;
    }
}///general
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
}///general

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
}///general
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
}///general
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
}///general

void show_text(SDL_Renderer *renderer,int x,int y,const char * text,int font_size,int R,int G,int B, int A)
{
    TTF_Init();
    SDL_Color text_color = { R, G, B, A};
    int mWidth = 0;
    int mHeight = 0;
    TTF_Font *gFont = NULL;
    SDL_Texture* mTexture = NULL;
    gFont = TTF_OpenFont("font.ttf", font_size );
    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont,text, text_color );

    mWidth = textSurface->w;
    mHeight = textSurface->h;
    mTexture = SDL_CreateTextureFromSurface( renderer, textSurface );

    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    SDL_RenderCopyEx( renderer, mTexture, NULL, &renderQuad, 0, NULL, SDL_FLIP_NONE );

    SDL_FreeSurface( textSurface );
    SDL_DestroyTexture( mTexture );
    TTF_CloseFont(gFont);
}///general
void txtRGBA(SDL_Renderer *renderer,int x,int y,const char * text,int font_size,int R,int G,int B, int A)
{
    SDL_GetMouseState(&xCursor,&yCursor);
    roundedBoxRGBA(renderer,x-50,y-50,x+450,y+150,90,61,61,61,255);
    roundedBoxRGBA(renderer,x,y,x+400,y+100,90,78,78,78,255);
    x+=75;
    y+=20;
    TTF_Init();
    SDL_Color text_color = { R, G, B, A};
    int mWidth = 0;
    int mHeight = 0;
    TTF_Font *gFont = NULL;
    SDL_Texture* mTexture = NULL;
    gFont = TTF_OpenFont("font.ttf", font_size );
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
    }
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    SDL_RenderCopyEx( renderer, mTexture, NULL, &renderQuad, 0, NULL, SDL_FLIP_NONE );

    SDL_DestroyTexture( mTexture );
    SDL_FreeSurface( textSurface );
    TTF_CloseFont(gFont);
}///general

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

}///general

char inputs_string(SDL_Event ev){
    char ch;
    if(ev.type==SDL_KEYUP)
    {
        ch = (char)ev.key.keysym.sym;
        return ch;
    }
}///general

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
}///general
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
} ///general
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
}///general
bool LEADERBOARDback(SDL_Event ev)
{
    SDL_GetMouseState(&xCursor,&yCursor);
    if(ev.type==SDL_MOUSEBUTTONDOWN && xCursor<=1828 && xCursor>=1720 &&yCursor<=138 && yCursor>=30)
    {
        return true;
    } else
        return false;
}  ///general