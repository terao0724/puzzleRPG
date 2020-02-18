//宝石の配列作成
int make_Gems(char gems[14])
{
  srand((unsigned)time(0UL));
  for (int i=0; i<14; i++)
  {
    if (gems[i] == 0 || gems[i] == ' ')
    {
      switch(rand()%5)
      {
        case 0: gems[i] = 'H';break;
        case 1: gems[i] = '@'; break;
        case 2: gems[i] = '#'; break;
        case 3: gems[i] = '&'; break;
        case 4: gems[i] = '*'; break;
      }
    }
  }
  return 0;
}

//配列表示
void display_gems(char gems[], int num, int index_print)
{
  if(index_print == 1)
  {
    printf("   1    2    3    4    5    6    7    8    9 　 10   11   12   13   14\n");

    for (int i=0; i<num; i++)
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
    printf("\n");
    printf("\n");
  }
  else
  {
    for (int i=0; i<num; i++)
    {
      switch(gems[i])
       {
         case 'H': printf("   %c ",gems[i]); break;
         case '@': printf("  \x1b[41m %c \x1b[m", gems[i]); break;
         case '#': printf("  \x1b[42m %c \x1b[m", gems[i]); break;
         case '&': printf("  \x1b[43m %c \x1b[m", gems[i]); break;
         case '*': printf("  \x1b[44m %c \x1b[m", gems[i]); break;
         default:  printf("  \x1b[40m   \x1b[m");
       }
    }
    printf("\n");
    printf("\n");
  }
  return ;  
}
