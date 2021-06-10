#include <iostream>
#include <cmath>
#include <random>
#include <functional>

#include "instances/instance-formations39.h"

#include "Interface.h"
#include "Formation.h"

using namespace std;

inline float getMean(float travelDistance){
    return travelDistance / NBR_INTERFACES;
}

float evaluatePopulation(Interface *(&population)[NBR_INTERFACES])
{
    int nbPenalty = 0;    //get total number of specialties non fufilled

    float travelDistance = 0.0, valVariance = 0.0;
    float variance, ecart_type, mean_distance, correlation;      // facteur de correlation (cf. pdf)

    for (auto & indiv : population) {
        nbPenalty += indiv->getPenalty();
        travelDistance += indiv->distance;
        valVariance += indiv->distance * indiv->distance;
    }

    mean_distance = getMean(travelDistance);
    correlation = travelDistance / NBR_FORMATIONS;

    variance = valVariance / pow((NBR_INTERFACES - mean_distance), 2);

    ecart_type = sqrt(variance);

    return (float)(0.5 * (mean_distance + ecart_type) + 0.5 * correlation * nbPenalty);
}

void fillPopulation(Interface *(&population)[NBR_INTERFACES])
{
    for(int i = 0; i < NBR_INTERFACES; i++)
    {
        cout << "hello" << endl;
        auto *intervenant = new Interface();
        cout << "coucou" << endl;
        intervenant->competence = competences_interfaces[i];
        intervenant->speciality = specialite_interfaces[i];
        cout << "au revoir" << endl;
        population[i] = intervenant;
    }
}

