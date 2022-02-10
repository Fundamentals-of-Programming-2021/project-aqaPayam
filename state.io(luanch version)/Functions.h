
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
}//first page

int readfileforleaderboardandsort(struct line lines[]){
    struct person all[500];
    int number_player=0;
    char temp[5];
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
        if (c == '\n')
            continue;
        int counter = 0;
        while (c != '\n') {
            tempname[counter] = c;
            counter++;
            fscanf(fptr, "%c", &c);
        }
        tempname[counter] = '\0';
        fscanf(fptr, " %d %d", &win, &lose);
        fscanf(fptr, "%c", &c); /// for enter


        strcpy(all[number_player].name, tempname);
        all[number_player].win = win;
        all[number_player].lose = lose;

        number_player++;
    }
    fclose(fptr);

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
    // sort
    for(int i=0;i<number_player;i++)
    {
        numberTOstring(all[i].win,lines[i].win);
        numberTOstring(all[i].lose,lines[i].lose);
        strcpy(lines[i].name,all[i].name);
        numberTOstring(i+1,lines[i].place);
        numberTOstring(3*all[i].win-all[i].lose,lines[i].point);
    }
    return number_player;
}///leaderboard
void boxleaderboard(SDL_Renderer * renderer,int x,int y,struct line khat,int R,int G,int B, int A)
{
    roundedBoxRGBA(renderer,x,y,x+1600,y+100,80,80,80,80,255);
    x+=75;
    y+=20;
    show_text(renderer,x+10,y-20,khat.place,70,255,0,0,255);
    show_text(renderer,x+350,y,khat.name,50,255,255,255,255);
    show_text(renderer,x+800,y,khat.win,50,0,255,0,255);
    show_text(renderer,x+1050,y,khat.lose,50,0,0,255,255);
    show_text(renderer,x+1300,y,khat.point,50,255,255,255,255);

}///leaderboard
void delete_leaderboard_data()
{
    remove("names.txt");
    FILE *fptr;
    fptr= fopen("names.txt","w");
    fprintf(fptr,"%s\n0 0\n",name);
    fprintf(fptr,"AI one\n0 0\n");
    fprintf(fptr,"AI two\n0 0\n");
    fprintf(fptr,"AI three\n0 0\n");
    fclose(fptr);
}///leaderboard
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
                "Are you sure you want to delete leaderboard data ?", /* .message */
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
}///leaderboard

int which_map_selected(SDL_Event ev,int scrol)
{
    if(ev.type==SDL_MOUSEBUTTONDOWN)
    {
        SDL_GetMouseState(&xCursor,&yCursor);
        how_many_maps();
        for(int i=0;i<number_of_maps;i++)
        {
            if(xCursor>=800 && xCursor<=960+800 && yCursor>=scrol+600*i && yCursor<=scrol+600*i+540)
            {
                return i;
            }
        }
    }
    return -1;
}///select map
void delete_all_maps()
{
    how_many_maps();
    for(int i=2;i<number_of_maps;i++)
    {
        char endname[10];
        numberTOstring(i,endname);
        char mamad[50]="screenshot";
        strcat(mamad,endname);
        strcat(mamad,".bmp");
        remove(mamad);

        strcpy(mamad,"saved");
        strcat(mamad,endname);
        strcat(mamad,".txt");
        remove(mamad);

        strcpy(mamad,"arr_colors");
        strcat(mamad,endname);
        strcat(mamad,".txt");
        remove(mamad);
    }

    FILE * fptr=fopen("nummaps.txt","w");
    fprintf(fptr,"%d",2);
    fclose(fptr);
}///select map
bool check_delete_maps(SDL_Event ev)
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
                "Are you sure you want to delete all maps ?", /* .message */
                SDL_arraysize(buttons), /* .numbuttons */
                buttons, /* .buttons */
                &colorScheme /* .colorScheme */
        };
        int buttonid=-1;
        SDL_ShowMessageBox(&messageboxdata, &buttonid);
        if(buttonid==0)
        {
            delete_all_maps();
            return true;
        }
    }
    return false;
}///select map

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
        SDL_Surface *imgg = SDL_LoadBMP("hint.bmp");
        if (!img)
            printf("ridi  %s", SDL_GetError());
        SDL_Rect placee = {.x=-150, .y=130, .w=960*1.5, .h=540*1.5};
        SDL_Texture *texture_hitlerr = SDL_CreateTextureFromSurface(renderer, imgg);
        SDL_RenderCopy(renderer, texture_hitlerr, NULL, &placee);
        SDL_FreeSurface(imgg);
        SDL_DestroyTexture(texture_hitlerr);
    }
}///menu
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
}///menu
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
}///menu


