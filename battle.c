//プレイヤーターンの処理

void your_turn(my_monster box[7], enemy enemys[3], int attacks[5], int party[4], int* enemy_search)
{
  int enemy_hp = 0;
  int attack_point = 0;

  for (int i=0; i<4; i++)
  {
    if (attacks[i] >= 1)
    {
      for (int j=0; j<4; j++)
      {
        if (box[party[j]].pro_num == i)
        {
          if (box[party[j]].hp == 0)
          {
            printf("  %sは瀕死の状態だ!!\n", box[party[j]].name);
            printf("\n");
            sleep(2);
          }
          else
          {
            attack_point = box[party[j]].attack + (int)ceil(box[party[j]].attack*(attacks[i]-1)*0.2);
            printf("  %sの攻撃!!\n", box[party[j]].name);
            printf("\n");
            sleep(2);
            printf("  %sへ%dのダメージ!!\n", enemys[*enemy_search].name, attack_point);
            enemy_hp = enemys[*enemy_search].hp;
            enemys[*enemy_search].hp = enemys[*enemy_search].hp - attack_point;
            printf("  HP:%d -----> HP:%d\n", 
                                       enemy_hp, (enemys[*enemy_search].hp)>0 ? enemys[*enemy_search].hp:0);
            printf("\n");
            sleep(2);
            enemys[*enemy_search].hp = enemys[*enemy_search].hp>0 ? enemys[*enemy_search].hp:0;
            if (enemys[*enemy_search].hp <= 0)
            {
              for (int i=0; i<4; i++)
              {
                attacks[i] = 0;
              }
              return;
            }
            attack_point = 0;
          }
        }
      }
    }
  }
  if (attacks[4] ==0)
  {
    for (int i=0; i<4; i++)
    {
      attacks[i] = 0;
    }
  }
}
void hp_hearing(my_monster box[7], int party[4], int attacks[4])
{
  int hp = 0;
  int heal_point = 0;
  for (int i=0; i<4; i++)
  {
    if (box[party[i]].hp == 0 && attacks[box[party[i]].pro_num] == 0)
    {
      printf("  %sは瀕死の状態だ!!\n", box[party[i]].name);
      printf("\n");
      sleep(2);
    }
    else if (box[party[i]].hp == 0)
    {
      continue;
    }
    else
    {
      hp = box[party[i]].hp;
      heal_point = box[party[i]].resilience;
      for (int i=0; i < attacks[4]; i++)
      {
        heal_point += (heal_point * i * 0.2);
      }
      if (box[party[i]].hp == box[party[i]].max_hp)
      {
        printf("  %sのHPは最大です!! HP:%3d/%3d\n", box[party[i]].name, box[party[i]].hp,  box[party[i]].max_hp);
        printf("\n");
        sleep(2);
      }
      else
      {
        hp += heal_point;
        if (hp < box[party[i]].max_hp)
        {
          printf("  %sのHPが%d回復!!\n", box[party[i]].name, heal_point);
          printf("  HP:%3d/%3d ----> HP:%3d/%3d\n", box[party[i]].hp, box[party[i]].max_hp, hp,  box[party[i]].max_hp);
          printf("\n");
          sleep(2);
          box[party[i]].hp = hp;
        }
        else if (hp > box[party[i]].max_hp)
        {
          printf("  %sのHP全回復!!\n", box[party[i]].name);
          printf("  HP:%3d/%3d ----> HP%3d/%3d\n", box[party[i]].hp,  box[party[i]].max_hp, 
                                                                                  box[party[i]].max_hp, box[party[i]].max_hp);
          printf("\n");
          box[party[i]].hp = box[party[i]].max_hp;
          sleep(2);
        }
      }
    }
  }
  for (int i=0; i<5; i++)
  {
    attacks[i] = 0;
  }
}

//敵ターンの処理
void earmy_turn(enemy enemys[3], my_monster box[7], int party[4], int* enemy_search)
{
  srand((unsigned)time(0UL));
  int r = 0;

  while (1)
  {
    r = 0;
    if (box[party[r]].hp != 0)
    {
      break;
    }
  }

  int hp = box[party[r]].hp;

  printf("  %sの攻撃!!\n", enemys[*enemy_search].name);
  printf("\n");
  sleep(2);
  printf("  %sへ%dのダメージ!!\n", box[party[r]].name,  enemys[*enemy_search].attack);
  hp -= enemys[*enemy_search].attack;
  printf("  HP:%3d/%3d -----> HP:%3d/%3d\n", 
                             box[party[r]].hp, box[party[r]].max_hp ,hp>0 ? hp:0,  box[party[r]].max_hp);
  printf("\n");
  box[party[r]].hp = hp > 0 ? hp:0;
  sleep(2);
  if (box[party[r]].hp == 0)
  {
    printf("  %sは倒れた!!\n", box[party[r]].name);
    printf("\n");
    sleep(2);
  }
}
