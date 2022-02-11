

#ifndef STATE_IO_MAPFUNC_H
#define STATE_IO_MAPFUNC_H
#pragma once

int which_block_clicked(struct block arr_of_valid_block[],int num_of_valiv_block,SDL_Event ev);
void render_blocks(int num_block,uint32_t arr[],struct block block[],struct potion pts[]);
void make_randomcolor(uint32_t arr[],int n);
void render_soldier(struct warstatus war[],int number_of_war,uint32_t arr_color[],struct block blocks[]);
void generate_one_soldier_end_of_list(struct soldier * head,struct block* att,struct block def,int number_of_dest_block,int number_of_beg_block);
bool is_same_soldier(struct soldier a,struct soldier b);
int delete_soldier(struct soldier dest_for_delete,struct soldier ** head);
void moving_soldiers(struct warstatus war[],struct block arr_block[]);
void generate_all_wars_soldiers(struct warstatus war[],int number_of_wars,struct block arr_of_blocks[]);
struct axis generate_random_potion(struct block arr_block[],int num_block);
void render_potion(struct potion all[]);
void check_to_active_potion(struct potion all[],struct  warstatus war[]);
void run_potion(struct potion potions[],struct warstatus wars[],struct block arr_block[],int numBlock);
void deactive_potion(struct potion potions,int i,struct warstatus wars[],struct block arr_block[],int numBlock);
void make_game_easy(struct block arr[]);
struct axis AI1(struct block arr[],int numblock);
struct axis AI2(struct block arr[],int numblock);
struct axis AI3(struct block arr[],int numblock);
struct axis AI4(struct block arr[],int numblock);
struct axis AI5(struct block arr[],int numblock);
struct axis AI6(struct block arr[],int numblock);

bool win(struct block arr[],int numblock,struct warstatus war[],int numwar);
bool lose(struct block arr[],int numblock,struct warstatus war[],int numwar);


void write_win_to_file();
void write_lose_to_file();
void write_loseAI_to_file(int i);
void write_winAI_to_file(int i);

void rasm_khat(struct block arr[],int att);
void screenshot();
void save(SDL_Event ev);

void delete_last_map_save();
void generaterandomblock();
void load_az_ghabl_continue();
void load_azghabl(int which);
void saveexit(int which);


#endif //STATE_IO_MAPFUNC_H

