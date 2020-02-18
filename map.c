struct termios CookedTermIos; // cooked モード用
struct termios RawTermIos; // raw モード用
void display_map (char map[10][10])
{ 
  for (int i=0; i<10; i++)
  {
    for (int j=0; j<10; j++)
    {
      if(j == 0)
      {
        printf("%3c", map[i][j]);
      }
      else
      {
        printf("%2c", map[i][j]);
      }
    }
    printf("\n");
  }
  printf("\n");
}

int monster_earch(char map[10][10], int* p_pos_x, int* p_pos_y)
{
  srand((unsigned)time(0UL));
  int battle_flg = 0;
  char p_dic; //プレイヤーの選択した進行方向
  display_map (map);
  // 初期状態の端末設定 (cooked モード) を取得・保存する
  tcgetattr(STDIN_FILENO, &CookedTermIos);
  while (1)
  {
    // raw モードの端末設定を作成・保存する
    RawTermIos = CookedTermIos;
    cfmakeraw(&RawTermIos);

    // 端末を raw モードに設定する
    tcsetattr(STDIN_FILENO, 0, &RawTermIos);

    p_dic = getchar();
    // 端末設定を元に戻す
    tcsetattr(STDIN_FILENO, 0, &CookedTermIos);
    switch (p_dic)
    {
      case 'i':
      if (map[*p_pos_y-1][*p_pos_x] == ' '&& *p_pos_y-1 >= 0 && *p_pos_y-1 < 10)
      {
        map[*p_pos_y-1][*p_pos_x] = 'P';
        map[*p_pos_y][*p_pos_x] = ' ';
        *p_pos_y = *p_pos_y-1;
        display_map (map);
        battle_flg = rand()%15+1;
        break;
      }
      else if (map[*p_pos_y-1][*p_pos_x] == 'G')
      {
        return 2;
      }
      else
      {
        break;
      }

      case 'j':
      if (map[*p_pos_y][*p_pos_x-1] == ' '&& *p_pos_x-1 >= 0 && *p_pos_x-1 < 10)
      {
        map[*p_pos_y][*p_pos_x-1] = 'P';
        map[*p_pos_y][*p_pos_x] = ' ';
        *p_pos_x = *p_pos_x-1;
        display_map (map);
        battle_flg = rand()%15+1;
        break;
      }
      else if (map[*p_pos_y-1][*p_pos_x] == 'G')
      {
        return 2;
      }
      else
      {
        break;
      }
      case 'k':
      if (map[*p_pos_y+1][*p_pos_x] == ' ' && *p_pos_y+1 >= 0 && *p_pos_y+1 < 10)
      {
        map[*p_pos_y+1][*p_pos_x] = 'P';
        map[*p_pos_y][*p_pos_x] = ' ';
        *p_pos_y = *p_pos_y+1;
        display_map (map);
        battle_flg = rand()%15+1;
        break;
      }
      else if (map[*p_pos_y+1][*p_pos_x] == 'G')
      {
        return 2;
      }
      else
      {
        break;
      }

      case 'l':
      if (map[*p_pos_y][*p_pos_x+1] == ' '&& *p_pos_x+1 >= 0 && *p_pos_x+1 < 10)
      {
        map[*p_pos_y][*p_pos_x+1] = 'P';
        map[*p_pos_y][*p_pos_x] = ' ';
        *p_pos_x = *p_pos_x+1;
        display_map (map);
        battle_flg = rand()%15+1;
        break;
      }
      else if (map[*p_pos_y-1][*p_pos_x] == 'G')
      {
        return 2;
      }
      else
      {
        break;
      }
      case 'M':
      return 0;
    }
    if (battle_flg>= 1 && battle_flg <= 3)
    {
      return 0;
      break;
    }
    else if (battle_flg>=4  && battle_flg <= 5)
    {
      return 1;
      break;
    }
  }
}
