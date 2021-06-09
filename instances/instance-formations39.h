                  
#define NBR_INTERFACES        24
#define NBR_APPRENANTS        20
#define NBR_FORMATIONS        40
#define NBR_CENTRES_FORMATION 3
#define NBR_SPECIALITES       3
#define NBR_NODES 	      NBR_CENTRES_FORMATION + NBR_INTERFACES + NBR_APPRENANTS
                  
/* code des compétence en langage des signes et en codage LPC */
#define COMPETENCE_SIGNES     0
#define COMPETENCE_CODAGE     1
                  
/* competences des interfaces en SIGNES et CODAGE*/
int competences_interfaces[NBR_INTERFACES][2]={
    {1,0}, /* compétence en langages des SIGNES mais pas en CODAGE LPC */
    {0,1}, /* pas de compétence en langages des SIGNES mais compétence en CODAGE LPC */
    {0,1},
    {0,1},
    {0,1},
    {0,1},
    {1,0},
    {1,0},
    {1,0},
    {0,1},
    {1,0},
    {0,1},
    {1,0},
    {0,1},
    {0,1},
    {1,0},
    {1,0},
    {1,0},
    {1,0},
    {0,1},
    {1,0},
    {1,0},
    {1,0},
    {1,0}
};
                  
/* spécialités des interfaces */
#define SPECIALITE_SANS       -1 /* Enseigné dans le centre le plus proche */
#define SPECIALITE_MENUISERIE  0 
#define SPECIALITE_ELECTRICITE 1
#define SPECIALITE_MECANIQUE   2
                  
/* specialite des interfaces */
int specialite_interfaces[NBR_INTERFACES][NBR_SPECIALITES]={
    {0,0,0},
    {0,0,0},
    {1,1,0},
    {1,0,1},
    {0,0,0},
    {0,0,1},
    {0,0,1},
    {0,0,1},
    {0,0,0},
    {0,0,0},
    {0,0,0},
    {1,0,0},
    {0,1,0},
    {0,0,0},
    {0,0,0},
    {0,1,0},
    {0,1,0},
    {1,0,1},
    {1,0,1},
    {0,0,1},
    {0,0,0},
    {0,0,0},
    {1,0,0},
    {0,0,0}
};
                  
/* coordonnées des centres de formation, des interfaces et des apprenants */
float coord[NBR_NODES][2]={
                  
    /* Les interfaces se rendent du centre SESSAD à l'école de formation */
    {89,134}, /* centre 0 */
                  
    /* Centres de formation */
    {93,166}, /* ecole formation SPECIALITE_MENUISERIE */
    {33,73}, /* ecole formation SPECIALITE_ELECTRICITE */
    {165,149}, /* ecole formation SPECIALITE_MECANIQUE */
                  
    /* Apprenants */
    {190,165}, /* apprenant 0 */
    {131,59}, /* apprenant 1 */
    {4,153}, /* apprenant 2 */
    {157,81}, /* apprenant 3 */
    {193,80}, /* apprenant 4 */
    {105,69}, /* apprenant 5 */
    {173,189}, /* apprenant 6 */
    {171,173}, /* apprenant 7 */
    {126,97}, /* apprenant 8 */
    {20,28}, /* apprenant 9 */
    {105,141}, /* apprenant 10 */
    {24,128}, /* apprenant 11 */
    {169,0}, /* apprenant 12 */
    {7,146}, /* apprenant 13 */
    {21,32}, /* apprenant 14 */
    {102,172}, /* apprenant 15 */
    {6,82}, /* apprenant 16 */
    {161,62}, /* apprenant 17 */
    {42,135}, /* apprenant 18 */
    {0,39}/* apprenant 19 */
};
                  
#define NBR_FORMATION          40
                  
#define LUNDI                  1
#define MARDI                  2
#define MERCREDI               3
#define JEUDI                  4
#define VENDREDI               5
#define SAMEDI                 6
                  
/* formation : id formation, specialite ou centre de formation, competence, horaire debut formation, horaire fin formation */
int formation[NBR_FORMATION][6]={
   {0,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,VENDREDI,15,18},//0
   {0,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,JEUDI,9,11},//1
   {1,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,SAMEDI,16,18},//2
   {1,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,SAMEDI,10,12},//3
   {2,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,SAMEDI,15,18},//4
   {2,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,JEUDI,9,12},//5
   {3,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,JEUDI,9,12},//6
   {3,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,JEUDI,13,17},//7
   {4,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,SAMEDI,9,11},//8
   {4,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,LUNDI,9,12},//9
   {5,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,MERCREDI,13,16},//10
   {5,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,VENDREDI,9,12},//11
   {6,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,MERCREDI,15,19},//12
   {6,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,MERCREDI,13,17},//13
   {7,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,MERCREDI,10,12},//14
   {7,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,VENDREDI,16,18},//15
   {8,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,SAMEDI,10,12},//16
   {8,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,VENDREDI,15,18},//17
   {9,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,LUNDI,13,18},//18
   {9,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,JEUDI,9,11},//19
   {10,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,SAMEDI,13,15},//20
   {10,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,LUNDI,9,11},//ici//21/
   {11,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,LUNDI,14,19},//22
   {11,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,VENDREDI,9,12},//23
   {12,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,SAMEDI,9,11},//24
   {12,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,JEUDI,16,18},//25
   {13,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,SAMEDI,16,19},//26
   {13,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,LUNDI,15,19},//27
   {14,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,VENDREDI,9,12},//28
   {14,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,MERCREDI,15,17},//29
   {15,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,MERCREDI,16,19},//30
   {15,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,SAMEDI,8,12},//31
   {16,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,LUNDI,8,10},//ici//32
   {16,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,SAMEDI,16,19},//33
   {17,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,VENDREDI,9,11},//34
   {17,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,LUNDI,8,11},//35
   {18,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,JEUDI,13,18},//36
   {18,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,VENDREDI,15,18},//37
   {19,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,MERCREDI,14,18},//38
   {19,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,LUNDI,8,10}//39
};
                  

//EOF
