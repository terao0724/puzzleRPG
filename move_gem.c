// 移動させるジェムを選択
void choice_gem(int* start, int* end)
{
  char start_gem[4];
  char end_gem[4];
  sleep(1);
  printf("  動かしたいジェムを選択してください: ");
  while (1)
  {
    scanf("%3s%*[^\n]", start_gem);
    printf("\n");
    sleep(1);
    *start = atoi(start_gem);
    if (1 <= *start && *start <= 14)
    {
      break;
    }
    else
    {
      printf("  値が間違っています\n");
      sleep(1);
      printf("  動かしたいジェムを選択してください: ");
    }
  }

  printf("  ジェムの移動先を指定してださい: ");
  while (1)
  {
    scanf("%3s%*[^\n]", end_gem);
    sleep(1);
    printf("\n");
    *end = atoi(end_gem);
    if (1 <= *end && *end <= 14 && *end != *start)
    {
      break;
    }
    else if(1 <= *end && *end <= 14 && *end == *start)
    {
      printf("  スタート位置と同じ位置の指定はできません\n");
      sleep(1);
      printf("  ジェムの移動先を指定してださい: ");
    }
    else
    {
      printf("  値が間違っています\n");
      sleep(1);
      printf("  ジェムの移動先を指定してださい: ");
    }
  }
  return ;
}

//ジェムを移動させる関数
void move_gems(char gems[14], int* start, int* end)
{
  char change_gems;
  printf("   1    2    3    4    5    6    7    8    9 　 10   11   12   13   14\n");
  for (int i=0; i<14; i++)
  {
    if (i == *start-1)
    {
      printf("  \x1b[7m %c \x1b[m", gems[i]);
    }
    else
    {
      switch(gems[i])
      {
        case 'H': printf("   %c ",gems[i]); break;
        case '@': printf("  \x1b[41m %c \x1b[m", gems[i]); break;
        case '#': printf("  \x1b[42m %c \x1b[m", gems[i]); break;
        case '&': printf("  \x1b[43m %c \x1b[m", gems[i]); break;
        case '*': printf("  \x1b[44m %c \x1b[m", gems[i]); break;
        default:  printf("     ");
      }
    }
  }
  printf("\n");
  printf("\n");
  sleep(1);
  
  if (*start < *end)
  { 
    for(int i=((*start)-1); i<(*end)-1; i++)
    { 
      change_gems = gems[i+1];
      gems[i+1] = gems[i];
      gems[i] = change_gems;
      for (int m=0; m<14; m++)
      {
        if (m == i+1)
        {
          printf("  \x1b[7m %c \x1b[m", gems[m]);
        }
        else
        {
          switch(gems[m])
           {
             case 'H': printf("   %c ",gems[m]); break;
             case '@': printf("  \x1b[41m %c \x1b[m", gems[m]); break;
             case '#': printf("  \x1b[42m %c \x1b[m", gems[m]); break;
             case '&': printf("  \x1b[43m %c \x1b[m", gems[m]); break;
             case '*': printf("  \x1b[44m %c \x1b[m", gems[m]); break;
           }
        }
      }
      printf("\n");
      printf("\n");
      sleep(1);
    }
  }
  else
  {
    for(int i=((*start)-1); i>(*end)-1; i--)
    {
      change_gems = gems[i-1];
      gems[i-1] = gems[i];
      gems[i] = change_gems;
      for (int m=0; m<14; m++)
      {
        if (m == i-1)
        { 
          printf("  \x1b[7m %c \x1b[m", gems[m]);
        }
        else
        {
          switch(gems[m])
          {
            case 'H': printf("   %c ",gems[m]); break;
            case '@': printf("  \x1b[41m %c \x1b[m", gems[m]); break;
            case '#': printf("  \x1b[42m %c \x1b[m", gems[m]); break;
            case '&': printf("  \x1b[43m %c \x1b[m", gems[m]); break;
            case '*': printf("  \x1b[44m %c \x1b[m", gems[m]); break;
          }
        }
      }
      printf("\n");
      printf("\n");
      sleep(1);
    }
  }
}
