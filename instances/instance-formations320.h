 #define NBR_INTERFACES        24
#define NBR_APPRENANTS        80
#define NBR_FORMATIONS        320
#define NBR_CENTRES_FORMATION 5
#define NBR_SPECIALITES       5
#define NBR_NODES 	      NBR_CENTRES_FORMATION + NBR_INTERFACES + NBR_APPRENANTS
                  
/* code des compétence en langage des signes et en codage LPC */
#define COMPETENCE_SIGNES     0
#define COMPETENCE_CODAGE     1
                  
/* competences des interfaces en SIGNES et CODAGE*/
int competences_interfaces[NBR_INTERFACES][2]={
    {1,0}, /* compétence en langages des SIGNES mais pas en CODAGE LPC */
    {0,1}, /* pas de compétence en langages des SIGNES mais compétence en CODAGE LPC */
    {0,1},
    {1,1},
    {1,0},
    {1,0},
    {1,0},
    {0,1},
    {0,1},
    {0,1},
    {1,0},
    {1,0},
    {1,0},
    {1,1},
    {1,0},
    {1,1},
    {1,0},
    {0,1},
    {0,1},
    {1,1},
    {1,0},
    {0,1},
    {0,1},
    {1,0}
};
                  
/* spécialités des interfaces */
#define SPECIALITE_SANS       -1 /* Enseigné dans le centre le plus proche */
#define SPECIALITE_MENUISERIE 0
#define SPECIALITE_ELECTRICITE 1
#define SPECIALITE_MECANIQUE 2
#define SPECIALITE_INFORMATIQUE 3
#define SPECIALITE_CUISINE 4
                  
/* specialite des interfaces */
int specialite_interfaces[NBR_INTERFACES][NBR_SPECIALITES]={
    {0,0,0,0,1},
    {0,0,1,0,0},
    {1,0,0,0,0},
    {0,0,0,0,0},
    {0,0,0,0,1},
    {0,0,1,0,0},
    {0,0,0,0,0},
    {0,0,0,1,1},
    {0,0,0,0,0},
    {1,0,0,1,0},
    {1,0,0,0,0},
    {0,0,1,0,0},
    {0,1,0,0,0},
    {0,0,0,0,1},
    {0,1,1,0,0},
    {1,0,1,1,0},
    {0,0,0,0,0},
    {0,0,0,1,0},
    {0,0,0,0,1},
    {0,0,0,0,0},
    {0,0,0,0,0},
    {0,0,0,1,0},
    {0,0,0,0,0},
    {0,0,0,0,0}
};
                  
