#include <iostream>
#include <cmath>

#include "instance-formations.h"
#include "Interface.h"

using namespace std;

float evaluatePopulation(Interface (&population)[NBR_INTERFACES])
{
    float score, travelDistance = 0;
    //int hq[2] = coord[0];
    int penalty = 3;//get total number of specialties non fufilled

    for (auto & Individu : population) {
        travelDistance = 0;

        for (int i = 0; i < NBR_INTERFACES; i++) {

        }
    }

    float meandistance;
    float variance = NBR_INTERFACES / (NBR_INTERFACES- meandistance * meandistance);
    float ecart_type = sqrt(variance);

    score = (float)(0.5 * penalty);
    return score;
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

bool isFree(int index_interface, int index_formation, Interface population[])
{
// TODO:finish when time table is clear in my head
}

void greedyFirstSolution(Interface population[])
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

}

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
    //float eval = evaluatePopulation(starting_population);

    return 0;
}

