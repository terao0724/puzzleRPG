void chose_monster(my_monster box[7], int party[4])
{
  char choise[4];
  int loop_counter = 0;
  int end_flg = 0;
  party[0] = 10;
  party[1] = 10;
  party[2] = 10;
  party[3] = 10;
  printf("  バトルに使用するモンスターを選択してください\n");
  printf("\n");
  sleep(1);

  while (1)
  {
    for (int i=0; i<7; i++)
    {
      if (i == party[0] || i == party[1] || i == party[2]||i == party[3])
      {
         printf("  \x1b[41m%s{レベル:%1d  属性:%c  HP:%3d/%3d  AP:%4d  経験値:%3d/%3d}\x1b[m\n", box[i].name, box[i].revel,
                                          box[i].property, box[i].hp, box[i].max_hp,  box[i].attack, box[i].exp, box[i].lu_exp);
      }
      else if (box[i].hp != 0)
      {
        printf("  %2s{レベル:%1d  属性:%c  HP:%3d/%3d  AP:%4d  経験値:%3d/%3d}\n", box[i].name, box[i].revel,
                                          box[i].property, box[i].hp, box[i].max_hp, box[i].attack, box[i].exp, box[i].lu_exp);
      }
      else if (box[i].revel == 0)
      {
        printf("  モンスターはいません\n");
      }

      else
      {
        printf("  \x1b[44m\x1b[30m%s{レベル:%1d  属性:%c  HP:%3d/%3d  AP:%4d  経験値:%3d/%3d}\033[m\x1b[m\n", box[i].name, box[i].revel,
                                           box[i].property, box[i].hp, box[i].max_hp, box[i].attack, box[i].exp, box[i].lu_exp);
      }
    }
    printf("\n");
    if (loop_counter == 4)
    {
      sleep(1);
      break;
    }
    printf("  %d匹目: ", loop_counter+1);
    scanf("%3s%*[^\n]", choise);
    printf("\n");
    sleep(1);
    if (1 <= atoi(choise) && atoi(choise) <= 7)
    {
      if((party[0] == atoi(choise)-1) || (party[1] == atoi(choise)-1) || (party[2] == atoi(choise)-1) ||(party[3] == atoi(choise)-1))
      {
        printf("  同一モンスターは選択できません\n");
        printf("\n");
        sleep(1);
      }
      else if (box[atoi(choise)-1].revel == 0)
      {
        printf(" 選択できません\n");
        printf("\n");
        sleep(1);
      }
      else
      {
        party[loop_counter] = atoi(choise)-1;
        loop_counter ++;
      }
    }
    else if(choise[0] == 'q')
    {
      sleep(1);
      return;
    }
    else
    {
      printf("  認識できませんでした\n");
      printf("\n");
      sleep(1);
    }
  }
}