void fillFormations(Formation *(&form_list)[NBR_FORMATION])
{
    for (int i = 0; i < NBR_FORMATIONS; i++)
    {
        auto *form = new Formation();

        form->id = formation[i][0];
        form->spec = formation[i][1];
        form->comp = formation[i][2];
        form->day = formation[i][3];
        form->hDebut = formation[i][4];
        form->hFin = formation[i][5];

        form_list[i] = form;
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
    /*
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
    }*/

    return available;
}
/*
bool areFormationTheSame(int indexFormation, int indexOnDay, int indexHour, vector<int> daySchedule)
{
    if (getDayFormation(indexFormation) == indexOnDay) //if they are on the same day
    {
        if ((formation[indexFormation][4] == daySchedule[indexHour]) && (formation[indexFormation][5] == daySchedule[indexHour+1])) //if they have the same hours
        {
            if
        }
}

void updateInterfaceDistance(Interface *(&population)[NBR_INTERFACES])
{
    for (int indexInterface = 0; indexInterface < NBR_INTERFACES; indexInterface++)
    {
        vector<int> assignedMissions = population[indexInterface]->assigned_missions;

        for (int indexOnDay = 1; indexOnDay < 7; indexOnDay++)
        {
            //retrieve the schedule of the day number indexOnDay from the interface at index indexInterface
            vector<int> daySchedule = population[indexInterface]->time_table[indexOnDay];
            for (int indexHour = 0; indexHour < daySchedule.size(); indexHour +=2)
            {
                for (auto indexFormation : assignedMissions) //look through assigned missions to find corresponding formation
                {
                    if (areFormationTheSame(indexFormation, indexOnDay, indexHour, daySchedule))
                    {

                    }

                    }
                }
            }

        }
    }
}*/

void greedyFirstSolution(Interface *(&population)[NBR_INTERFACES]) {
    //vector created to keep track of missing formations at the end of greedy
    vector<int> formationIndexes(NBR_FORMATIONS);
    for (int i = 0; i < NBR_FORMATIONS; i++) {
        formationIndexes[i] = i;
    }

    //for (auto i : formationIndexes)
    //{
    //    cout << i << " ";
    //}
    //int count = 0;
    //while (!(formationIndexes.empty()))
    //while (count != 10)
    //{
    //while (!(formationIndexes.empty()) && (count != 1500))
    //{
    //int indexFormation = formationIndexes[0];
    //for(auto indexFormation : formationIndexes)
    for (int indexFormation = 0; indexFormation < NBR_FORMATIONS; indexFormation++) {
        //cout << indexFormation << endl;
        for (int indexInterface = 0; indexInterface < NBR_INTERFACES; indexInterface++) {
            if (hasSameCompetence(indexFormation, indexInterface) == 1) //if interface has required competence
            {
                /*
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

                    //delete assigned formation from formationIndexes vector
                    formationIndexes.erase(remove(formationIndexes.begin(), formationIndexes.end(), indexFormation), formationIndexes.end());

                    //add assigned mission to current interface assigned missions vector
                    population[indexInterface]->assigned_missions.insert(population[indexInterface]->assigned_missions.begin(),indexFormation);

                    //update the distance traveled by the interface
                    population[indexInterface]->distance += sqrt(pow((currPosition[0] - formationPosition[0]),2.0) + pow((currPosition[1] - formationPosition[1]), 2.0));

                    //update current position of the interface
                    population[indexInterface]->currentPosition = formationPosition;

                    break;
                }

            }*/
            }
            // += 1;
        }


        //}

    }
}

// Crossover Operator on two interfaces given two formation slots
void crossingOperator(Interface *(&population)[NBR_INTERFACES], int indexInterfaceOne, int indexInterfaceTwo, int indexFormationOne, int indexFormationTwo)
{
    //reversal of assigned missions
    population[indexInterfaceOne]->assigned_missions.erase(remove(population[indexInterfaceOne]->assigned_missions.begin(), population[indexInterfaceOne]->assigned_missions.end(), indexFormationOne), population[indexInterfaceOne]->assigned_missions.end());
    population[indexInterfaceTwo]->assigned_missions.erase(remove(population[indexInterfaceTwo]->assigned_missions.begin(), population[indexInterfaceTwo]->assigned_missions.end(), indexFormationTwo), population[indexInterfaceTwo]->assigned_missions.end());

    population[indexInterfaceOne]->assigned_missions.insert(population[indexInterfaceOne]->assigned_missions.begin(),indexFormationTwo);
    population[indexInterfaceTwo]->assigned_missions.insert(population[indexInterfaceTwo]->assigned_missions.begin(),indexFormationOne);

    //declare intermediate variables for readability
    int startHF1 = formation[indexFormationOne][4];
    int startHF2 = formation[indexFormationTwo][4];

    //int dayF1 = getDayFormation(indexFormationOne);
    //int dayF2 = getDayFormation(indexFormationTwo);

    //int endHF1 = formation[indexFormationOne][5];
    //int endHF2 = formation[indexFormationTwo][5];

    //int startingPointF1 = dayF1 ? 0 : int(population[indexInterfaceOne]->time_table[dayF1].size() / 2);
    //int startingPointF2 = dayF2 ? 0 : int(population[indexInterfaceTwo]->time_table[dayF2].size() / 2);

    //adding Formation 2 to Interface 1 schedule
    //population[indexInterfaceOne]->time_table[dayF2][startingPointF2] = startHF2;
    //population[indexInterfaceOne]->time_table[dayF2][startingPointF2+1] = endHF2;

    //adding Formation 1 to Interface 2 schedule
    //population[indexInterfaceTwo]->time_table[dayF1][startingPointF1] = startHF1;
    //population[indexInterfaceTwo]->time_table[dayF1][startingPointF1+1] = endHF1;
}

void tournamentSelection(float mean_distance, vector<Interface*> pool, Interface *(&new_pop)[NBR_INTERFACES], bool secondSelection = false) {

    int pool_length = pool.size(); // 24
    int tournament_pool_length = pool_length / 2; //12
    float score;

    vector<Interface *> tournament_pool;
    vector<Interface *> result_pool;

    random_device rd;
    mt19937 nb_gen(rd());
    uniform_int_distribution<int> pool_distribution(0, pool_length - 1);

    for (int i = 0; i < tournament_pool_length; i++)
        tournament_pool.push_back(pool[pool_distribution(nb_gen)]);

    while (result_pool.size() != tournament_pool_length) {
        float maxFitness = 0;
        Interface *bestInterface;

        for (auto &indiv : tournament_pool) {
            score = indiv->evaluateIndividu(mean_distance);

            if (score >= maxFitness) {
                bestInterface = indiv;
                maxFitness = score;
            }
        }
        result_pool.push_back(bestInterface);
        tournament_pool.erase(remove(tournament_pool.begin(), tournament_pool.end(), bestInterface), tournament_pool.end());
    }

    int secondTurn = secondSelection ? tournament_pool_length  : 0;

    for (int j = 0; j < result_pool.size(); j++) {
        new_pop[j + secondTurn] = result_pool[j];
    }
}

void createNewPopulation(Interface *(&population)[NBR_INTERFACES], Interface *(&new_pop)[NBR_INTERFACES])
{
    float mean_distance, travelDistance = 0.0;

    vector<Interface *> sign_pool;
    vector<Interface *> lpc_pool;

    // remplissage des pools
    for(int i = 0; i < NBR_INTERFACES; i++){
        travelDistance += population[i]->distance;

        new_pop[i] = new Interface();

        if (population[i]->competence[0] == 1 && population[i]->competence[1] == 0)
            sign_pool.push_back(population[i]);

        else if(population[i]->competence[0] == 0 && population[i]->competence[1] == 1)
            lpc_pool.push_back(population[i]);
        else
            sign_pool.size() < lpc_pool.size() ? sign_pool.push_back(population[i]) : lpc_pool.push_back(population[i]);

    }
    mean_distance = getMean(travelDistance);

    tournamentSelection(mean_distance, sign_pool, new_pop);
    tournamentSelection(mean_distance, lpc_pool, new_pop, true);
}

int main()
{
    cout << "IT45 - Probleme d affectation d employes\n" << endl;
    cout << "Configuration of the problem" << endl;
    cout << "* Number of Interfaces = " << NBR_INTERFACES << endl;
    cout << "* Number of Apprentices = " << NBR_APPRENANTS << endl;
    cout << "* Number of nodes = " << NBR_NODES << endl << endl;

    Interface *starting_population[NBR_INTERFACES];
    Interface *next_population[NBR_INTERFACES];
    Formation *formations_list[NBR_FORMATIONS];

    cout << "fill population" << endl;
    fillPopulation(starting_population);    // Remplir la solution initiale starting_population
    cout << "fill formation" << endl;
    fillFormations(formations_list);

    for(Formation *f : formations_list)
        cout << *f << endl;

    /*
    greedyFirstSolution(starting_population);
    createNewPopulation(starting_population, next_population);

    float eval = evaluatePopulation(starting_population);
    cout << "Eval of starting pop is " << eval << endl;

    eval = evaluatePopulation(next_population);
    cout << "Eval of next pop is " << eval << endl;

    cout << *starting_population[1] << endl << *starting_population[2] << endl;

    for(Interface *i : starting_population)
        cout << *i << endl;

    //for(Interface *i : next_population)
    //    cout << *i << endl;

    if(isSolutionFeasible(starting_population))
        cout << "Complete solution" << endl;
    else
        cout << "Incomplete solution" << endl;

    //crossingOperator(starting_population, 1, 2, 21, 32);
    */

    /* Main algo
        1. Init pop - DONE
        2. Eval pop - DONE

        3. while(nbIteration < limit || score qui stagne)
            4. next_pop filled grâce à la selection = selection des parents - ALMOST DONE
            5. Croisement dans next_population
            6. Contenu de next pop dans starting pop
            7. Evaluer new pop - DONE
     */

    return 0;
}

