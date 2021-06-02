#include <iostream>
#include <cmath>
#include "instance-formations.h"
#include "Interface.h"

using namespace std;

int getPenalty(const Interface* individu)
{
    int nbPenalty = 0;

    // Formation struct ?


    return nbPenalty;
}
float evaluatePopulation(Interface *(&population)[NBR_INTERFACES])
{
    int penalty;    //get total number of specialties non fufilled

    float travelDistance = 0;
    float variance, ecart_type, meandistance, correlation;      // facteur de correlation (cf. pdf)

    for (auto & indiv : population) {
        penalty = getPenalty(indiv);
        travelDistance += indiv->distance;
    }

    meandistance = travelDistance / NBR_INTERFACES;
    correlation = travelDistance / NBR_FORMATIONS;
    variance = NBR_INTERFACES / (NBR_INTERFACES- meandistance * meandistance);
    ecart_type = sqrt(variance);

    return (float)(0.5 * (meandistance + ecart_type) + 0.5 * correlation * penalty);
}

void fillPopulation(Interface *(&population)[NBR_INTERFACES])
{
    for(int i = 0; i < NBR_INTERFACES; i++)
    {
        auto *intervenant = new Interface();

        intervenant->competence = competences_interfaces[i];
        intervenant->speciality = specialite_interfaces[i];

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

bool isFree(int index_interface, int index_formation, Interface *(&population)[NBR_INTERFACES])
{
// TODO:finish when time table is clear in my head
    return true;
}

int getDayFormation(int indexFormation)
{
    return formation[indexFormation][3];
}

bool getPartOfDayFormation(int indexFormation)
{
    return formation[indexFormation][4] <= 12;
}


void greedyFirstSolution(Interface *(&population)[NBR_INTERFACES])
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
                    bool partOfDay = getPartOfDayFormation(indexFormation); //true if morning false otherwise

                    vector<int> timeTableInterface = population[indexInterface]->time_table[day];

                    int startingPoint = partOfDay ? 0 : int(timeTableInterface.size() / 2);;

                    for (int k = startingPoint; k < startingPoint+4; k++)
                    {
                        if (population[indexInterface]->time_table[day][k] == -1)
                        {
                            population[indexInterface]->time_table[day][k] = formation[indexFormation][4]; //starting hour
                            population[indexInterface]->time_table[day][k+1] = formation[indexFormation][5]; //finishing hour
                            break;
                        }
                        else
                        {
                            population[indexInterface]->time_table[day][k+2] = formation[indexFormation][4]; //starting hour
                            population[indexInterface]->time_table[day][k+3] = formation[indexFormation][5]; //finishing hour
                            break;
                        }
                        //TODO: SI BREAK SE FAIT DANS LE IF ET LE ELSE METS LE ICI A LA PLACE
                        //SINON LA BOUCLE FOR TOURNE JAMAIS
                    }
                }
            }
        }
    }
    float hq[2]{coord[0][0], coord[0][1]};  // Coordonnées du QG
    /*TODO: ajouter la distance parcourue quand une formation est rentrée.
     * Needed pour les fonctions évaluation et fitness
    */
}

int main()
{
    cout << "IT45 - Probleme d affectation d employes\n" << endl;
    cout << "Configuration of the problem" << endl;
    cout << "\tNumber of Interfaces = " << NBR_INTERFACES << endl;
    cout << "\tNumber of Apprentices = " << NBR_APPRENANTS << endl;
    cout << "\tNumber of nodes = " << NBR_NODES << endl << endl;

    Interface *starting_population[NBR_INTERFACES];

    fillPopulation(starting_population);    // Remplir la solution initiale starting_population

    greedyFirstSolution(starting_population);

    float eval = evaluatePopulation(starting_population);

    for(Interface *i : starting_population)
        i->display();

    return 0;
}

