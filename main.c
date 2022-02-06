#include "functions.h"
#include "default_funcs.h"
int main()
{
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

      menu();
  }


    Mix_Quit();
    SDL_Quit();

    return 0;

}

