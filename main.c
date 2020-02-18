#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <math.h>
#include "config.c"
#include "make_gems.c"   //ジェム初期設定、表示
#include "move_gem.c"    //ジェム移動
#include "combo_count.c" //コンボ数集計
#include "battle.c"      //バトルシーン処理
#include "map.c"         //map移動処理
#include "exp_count.c"    //経験値処理
#include "make_party.c"

#define QUIT_CHAR 0x04 /* CTRL-D を押すと終了する．*/ 

int main(void)
{
  my_monster box[7] = {{"青龍", 1, 100, 100, 100, 10, '@', 0, 0, 10}, //名前 レベル hp 最大hp 攻撃力 回復力 属性 属性クラス 経験値 経験値上限
                  {"朱雀" ,1, 100, 200, 200, 20, '&', 1, 0, 200},
                  {"玄武", 1, 100, 100, 300, 30, '#', 2, 0, 300},
                  {"白虎", 1, 100, 200, 400, 40, '*', 3, 0, 400},
                  {"NO"},
                  {"NO"},
                  {"NO"},
                 };

  enemy first_enemys[3] = {{"スライム", 500,  50, '@'},
                           {"ゴブリン", 1000, 80, '#'},
                           {"ドラゴン", 5000, 100,'&'}  
                          };

  enemy enemys[3] = {{"スライム", 500,  50, '@', 30},
                     {"ゴブリン", 1000, 80, '#', 60},
                     {"ドラゴン", 5000, 100,'&', 100}
                    };

  char map[10][10] = {{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
                      {'#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
                      {'#', ' ', '#', ' ', '#', '#', '#', '#', '#', '#'},
                      {'#', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', '#'},
                      {'#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', '#'},
                      {'#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', '#'},
                      {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', '#'},
                      {'#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', '#'},
                      {'#', ' ', '#', ' ', '#', '#', '#', ' ', ' ', 'G'},
                      {'#', 'P', '#', '#', '#', '#', '#', '#', '#', '#'},
                     };

  char gems[14]={0};
  char copy_gems[14] = {0}; //ジェムのラスト3つだけが消えた場合の重複を避けるため
  //char gems[14] = {'H','H','*','@','*','*','*','@','*','#','#','H','H','H'}; //テスト用
  int start_gem = 0; //移動させるジェムの番地
  int end_gem = 0;   //移動先の番地
  int combo=0;       //コンボ数用変数
  int start_index[4] = {0}; //ドロップさせるジェムの最初の位置確保用
  int end_index[4] = {0};   //ドロップさせるジェムの最後の位置確保用
  int start_pack = 0;       //移動させるジェムの最初の位置確保
  int end_pack = 0;         //移動させるジェムの最後の位置確保
  int display_flg = 0;      //ジェム配列を表示するかしないかを管理するフラグ

  int p_pos_x = 1;          //プレイヤーのマップ上の位置(X軸)
  int p_pos_y = 9;          //プレイヤーのマップ上の位置(Y軸)

  int enemy_search =0;      //敵モンスターのインデックス
  int party[4] = {10, 10, 10, 10};

  int attacks[5] = {0};  //揃ったジェムの属性
  int pack_loop = 0;

  printf("  ゲームスタート\n");
  printf("\n");
  sleep(1);
  while (1)
  {
    enemy_search = monster_earch(map, &p_pos_x, &p_pos_y);
    printf("  %sがあらわれた!!\n", enemys[enemy_search].name);
    printf("\n");
    sleep(1);
    printf("  %s{属性: %c  HP: %d/%d AP: %d}\n", enemys[enemy_search].name, enemys[enemy_search].property,  
                       enemys[enemy_search].hp, first_enemys[enemy_search].hp, enemys[enemy_search].attack);

    printf("\n");
    sleep(1);
    chose_monster(box, party);

    while (1)
    {
      printf("  敵\n");
      printf("  %s{属性: %c  HP: %d/%d AP: %d}\n", enemys[enemy_search].name, enemys[enemy_search].property,
                       enemys[enemy_search].hp, first_enemys[enemy_search].hp, enemys[enemy_search].attack);

      printf("\n");
      sleep(1);
      printf("  パーティ\n");
      for (int i=0; i<4; i++)
      {
        if (box[party[i]].hp == 0)
        {
          printf("  \x1b[44m\x1b[30m%s{レベル: %2d 属性: %c  HP: %3d/%3d AP: %4d}\033[m\x1b[m\n", 
                         box[party[i]].name, box[party[i]].revel, box[party[i]].property,
                         box[party[i]].hp, box[party[i]].max_hp, box[party[i]].attack);
        }
        else
        {
          printf("  %s{レベル: %2d 属性: %c  HP: %3d/%3d AP: %4d}\n", 
                         box[party[i]].name, box[party[i]].revel, box[party[i]].property, 
                         box[party[i]].hp, box[party[i]].max_hp,  box[party[i]].attack);
        }
      }
      printf("\n");
      sleep(1);
      
      make_Gems(gems);
      display_gems(gems, sizeof(gems)/sizeof(gems[0]), 1);
      choice_gem(&start_gem, &end_gem);

      move_gems(gems, &start_gem, &end_gem);
      while(combo_count(gems, start_index, end_index, attacks, 0) != 0)
      {
        combo += combo_count(gems, start_index, end_index, attacks, 1);
        for (int i=0; i<4; i++)
        {
          gem_drop(gems,start_index, end_index, i);
          if (start_index[i]!=0 && end_index[i] !=0)
          {
            display_gems(gems, sizeof(gems)/sizeof(gems[0]), 0);
            sleep(1);
          }
          start_index[i] = 0;
          end_index[i] = 0;
        }
        memcpy(copy_gems, gems, 14);
        gem_pack(gems);
        for (int i=0; i<14; i++)
        {
          if (copy_gems[i] != gems[i])
          {
            display_flg = 1;
          }
        }
        if (display_flg == 1)
        {
          display_gems(gems, sizeof(gems)/sizeof(gems[0]), 0);
          //printf("\n");
          sleep(1);
        }
        display_flg = 0;
      }
      if (combo == 0)
      {
        printf("\n");
        printf("  0コンボ\n");
        printf("\n");
        sleep(1);
      }
      else
      {
        printf("  @:%d &:%d #:%d *:%d H:%d\n", attacks[0], attacks[1], attacks[2], attacks[3], attacks[4]);
        printf("\n");
        sleep(1);
        your_turn(box, enemys, attacks, party, &enemy_search);
        if(attacks[4] >=1)
        {
          hp_hearing(box, party, attacks);
        }
        combo = 0;
        if (enemys[enemy_search].hp <= 0)
        {
          if (enemy_search == 2)
          {
            printf("  ボスを倒した!!\n");
            printf("\n");
            sleep(1);
            printf("  あなたの勝ちです!!\n");
            sleep(1);
            printf("  ゲームを終了します...\n");
            return 0;
          }
          else
          {
            printf("  %sを倒した!!\n", enemys[enemy_search].name);
            printf("\n");
            sleep(2);
            get_exp(box, enemys, party, &enemy_search);
            enemys[enemy_search].hp = first_enemys[enemy_search].hp;            
            break;
          }
        }
      }
      earmy_turn(enemys, box, party, &enemy_search);
      if (box[party[0]].hp <= 0 && box[party[1]].hp <= 0 && box[party[2]].hp <= 0 && box[party[3]].hp <= 0)
      {
        printf("  あなたの負けです\n");
        printf("\n");
        printf("  ゲームオーバー...\n");
        sleep(1);
        return 0;
      }
    }
  }
}
