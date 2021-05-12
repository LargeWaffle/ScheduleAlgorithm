                  
#define NBR_INTERFACES        12
#define NBR_APPRENANTS        10
#define NBR_CENTRES_FORMATION 3
#define NBR_SPECIALITES       3
#define NBR_NODES 	      NBR_CENTRES_FORMATION+NBR_INTERFACES+NBR_APPRENANTS
                  
/* code des compétence en langage des signes et en codage LPC */
#define COMPETENCE_SIGNES     0
#define COMPETENCE_CODAGE     1
                  
/* competences des interfaces en SIGNES et CODAGE*/
int competences_interfaces[NBR_INTERFACES][2]={
    {1,0}, /* compétence en langages des SIGNES mais pas en CODAGE LPC */
    {0,1}, /* pas de compétence en langages des SIGNES mais compétence en CODAGE LPC */
    {1,0},
    {1,0},
    {1,0},
    {0,1},
    {0,1},
    {1,0},
    {0,1},
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
    {0,1,0},
    {0,0,0},
    {1,0,0},
    {0,0,0},
    {0,1,0},
    {0,0,0},
    {1,1,1},
    {0,1,0},
    {1,1,0},
    {0,0,0},
    {0,0,0},
    {0,0,1}
};
                  
/* coordonnées des centres de formation, des interfaces et des apprenants */
float coord[NBR_NODES][2]={
                  
    /* Les interfaces se rendent du centre SESSAD à l'école de formation */
    {156,186}, /* centre 0 */
                  
    /* Centres de formation */
    {174,81}, /* ecole formation SPECIALITE_MENUISERIE */
    {56,98}, /* ecole formation SPECIALITE_ELECTRICITE */
    {173,102}, /* ecole formation SPECIALITE_MECANIQUE */
                  
    /* Apprenants */
    {65,108}, /* apprenant 0 */
    {148,1}, /* apprenant 1 */
    {45,125}, /* apprenant 2 */
    {14,149}, /* apprenant 3 */
    {87,61}, /* apprenant 4 */
    {102,132}, /* apprenant 5 */
    {197,54}, /* apprenant 6 */
    {38,122}, /* apprenant 7 */
    {108,3}, /* apprenant 8 */
    {32,65}/* apprenant 9 */
};
                  
#define NBR_FORMATION          40
                  
#define LUNDI                  1
#define MARDI                  2
#define MERCREDI               3
#define JEUDI                  4
#define VENDREDI               5
#define SAMEDI                 6
                  
/* formation : apprenant, specialite ou centre de formation, competence, horaire debut formation, horaire fin formation */
int formation[NBR_FORMATION][6]={
   {0,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,MARDI,10,12},
   {0,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,MARDI,15,17},
   {0,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,VENDREDI,9,12},
   {0,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,VENDREDI,9,11},
   {1,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,VENDREDI,16,19},
   {1,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,MARDI,16,19},
   {1,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,LUNDI,10,12},
   {1,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,MARDI,9,11},
   {2,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,LUNDI,10,12},
   {2,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,VENDREDI,8,12},
   {2,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,SAMEDI,9,11},
   {2,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,LUNDI,8,10},
   {3,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,JEUDI,14,18},
   {3,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,MARDI,16,19},
   {3,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,MERCREDI,14,18},
   {3,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,MARDI,8,12},
   {4,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,LUNDI,14,16},
   {4,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,MERCREDI,14,18},
   {4,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,SAMEDI,15,18},
   {4,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,SAMEDI,8,10},
   {5,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,SAMEDI,14,17},
   {5,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,LUNDI,14,18},
   {5,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,MARDI,8,10},
   {5,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,JEUDI,8,10},
   {6,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,SAMEDI,13,19},
   {6,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,JEUDI,8,10},
   {6,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,JEUDI,9,12},
   {6,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,LUNDI,16,18},
   {7,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,LUNDI,8,11},
   {7,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,MERCREDI,13,17},
   {7,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,VENDREDI,14,19},
   {7,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,SAMEDI,13,18},
   {8,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,JEUDI,16,19},
   {8,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,VENDREDI,8,10},
   {8,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,JEUDI,13,16},
   {8,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,MERCREDI,9,12},
   {9,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,MARDI,15,19},
   {9,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,LUNDI,14,17},
   {9,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,MARDI,8,10},
   {9,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,MARDI,16,19}
};

//End of File