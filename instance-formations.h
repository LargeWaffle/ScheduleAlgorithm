#define NBR_INTERFACES        6
#define NBR_APPRENANTS        20
#define NBR_FORMATIONS        20
#define NBR_CENTRES_FORMATION 5
#define NBR_SPECIALITES       5
#define NBR_NODES 	      NBR_CENTRES_FORMATION+NBR_INTERFACES+NBR_APPRENANTS
                  
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
    {0,0,0,0,0},
    {0,1,0,1,0},
    {0,0,0,0,0},
    {1,0,1,0,0},
    {0,1,1,1,0},
    {0,0,0,0,0}
};
                  
/* coordonnées des centres de formation, des interfaces et des apprenants */
float coord[NBR_NODES][2]={
                  
    /* Les interfaces se rendent du centre SESSAD à l'école de formation */
    {94,78}, /* centre 0 */
                  
    /* Centres de formation */
    {127,109}, /* ecole formation SPECIALITE_MENUISERIE */
    {119,198}, /* ecole formation SPECIALITE_ELECTRICITE */
    {177,61}, /* ecole formation SPECIALITE_MECANIQUE */
    {113,78}, /* ecole formation SPECIALITE_INFORMATIQUE */
    {35,134}, /* ecole formation SPECIALITE_CUISINE */
                  
    /* Apprenants */
    {52,89}, /* apprenant 0 */
    {58,199}, /* apprenant 1 */
    {188,142}, /* apprenant 2 */
    {179,109}, /* apprenant 3 */
    {156,8}, /* apprenant 4 */
    {168,182}, /* apprenant 5 */
    {0,189}, /* apprenant 6 */
    {143,100}, /* apprenant 7 */
    {199,38}, /* apprenant 8 */
    {191,179}, /* apprenant 9 */
    {44,149}, /* apprenant 10 */
    {105,153}, /* apprenant 11 */
    {18,101}, /* apprenant 12 */
    {171,171}, /* apprenant 13 */
    {36,24}, /* apprenant 14 */
    {197,155}, /* apprenant 15 */
    {181,109}, /* apprenant 16 */
    {36,7}, /* apprenant 17 */
    {107,175}, /* apprenant 18 */
    {20,27}/* apprenant 19 */
};
                  
#define NBR_FORMATION          20
                  
#define LUNDI                  1
#define MARDI                  2
#define MERCREDI               3
#define JEUDI                  4
#define VENDREDI               5
#define SAMEDI                 6
                  
/* formation : id formation, specialite ou centre de formation, competence, horaire debut formation, horaire fin formation */
int formation[NBR_FORMATION][6]={
   {0,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,JEUDI,8,11},
   {1,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,MERCREDI,10,12},
   {2,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,MARDI,8,11},
   {3,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,SAMEDI,8,12},
   {4,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,MERCREDI,15,17},
   {5,SPECIALITE_CUISINE,COMPETENCE_CODAGE,MARDI,9,11},
   {6,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,VENDREDI,9,11},
   {7,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,VENDREDI,10,12},
   {8,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,MARDI,13,16},
   {9,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,LUNDI,14,18},
   {10,SPECIALITE_CUISINE,COMPETENCE_SIGNES,SAMEDI,9,11},
   {11,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,VENDREDI,13,18},
   {12,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,VENDREDI,15,19},
   {13,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,VENDREDI,14,18},
   {14,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,VENDREDI,10,12},
   {15,SPECIALITE_CUISINE,COMPETENCE_SIGNES,VENDREDI,8,12},
   {16,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,LUNDI,10,12},
   {17,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,VENDREDI,14,16},
   {18,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,MERCREDI,8,12},
   {19,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,JEUDI,13,18}
};
                  
// EOF
