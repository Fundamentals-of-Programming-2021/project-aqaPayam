//
// Created by payam on 2/11/22.
//

#include "Generals.h"
#include "Generalfunc.h"
#include "Mapfunc.h"
#include "Functions.h"


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
}//map
void render_blocks(int num_block,uint32_t arr[],struct block block[],struct potion pts[])
{
    SDL_Surface *image_block_por = SDL_LoadBMP("block_por.bmp");
    if (!image_block_por)
        printf("ridi %s", SDL_GetError());
    SDL_Texture *texture_block_por = SDL_CreateTextureFromSurface(renderer, image_block_por);

    SDL_Surface *image_block_khali = SDL_LoadBMP("block_khali.bmp");
    if (!image_block_khali)
        printf("ridi %s", SDL_GetError());
    SDL_Texture *texture_block_khali = SDL_CreateTextureFromSurface(renderer, image_block_khali);

    SDL_Surface *image_block_active = IMG_Load("activatedblocl.png");
    if (!image_block_khali)
        printf("ridi %s", SDL_GetError());
    SDL_Texture *texture_block_active = SDL_CreateTextureFromSurface(renderer, image_block_active);

    for(int i=0;i<num_block;i++)
    {
        if (block[i].index==-1)
        {
            SDL_Rect rect={.x=block[i].xpos-100, .y=block[i].ypos-100,.w=200,.h=200};
            SDL_RenderCopy(renderer,texture_block_khali,NULL,&rect);
            if(number_to_string(block[i].number_soldier)==1)
                show_text(renderer,block[i].xpos-15,block[i].ypos+10,temp_of_function_numberToString,40,0,255,0,255);
            else if(number_to_string(block[i].number_soldier)==2)
                show_text(renderer,block[i].xpos-25,block[i].ypos+10,temp_of_function_numberToString,40,0,0,255,255);
            else if(number_to_string(block[i].number_soldier)==3)
                show_text(renderer,block[i].xpos-35,block[i].ypos+10,temp_of_function_numberToString,40,255,0,0,255);
        }
        else {
            bool active = false;
            for (int j = 0; j < NUM_POTOION; j++)
            {
                if (pts[j].index == block[i].index && pts[j].exist == true && pts[j].runnig == true) {
                    active = true;
                    break;
                }
            }
            if(active)
            {
                SDL_Rect rect={.x=block[i].xpos-100, .y=block[i].ypos-100,.w=200,.h=200};
                filledCircleColor(renderer, block[i].xpos, block[i].ypos, 100, arr[block[i].index]);
                SDL_RenderCopy(renderer,texture_block_active,NULL,&rect);
                if(number_to_string(block[i].number_soldier)==1)
                    show_text(renderer,block[i].xpos-15,block[i].ypos+5,temp_of_function_numberToString,50,0,255,0,255);
                else if(number_to_string(block[i].number_soldier)==2)
                    show_text(renderer,block[i].xpos-30,block[i].ypos+5,temp_of_function_numberToString,50,0,0,255,255);
                else if(number_to_string(block[i].number_soldier)==3)
                    show_text(renderer,block[i].xpos-44,block[i].ypos+5,temp_of_function_numberToString,50,255,0,0,255);
            }
            else
            {
                SDL_Rect rect={.x=block[i].xpos-100, .y=block[i].ypos-100,.w=200,.h=200};
                filledCircleColor(renderer, block[i].xpos, block[i].ypos, 100, arr[block[i].index]);
                SDL_RenderCopy(renderer,texture_block_por,NULL,&rect);
                if(number_to_string(block[i].number_soldier)==1)
                    show_text(renderer,block[i].xpos-15,block[i].ypos+5,temp_of_function_numberToString,50,0,255,0,255);
                else if(number_to_string(block[i].number_soldier)==2)
                    show_text(renderer,block[i].xpos-30,block[i].ypos+5,temp_of_function_numberToString,50,0,0,255,255);
                else if(number_to_string(block[i].number_soldier)==3)
                    show_text(renderer,block[i].xpos-44,block[i].ypos+5,temp_of_function_numberToString,50,255,0,0,255);

            }
        }
    }
    SDL_FreeSurface(image_block_por);
    SDL_FreeSurface(image_block_khali);
    SDL_FreeSurface(image_block_active);
    SDL_DestroyTexture(texture_block_khali);
    SDL_DestroyTexture(texture_block_por);
    SDL_DestroyTexture(texture_block_active);

}///map
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
} //map
void render_soldier(struct warstatus war[],int number_of_war,uint32_t arr_color[],struct block blocks[])
{
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

    SDL_Texture *temp;
    for(int i=0;i<number_of_war;i++)
    {
        struct soldier * current= war[i%NUM_WAR].head;
        while(current->next!=NULL)
        {
            if ( arr_color[current->index] == clr[0])
                temp = texture_soldier[0];
            else if ( arr_color[current->index]  == clr[1])
                temp=texture_soldier[1];
            else if (arr_color[current->index] == clr[2])
                temp=texture_soldier[2];
            else if (arr_color[current->index] == clr[3])
                temp=texture_soldier[3];
            else if (arr_color[current->index] == clr[4])
                temp=texture_soldier[4];
            else if (arr_color[current->index] == clr[5])
                temp=texture_soldier[5];
            else if (arr_color[current->index] == clr[6])
                temp=texture_soldier[6];
            else if (arr_color[current->index] == clr[7])
                temp=texture_soldier[7];
            else if (arr_color[current->index] == clr[8])
                temp=texture_soldier[8];
            else if (arr_color[current->index] == clr[9])
                temp=texture_soldier[9];

            SDL_Rect texture_soldier={.x=current->x-25,.y=current->y-25,.w=50,.h=50};
            SDL_RenderCopy(renderer,temp,NULL,&texture_soldier);
            current=current->next;
        }
    }
    for(int i=0;i<10;i++)
    {
        SDL_DestroyTexture(texture_soldier[i]);
        SDL_FreeSurface(image_soldier[i]);
    }
} //map
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
}//map
bool is_same_soldier(struct soldier a,struct soldier b)
{
    if(a.x==b.x && a.y==b.y && a.vx==b.vx && a.vy==b.vy)
        return true;
    else
        return false;
}///map
int delete_soldier(struct soldier dest_for_delete,struct soldier ** head)
{
    struct  soldier *current = (*head);
    if (is_same_soldier(*current,dest_for_delete))
    {
        struct soldier *temp= (*head)->next;
        free(*head);
        *head=temp;
        ///
        // (*head) = (*head)->next;
        return 1;
    }
    while(current->next!=NULL)
    {
        if (is_same_soldier(*(current->next),dest_for_delete))
        {
            struct soldier *temp= current->next->next;
            free(current->next);
            current->next = temp;
            /// current->next = current->next->next;
            return 1;
        }
        current=current->next;
    }
    return 0;//in sarbaz vojood nadasht
}//map
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
                        arr_block[current->num_dest_block].nolimit=false;
                        arr_block[current->num_dest_block].fastblock=false;
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
}//map
void generate_all_wars_soldiers(struct warstatus war[],int number_of_wars,struct block arr_of_blocks[])
{
    for(int i=0;i<number_of_wars;i++)
    {
        if( arr_of_blocks[war[i%NUM_WAR].att].number_soldier == 0)
        {
            war[i%NUM_WAR].num_soldier=0;
        }
        if (war[i%NUM_WAR].counter < war[i%NUM_WAR].num_soldier)
        {
            generate_one_soldier_end_of_list(war[i%NUM_WAR].head,&arr_of_blocks[war[i%NUM_WAR].att],arr_of_blocks[war[i%NUM_WAR].def],war[i%NUM_WAR].def,war[i%NUM_WAR].att);
            war[i%NUM_WAR].counter+=1;
        }
    }
}//map
struct axis generate_random_potion(struct block arr_block[],int num_block)
{
    time_t t;
    srand((unsigned) time(&t));
    int a=rand() % num_block;
    int b=rand() % num_block;
    while(arr_block[a].index == -1 || arr_block[b].index == -1)
    {
        a=rand() % num_block;
        while(b==a)
            b=rand() % num_block;
    }
    if(arr_block[a].index>0 && arr_block[b].index>0)
    {
        temp1 = a;
        temp2 = b;
    }