/* coordonnées des centres de formation, des interfaces et des apprenants */
float coord[NBR_NODES][2]={
                  
    /* Les interfaces se rendent du centre SESSAD à l'école de formation */
    {38,121}, /* centre 0 */
                  
    /* Centres de formation */
    {66,39}, /* ecole formation SPECIALITE_MENUISERIE */
    {28,123}, /* ecole formation SPECIALITE_ELECTRICITE */
    {194,57}, /* ecole formation SPECIALITE_MECANIQUE */
    {122,164}, /* ecole formation SPECIALITE_INFORMATIQUE */
    {109,22}, /* ecole formation SPECIALITE_CUISINE */
                  
    /* Apprenants */
    {35,62}, /* apprenant 0 */
    {183,113}, /* apprenant 1 */
    {94,102}, /* apprenant 2 */
    {111,138}, /* apprenant 3 */
    {157,42}, /* apprenant 4 */
    {155,61}, /* apprenant 5 */
    {82,42}, /* apprenant 6 */
    {67,124}, /* apprenant 7 */
    {190,34}, /* apprenant 8 */
    {46,127}, /* apprenant 9 */
    {125,195}, /* apprenant 10 */
    {31,36}, /* apprenant 11 */
    {83,9}, /* apprenant 12 */
    {66,122}, /* apprenant 13 */
    {114,66}, /* apprenant 14 */
    {153,132}, /* apprenant 15 */
    {124,160}, /* apprenant 16 */
    {21,115}, /* apprenant 17 */
    {100,28}, /* apprenant 18 */
    {89,14}, /* apprenant 19 */
    {175,128}, /* apprenant 20 */
    {56,5}, /* apprenant 21 */
    {191,79}, /* apprenant 22 */
    {170,63}, /* apprenant 23 */
    {98,146}, /* apprenant 24 */
    {159,153}, /* apprenant 25 */
    {109,1}, /* apprenant 26 */
    {169,72}, /* apprenant 27 */
    {179,34}, /* apprenant 28 */
    {161,83}, /* apprenant 29 */
    {138,199}, /* apprenant 30 */
    {141,198}, /* apprenant 31 */
    {189,68}, /* apprenant 32 */
    {55,145}, /* apprenant 33 */
    {28,161}, /* apprenant 34 */
    {85,41}, /* apprenant 35 */
    {182,167}, /* apprenant 36 */
    {90,19}, /* apprenant 37 */
    {70,103}, /* apprenant 38 */
    {2,88}, /* apprenant 39 */
    {179,107}, /* apprenant 40 */
    {157,62}, /* apprenant 41 */
    {40,32}, /* apprenant 42 */
    {188,2}, /* apprenant 43 */
    {136,110}, /* apprenant 44 */
    {11,89}, /* apprenant 45 */
    {105,117}, /* apprenant 46 */
    {52,115}, /* apprenant 47 */
    {44,18}, /* apprenant 48 */
    {160,70}, /* apprenant 49 */
    {86,83}, /* apprenant 50 */
    {183,106}, /* apprenant 51 */
    {52,104}, /* apprenant 52 */
    {67,46}, /* apprenant 53 */
    {85,6}, /* apprenant 54 */
    {60,106}, /* apprenant 55 */
    {173,19}, /* apprenant 56 */
    {176,47}, /* apprenant 57 */
    {161,157}, /* apprenant 58 */
    {42,121}, /* apprenant 59 */
    {160,38}, /* apprenant 60 */
    {129,8}, /* apprenant 61 */
    {172,149}, /* apprenant 62 */
    {114,121}, /* apprenant 63 */
    {0,0}, /* apprenant 64 */
    {181,176}, /* apprenant 65 */
    {153,136}, /* apprenant 66 */
    {132,175}, /* apprenant 67 */
    {135,3}, /* apprenant 68 */
    {66,90}, /* apprenant 69 */
    {55,27}, /* apprenant 70 */
    {144,87}, /* apprenant 71 */
    {145,155}, /* apprenant 72 */
    {43,135}, /* apprenant 73 */
    {123,159}, /* apprenant 74 */
    {36,14}, /* apprenant 75 */
    {92,129}, /* apprenant 76 */
    {53,64}, /* apprenant 77 */
    {27,96}, /* apprenant 78 */
    {176,6}/* apprenant 79 */
};
                  
#define NBR_FORMATIONS          320
                  
#define LUNDI                  1
#define MARDI                  2
#define MERCREDI               3
#define JEUDI                  4
#define VENDREDI               5
#define SAMEDI                 6
                  
