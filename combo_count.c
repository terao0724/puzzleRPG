//コンボ数計算
int combo_count(char gems[14], int start_index[4], int end_index[4], int attacks[4], int attack_count)
{
  int combo_counter = 0;
  int continue_num = 1;
  int index_count = 0;
  for (int i = 0; i<14; i++)
  {
    if(gems[i] == gems[i+1] && gems[i] != ' ')
    {
      continue_num ++;
      if (continue_num == 3)
      {
        start_index[index_count] = i;
      }
    }

    else if((gems[i] != gems[i+1] && gems[i] != ' ') || (continue_num > 3 && i == 13))
    {
      if (continue_num>=3)
      {
        end_index[index_count] = i;
        index_count += 1;
        combo_counter += 1;
        if (attack_count == 1)
        {
          switch(gems[i])
          {
           case '@': attacks[0] += 1; break;
           case '&': attacks[1] += 1; break;
           case '#': attacks[2] += 1; break;
           case '*': attacks[3] += 1; break;
           case 'H': attacks[4] += 1; break;
           default: break;
         }
       }
      }
      continue_num = 1;
    }
  }
  return combo_counter;
}

//ジェム消失
void gem_drop(char gems[14], int start_index[4], int end_index[4], int i)
{
  if (start_index[i] != 0 && end_index[i] != 0)
  {
     for(int j = start_index[i]-1; j <= end_index[i]; j++)
     {
       gems[j] = ' ';
     }
  }
}

//ジェムの値詰め
void gem_pack(char gems[14])
{
  char cange_val;
  for (int i=0; i<13; i++)
  {
    for (int j=i+1; j<14; j++)
    {
      if (gems[i] == ' ' && gems[j] != ' ')
      {
        cange_val = gems[j];
        gems[j] = gems[i];
        gems[i] = cange_val;
      }
    }
  }
}
