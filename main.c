#include "functions.h"

int main()
{
    /////////////////
    for(int i=0;i<NUM_POTOION;i++)
    {
        pot[i].x=-1;
        pot[i].y=-1;
        pot[i].exist=false;
        pot[i].runnig=false;
        pot[i].index=-1;
    }
    declareclr();
    for(int i=0;i<NUM_WAR;i++)
        wars[i].head=(struct soldier*)malloc(sizeof(struct soldier));
    for(int i=0;i<NUM_WAR;i++)
    {
        wars[i].head->next=NULL;
        wars[i].head->x=0;
    }
    ////////////////
    //new_game();
    //intro();
   first_page();
  // menu();
  // map(-2);
  // return 0;
  while(run_menu)
  {
      run_menu=false;
      menu();
  }

}