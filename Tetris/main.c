#include "tetris.h"

int game_table[GAME_Y][GAME_X];
int game_table_copy[GAME_Y][GAME_X];
int blocks[7][4][4][4] =
{
    {{0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0}, {0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0},
    {0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0}, {0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0}},

    {{0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0}, {0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0},
    {0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0}, {0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0}},

    {{0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0}, {0,0,0,1,0,0,1,1,0,0,1,0,0,0,0,0},
    {0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0}, {0,0,0,1,0,0,1,1,0,0,1,0,0,0,0,0}},

    {{0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0}, {0,0,1,0,0,0,1,1,0,0,0,1,0,0,0,0},
    {0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0}, {0,0,1,0,0,0,1,1,0,0,0,1,0,0,0,0}},

    {{0,0,0,0,0,1,1,1,0,1,0,0,0,0,0,0}, {0,0,1,0,0,0,1,0,0,0,1,1,0,0,0,0},
    {0,0,0,1,0,1,1,1,0,0,0,0,0,0,0,0}, {0,1,1,0,0,0,1,0,0,0,1,0,0,0,0,0}},

    {{0,0,0,0,0,1,1,1,0,0,0,1,0,0,0,0}, {0,0,1,1,0,0,1,0,0,0,1,0,0,0,0,0},
    {0,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0}, {0,0,1,0,0,0,1,0,0,1,1,0,0,0,0,0}},

    {{0,0,0,0,0,1,1,1,0,0,1,0,0,0,0,0}, {0,0,1,0,0,0,1,1,0,0,1,0,0,0,0,0},
    {0,0,1,0,0,1,1,1,0,0,0,0,0,0,0,0}, {0,0,1,0,0,1,1,0,0,0,1,0,0,0,0,0}}
};



int new_block_flag; // 새 블럭이 필요한가
int current_block; //현재 블럭 저장
int next_block; //다음 블럭 저장
int game_running; // 게임 시작했는지
int b_pos_x; // 블럭의 X,Y 좌표 및 회전 상태
int b_pos_y;
int b_rotation;
int loop = 0;
int key;
int score = 0;
int sysloop = 1;
int esc_paused = 0;
int paused = 0;
int floop = 0;
int gameover_flag = 0;
int new_color_flag = 0;
int game_speed;

int main(void)
{
    init();
    draw_title();

    while (sysloop == 1)
    {
        check_key();

        if(game_running == 1)
        {
            system("cls");
            draw_next_block();
            reset_table();
            score = 0;
            total_lines = 0;
            game_level = 1;
            line_need = 4 + game_level;
            game_speed = 12;
            random_color();
            random_color();
        }

        while(game_running == 1)
        {
            draw_ui();
            draw_table();
            check_key();
            loop++;
            if (loop >= game_speed) // 초당 약 game_speed 만큼씩 루프 증가 후 블럭 하강
            {
                block_down();
                loop = 0;
            }
            Sleep(33);
            check_line();
            check_level();
            new_block();
            check_gameover();
        }

        Sleep(33);
    }

    return 0;
}
