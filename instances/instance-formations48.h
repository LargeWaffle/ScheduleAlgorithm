#define NBR_INTERFACES        4
#define NBR_APPRENANTS        16
#define NBR_FORMATIONS        48
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
    {1,0,0,1,0},
    {0,0,0,0,0},
    {0,0,0,1,0},
    {1,0,0,0,0}
};
                  
/* coordonnées des centres de formation, des interfaces et des apprenants */
float coord[NBR_NODES][2]={
                  
    /* Les interfaces se rendent du centre SESSAD à l'école de formation */
    {72,61}, /* centre 0 */
                  
    /* Centres de formation */
    {78,41}, /* ecole formation SPECIALITE_MENUISERIE */
    {122,195}, /* ecole formation SPECIALITE_ELECTRICITE */
    {108,48}, /* ecole formation SPECIALITE_MECANIQUE */
    {87,68}, /* ecole formation SPECIALITE_INFORMATIQUE */
    {57,187}, /* ecole formation SPECIALITE_CUISINE */
                  
    /* Apprenants */
    {39,8}, /* apprenant 0 */
    {176,5}, /* apprenant 1 */
    {71,193}, /* apprenant 2 */
    {63,109}, /* apprenant 3 */
    {194,86}, /* apprenant 4 */
    {71,101}, /* apprenant 5 */
    {6,21}, /* apprenant 6 */
    {180,148}, /* apprenant 7 */
    {86,192}, /* apprenant 8 */
    {4,83}, /* apprenant 9 */
    {138,169}, /* apprenant 10 */
    {178,124}, /* apprenant 11 */
    {16,110}, /* apprenant 12 */
    {187,51}, /* apprenant 13 */
    {101,56}, /* apprenant 14 */
    {92,38}/* apprenant 15 */
};
                  
#define NBR_FORMATIONS          48
                  
#define LUNDI                  1
#define MARDI                  2
#define MERCREDI               3
#define JEUDI                  4
#define VENDREDI               5
#define SAMEDI                 6
                  
/* formation : id formation, specialite ou centre de formation, competence, horaire debut formation, horaire fin formation */
int formation[NBR_FORMATIONS][6]={
   {0,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,JEUDI,8,11},
   {0,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,MARDI,8,12},
   {0,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,MARDI,8,10},
   {1,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,SAMEDI,8,10},
   {1,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,MARDI,8,11},
   {1,SPECIALITE_CUISINE,COMPETENCE_CODAGE,JEUDI,16,19},
   {2,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,MARDI,9,12},
   {2,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,VENDREDI,8,12},
   {2,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,VENDREDI,8,10},
   {3,SPECIALITE_CUISINE,COMPETENCE_CODAGE,MERCREDI,10,12},
   {3,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,LUNDI,14,16},
   {3,SPECIALITE_CUISINE,COMPETENCE_CODAGE,VENDREDI,9,11},
   {4,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,VENDREDI,14,17},
   {4,SPECIALITE_CUISINE,COMPETENCE_CODAGE,SAMEDI,13,16},
   {4,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,JEUDI,10,12},
   {5,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,VENDREDI,14,16},
   {5,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,LUNDI,10,12},
   {5,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,MERCREDI,13,18},
   {6,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,SAMEDI,15,19},
   {6,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,JEUDI,10,12},
   {6,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,MARDI,8,12},
   {7,SPECIALITE_CUISINE,COMPETENCE_CODAGE,MARDI,8,10},
   {7,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,VENDREDI,8,10},
   {7,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,JEUDI,10,12},
   {8,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,JEUDI,13,19},
   {8,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,JEUDI,13,16},
   {8,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,JEUDI,9,11},
   {9,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,SAMEDI,14,16},
   {9,SPECIALITE_CUISINE,COMPETENCE_CODAGE,LUNDI,9,12},
   {9,SPECIALITE_CUISINE,COMPETENCE_CODAGE,MARDI,8,11},
   {10,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,MERCREDI,8,11},
   {10,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,JEUDI,14,16},
   {10,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,JEUDI,9,12},
   {11,SPECIALITE_CUISINE,COMPETENCE_CODAGE,LUNDI,9,12},
   {11,SPECIALITE_CUISINE,COMPETENCE_CODAGE,MERCREDI,16,18},
   {11,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,MERCREDI,10,12},
   {12,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,LUNDI,15,17},
   {12,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,SAMEDI,14,16},
   {12,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,JEUDI,14,17},
   {13,SPECIALITE_CUISINE,COMPETENCE_CODAGE,LUNDI,10,12},
   {13,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,VENDREDI,16,19},
   {13,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,VENDREDI,8,12},
   {14,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,SAMEDI,15,19},
   {14,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,MARDI,15,18},
   {14,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,LUNDI,15,18},
   {15,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,SAMEDI,9,12},
   {15,SPECIALITE_CUISINE,COMPETENCE_CODAGE,VENDREDI,13,19},
   {15,SPECIALITE_CUISINE,COMPETENCE_SIGNES,JEUDI,10,12}
};
                  
// EOF