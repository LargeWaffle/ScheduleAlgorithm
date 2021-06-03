#include <iostream>
#include <cmath>
#include "instance-formations.h"
#include "Interface.h"

using namespace std;

float evaluatePopulation(Interface *(&population)[NBR_INTERFACES])
{
    int nbPenalty = 0;    //get total number of specialties non fufilled

    float travelDistance = 0, valVariance = 0;
    float variance, ecart_type, meandistance, correlation;      // facteur de correlation (cf. pdf)

    for (auto & indiv : population) {
        nbPenalty += indiv->getPenalty();
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
bool isSolutionFeasible(Interface *(&population)[NBR_INTERFACES])
{
    int sum = 0;
    for(Interface *i : population)
    {
        sum += i->assigned_missions.size();
    }
    cout << "sum = " << sum << endl;
    cout << "size of formation : " << (sizeof(formation)/sizeof(*formation)) << endl;
    return sum == ((sizeof(formation)/sizeof(*formation)));
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

bool isFree(int indexInterface, int indexFormation, Interface *(&population)[NBR_INTERFACES], int day, bool partOfDay, int startingPoint)
{
    int startingHour = formation[indexFormation][4];
    int endingHour = formation[indexFormation][5];
    //cout << "startingHour : " << startingHour << " endingHour : " << endingHour << endl;
    //if (partOfDay == 1)
        //cout << "morning" << endl;
    //else
        //cout << "evening" << endl;
    bool available = false;

    if (!population[indexInterface]->assigned_missions.empty()) //if interface already has at least 1 mission assigned
    {
        //cout << "assigned missions > 0" << endl;
        for(const auto& value: population[indexInterface]->assigned_missions)
        {
            //cout << "index of assigned missions : " << value << endl;
            for(int k = startingPoint; k < startingPoint+2; k+=2)
            {
                if((population[indexInterface]->time_table[day][k] != -1) && (population[indexInterface]->time_table[day][k+1] != -1))
                {
                    //cout << "not -1" << endl;
                    if (((startingHour >= population[indexInterface]->time_table[value][k]) && (startingHour <= population[indexInterface]->time_table[value][k+1]))
                    ||
                            (endingHour >= population[indexInterface]->time_table[value][k]) && (endingHour <= population[indexInterface]->time_table[value][k+1])
                    )
                    {
                        //cout << "not available";
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
                int day = getDayFormation(indexFormation); //get day of curr formation
                bool partOfDay = getPartOfDayFormation(indexFormation); //1 if morning 0 otherwise
                int startingPoint = partOfDay ? 0 : int(population[indexInterface]->time_table[day].size() / 2);
                //population[indexInterface]->displayTimeTable();
                //cout << "day : " << day << " partofDay : " << partOfDay << " startingPoint : " << startingPoint << " interface : " << indexInterface << endl;
                if (isFree(indexInterface, indexFormation, population, day, partOfDay, startingPoint))
                {
                    //cout << "indexFormation : " << indexFormation << " possible" << endl;
                    for (int k = startingPoint; k < startingPoint+4; k+=2)
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
                            population[indexInterface]->time_table[day][k+2] = formation[indexFormation][4]; //starting hour
                            population[indexInterface]->time_table[day][k+3] = formation[indexFormation][5]; //finishing hour
                            population[indexInterface]->assigned_missions.insert(population[indexInterface]->assigned_missions.begin(),indexFormation);
                            break;
                        }
                    }
                }
                else
                {
                    //cout << "not available" << endl;
                }
            }
            else
            {
                //cout << "pas les bonnes competences" << endl;
            }
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

    for(Interface *i : starting_population)
        i->display();

    if(isSolutionFeasible(starting_population))
        cout << "solution feasible" << endl;
    else
        cout << "solution unfeasible" << endl;


    return 0;
}

