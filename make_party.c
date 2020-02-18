void chose_monster(my_monster box[7], int party[4])
{
  char choise[4];
  int loop_counter = 0;
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
         printf(" \x1b[41m %s{レベル: %d 属性: %c  HP: %d AP: %d 経験値 : %d/%d}\x1b[m\n", box[i].name, box[i].revel,
                                          box[i].property, box[i].hp, box[i].attack, box[i].exp, box[i].lu_exp);
      }
      else
      {
        printf("  %s{レベル: %d 属性: %c  HP: %d AP: %d 経験値 : %d/%d}\n", box[i].name, box[i].revel,
                                             box[i].property, box[i].hp, box[i].attack, box[i].exp, box[i].lu_exp);
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
        sleep(1);
      }
      else if (box[atoi(choise)-1].revel == 0)
      {
        printf("選択できません\n");
        sleep(1);
      }
      else
      {
        party[loop_counter] = atoi(choise)-1;
        loop_counter ++;
      }
    }
    else
    {
      printf("  認識できませんでした\n");
      sleep(1);
    }
  }
}
