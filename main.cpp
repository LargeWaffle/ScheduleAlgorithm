#include <iostream>
#include <cmath>
#include <list>
#include <iterator>
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
    for(int i = 0; i < NBR_INTERFACES; i++)
    {
        Interface intervenant = Interface();

        intervenant.competence = competences_interfaces[i];
        intervenant.speciality = specialite_interfaces[i];

        population[i] = intervenant;
    }
}

bool hasSameCompetence(int indexFormation, int indexInterface)
{
    int comp_form = formation[indexFormation][2];
    bool result = false;

    if (comp_form == 0) // competence formation : signe
        result = (competences_interfaces[indexInterface][0] == 1);
    else // competence formation : codage LPC
        result = (competences_interfaces[indexInterface][1] == 1);

    return result;
}

bool isFree(int index_interface, int index_formation, Interface (&population)[NBR_INTERFACES])
{
// TODO:finish when time table is clear in my head
    return true;
}

int getDayFormation(int indexFormation)
{
    return formation[indexFormation][3];
}

void greedyFirstSolution(Interface (&population)[NBR_INTERFACES])
{
    for (int indexFormation = 0; indexFormation < NBR_FORMATIONS; indexFormation++)
    {
        for (int indexInterface = 0; indexInterface < NBR_INTERFACES; indexInterface++)
        {
            if (hasSameCompetence(indexFormation, indexInterface) == 1)
            {
                //cout << "memes competences" << endl;
                if (isFree(indexInterface, indexFormation, population))
                {

                    int day = getDayFormation(indexFormation);
                    //cout << day << endl;
                    
                    vector<int> test = population[indexInterface].time_table[day];

                    test[0];

                    test[4] = 23;
                    for (auto const &i: test) {
                        std::cout << i;
                    }
                    cout << endl;
                    vector<int> test2 = population[indexInterface].time_table[day];
                    for (auto const &i: test2) {
                        std::cout << i;
                    }

                    cout << endl;
                    //cout << "interface disponible" << endl;
                }
                else
                {
                    //cout << "interface pas disponible" << endl;
                }
            }
            else
            {
                //cout << "pas memes competences" << endl;
            }

        }
    }
    float hq[2]{coord[0][0], coord[0][1]};  // Coordonnées du QG
    /*TODO: ajouter la distance parcourue quand une formation est rentrée.
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

