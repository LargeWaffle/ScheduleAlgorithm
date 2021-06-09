#include <iostream>
#include <cmath>
#include "instance-formations.h"
#include "Interface.h"
#include <stdlib.h>

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
    int difference  = sum - ((sizeof(formation)/sizeof(*formation)));
    cout << abs(difference) << " formations missing" << endl;
    return sum == ((sizeof(formation)/sizeof(*formation))); // true if we assigned all the missions false otherwise
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

vector<float> getFormationPosition(int indexFormation)
{
    if (formation[indexFormation][1] == SPECIALITE_MENUISERIE)
    {
        return {coord[1][0], coord[1][1]};
    }
    else if (formation[indexFormation][1] == SPECIALITE_ELECTRICITE)
    {
        return {coord[2][0], coord[2][1]};
    }
    else
    {
        return {coord[3][0], coord[3][1]};
    }
}

inline bool areRangesOverlapping(int startTime1, int endTime1, int startTime2, int endTime2)
{
    return (endTime1 <= startTime2) || (endTime2 <= startTime1);
}


bool isFree(int indexInterface, int indexFormation, Interface *(&population)[NBR_INTERFACES], int day, int startingPoint)
{
    int startingHour = formation[indexFormation][4];
    int endingHour = formation[indexFormation][5];
    bool available = false;

    if (!population[indexInterface]->assigned_missions.empty()) //if interface already has at least 1 mission assigned
    {
        if ((population[indexInterface]->time_table[day][startingPoint] == -1) && (population[indexInterface]->time_table[day][startingPoint+2] == -1))
        {
            available = true;
        }
        else if((population[indexInterface]->time_table[day][startingPoint] != -1) && (population[indexInterface]->time_table[day][startingPoint + 2] == -1))
        {
            if (areRangesOverlapping(startingHour, endingHour, population[indexInterface]->time_table[day][startingPoint], population[indexInterface]->time_table[day][startingPoint+1]))
            {
                available = true;
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
            if (hasSameCompetence(indexFormation, indexInterface) == 1) //if interface has required competence
            {
                int day = getDayFormation(indexFormation); //get day of curr formation
                bool partOfDay = getPartOfDayFormation(indexFormation); //1 if morning 0 otherwise
                int startingPoint = partOfDay ? 0 : int(population[indexInterface]->time_table[day].size() / 2); //morning or afternoon

                if (isFree(indexInterface, indexFormation, population, day, startingPoint)) //if interface is free at formation time
                {
                    for (int indexOnHours = startingPoint; indexOnHours < startingPoint + 4; indexOnHours+=2)
                    {
                        if (population[indexInterface]->time_table[day][indexOnHours] == -1)
                        {
                            population[indexInterface]->time_table[day][indexOnHours] = formation[indexFormation][4]; //starting hour
                            population[indexInterface]->time_table[day][indexOnHours + 1] = formation[indexFormation][5]; //finishing hour
                            break;
                        }
                        else
                        {
                            if (population[indexInterface]->time_table[day][indexOnHours + 1] <= formation[indexFormation][4])
                            {
                                population[indexInterface]->time_table[day][indexOnHours + 2] = formation[indexFormation][4]; //starting hour
                                population[indexInterface]->time_table[day][indexOnHours + 3] = formation[indexFormation][5]; //finishing hour
                            }
                            else
                            {
                                //SWAP
                                population[indexInterface]->time_table[day][indexOnHours + 2] = population[indexInterface]->time_table[day][indexOnHours]; //starting hour
                                population[indexInterface]->time_table[day][indexOnHours + 3] = population[indexInterface]->time_table[day][indexOnHours + 1];//finishing hour
                                population[indexInterface]->time_table[day][indexOnHours] = formation[indexFormation][4]; //starting hour
                                population[indexInterface]->time_table[day][indexOnHours + 1] = formation[indexFormation][5]; //finishing hour
                            }
                            break;
                        }
                    }
                    vector<float> currPosition = population[indexInterface]->currentPosition;
                    vector<float> formationPosition = getFormationPosition(indexFormation);

                    population[indexInterface]->assigned_missions.insert(population[indexInterface]->assigned_missions.begin(),indexFormation);
                    population[indexInterface]->distance += sqrt(pow((currPosition[0] - formationPosition[0]),2.0) + pow((currPosition[1] - formationPosition[1]), 2.0));
                    population[indexInterface]->currentPosition = formationPosition;
                    break;
                }

            }
        }
    }

    if (!(isSolutionFeasible(population)))
    {

    }

}

// Crossover Operator on two interfaces of the same skill working on the same part of the day
bool crossingOperator(Interface *(&population)[NBR_INTERFACES], int indexInterfaceOne, int indexInterfaceTwo, int indexFormationOne, int indexFormationTwo)
{
    //reversal of assigned missions
    population[indexInterfaceOne]->assigned_missions.erase(remove(population[indexInterfaceOne]->assigned_missions.begin(), population[indexInterfaceOne]->assigned_missions.end(), indexFormationOne), population[indexInterfaceOne]->assigned_missions.end());
    population[indexInterfaceTwo]->assigned_missions.erase(remove(population[indexInterfaceTwo]->assigned_missions.begin(), population[indexInterfaceTwo]->assigned_missions.end(), indexFormationTwo), population[indexInterfaceTwo]->assigned_missions.end());

    population[indexInterfaceOne]->assigned_missions.insert(population[indexInterfaceOne]->assigned_missions.begin(),indexFormationTwo);
    population[indexInterfaceTwo]->assigned_missions.insert(population[indexInterfaceTwo]->assigned_missions.begin(),indexFormationOne);

    //inversion of assigned mission schedules
    vector <int> daySchedule = population[indexInterfaceOne]->time_table[getDayFormation(indexFormationTwo)];
    /*
     * remove indexFormation one de assigned missions de F1
     * population[indexInterfaceOne]->assigned_missions.erase(remove(population[indexInterfaceOne]->assigned_missions.begin, population[indexInterfaceOne]->assigned_missions.end, indexFormationOne), population[indexInterfaceOne]->assigned_missions.end());
     * vec.erase(std::remove(vec.begin(), vec.end(), indexFormationOne), vec.end());
     * vec.erase(std::remove(vec.begin(), vec.end(), indexFormationTwo), vec.end());
     * remove indexFormation two de assigned missons de F2
     * ajoute indexFormation two a assigned missions de F1
     * ajoute indexFormation one a assigned missions de F2
     *
     *
     */
    //I1's doing the F1 | he's gonna switch with I2 who's doing F2
    //population[indexFormationOne]->time_table[getDayFormation(indexFormationTwo)][]
    return true;
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
        cout << "Complete solution" << endl;
    else
        cout << "Incomplete solution" << endl;

    //crossingOperator(starting_population, 0, 8, 4, 9);
    return 0;
}