    ////
    double num;
    int k=rand()%60;
    k+=20;
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
}//map
void render_potion(struct potion all[])
{
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

    for(int i=0;i<NUM_POTOION;i++)
    {
        if(all[i].exist==true && all[i].runnig==false)
        {
            SDL_Rect temp={.x=all[i].x-60,.y=all[i].y-60,.h=120,.w=120};
            SDL_RenderCopy(renderer,texture_potionD[i%4],NULL,&temp);
        }
        if(all[i].exist==true && all[i].runnig==true)
        {
            SDL_Rect temp={.x=all[i].x-60,.y=all[i].y-60,.h=120,.w=120};
            SDL_RenderCopy(renderer,texture_potionA[i%4],NULL,&temp);
        }
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
}///map
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
                        bool ok=true;
                        for(int q=0;q<NUM_POTOION;q++)
                        {
                            if(all[q].runnig==true && all[q].exist==true && all[q].index==current->index)
                            {
                                ok=false;
                                break;
                            }
                        }
                        if(ok)
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
                    }
                    current = current->next;
                }
            }
        }
    }
}///map
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
}//map
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
}//map
void make_game_easy(struct block arr[])
{
    time_t t;
    srand(&t);
    if(rand()%2)
        for(int i=0;i<number_of_block;i++)
            if(arr[i].index==-1)
            {
                arr[i].index=0;
                break;
            }
    for(int i=0;i<number_of_block;i++)
        if(arr[i].index==0)
        {
            arr[i].number_soldier=20;
            arr[i].number_soldier2=20;
        }
    for(int i=0;i<number_of_block;i++)
        if(arr[i].index>0)
        {
            arr[i].number_soldier=20;
            arr[i].number_soldier2=20;
        }
}///map
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
struct axis AI5(struct block arr[],int numblock)
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
                if (arr[random_numbers[i]].index == arr[random_numbers[j]].index && arr[random_numbers[j]].number_soldier2<10)
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
}//baraye defa hamle mikone
struct axis AI6(struct block arr[],int numblock)
{
    struct axis temp;
    if(temp1!=-1 && temp2!=-1)
    {
        temp.x=temp1;
        temp.y=temp2;
        temp1=-1;
        temp2=-1;
    }
    struct axis p;
    p.x=-1;
    p.y=-1;
    return p;
}//bara gereftan majoon mire

