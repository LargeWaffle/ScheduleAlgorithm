#include <iostream>
#include <cmath>
#include "instance-formations.h"
#include "Interface.h"

using namespace std;

int getPenalty(const Interface* individu)
{
    int nbPenalty = 0;

    for(int i = 0; i < individu->assigned_missions.size(); i++){

        int index = individu->assigned_missions[i];

        for (int j = 0; j < NBR_SPECIALITES; j++)

            if(individu->speciality[j] == 1)

                if(j == formation[index][1])
                    nbPenalty++;

    }


    return nbPenalty;
}

float evaluatePopulation(Interface *(&population)[NBR_INTERFACES])
{
    int nbPenalty = 0;    //get total number of specialties non fufilled

    float travelDistance = 0, valVariance = 0;
    float variance, ecart_type, meandistance, correlation;      // facteur de correlation (cf. pdf)

    for (auto & indiv : population) {
        nbPenalty += getPenalty(indiv);
        travelDistance += indiv->distance;
        valVariance += indiv->distance * indiv->distance;
    }

    meandistance = travelDistance / NBR_INTERFACES;
    correlation = travelDistance / NBR_FORMATIONS;

    if (NBR_INTERFACES == meandistance * meandistance)
        throw "Division by zero dumb dumb!";
    else
        variance = valVariance / (NBR_INTERFACES- meandistance * meandistance);

    ecart_type = sqrt(variance);

    return (float)(0.5 * (meandistance + ecart_type) + 0.5 * correlation * nbPenalty);
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

    bool result = comp_form == 0 ?
            competences_interfaces[indexInterface][0] == 1
            : competences_interfaces[indexInterface][1] == 1;

    return result;
}

int getDayFormation(int indexFormation)
{
    return formation[indexFormation][3];
}

bool getPartOfDayFormation(int indexFormation)
{
    return formation[indexFormation][4] <= 12;
}

bool isFree(int indexInterface, int indexFormation, Interface *(&population)[NBR_INTERFACES])
{
    population[indexInterface]->displayTimeTable();
    cout << indexFormation << endl;
    bool partOfDay = getPartOfDayFormation(indexFormation); //true if morning false otherwise
    int startingHour = formation[indexFormation][4];
    int endingHour = formation[indexFormation][5];
    int startingPoint = partOfDay ? 0 : int(population[indexInterface]->time_table.size() / 2);
    bool available = false;

    if (population[indexInterface]->assigned_missions.size() > 0)
    {
        cout << "hello";
        for(const auto& value: population[indexInterface]->assigned_missions)
        {
            cout << value << endl;
            for(int k = startingPoint; k < startingPoint+2; k++)
            {
                cout << "hello";
                if(indexInterface == 7)
                {
                    cout << k, startingPoint;
                    cout << "" <<endl;
                    cout << population[indexInterface]->time_table[value][k], population[indexInterface]->time_table[value][k+1];

                }
                cout << "coucou";
                for (int i: population[indexFormation]->time_table[value])
                    std::cout << i << ' ';
                cout << "bjr";

                if((population[indexFormation]->time_table[value][k] != -1) && (population[indexFormation]->time_table[value][k+1] != -1))
                {
                    cout << "not -1" << endl;
                    if (startingHour > population[indexInterface]->time_table[value][k] && startingHour < population[indexInterface]->time_table[value][k+1])
                    {
                        cout << "not available";
                    }
                }
                else
                {
                    available = true;
                }
            }
        }
    }
    else
    {
        available = true;
    }

    return available;
}

void greedyFirstSolution(Interface *(&population)[NBR_INTERFACES])
{
    for (int indexFormation = 0; indexFormation < NBR_FORMATIONS; indexFormation++)
    {
        for (int indexInterface = 0; indexInterface < NBR_INTERFACES; indexInterface++)
        {
            if (hasSameCompetence(indexFormation, indexInterface) == 1)
            {
                if (isFree(indexInterface, indexFormation, population))
                {

                    int day = getDayFormation(indexFormation);
                    bool partOfDay = getPartOfDayFormation(indexFormation); //true if morning false otherwise

                    vector<int> timeTableInterface = population[indexInterface]->time_table[day];
                    int startingPoint = partOfDay ? 0 : int(timeTableInterface.size() / 2);

                    for (int k = startingPoint; k < startingPoint+4; k++)
                    {
                        if (population[indexInterface]->time_table[day][k] == -1)
                        {
                            population[indexInterface]->time_table[day][k] = formation[indexFormation][4]; //starting hour
                            population[indexInterface]->time_table[day][k+1] = formation[indexFormation][5]; //finishing hour
                            population[indexInterface]->assigned_missions.insert(population[indexInterface]->assigned_missions.begin(),indexFormation);
                            break;
                        }
                        else
                        {
                            cout << "there" << endl;
                            population[indexInterface]->time_table[day][k+2] = formation[indexFormation][4]; //starting hour
                            population[indexInterface]->time_table[day][k+3] = formation[indexFormation][5]; //finishing hour
                            population[indexInterface]->assigned_missions.insert(population[indexInterface]->assigned_missions.begin(),indexFormation);
                            break;
                        }
                    }
                }
            }
            population[0]->displayTimeTable();
        }
    }
    float hq[2] = {coord[0][0], coord[0][1]};  // Coordonnées du QG

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

    cout << "Eval is " << eval << endl;
    /*
    for(Interface *i : starting_population)
        i->displayTimeTable();
    */
    return 0;
}

