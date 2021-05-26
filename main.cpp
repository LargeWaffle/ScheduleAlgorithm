#include <iostream>
#include <cmath>

#include "instance-formations.h"
#include "Interface.h"

using namespace std;

float evaluatePopulation(Interface (&population)[NBR_INTERFACES])
{
    int penalty = 3;    //get total number of specialties non fufilled

    float travelDistance = 0;
    float variance, ecart_type, meandistance, correlation;      // facteur de correlation (cf. pdf)

    for (auto & indiv : population) {
        travelDistance = 0;
        travelDistance += indiv.distance;
    }

    meandistance = travelDistance / NBR_INTERFACES;
    correlation = travelDistance / NBR_FORMATIONS;
    variance = NBR_INTERFACES / (NBR_INTERFACES- meandistance * meandistance);
    ecart_type = sqrt(variance);

    return (float)(0.5 * (meandistance + ecart_type) + 0.5 * correlation * penalty);
}

void fillPopulation(Interface (&population)[NBR_INTERFACES])
{

    int indiv_index = 0;
    for(auto & indiv : population)
    {
        indiv.competence = competences_interfaces[indiv_index];
        indiv.speciality = specialite_interfaces[indiv_index];

        indiv_index++;
    }
}

bool hasSameCompetence(int index_formation, int index_interface)
{
    int comp_form = formation[index_formation][2];
    bool result = false;

    if (comp_form == 0) // competence formation : signe
        result = (competences_interfaces[index_interface][0] == 1);
    else // competence formation : codage LPC
        result = (competences_interfaces[index_interface][1] == 1);

    return result;
}

bool isFree(int index_interface, int index_formation, Interface (&population)[NBR_INTERFACES])
{
// TODO:finish when time table is clear in my head

}

void greedyFirstSolution(Interface (&population)[NBR_INTERFACES])
{
    for (int i = 0; i < NBR_FORMATIONS; i++)
    {
        for (int j = 0; j < NBR_INTERFACES; j++)
        {
            if (hasSameCompetence(i, j) == 1)
            {
                cout << "memes competences" << endl;
                if (isFree(j, i, population))
                {
                    cout << "interface disponible" << endl;
                }
                else
                {
                    cout << "interface pas disponible" << endl;
                }
            }
            else
            {
                cout << "pas memes competences" << endl;
            }

        }
    }
    float hq[2]{coord[0][0], coord[0][1]};  // Coordonnées du QG
    /*TODO: ajouter la distance parcourue quand une formation est rentré.
     * Needed pour les fonctions évaluation et fitness
    */
}

// La notation Interface (&population)[NBR_INTERFACES] permet de passer par réference

int main()
{
    cout << "IT45 - Probleme d affectation d employes\n" << endl;
    cout << "Configuration of the problem" << endl;
    cout << "\tNumber of Interfaces = " << NBR_INTERFACES << endl;
    cout << "\tNumber of Apprentices = " << NBR_APPRENANTS << endl;
    cout << "\tNumber of nodes = " << NBR_NODES << endl << endl;

    Interface starting_population[NBR_INTERFACES];

    fillPopulation(starting_population);    // Remplir la solution initiale starting_population
    greedyFirstSolution(starting_population);
    float eval = evaluatePopulation(starting_population);

    return 0;
}