bool win(struct block arr[],int numblock,struct warstatus war[],int numwar)
{
    bool youwin=true;
    for(int i=0;i<numblock;i++)
    {
        if(arr[i].index!=0 && arr[i].index!=-1)
            youwin=false;
    }
    for(int i=0;i<numwar;i++)
    {
        struct soldier *current=war[i%NUM_WAR].head;
        while(current->next!=NULL)
        {
            if(current->index!=0 && !isnan(current->x) )
            {
                youwin=false;
            }
            current=current->next;
        }
    }
    return youwin;
}///map
bool lose(struct block arr[],int numblock,struct warstatus war[],int numwar)
{
    bool youlose=true;
    for(int i=0;i<numblock;i++)
    {
        if(arr[i].index == 0 )
            youlose=false;
    }
    for(int i=0;i<numwar;i++)
    {
        struct soldier *current=war[i%NUM_WAR].head;
        while(current->next!=NULL)
        {
            if(current->index==0 && !isnan(current->x))
            {
                youlose=false;
            }
            current=current->next;
        }
    }
    return youlose;
}///map


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
}//map
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
}//map
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
}//map
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
}//map

void rasm_khat(struct block arr[],int att)
{
    SDL_GetMouseState(&xCursor,&yCursor);
    for(int i=-5;i!=5;i++)
        aalineRGBA(renderer,arr[att].xpos+i,arr[att].ypos+i,xCursor+i,yCursor+i,0,0,0,255);

}//map
void screenshot()
{
    char endname[10];
    how_many_maps();
    numberTOstring(number_of_maps-1,endname);
    char mamad[50]="screenshot";
    strcat(mamad,endname);
    strcat(mamad,".bmp");
    SDL_Surface *sshot = SDL_CreateRGBSurface(0, 1920, 1080, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
    SDL_SaveBMP(sshot, mamad);
    SDL_FreeSurface(sshot);
}///map
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

}///map

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
        char temp3[20]="screenshot";
        strcat(temp3,ch);
        strcat(temp3,".bmp");
        strcat(temp1,ch);
        strcat(temp1,".txt");
        strcat(temp2,ch);
        strcat(temp2,".txt");
        remove(temp1);
        remove(temp2);
        remove(temp3);
        number_of_maps--;
        write_number_of_maps();
    }
    else
        Mix_ResumeMusic();

}///map
void generaterandomblock()
{
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
}//map
void load_az_ghabl_continue()
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
            {
                break;
            }
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
}//map
void load_azghabl(int which)
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
        return ;
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
        return ;
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
    // printf("loaded\n");
}//map
void saveexit(int which)
{
    SDL_Surface *img_waiting= SDL_LoadBMP("waiting.bmp");
    if(!img_waiting)
        printf("ridi %s", SDL_GetError());
    SDL_Texture *textture_waiting= SDL_CreateTextureFromSurface(renderer,img_waiting);

    if(which==-1)
        delete_last_map_save();
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
    SDL_Delay(2500);

    SDL_DestroyTexture(textture_waiting);
    SDL_FreeSurface(img_waiting);

    run_menu=true;
}//map