/* formation : id formation, specialite ou centre de formation, competence, horaire debut formation, horaire fin formation */
int formation[NBR_FORMATIONS][6]={
   {0,SPECIALITE_CUISINE,COMPETENCE_SIGNES,VENDREDI,8,11},
   {0,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,SAMEDI,14,16},
   {0,SPECIALITE_CUISINE,COMPETENCE_SIGNES,MERCREDI,13,19},
   {0,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,LUNDI,16,19},
   {1,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,MARDI,14,18},
   {1,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,MARDI,14,19},
   {1,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,MARDI,14,18},
   {1,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,SAMEDI,9,12},
   {2,SPECIALITE_CUISINE,COMPETENCE_SIGNES,LUNDI,9,11},
   {2,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,MERCREDI,9,12},
   {2,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,MERCREDI,8,10},
   {2,SPECIALITE_CUISINE,COMPETENCE_CODAGE,MERCREDI,10,12},
   {3,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,MARDI,16,18},
   {3,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,VENDREDI,10,12},
   {3,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,VENDREDI,15,17},
   {3,SPECIALITE_CUISINE,COMPETENCE_CODAGE,LUNDI,8,10},
   {4,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,MERCREDI,15,19},
   {4,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,JEUDI,14,19},
   {4,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,JEUDI,15,17},
   {4,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,MARDI,10,12},
   {5,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,LUNDI,10,12},
   {5,SPECIALITE_CUISINE,COMPETENCE_SIGNES,VENDREDI,15,19},
   {5,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,MARDI,10,12},
   {5,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,VENDREDI,8,10},
   {6,SPECIALITE_CUISINE,COMPETENCE_CODAGE,MERCREDI,15,19},
   {6,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,MERCREDI,9,12},
   {6,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,JEUDI,13,16},
   {6,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,MARDI,9,12},
   {7,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,LUNDI,10,12},
   {7,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,MARDI,13,16},
   {7,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,SAMEDI,8,10},
   {7,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,LUNDI,13,17},
   {8,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,LUNDI,10,12},
   {8,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,MARDI,10,12},
   {8,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,JEUDI,9,11},
   {8,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,MERCREDI,14,18},
   {9,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,MERCREDI,15,17},
   {9,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,JEUDI,16,19},
   {9,SPECIALITE_CUISINE,COMPETENCE_CODAGE,VENDREDI,16,19},
   {9,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,SAMEDI,13,19},
   {10,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,MERCREDI,16,19},
   {10,SPECIALITE_CUISINE,COMPETENCE_CODAGE,JEUDI,9,12},
   {10,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,MARDI,14,18},
   {10,SPECIALITE_CUISINE,COMPETENCE_SIGNES,MERCREDI,9,11},
   {11,SPECIALITE_CUISINE,COMPETENCE_CODAGE,SAMEDI,9,12},
   {11,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,MARDI,10,12},
   {11,SPECIALITE_CUISINE,COMPETENCE_SIGNES,VENDREDI,8,11},
   {11,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,LUNDI,9,12},
   {12,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,VENDREDI,10,12},
   {12,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,SAMEDI,9,12},
   {12,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,SAMEDI,9,11},
   {12,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,MARDI,9,11},
   {13,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,SAMEDI,16,19},
   {13,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,SAMEDI,8,10},
   {13,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,MERCREDI,16,18},
   {13,SPECIALITE_CUISINE,COMPETENCE_SIGNES,SAMEDI,16,19},
   {14,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,MERCREDI,15,19},
   {14,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,SAMEDI,16,18},
   {14,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,SAMEDI,15,18},
   {14,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,SAMEDI,10,12},
   {15,SPECIALITE_CUISINE,COMPETENCE_CODAGE,MARDI,16,18},
   {15,SPECIALITE_CUISINE,COMPETENCE_SIGNES,VENDREDI,15,18},
   {15,SPECIALITE_CUISINE,COMPETENCE_SIGNES,SAMEDI,16,18},
   {15,SPECIALITE_CUISINE,COMPETENCE_SIGNES,SAMEDI,13,16},
   {16,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,LUNDI,15,18},
   {16,SPECIALITE_CUISINE,COMPETENCE_SIGNES,VENDREDI,8,12},
   {16,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,VENDREDI,14,19},
   {16,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,VENDREDI,8,12},
   {17,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,SAMEDI,13,17},
   {17,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,VENDREDI,13,16},
   {17,SPECIALITE_CUISINE,COMPETENCE_CODAGE,JEUDI,13,18},
   {17,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,VENDREDI,13,18},
   {18,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,VENDREDI,14,16},
   {18,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,MARDI,10,12},
   {18,SPECIALITE_CUISINE,COMPETENCE_CODAGE,LUNDI,14,19},
   {18,SPECIALITE_CUISINE,COMPETENCE_SIGNES,LUNDI,9,11},
   {19,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,MERCREDI,8,11},
   {19,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,LUNDI,10,12},
   {19,SPECIALITE_CUISINE,COMPETENCE_CODAGE,SAMEDI,14,19},
   {19,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,VENDREDI,15,19},
   {20,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,MERCREDI,16,19},
   {20,SPECIALITE_CUISINE,COMPETENCE_CODAGE,SAMEDI,14,16},
   {20,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,VENDREDI,10,12},
   {20,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,VENDREDI,14,16},
   {21,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,SAMEDI,10,12},
   {21,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,MERCREDI,13,17},
   {21,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,VENDREDI,10,12},
   {21,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,LUNDI,10,12},
   {22,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,JEUDI,16,18},
   {22,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,VENDREDI,10,12},
   {22,SPECIALITE_CUISINE,COMPETENCE_SIGNES,SAMEDI,13,19},
   {22,SPECIALITE_CUISINE,COMPETENCE_CODAGE,LUNDI,15,18},
   {23,SPECIALITE_CUISINE,COMPETENCE_SIGNES,JEUDI,15,17},
   {23,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,MARDI,9,12},
   {23,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,SAMEDI,14,19},
   {23,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,MARDI,9,12},
   {24,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,LUNDI,8,10},
   {24,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,JEUDI,10,12},
   {24,SPECIALITE_CUISINE,COMPETENCE_SIGNES,VENDREDI,13,15},
   {24,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,SAMEDI,16,19},
   {25,SPECIALITE_CUISINE,COMPETENCE_SIGNES,JEUDI,15,19},
   {25,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,MERCREDI,10,12},
   {25,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,LUNDI,14,16},
   {25,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,SAMEDI,8,10},
   {26,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,MARDI,15,17},
   {26,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,JEUDI,16,19},
   {26,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,MARDI,9,11},
   {26,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,MERCREDI,16,19},
   {27,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,MARDI,15,17},
   {27,SPECIALITE_CUISINE,COMPETENCE_SIGNES,LUNDI,15,17},
   {27,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,MARDI,13,15},
   {27,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,JEUDI,13,17},
   {28,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,JEUDI,10,12},
   {28,SPECIALITE_CUISINE,COMPETENCE_SIGNES,JEUDI,13,19},
   {28,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,MARDI,8,10},
   {28,SPECIALITE_CUISINE,COMPETENCE_CODAGE,VENDREDI,13,18},
   {29,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,SAMEDI,13,18},
   {29,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,VENDREDI,8,10},
   {29,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,MERCREDI,16,19},
   {29,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,MARDI,8,12},
   {30,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,MERCREDI,16,18},
   {30,SPECIALITE_CUISINE,COMPETENCE_CODAGE,SAMEDI,13,15},
   {30,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,MERCREDI,8,12},
   {30,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,VENDREDI,14,17},
   {31,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,MARDI,9,12},
   {31,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,MARDI,15,17},
   {31,SPECIALITE_CUISINE,COMPETENCE_SIGNES,MERCREDI,9,12},
   {31,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,MARDI,15,17},
   {32,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,VENDREDI,16,19},
   {32,SPECIALITE_CUISINE,COMPETENCE_SIGNES,SAMEDI,16,19},
   {32,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,MARDI,13,19},
   {32,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,MERCREDI,16,19},
   {33,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,LUNDI,10,12},
   {33,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,MERCREDI,9,12},
   {33,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,VENDREDI,10,12},
   {33,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,JEUDI,10,12},
   {34,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,LUNDI,10,12},
   {34,SPECIALITE_CUISINE,COMPETENCE_SIGNES,VENDREDI,9,12},
   {34,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,MERCREDI,9,12},
   {34,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,MARDI,9,12},
   {35,SPECIALITE_CUISINE,COMPETENCE_SIGNES,JEUDI,9,11},
   {35,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,LUNDI,14,17},
   {35,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,SAMEDI,14,18},
   {35,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,JEUDI,13,15},
   {36,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,MARDI,8,10},
   {36,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,VENDREDI,9,12},
   {36,SPECIALITE_CUISINE,COMPETENCE_SIGNES,JEUDI,15,17},
   {36,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,VENDREDI,14,16},
   {37,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,VENDREDI,13,19},
   {37,SPECIALITE_CUISINE,COMPETENCE_CODAGE,VENDREDI,8,10},
   {37,SPECIALITE_CUISINE,COMPETENCE_CODAGE,JEUDI,8,11},
   {37,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,MARDI,14,19},
   {38,SPECIALITE_CUISINE,COMPETENCE_CODAGE,MERCREDI,14,17},
   {38,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,SAMEDI,15,17},
   {38,SPECIALITE_CUISINE,COMPETENCE_SIGNES,LUNDI,9,12},
   {38,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,LUNDI,10,12},
   {39,SPECIALITE_CUISINE,COMPETENCE_CODAGE,MARDI,13,15},
   {39,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,JEUDI,10,12},
   {39,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,VENDREDI,10,12},
   {39,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,LUNDI,8,11},
   {40,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,LUNDI,9,11},
   {40,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,MERCREDI,9,12},
   {40,SPECIALITE_CUISINE,COMPETENCE_CODAGE,VENDREDI,9,11},
   {40,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,MARDI,10,12},
   {41,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,MARDI,14,19},
   {41,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,LUNDI,14,19},
   {41,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,MERCREDI,14,17},
   {41,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,LUNDI,9,12},
   {42,SPECIALITE_CUISINE,COMPETENCE_SIGNES,VENDREDI,10,12},
   {42,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,MERCREDI,15,19},
   {42,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,JEUDI,10,12},
   {42,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,LUNDI,16,19},
   {43,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,MARDI,10,12},
   {43,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,MERCREDI,10,12},
   {43,SPECIALITE_CUISINE,COMPETENCE_SIGNES,VENDREDI,8,11},
   {43,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,LUNDI,9,12},
   {44,SPECIALITE_CUISINE,COMPETENCE_CODAGE,JEUDI,8,12},
   {44,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,MARDI,10,12},
   {44,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,SAMEDI,13,17},
   {44,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,SAMEDI,13,17},
   {45,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,MERCREDI,16,18},
   {45,SPECIALITE_CUISINE,COMPETENCE_CODAGE,MERCREDI,15,19},
   {45,SPECIALITE_CUISINE,COMPETENCE_CODAGE,MERCREDI,15,18},
   {45,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,JEUDI,9,11},
   {46,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,LUNDI,9,12},
   {46,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,MARDI,15,17},
   {46,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,VENDREDI,15,19},
   {46,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,VENDREDI,13,19},
   {47,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,VENDREDI,9,12},
   {47,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,LUNDI,14,18},
   {47,SPECIALITE_CUISINE,COMPETENCE_CODAGE,LUNDI,9,12},
   {47,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,VENDREDI,10,12},
   {48,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,MERCREDI,14,16},
   {48,SPECIALITE_CUISINE,COMPETENCE_CODAGE,MARDI,16,18},
   {48,SPECIALITE_CUISINE,COMPETENCE_SIGNES,VENDREDI,10,12},
   {48,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,JEUDI,16,18},
   {49,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,MARDI,13,17},
   {49,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,MERCREDI,13,18},
   {49,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,JEUDI,14,17},
   {49,SPECIALITE_CUISINE,COMPETENCE_SIGNES,MERCREDI,15,19},
   {50,SPECIALITE_CUISINE,COMPETENCE_CODAGE,MARDI,16,18},
   {50,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,JEUDI,14,16},
   {50,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,VENDREDI,13,18},
   {50,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,MARDI,14,16},
   {51,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,JEUDI,16,18},
   {51,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,JEUDI,10,12},
   {51,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,MERCREDI,16,18},
   {51,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,VENDREDI,10,12},
   {52,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,LUNDI,13,16},
   {52,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,VENDREDI,14,16},
   {52,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,JEUDI,15,17},
   {52,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,LUNDI,16,19},
   {53,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,LUNDI,8,11},
   {53,SPECIALITE_CUISINE,COMPETENCE_CODAGE,SAMEDI,16,19},
   {53,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,JEUDI,15,19},
   {53,SPECIALITE_CUISINE,COMPETENCE_SIGNES,LUNDI,9,12},
   {54,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,MARDI,9,11},
   {54,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,LUNDI,9,12},
   {54,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,MARDI,16,18},
   {54,SPECIALITE_CUISINE,COMPETENCE_SIGNES,SAMEDI,13,18},
   {55,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,JEUDI,16,19},
   {55,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,MARDI,10,12},
   {55,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,SAMEDI,10,12},
   {55,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,LUNDI,15,17},
   {56,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,LUNDI,8,12},
   {56,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,JEUDI,15,17},
   {56,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,MERCREDI,16,18},
   {56,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,MARDI,15,18},
   {57,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,LUNDI,16,18},
   {57,SPECIALITE_CUISINE,COMPETENCE_CODAGE,JEUDI,8,12},
   {57,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,VENDREDI,16,18},
   {57,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,VENDREDI,9,11},
   {58,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,JEUDI,16,19},
   {58,SPECIALITE_CUISINE,COMPETENCE_SIGNES,MARDI,10,12},
   {58,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,VENDREDI,16,18},
   {58,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,MARDI,10,12},
   {59,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,VENDREDI,14,18},
   {59,SPECIALITE_CUISINE,COMPETENCE_SIGNES,VENDREDI,14,18},
   {59,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,LUNDI,13,18},
   {59,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,SAMEDI,9,11},
   {60,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,VENDREDI,10,12},
   {60,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,VENDREDI,13,18},
   {60,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,VENDREDI,8,12},
   {60,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,SAMEDI,13,16},
   {61,SPECIALITE_CUISINE,COMPETENCE_CODAGE,MARDI,16,19},
   {61,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,LUNDI,14,18},
   {61,SPECIALITE_CUISINE,COMPETENCE_CODAGE,VENDREDI,10,12},
   {61,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,JEUDI,9,11},
   {62,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,JEUDI,8,11},
   {62,SPECIALITE_CUISINE,COMPETENCE_SIGNES,MARDI,10,12},
   {62,SPECIALITE_CUISINE,COMPETENCE_CODAGE,VENDREDI,16,18},
   {62,SPECIALITE_CUISINE,COMPETENCE_CODAGE,VENDREDI,13,15},
   {63,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,JEUDI,10,12},
   {63,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,LUNDI,14,17},
   {63,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,MARDI,9,12},
   {63,SPECIALITE_CUISINE,COMPETENCE_SIGNES,JEUDI,16,19},
   {64,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,SAMEDI,15,18},
   {64,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,SAMEDI,10,12},
   {64,SPECIALITE_CUISINE,COMPETENCE_CODAGE,SAMEDI,9,11},
   {64,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,MERCREDI,10,12},
   {65,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,MARDI,16,19},
   {65,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,MARDI,15,19},
   {65,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,VENDREDI,15,18},
   {65,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,MERCREDI,8,10},
   {66,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,JEUDI,8,12},
   {66,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,MARDI,10,12},
   {66,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,JEUDI,14,19},
   {66,SPECIALITE_CUISINE,COMPETENCE_CODAGE,MARDI,10,12},
   {67,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,JEUDI,16,19},
   {67,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,SAMEDI,10,12},
   {67,SPECIALITE_CUISINE,COMPETENCE_SIGNES,JEUDI,13,17},
   {67,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,MARDI,10,12},
   {68,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,VENDREDI,13,15},
   {68,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,VENDREDI,8,12},
   {68,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,JEUDI,14,16},
   {68,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,MARDI,13,16},
   {69,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,SAMEDI,10,12},
   {69,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,VENDREDI,14,19},
   {69,SPECIALITE_CUISINE,COMPETENCE_SIGNES,SAMEDI,14,19},
   {69,SPECIALITE_CUISINE,COMPETENCE_SIGNES,VENDREDI,15,18},
   {70,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,SAMEDI,10,12},
   {70,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,LUNDI,16,18},
   {70,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,VENDREDI,9,11},
   {70,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,SAMEDI,15,18},
   {71,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,MERCREDI,16,19},
   {71,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,JEUDI,15,19},
   {71,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,JEUDI,9,11},
   {71,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,MARDI,16,19},
   {72,SPECIALITE_CUISINE,COMPETENCE_CODAGE,LUNDI,8,10},
   {72,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,JEUDI,10,12},
   {72,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,MARDI,15,17},
   {72,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,MARDI,14,16},
   {73,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,JEUDI,8,12},
   {73,SPECIALITE_CUISINE,COMPETENCE_SIGNES,MERCREDI,10,12},
   {73,SPECIALITE_CUISINE,COMPETENCE_CODAGE,JEUDI,15,19},
   {73,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,VENDREDI,13,19},
   {74,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,SAMEDI,9,11},
   {74,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,VENDREDI,9,12},
   {74,SPECIALITE_CUISINE,COMPETENCE_SIGNES,VENDREDI,10,12},
   {74,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,MERCREDI,16,18},
   {75,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,LUNDI,15,19},
   {75,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,SAMEDI,8,10},
   {75,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,MERCREDI,9,11},
   {75,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,MERCREDI,14,19},
   {76,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,MARDI,14,17},
   {76,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,JEUDI,9,12},
   {76,SPECIALITE_CUISINE,COMPETENCE_SIGNES,LUNDI,13,15},
   {76,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,MARDI,14,17},
   {77,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,JEUDI,14,18},
   {77,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,LUNDI,13,19},
   {77,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,SAMEDI,13,16},
   {77,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,LUNDI,9,12},
   {78,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,MERCREDI,13,19},
   {78,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,LUNDI,9,11},
   {78,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,JEUDI,14,19},
   {78,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,SAMEDI,8,11},
   {79,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,SAMEDI,13,15},
   {79,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,JEUDI,8,12},
   {79,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,MARDI,9,11},
   {79,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,SAMEDI,13,17}
};
                  
// EOF