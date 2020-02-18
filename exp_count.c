void get_exp(my_monster box[4], enemy enemys[3], int party[4], int* enemy_search)
{
  int rem_exp = 0;
  for (int i=0; i<4; i++)
  {
    printf("  %sは経験値%dをもらった!!\n",box[party[i]].name, enemys[*enemy_search].get_exp);
    printf("\n");
    sleep(2);
    box[party[i]].exp += enemys[*enemy_search].get_exp;
    if (box[party[i]].exp >= box[party[i]].lu_exp)
    {
      rem_exp = box[party[i]].exp - box[party[i]].lu_exp;
      while (1)
      {
        if (rem_exp < 0)
        { 
          break;
        }
        printf("  %sのレベルが上がった!!\n", box[party[i]].name);
        sleep(2);
        printf("---------------------------------\n");
        printf("  レベル: %d ----> %d\n", box[party[i]].revel, box[party[i]].revel+1); 
        box[party[i]].revel ++;
        printf("\n");

        printf("  HP: %d/%d ----> %d/%d\n", box[party[i]].hp, box[party[i]].max_hp, (int)(box[party[i]].hp*1.3), (int)(box[party[i]].max_hp*1.3));
        box[party[i]].hp = (int)(box[party[i]].hp*1.3);
        box[party[i]].max_hp = (int)(box[party[i]].max_hp*1.3);
        printf("\n");

        printf("  AP: %d ----> %d\n", box[party[i]].attack, (int)(box[party[i]].attack*1.3));
        box[party[i]].attack = (int)(box[party[i]].attack*1.3);
        printf("\n");

        printf("  回復力: %d ----> %d\n", box[party[i]].resilience, (int)(box[party[i]].resilience*1.3));
        box[party[i]].resilience = (int)(box[party[i]].resilience*1.3);
        printf("---------------------------------\n");
        printf("\n");
        sleep(3);
        box[party[i]].lu_exp *= 1.3;
        box[party[i]].exp = rem_exp;
        rem_exp -= box[party[i]].lu_exp;
      }
    }
  }
}
