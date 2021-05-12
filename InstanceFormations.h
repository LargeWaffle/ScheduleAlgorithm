#include <stdio.h>
                  
#define NBR_INTERFACES        2
#define NBR_APPRENANTS        2
#define NBR_CENTRES_FORMATION 3
#define NBR_SPECIALITES       3
#define NBR_NODES 	      NBR_CENTRES_FORMATION+NBR_INTERFACES+NBR_APPRENANTS
                  
/* code des compétence en langage des signes et en codage LPC */
#define COMPETENCE_SIGNES     0
#define COMPETENCE_CODAGE     1
                  
/* competences des interfaces en SIGNES et CODAGE*/
int competences_interfaces[NBR_INTERFACES][2]= {
        {1, 0}, /* compétence en langages des SIGNES mais pas en CODAGE LPC */
        {0, 1}, /* pas de compétence en langages des SIGNES mais compétence en CODAGE LPC */
};

/* spécialités des interfaces */
#define SPECIALITE_SANS       -1 /* Enseigné dans le centre le plus proche */
#define SPECIALITE_MENUISERIE  0 
#define SPECIALITE_ELECTRICITE 1
#define SPECIALITE_MECANIQUE   2
                  
/* specialite des interfaces */
int specialite_interfaces[NBR_INTERFACES][NBR_SPECIALITES]={
    {0,1,0},
    {0,0,0}
};
                  
/* coordonnées des centres de formation, des interfaces et des apprenants */
float coord[NBR_NODES][2]={
                  
    /* Les interfaces se rendent du centre SESSAD à l'école de formation */
    {12,184}, /* centre 0 */
                  
    /* Centres de formation */
    {63,87}, /* ecole formation SPECIALITE_MENUISERIE */
    {16,75}, /* ecole formation SPECIALITE_ELECTRICITE */
    {57,33}, /* ecole formation SPECIALITE_MECANIQUE */
                  
    /* Apprenants */
    {164,156}, /* apprenant 0 */
    {94,74}/* apprenant 1 */
};
                  
#define NBR_FORMATION          8
                  
#define LUNDI                  1
#define MARDI                  2
#define MERCREDI               3
#define JEUDI                  4
#define VENDREDI               5
#define SAMEDI                 6
                  
/* formation : apprenant, specialite ou centre de formation, competence, horaire debut formation, horaire fin formation */
int formation[NBR_FORMATION][6]={
   {0,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,SAMEDI,10,12},
   {0,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,LUNDI,13,16},
   {0,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,MARDI,13,18},
   {0,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,VENDREDI,14,19},
   {1,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,JEUDI,14,16},
   {1,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,MERCREDI,14,18},
   {1,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,MARDI,8,11},
   {1,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,MERCREDI,13,19}
};
void initConfig() {
                  
    printf("NBR_INTERFACES=%d\n",NBR_INTERFACES) ;
    printf("NBR_APPRENANTS=%d\n",NBR_APPRENANTS) ;
    printf("NBR_NODES=%d\n",NBR_NODES) ;
                  
}
                  
