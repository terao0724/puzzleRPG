// パーティのステータス
typedef struct{
  char name[13];
  int revel;
  int hp;
  int max_hp;
  int attack;
  int resilience;
  char property;
  short pro_num;
  int exp;
  int lu_exp;
}my_monster;

// 敵のステータス
typedef struct{
  char name[13];
  int hp;
  int attack;
  char property;
  int get_exp;
}enemy;

// ドロップされたジェムの属性と個数
typedef struct{
  int Se;
  int Su;
  int Ge;
  int Bya;
  int H;
}attack_gems;
