#include "generals.h"
#include "generalfunc.h"
#include "mapfunc.h"
#include "functions.h"

bool is_ok_to_run_game()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER |SDL_INIT_AUDIO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    if(Mix_Init(MIX_INIT_MP3) <0)
        return false;
    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,2,2048) < 0)
    {
        printf("%s",Mix_GetError());
        return false;
    }
    return true;
}///for main

int main()
{
    if(!is_ok_to_run_game())
        return -1;

    for (int i = 0; i < NUM_POTOION; i++) {
        pot[i].x = -1;
        pot[i].y = -1;
        pot[i].exist = false;
        pot[i].runnig = false;
        pot[i].index = -1;
    }
    declareclr();
    for (int i = 0; i < NUM_WAR; i++)
        wars[i].head = (struct soldier *) malloc(sizeof(struct soldier));
    for (int i = 0; i < NUM_WAR; i++) {
        wars[i].head->next = NULL;
        wars[i].head->x = 0;
    }

  first_page();

  while(run_menu)
  {
      for (int i = 0; i < NUM_WAR; i++)
      {
          struct soldier * temp;
          struct soldier *current=wars[i].head;
          while(current->next!=NULL)
          {
              temp=current;
              current=current->next;
              free(temp);
          }
          free(current);
      }

          for (int i = 0; i < NUM_POTOION; i++) {
              pot[i].x = -1;
              pot[i].y = -1;
              pot[i].exist = false;
              pot[i].runnig = false;
              pot[i].index = -1;
          }
          declareclr();
          for (int i = 0; i < NUM_WAR; i++)
              wars[i].head = (struct soldier *) malloc(sizeof(struct soldier));
          for (int i = 0; i < NUM_WAR; i++) {
              wars[i].head->next = NULL;
              wars[i].head->x = 0;
          }

    for(int i=0;i<NUM_POTOION;i++)
        pot[i].exist=false;

      number_of_attack=0;
      counterFPS=0;
      countai=0;
      saveandexit=false;
      your_potion=false;
      ai_potion=false;
      for(int i=0;i<NUM_POTOION;i++)
         fps_potion[i]=0;
      number_of_maps=0;
      strcpy(number,"");
      strcpy(number2,"");
      strcpy(number3,"");
      strcpy(name_used_in_menu,"welcome ");
      strcpy(temp_of_function_numberToString,"");
      game_is_running=true;
      sound=true;
      run_menu=false;
      temp1=-1;
      temp2=-1;

      menu();
  }

    for (int i = 0; i < NUM_WAR; i++)
    {
        struct soldier * temp;
        struct soldier *current=wars[i].head;
        while(current->next!=NULL)
        {
            temp=current;
            current=current->next;
            free(temp);
        }
        free(current);
    }

    Mix_Quit();
    SDL_Quit();

    return 0;

}

