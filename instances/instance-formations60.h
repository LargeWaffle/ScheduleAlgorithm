#define NBR_INTERFACES        6
#define NBR_APPRENANTS        20
#define NBR_FORMATIONS        60
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
    {0,1},
    {1,0},
    {0,1}
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
    {0,0,0,1,0},
    {0,1,0,1,1},
    {0,0,1,0,0},
    {0,0,1,0,0},
    {0,0,1,1,0}
};
                  
/* coordonnées des centres de formation, des interfaces et des apprenants */
float coord[NBR_NODES][2]={
                  
    /* Les interfaces se rendent du centre SESSAD à l'école de formation */
    {142,93}, /* centre 0 */
                  
    /* Centres de formation */
    {6,98}, /* ecole formation SPECIALITE_MENUISERIE */
    {39,15}, /* ecole formation SPECIALITE_ELECTRICITE */
    {178,163}, /* ecole formation SPECIALITE_MECANIQUE */
    {64,73}, /* ecole formation SPECIALITE_INFORMATIQUE */
    {161,187}, /* ecole formation SPECIALITE_CUISINE */
                  
    /* Apprenants */
    {112,101}, /* apprenant 0 */
    {132,84}, /* apprenant 1 */
    {4,111}, /* apprenant 2 */
    {100,100}, /* apprenant 3 */
    {10,177}, /* apprenant 4 */
    {109,51}, /* apprenant 5 */
    {97,168}, /* apprenant 6 */
    {98,93}, /* apprenant 7 */
    {93,188}, /* apprenant 8 */
    {159,49}, /* apprenant 9 */
    {145,47}, /* apprenant 10 */
    {190,192}, /* apprenant 11 */
    {150,45}, /* apprenant 12 */
    {139,98}, /* apprenant 13 */
    {35,91}, /* apprenant 14 */
    {51,141}, /* apprenant 15 */
    {3,161}, /* apprenant 16 */
    {65,156}, /* apprenant 17 */
    {17,127}, /* apprenant 18 */
    {115,33}/* apprenant 19 */
};
                  
#define NBR_FORMATIONS          60
                  
#define LUNDI                  1
#define MARDI                  2
#define MERCREDI               3
#define JEUDI                  4
#define VENDREDI               5
#define SAMEDI                 6
                  
/* formation : id formation, specialite ou centre de formation, competence, horaire debut formation, horaire fin formation */
int formation[NBR_FORMATIONS][6]={
   {0,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,LUNDI,8,11},
   {0,SPECIALITE_CUISINE,COMPETENCE_CODAGE,MERCREDI,16,19},
   {0,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,MERCREDI,13,16},
   {1,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,VENDREDI,15,19},
   {1,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,VENDREDI,13,19},
   {1,SPECIALITE_CUISINE,COMPETENCE_CODAGE,JEUDI,8,10},
   {2,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,MERCREDI,9,11},
   {2,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,JEUDI,10,12},
   {2,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,SAMEDI,14,17},
   {3,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,LUNDI,10,12},
   {3,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,SAMEDI,13,18},
   {3,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,MARDI,16,18},
   {4,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,LUNDI,16,18},
   {4,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,MERCREDI,16,18},
   {4,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,MARDI,8,12},
   {5,SPECIALITE_CUISINE,COMPETENCE_SIGNES,SAMEDI,10,12},
   {5,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,SAMEDI,15,17},
   {5,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,SAMEDI,10,12},
   {6,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,LUNDI,10,12},
   {6,SPECIALITE_CUISINE,COMPETENCE_SIGNES,MERCREDI,9,11},
   {6,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,JEUDI,13,15},
   {7,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,MARDI,16,18},
   {7,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,MARDI,10,12},
   {7,SPECIALITE_CUISINE,COMPETENCE_CODAGE,JEUDI,13,18},
   {8,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,MARDI,9,11},
   {8,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,JEUDI,8,11},
   {8,SPECIALITE_CUISINE,COMPETENCE_CODAGE,MARDI,9,11},
   {9,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,SAMEDI,14,18},
   {9,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,MERCREDI,14,18},
   {9,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,JEUDI,10,12},
   {10,SPECIALITE_CUISINE,COMPETENCE_CODAGE,MERCREDI,16,19},
   {10,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,VENDREDI,9,11},
   {10,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,LUNDI,9,12},
   {11,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,JEUDI,8,11},
   {11,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,SAMEDI,8,12},
   {11,SPECIALITE_CUISINE,COMPETENCE_SIGNES,LUNDI,10,12},
   {12,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,MERCREDI,10,12},
   {12,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,VENDREDI,13,19},
   {12,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,MERCREDI,9,11},
   {13,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,LUNDI,9,11},
   {13,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,SAMEDI,10,12},
   {13,SPECIALITE_CUISINE,COMPETENCE_SIGNES,MERCREDI,8,10},
   {14,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,LUNDI,10,12},
   {14,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,VENDREDI,9,11},
   {14,SPECIALITE_CUISINE,COMPETENCE_CODAGE,JEUDI,14,18},
   {15,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,LUNDI,8,12},
   {15,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,MARDI,9,12},
   {15,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,LUNDI,10,12},
   {16,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,SAMEDI,15,17},
   {16,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,MARDI,9,11},
   {16,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,MARDI,10,12},
   {17,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,MERCREDI,14,16},
   {17,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,MARDI,14,18},
   {17,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,JEUDI,9,11},
   {18,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,VENDREDI,9,11},
   {18,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,VENDREDI,16,19},
   {18,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,LUNDI,13,18},
   {19,SPECIALITE_CUISINE,COMPETENCE_SIGNES,VENDREDI,15,17},
   {19,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,LUNDI,14,16},
   {19,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,MERCREDI,9,11}
};
                  
// EOF