bool leaderboard()
{
    SDL_Surface* iimage = SDL_LoadBMP("leaderboard.bmp");
    if (!iimage)
        printf("ridi %s", SDL_GetError());
    SDL_Texture *ttexture = SDL_CreateTextureFromSurface(renderer, iimage);

    int scroll=100;
    struct line lines[500];
    struct line first;
    strcpy(first.place,"PLACE");
    strcpy(first.name,"NAME");
    strcpy(first.win,"WINS");
    strcpy(first.lose,"LOSES");
    strcpy(first.point,"POINT");
    while (game_is_running)
    {
        int number_player = readfileforleaderboardandsort(lines);
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
            check_delete_leaderboard(event);
            check_exit_game(event);
            if(event.type == SDL_MOUSEWHEEL)
            {
                if(event.wheel.y<0 && scroll <100)
                {
                    scroll+=20;
                }
                if(event.wheel.y>0 && scroll > number_player*-200+800)
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
    return false ;
}
bool map(int which)
{
    int blockclicked1=-1;
    int blockclicked2=-1;
    if (which==-1)
        generaterandomblock();
    else if(which==-2)
        load_az_ghabl_continue();
    else
        load_azghabl(which);

    music = Mix_LoadMUS("music_war2.mp3");
    Mix_Music *warningmusic=Mix_LoadMUS("potionmusic.mp3");
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
    SDL_SetTextureAlphaMod(warningtxt,150);

    Mix_PlayMusic(music,-1);
    bool take_screen_shot=true;
    int tempcounter=0;
    bool tempshow=false;
    while (game_is_running)
    {
        if (counterFPS == 9223372036854775807)
            counterFPS = 0;
        if (countai == 9223372036854775807)
            countai = 0;
        counterFPS++;
        SDL_RenderCopy(renderer, texture, NULL, &texture_rect);
        SDL_ShowCursor(SDL_DISABLE);
        render_blocks(number_of_block, arr_of_colors, arr_of_block,pot);
        if(take_screen_shot && which==-1)
        {
            SDL_RenderPresent(renderer);
            screenshot();
            take_screen_shot=false;
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, NULL, &texture_rect);
            SDL_ShowCursor(SDL_DISABLE);
            render_blocks(number_of_block, arr_of_colors, arr_of_block,pot);
        }
        while (SDL_PollEvent(&event))
        {
            blockclicked2 = which_block_clicked(arr_of_block, number_of_block, event);
            soundplay(event);
            check_exit_game(event);
            save(event);
        }
        moving_soldiers(wars, arr_of_block);
        check_to_active_potion(pot, wars);
        ////
        if (ai_potion == true)
        {
            tempshow=true;
            tempcounter=0;
        }
        ai_potion = false;
        if(tempshow && tempcounter<timeactivepotion)
        {
            SDL_RenderCopy(renderer, warningtxt, NULL, &texture_rect);
            tempcounter++;
        }
        if(tempcounter>=timeactivepotion)
        {
            tempcounter=0;
            tempshow=false;
        }
        if (your_potion == true) {
            Mix_PlayMusic(warningmusic, 1);
        }
        your_potion = false;
        if (!Mix_PlayingMusic())
            Mix_PlayMusic(music, -1);
        ///
        run_potion(pot, wars, arr_of_block, number_of_block);
        render_potion(pot);
        render_soldier(wars, number_of_attack, arr_of_colors, arr_of_block);
        show_save();
        showcursorandsound();
        if(saveandexit){
            saveexit(which);
            free(arr_of_block);
            free(arr_of_colors);
            Mix_FreeMusic(music);
            Mix_FreeMusic(warningmusic);
            SDL_FreeSurface(image);
            SDL_FreeSurface(warningimg);
            SDL_DestroyTexture(texture);
            SDL_DestroyTexture(warningtxt);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            return true;
        } //inja bayad bazi save va baste beshe
        if(blockclicked1 != -1 && blockclicked2 == -1)
        {
            rasm_khat(arr_of_block,blockclicked1);
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / FPS);
        SDL_RenderClear(renderer);
        if (counterFPS % 30 == 0){
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
        }//har 1 sanie ba ehtemal kamtar az 50% potion toolid she
        if (counterFPS % 60 == 0) {
            for (int i = 0; i < number_of_block; i++) {
                if (arr_of_block[i].index != -1) {
                    if (arr_of_block[i].nolimit == true && arr_of_block[i].fastblock == true) {
                        arr_of_block[i].number_soldier += 5;
                        arr_of_block[i].number_soldier2 += 5;
                    } else if (arr_of_block[i].nolimit == true && arr_of_block[i].fastblock == false) {
                        arr_of_block[i].number_soldier++;
                        arr_of_block[i].number_soldier2++;
                    } else if (arr_of_block[i].nolimit == false && arr_of_block[i].fastblock == true) {
                        if (arr_of_block[i].number_soldier < max_sarbaz) {
                            arr_of_block[i].number_soldier += 5;
                            arr_of_block[i].number_soldier2 += 5;
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
                if (blockclicked2 != blockclicked1 && arr_of_block[blockclicked1].index ==0 ) {
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
            if (fps_potion[i] > timeexistpotion && pot[i].runnig == false)
            {
                pot[i].exist = false;
                pot[i].runnig = false;
            }
            if (fps_potion[i] > timeactivepotion && pot[i].runnig == true)
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
        if (counterFPS % timeAIattack==0 )
        {
            countai++;
            if(countai%6==0)
                AIatack = AI1(arr_of_block, number_of_block);
            else if(countai %6==1)
                AIatack = AI2(arr_of_block, number_of_block);
            else if(countai %6==2)
                AIatack = AI3(arr_of_block, number_of_block);
            else if(countai %6==3)
                AIatack = AI4(arr_of_block, number_of_block);
            else if(countai %6==4)
                AIatack = AI5(arr_of_block, number_of_block);
            else if(countai %6==5)
                AIatack = AI6(arr_of_block, number_of_block);
            if (AIatack.x != -1 && AIatack.y != -1)
            {
                wars[number_of_attack%NUM_WAR].def = AIatack.y;
                wars[number_of_attack%NUM_WAR].att = AIatack.x;
                wars[number_of_attack%NUM_WAR].num_soldier = arr_of_block[AIatack.x].number_soldier2;
                arr_of_block[AIatack.x].number_soldier2 = 0;
                wars[number_of_attack%NUM_WAR].counter = 0;
                number_of_attack++;
            }
        }  //AI
        if (win(arr_of_block,number_of_block,wars,number_of_attack))
        {
            if(which==-1)
                delete_last_map_save();
            write_win_to_file();
            for(int i=0;i<3;i++)
                write_loseAI_to_file(i);
            Mix_PauseMusic();
            SDL_DestroyTexture(texture);
            SDL_FreeSurface(image);
            image= IMG_Load("win.jpg");
            texture= SDL_CreateTextureFromSurface(renderer,image);
            SDL_RenderCopy(renderer,texture,NULL,&texture_rect);
            if(strcmp(name,""))
                show_text(renderer,50,50,name,120,0,255,0,255);
            show_text(renderer,50,170,"WIN",120,0,255,0,255);
            show_text(renderer,50,710,"HITLER NARAHAT SHOD",120,255,0,0,255);
            SDL_RenderPresent(renderer);
            SDL_Delay(5000);
            free(arr_of_block);
            free(arr_of_colors);
            Mix_FreeMusic(music);
            Mix_FreeMusic(warningmusic);
            SDL_FreeSurface(image);
            SDL_FreeSurface(warningimg);
            SDL_DestroyTexture(texture);
            SDL_DestroyTexture(warningtxt);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            run_menu=true;
            return true;
        }
        if(lose(arr_of_block,number_of_block,wars,number_of_attack))
        {
            if(which==-1)
                delete_last_map_save();
            time_t t;
            srand((unsigned) time(&t));
            write_winAI_to_file(rand()%3);
            write_lose_to_file();

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(image);
            image= IMG_Load("lose.jpg");
            texture= SDL_CreateTextureFromSurface(renderer,image);
            SDL_RenderCopy(renderer,texture,NULL,&texture_rect);
            if(strcmp(name,""))
                show_text(renderer,50,50,name,120,255,0,0,255);
            show_text(renderer,50,170,"LOST",120,255,0,0,255);
            show_text(renderer,50,710,"HITLER KHOSHAL SHOD",120,255,0,0,255);
            SDL_RenderPresent(renderer);
            Mix_PauseMusic();
            SDL_Delay(5000);

            free(arr_of_block);
            free(arr_of_colors);
            Mix_FreeMusic(music);
            Mix_FreeMusic(warningmusic);
            SDL_FreeSurface(image);
            SDL_FreeSurface(warningimg);
            SDL_DestroyTexture(texture);
            SDL_DestroyTexture(warningtxt);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            run_menu=true;
            return true;
        }
    }

    if(which==-1)
        delete_last_map_save();

    free(arr_of_block);
    free(arr_of_colors);
    Mix_FreeMusic(music);
    Mix_FreeMusic(warningmusic);
    SDL_FreeSurface(image);
    SDL_FreeSurface(warningimg);
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(warningtxt);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return false;
}
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
    int scroll=100;
    while (game_is_running)
    {
        how_many_maps();
        SDL_RenderCopy(renderer, texture, NULL, &texture_rect);
        show_text(renderer,0,0,name_used_in_menu,60,255,0,0,255);
        SDL_ShowCursor(SDL_DISABLE);
        for(int i=0;i<number_of_maps;i++)
        {
            char endname[10];
            numberTOstring(i,endname);
            char mamad[50]="screenshot";
            strcat(mamad,endname);
            strcat(mamad,".bmp");
            SDL_Surface *temp= SDL_LoadBMP(mamad);
            SDL_Texture *texturemap= SDL_CreateTextureFromSurface(renderer,temp);
            SDL_Rect pos;
            pos.x=800;
            pos.y=scroll+600*i;
            pos.w=960;
            pos.h=540;
            SDL_RenderCopy(renderer,texturemap,NULL,&pos);
            SDL_FreeSurface(temp);
            SDL_DestroyTexture(texturemap);
            SDL_RectEmpty(&pos);
        }
        while(SDL_PollEvent(&event))
        {
            if(LEADERBOARDback(event))
            {
                return true;
            }
            if(check_delete_maps(event))
                scroll=100;
            int t=which_map_selected(event,scroll);
            if(t!=-1)
            {
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_DestroyTexture(texture);
                SDL_FreeSurface(image);
                Mix_FreeMusic(music);
                map(t);
                return false;
            }
            check_exit_game(event);
            if(event.type == SDL_MOUSEWHEEL)
            {
                if(event.wheel.y<0 && scroll <100)
                {
                    scroll+=20;
                }
                if(event.wheel.y>0 && scroll > (-1)*(600*(number_of_maps-1)-300))
                {
                    scroll-=20;
                }
            }
        }
        show_delete_leaderborad();
        showcursorandsoundLEADERBOARD();
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / FPS);
        SDL_RenderClear(renderer);
    }
    return false ;
}  //
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
    return false ;
}  ///
void menu(){
    strcat(name_used_in_menu,name);
    music= Mix_LoadMUS("music.mp3");

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
                }
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
                else
                {
                    fclose(fptr);
                    SDL_DestroyRenderer(renderer);
                    SDL_DestroyWindow(window);
                    SDL_DestroyTexture(texture);
                    SDL_FreeSurface(image);
                    Mix_FreeMusic(music);
                    map(-2);
                    return ;
                }
            }
            if(click_ranking(event))
            {
                if(!leaderboard())
                {
                    SDL_DestroyRenderer(renderer);
                    SDL_DestroyWindow(window);
                    SDL_DestroyTexture(texture);
                    SDL_FreeSurface(image);
                    Mix_FreeMusic(music);
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
    return ;
}  //
void intro()
{
    music= Mix_LoadMUS("m3.mp3");
    window = SDL_CreateWindow("intro", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    SDL_SetWindowBordered(window, SDL_WINDOW_FULLSCREEN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    char ch[20]="";
    char namep[30]="";
    Mix_PlayMusic(music,1);
    for (int i = 1; i <= 855; i++)
    {
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
            check_exit_game(event);
        }
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
    return;
}  //
void first_page()
{
    music= Mix_LoadMUS("music_first.mp3");
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
        if(game_is_running) {
            while (SDL_PollEvent(&event)) {
                check_exit_game(event);
            }
            SDL_SetTextureAlphaMod(txt, i);
            SDL_RenderCopy(renderer, txt, NULL, &texture_rect);
            SDL_RenderPresent(renderer);
            SDL_RenderClear(renderer);
            SDL_Delay(1000 / FPS);
        }
    }
    if(game_is_running) {
        SDL_SetTextureAlphaMod(txt, 255);
        SDL_RenderCopy(renderer, txt, NULL, &texture_rect);
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        SDL_Delay(500);
        Mix_PlayMusic(music, -1);
    }
    for(int i=255;i>=0;i--)
    {
        if(game_is_running)
        {
            while (SDL_PollEvent(&event)) {
                check_exit_game(event);
            }
            SDL_SetTextureAlphaMod(txt, i);
            SDL_RenderCopy(renderer, txt, NULL, &texture_rect);
            SDL_RenderPresent(renderer);
            SDL_RenderClear(renderer);
            SDL_Delay(1000 / FPS);
        }
    }
    SDL_FreeSurface(war_first);
    SDL_DestroyTexture(txt);
    //////////////////////////////////
    while(tool < imagegame->w /2 && game_is_running)
    {
        SDL_ShowCursor(SDL_DISABLE);
        SDL_RenderCopy(renderer, texture, NULL, &texture_rect);
        show_text(renderer,30,30,"LOADING PLEASE WAIT ..",60,0,0,0,255);
        temp_rect.x=centerx-tool/2;
        temp_rect.y=centery-arz/2;
        temp_rect.w=tool;
        temp_rect.h=arz;
        tool+=2;
        arz+=2;
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
        show_text(renderer, 30, 30, "PLEASE ENTER YOUR NAME", 50, 255, 0, 90, temp99);
        show_text(renderer, 30, 80, "THEN PRESS ENTER :", 50, 255, 0, 90, temp99);
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
        show_text(renderer, 30, 30, "PLEASE ENTER YOUR NAME", 50, 255, 0, 90, 255);
        show_text(renderer, 30, 80, "THEN PRESS ENTER :", 50, 255, 0, 90, 255);
        roundedBoxRGBA(renderer,40,150,600,220,10,255,255,255,170);
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
                SDL_DestroyTexture(texture);
                SDL_FreeSurface(image);
                SDL_FreeSurface(imagegame);
                SDL_DestroyTexture(texturegame);
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                Mix_FreeMusic(music);
                if(new_user)
                {
                    intro();
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
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    SDL_FreeSurface(imagegame);
    SDL_DestroyTexture(texturegame);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_FreeMusic(music);
    return;
}  //

