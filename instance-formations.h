#define NBR_INTERFACES        2
#define NBR_APPRENANTS        8
#define NBR_FORMATIONS        8
#define NBR_CENTRES_FORMATION 5
#define NBR_SPECIALITES       5
#define NBR_NODES 	      NBR_CENTRES_FORMATION + NBR_INTERFACES + NBR_APPRENANTS
                  
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
#define SPECIALITE_MENUISERIE 0
#define SPECIALITE_ELECTRICITE 1
#define SPECIALITE_MECANIQUE 2
#define SPECIALITE_INFORMATIQUE 3
#define SPECIALITE_CUISINE 4
                  
/* specialite des interfaces */
int specialite_interfaces[NBR_INTERFACES][NBR_SPECIALITES]={
    {0,0,0,0,1},
    {0,0,0,0,0}
};
                  
/* coordonnées des centres de formation, des interfaces et des apprenants */
float coord[NBR_NODES][2]={
                  
    /* Les interfaces se rendent du centre SESSAD à l'école de formation */
    {188,16}, /* centre 0 */
                  
    /* Centres de formation */
    {88,122}, /* ecole formation SPECIALITE_MENUISERIE */
    {140,90}, /* ecole formation SPECIALITE_ELECTRICITE */
    {125,62}, /* ecole formation SPECIALITE_MECANIQUE */
    {156,76}, /* ecole formation SPECIALITE_INFORMATIQUE */
    {35,129}, /* ecole formation SPECIALITE_CUISINE */
                  
    /* Apprenants */
    {72,187}, /* apprenant 0 */
    {23,52}, /* apprenant 1 */
    {29,54}, /* apprenant 2 */
    {76,148}, /* apprenant 3 */
    {102,15}, /* apprenant 4 */
    {101,173}, /* apprenant 5 */
    {84,11}, /* apprenant 6 */
    {51,69}/* apprenant 7 */
};
                  
#define NBR_FORMATIONS          8
                  
#define LUNDI                  1
#define MARDI                  2
#define MERCREDI               3
#define JEUDI                  4
#define VENDREDI               5
#define SAMEDI                 6
                  
/* formation : id formation, specialite ou centre de formation, competence, horaire debut formation, horaire fin formation */
int formation[NBR_FORMATIONS][6]={
   {0,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,SAMEDI,10,12},
   {1,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,JEUDI,14,16},
   {2,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,SAMEDI,14,18},
   {3,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,JEUDI,15,18},
   {4,SPECIALITE_CUISINE,COMPETENCE_SIGNES,MARDI,13,17},
   {5,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,MARDI,9,11},
   {6,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,MERCREDI,14,18},
   {7,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,JEUDI,13,18}
};
                  
// EOF
