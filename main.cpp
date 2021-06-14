#include <iostream>
#include <cmath>
#include <random>
#include <functional>
#include <ctime>

#include "instances/instance-formations8.h"

#include "Interface.h"

using namespace std;

Formation *formations_list[NBR_FORMATIONS];

inline float getMean(float travelDistance){
    return travelDistance / NBR_INTERFACES;
}

float evaluatePopulation(Interface *(&population)[NBR_INTERFACES])
{
    int nbPenalty = 0;    //get total number of specialties non fufilled

    float travelDistance = 0.0, varianceValue = 0.0;
    float variance, ecart_type, mean_distance, correlation;      // Correlation factor (cf. pdf)

    for (auto & indiv : population) {
        nbPenalty += indiv->getPenalty();
        travelDistance += indiv->distance;
        varianceValue += indiv->distance * indiv->distance;
    }

    mean_distance = getMean(travelDistance);
    correlation = travelDistance / NBR_FORMATIONS;

    variance = float(varianceValue / pow((NBR_INTERFACES - mean_distance), 2));

    ecart_type = sqrt(variance);

    return (float)(0.5 * (mean_distance + ecart_type) + 0.5 * correlation * nbPenalty);
}

vector<float> getFormationPosition(int indexFormation) //return formation center position according to formation's speciality
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

void fillPopulation(Interface *(&population)[NBR_INTERFACES]) //fill starting population according to instance
{
    for(int i = 0; i < NBR_INTERFACES; i++)
    {
        auto *intervenant = new Interface();

        intervenant->competence = competences_interfaces[i];
        intervenant->speciality = specialite_interfaces[i];
        intervenant->currentPosition = {coord[0][0], coord[0][1]};
        population[i] = intervenant;
    }
}

void fillFormations(Formation *(&form_list)[NBR_FORMATIONS]) //fill formations_lists according to instance
{
    for (int i = 0; i < NBR_FORMATIONS; i++)
    {
        auto *form = new Formation();

        form->id = formation[i][0];
        form->indexSpec = formation[i][1];
        form->comp = formation[i][2];
        form->day = formation[i][3];
        form->startHour = formation[i][4];
        form->endHour = formation[i][5];
        form->position = getFormationPosition(i);

        form_list[i] = form;
    }
}
bool isSolutionFeasible(Interface *(&population)[NBR_INTERFACES]) // true if all missions have been assigned
{
    int sum = 0;
    for(Interface *i : population)
    {
        sum += int(i->assigned_missions.size());
    }
    int difference  = int(sum - ((sizeof(formation)/sizeof(*formation))));
    cout << abs(difference) << " formations missing" << endl;
    return sum == ((sizeof(formation)/sizeof(*formation))); // true if we assigned all the missions false otherwise
}


inline bool hasSameCompetence(int indexFormation, int indexInterface) //true if interface has required competence for formation
{
    int competence_form = formation[indexFormation][2];

    return competence_form == 0 ?
                  competences_interfaces[indexInterface][0] == 1
                                 : competences_interfaces[indexInterface][1] == 1;

}


inline bool areRangesOverlapping(int startTime1, int endTime1, int startTime2, int endTime2)
{
    return (endTime1 <= startTime2) || (endTime2 <= startTime1);
}

inline int day(int indexFormation)
{
    return formations_list[indexFormation]->day;
}

inline bool isAmplitudeOutpassed(Interface *(&population)[NBR_INTERFACES], int indexInterface, int indexFormation) //true if daily hours limit isn't reached
{
    if ((population[indexInterface]->hoursWorkedPerDay[day(indexFormation)] + (formations_list[indexFormation]->endHour - formations_list[indexFormation]->startHour)) <= 12)
        return true;
    else
        return false;
}

inline bool isWeeklyHoursQuotaOutpassed(Interface *(&population)[NBR_INTERFACES], int indexInterface, int indexFormation) //true if weekly hours limits isn't reached
{
    return population[indexInterface]->hoursWorked + (formations_list[indexFormation]->endHour - formations_list[indexFormation]->startHour) < 35;
}

//check if interface's available for a formation, if yes returns true and where to insert the formation in the timetable
pair<bool, int> isFree(int indexInterface, int indexFormation, Interface *(&population)[NBR_INTERFACES])
{

    pair <bool, int> result (false, -1);
    int day_ = day(indexFormation);
    int dayScheduleSize = population[indexInterface]->time_table[day_].size();

    if(isAmplitudeOutpassed(population, indexInterface, indexFormation) && isWeeklyHoursQuotaOutpassed(population, indexInterface, indexFormation))
    {
        if(dayScheduleSize == 0)
        {
            result.first = true;
            result.second = 0;
            return result;
        }
        if (population[indexInterface]->time_table[day_][0]->id == -1)
        {
            result.first = true;
            result.second = 0;
            return result;
        } else if (formations_list[indexFormation]->endHour <=
                   population[indexInterface]->time_table[day_][0]->startHour)
        {
            result.first = true;
            result.second = 0;
            return result;
        } else if (formations_list[indexFormation]->startHour >=
                   population[indexInterface]->time_table[day_][
                           population[indexInterface]->time_table[day_].size()-1]->endHour)
        {
            result.first = true;
            result.second = int(population[indexInterface]->time_table[day_].size());
            return result;

        }
        else
        {
            int indexOnDaySchedule = 0;
            for (auto &currForm : population[indexInterface]->time_table[day_])
            {
                if (formations_list[indexFormation]->startHour > currForm->endHour)
                {
                    if (indexOnDaySchedule != population[indexInterface]->time_table[day_].size() - 1)
                    {
                        if (formations_list[indexFormation]->endHour <=
                            population[indexInterface]->time_table[day_][indexOnDaySchedule +
                                                                                        1]->startHour)
                        {
                            result.first = true;
                            result.second = indexOnDaySchedule + 1;
                            return result;
                        }
                    }
                } else if (indexOnDaySchedule !=
                           population[indexInterface]->time_table[day_].size() - 1)
                {
                    if (formations_list[indexFormation]->startHour == currForm->endHour)
                    {
                        if (formations_list[indexFormation]->endHour <=
                            population[indexInterface]->time_table[day_][indexOnDaySchedule +
                                                                                        1]->startHour)
                        {
                            result.first = true;
                            result.second = indexOnDaySchedule + 1;
                            return result;
                        }
                    }
                }
            }
        }
    }
    return result;
}

auto euclideanDistance(float x1, float x2, float y1, float y2)
{
    return float(sqrt(pow(x2 - x1, 2.0)+pow(y2 - y1,2.0)));
}


void updateInterfaceDistance(Interface *(&population)[NBR_INTERFACES]) //compute distance traveled by all the interfaces during a week
{
    for (auto &currInterface : population)
    {
        for (auto &timetable : currInterface->time_table)
        {
            for (int i = 0; i < 6; i++)
            {
                for (auto & j : timetable.second)
                {
                    vector<float> formationPlace = getFormationPosition(j->indexSpec);

                    currInterface->distance += euclideanDistance(currInterface->currentPosition[0], formationPlace[0], currInterface->currentPosition[1], formationPlace[1]);
                    currInterface->currentPosition = formationPlace;
                }
                //Distance from last formation to HQ at the end of the day
                currInterface->distance += euclideanDistance(currInterface->currentPosition[0], coord[0][0], currInterface->currentPosition[1], coord[0][1]);
                currInterface->currentPosition = {coord[0][0], coord[0][1]};

            }

        }

    }
}

void greedyFirstSolution(Interface *(&population)[NBR_INTERFACES])
{
    //vector created to keep track of missing formations at the end of greedy
    vector<int> formationIndexes(NBR_FORMATIONS);
    for (int i = 0; i < NBR_FORMATIONS; i++) {
        formationIndexes[i] = i;
    }

    for (int indexFormation = 0; indexFormation < NBR_FORMATIONS; indexFormation++)
    {
        for (int indexInterface = 0; indexInterface < NBR_INTERFACES; indexInterface++)
        {
            if (hasSameCompetence(indexFormation, indexInterface) == 1) //if interface has required competence
            {
                int day_ = day(indexFormation); //get day of curr formation
                pair<bool,int> result = isFree(indexInterface, indexFormation, population);

                if (result.first)
                {
                    //we have to place the formation at the right place on the day
                    if (result.second == 0) //replace first null formation
                    {
                        population[indexInterface]->time_table[day_].at(0) = formations_list[indexFormation];
                    }
                    else //insert at right time of the day
                    {
                        population[indexInterface]->time_table[day_].insert(
                                population[indexInterface]->time_table[day_].begin() + result.second, formations_list[indexFormation]);
                    }
                    //delete assigned formation from formationIndexes vector
                    formationIndexes.erase(remove(formationIndexes.begin(), formationIndexes.end(), indexFormation), formationIndexes.end());

                    //update hours worked
                    population[indexInterface]->hoursWorked += (formations_list[indexFormation]->endHour - formations_list[indexFormation]->startHour);
                    population[indexInterface]->hoursWorkedPerDay[day_] += (formations_list[indexFormation]->endHour - formations_list[indexFormation]->startHour);

                    //add assigned mission to current interface assigned missions vector
                    population[indexInterface]->assigned_missions.insert(population[indexInterface]->assigned_missions.begin(),indexFormation);
                    break;
                }
            }
        }
    }
    updateInterfaceDistance(population);
}

// Crossover Operator on two interfaces given two formation slots
void crossingOperator(Interface *(&population)[NBR_INTERFACES], int indexInterfaceOne, int indexInterfaceTwo, int indexFormationOne, int indexFormationTwo, int index1, int index2)
{
    int durationFormationOne = formations_list[indexFormationOne]->endHour - formations_list[indexFormationOne]->startHour;
    int durationFormationTwo = formations_list[indexFormationTwo]->endHour - formations_list[indexFormationTwo]->startHour;
    int dayF1 = day(indexFormationOne);
    int dayF2 = day(indexFormationTwo);

    //reversal of assigned missions
    population[indexInterfaceOne]->assigned_missions.erase(remove(population[indexInterfaceOne]->assigned_missions.begin(), population[indexInterfaceOne]->assigned_missions.end(), indexFormationOne), population[indexInterfaceOne]->assigned_missions.end());
    population[indexInterfaceTwo]->assigned_missions.erase(remove(population[indexInterfaceTwo]->assigned_missions.begin(), population[indexInterfaceTwo]->assigned_missions.end(), indexFormationTwo), population[indexInterfaceTwo]->assigned_missions.end());

    population[indexInterfaceOne]->assigned_missions.insert(population[indexInterfaceOne]->assigned_missions.begin(),indexFormationTwo);
    population[indexInterfaceTwo]->assigned_missions.insert(population[indexInterfaceTwo]->assigned_missions.begin(),indexFormationOne);

    population[indexInterfaceOne]->time_table[dayF1].erase(population[indexInterfaceOne]->time_table[dayF1].begin() + index1);
    population[indexInterfaceTwo]->time_table[dayF2].erase(population[indexInterfaceTwo]->time_table[dayF2].begin() + index2);

    population[indexInterfaceOne]->hoursWorked -= durationFormationOne;
    population[indexInterfaceOne]->hoursWorkedPerDay[dayF1] -= durationFormationOne;

    population[indexInterfaceTwo]->hoursWorked -= durationFormationTwo;
    population[indexInterfaceTwo]->hoursWorkedPerDay[dayF2] -= durationFormationTwo;

    population[indexInterfaceOne]->hoursWorked += durationFormationTwo;
    population[indexInterfaceOne]->hoursWorkedPerDay[dayF2] += durationFormationTwo;

    population[indexInterfaceTwo]->hoursWorked += durationFormationOne;
    population[indexInterfaceTwo]->hoursWorkedPerDay[dayF1] += durationFormationOne;

    population[indexInterfaceOne]->time_table[dayF2].insert(
            population[indexInterfaceOne]->time_table[dayF2].begin() + index1, formations_list[indexFormationTwo]);

    population[indexInterfaceTwo]->time_table[dayF1].insert(
            population[indexInterfaceTwo]->time_table[dayF1].begin() + index2, formations_list[indexFormationOne]);

}

pair<int, int> tournamentSelection(Interface *(&population)[NBR_INTERFACES], bool secondPool = false) {

    int pool_length, tournament_pool_length;
    float bestScore, secondBestScore, currScore, mean_distance, travelDistance = 0.0;

    vector<Interface *> pool;
    vector<int> indexes;
    vector<int> tournament_indexes;


    // POOL FILLING

    for(int i = 0; i < NBR_INTERFACES; i++){
        travelDistance += population[i]->distance;
        int true_index = i;

        if (secondPool){
            if (population[i]->competence[0] == 1)
            {
                pool.push_back(population[i]);
                indexes.push_back(true_index);
            }
        }
        else{
            if(population[i]->competence[1] == 1)
            {
                pool.push_back(population[i]);
                indexes.push_back(true_index);
            }
        }
    }

    mean_distance = getMean(travelDistance);

    pool_length = int(pool.size());
    tournament_pool_length = pool_length / 2;

    vector<Interface *> tournament_pool;

    random_device rd;
    mt19937 nb_gen(rd());
    uniform_int_distribution<int> pool_distribution(0, pool_length - 1);

    // SELECT PARTICIPANTS

    for (int i = 0; i < tournament_pool_length; i++)
    {
        int random = pool_distribution(nb_gen);

        tournament_pool.push_back(pool[random]);
        tournament_indexes.push_back(indexes[random]);
    }

    // GET 2 BEST INTERFACES

    pair<int, int> result;

    bestScore = tournament_pool[1]->getInterfaceEvaluation(mean_distance);
    result.first = tournament_indexes[1];

    secondBestScore = tournament_pool[0]->getInterfaceEvaluation(mean_distance);
    result.second = tournament_indexes[0];

    if(secondBestScore > bestScore){
        bestScore = tournament_pool[0]->getInterfaceEvaluation(mean_distance);
        result.first = tournament_indexes[0];

        secondBestScore = tournament_pool[1]->getInterfaceEvaluation(mean_distance);
        result.second = tournament_indexes[1];
    }

    for (int i = 2; i < tournament_pool_length; i++) {
        currScore = tournament_pool[i]->getInterfaceEvaluation(mean_distance);

        if (currScore > bestScore) {
            secondBestScore = bestScore;
            result.second = result.first;

            bestScore = currScore;
            result.first = tournament_indexes[i];
        }
        else if (currScore > secondBestScore && currScore != bestScore) {
            secondBestScore = currScore;
            result.second = tournament_indexes[i];
        }
    }

    return result;
}

bool containsValue(pair<int, int> value, vector<pair<int, int>>& visitedIndex)
{
    bool found = false;

    for (auto & elem : visitedIndex)

        if (value == elem)
        {
            found = true;
            break;
        }

    return found;
}

pair<int, int> getNonSpecialityForm(Interface * (&inter), vector<pair<int, int>>& visitedIndex)
{
    bool quit = false;
    pair<int, int> result(-1, -1);

    for (int i = 1; i < inter->time_table.size() + 1; i++)
    {
        for (int j = 0; j < inter->time_table[i].size(); j++)
        {
            if(inter->time_table[i][j]->id != -1 && inter->speciality[inter->time_table[i][j]->indexSpec] == 0 )
            {
                result.first = i; result.second = j;

                if (!containsValue(result, visitedIndex))
                {
                    quit = true;
                    break;
                }

            }
        }

        if(quit)
            break;
    }

    visitedIndex.push_back(result);
    return result;
}

pair<int, int> getRandomForm(Interface * (&inter), vector<pair<int, int>>& visitedIndex)
{
    random_device rd;
    mt19937 nb_gen(rd());

    int rd_day; int rd_form;
    pair<int, int> result{-1, -1};

    while (containsValue(result, visitedIndex) || inter->time_table[result.first][result.second]->id != -1)
    {
        uniform_int_distribution<int> day_distribution(1, 6);
        rd_day = day_distribution(nb_gen);

        uniform_int_distribution<int> form_distribution(0,  int(inter->time_table[rd_day].size() - 1));
        rd_form = form_distribution(nb_gen);

        result.first = rd_day, result.second = rd_form;
    }

    visitedIndex.push_back(result);

    return result;
}

int getIndexFromID(int id, int day, int startHour, int endHour)
{
    int result = -1;

    int initialValue = (NBR_FORMATIONS / NBR_APPRENANTS) * id;
    int limit = initialValue + (NBR_FORMATIONS / NBR_APPRENANTS);

    for (int k = initialValue; k < limit; k++)
    {
        if (formation[k][3] == day && formation[k][4] == startHour && formation[k][5] == endHour)
            result = k;
    }
    return result;
}

tuple <bool, int, int> isSwappable(int indexFirstInterface, int indexSecondInterface, pair<int, int>& firstFormIndexes, pair<int, int>& secondFormIndexes, Interface *(&population)[NBR_INTERFACES])
{
    Interface * copy_pop[NBR_INTERFACES];

    for (int i = 0; i < NBR_INTERFACES; i++)
    {
        copy_pop[i] = new Interface(*population[i]);
    }


    Interface * firstInter = copy_pop[indexFirstInterface];
    Interface * secondInter = copy_pop[indexSecondInterface];

    vector<Formation *> schedule = firstInter->time_table[firstFormIndexes.first];
    // TODO : ici schedule est vide car firstInter->time_table[3] est vide aussi
    // TODO :
    int durationFormationOne = firstInter->time_table[firstFormIndexes.first][firstFormIndexes.second]->endHour - firstInter->time_table[firstFormIndexes.first][firstFormIndexes.second]->startHour;
    firstInter->hoursWorked -= durationFormationOne;
    firstInter->hoursWorkedPerDay[day(firstFormIndexes.second)] -= durationFormationOne;
    int test = schedule[firstFormIndexes.second]->id;

    int index1 = getIndexFromID(schedule[firstFormIndexes.second]->id, schedule[firstFormIndexes.second]->day, schedule[firstFormIndexes.second]->startHour, schedule[firstFormIndexes.second]->endHour);

    schedule.erase(remove(schedule.begin(), schedule.end(), schedule[firstFormIndexes.second]), schedule.end());

    firstInter->time_table[firstFormIndexes.first] = schedule;



    schedule = secondInter->time_table[secondFormIndexes.first];

    int durationFormationTwo = secondInter->time_table[secondFormIndexes.first][secondFormIndexes.second]->endHour - secondInter->time_table[secondFormIndexes.first][secondFormIndexes.second]->startHour;
    secondInter->hoursWorked -= durationFormationTwo;
    secondInter->hoursWorkedPerDay[day(secondFormIndexes.second)] -= durationFormationTwo;

    int index2 = getIndexFromID(schedule[secondFormIndexes.second]->id, schedule[secondFormIndexes.second]->day, schedule[secondFormIndexes.second]->startHour, schedule[secondFormIndexes.second]->endHour);

    schedule.erase(remove(schedule.begin(), schedule.end(), schedule[secondFormIndexes.second]), schedule.end());

    secondInter->time_table[secondFormIndexes.first] = schedule;

    auto r1 = isFree(indexFirstInterface, index1, copy_pop);
    auto r2 = isFree(indexSecondInterface, index2, copy_pop);

    return {r1.first && r2.first, r1.second, r2.second};
}

// add pair<Interface*, Interface*> instead of void if problems occur
void crossInterfaces(int indexFirstInterface, int indexSecondInterface, Interface *(&population)[NBR_INTERFACES])
{
    bool swap = false;

    pair<int, int> firstFormIndexes;
    pair<int, int> secondFormIndexes;
    tuple<bool, int, int> result;

    vector<pair<int, int>> visitedIndexesFirst;
    vector<pair<int, int>> visitedIndexesSecond;

    Interface * firstInterface = population[indexFirstInterface];
    Interface * secondInterface = population[indexSecondInterface];

    while (visitedIndexesFirst.size() != firstInterface->assigned_missions.size() && visitedIndexesSecond.size() != secondInterface->assigned_missions.size())
    {
        firstFormIndexes = getNonSpecialityForm(firstInterface, visitedIndexesFirst);
        secondFormIndexes = getNonSpecialityForm(secondInterface, visitedIndexesSecond);

        if (firstFormIndexes.first == -1)
            firstFormIndexes = getRandomForm(firstInterface, visitedIndexesFirst);

        if (secondFormIndexes.first == -1)
            secondFormIndexes = getRandomForm(secondInterface, visitedIndexesSecond);
    }

    for (int i = 0; i < visitedIndexesFirst.size(); i++)
    {
        for (int j = 0; j < visitedIndexesSecond.size(); j++)
        {
            //firstFormIndexes.first = secondFormIndexes.first = 1;
            //firstFormIndexes.second = secondFormIndexes.second = 0;
            //result = isSwappable(1,2,firstFormIndexes, secondFormIndexes, population);

            result = isSwappable(indexFirstInterface, indexSecondInterface, visitedIndexesFirst[i], visitedIndexesSecond[j], population);

            swap = get<0>(result);

            if (swap)
            {
                firstFormIndexes = visitedIndexesFirst[i];
                secondFormIndexes = visitedIndexesSecond[j];
                break;
            }
        }

        if(swap)
            break;
    }

    cout << "DEBUG BEFORE" << endl;
    cout << *firstInterface << endl;
    cout << "Second inter" << endl;
    cout << *secondInterface << endl;

    if (swap)
    {
        cout << "swapped" << endl;

        int indexF1 = getIndexFromID(firstInterface->time_table[firstFormIndexes.first][firstFormIndexes.second]->id, firstInterface->time_table[firstFormIndexes.first][firstFormIndexes.second]->day, firstInterface->time_table[firstFormIndexes.first][firstFormIndexes.second]->startHour, firstInterface->time_table[firstFormIndexes.first][firstFormIndexes.second]->endHour);
        int indexF2 = getIndexFromID(secondInterface->time_table[secondFormIndexes.first][secondFormIndexes.second]->id, secondInterface->time_table[secondFormIndexes.first][secondFormIndexes.second]->day, secondInterface->time_table[secondFormIndexes.first][secondFormIndexes.second]->startHour, secondInterface->time_table[secondFormIndexes.first][secondFormIndexes.second]->endHour);

        //crossingOperator(population, 1, 2, 28, 47, get<1>(result), get<2>(result));
        //crossingOperator(population, indexFirstInterface, indexSecondInterface, firstFormIndexes.second, secondFormIndexes.second, get<1>(result), get<2>(result));
        if(indexF1 != -1 && indexF2 != -1)
            crossingOperator(population, indexFirstInterface, indexSecondInterface, indexF1, indexF2, get<1>(result), get<2>(result));
    }
    else
    {
        cout << "didn't swap" << endl;
    }

    cout << "DEBUG AFTER" << endl;
    cout << *firstInterface << endl;
    cout << "Second inter" << endl;
    cout << *secondInterface << endl;

    for (int i = 0; i < 8; ++i) {
        cout << endl;
    }

}

inline void print_population(Interface *(&population)[NBR_INTERFACES])
{
    for(Interface *i : population)
        cout << *i << endl;
}

int main()
{
    /*
    cout << "IT45 - Probleme d affectation d employes\n" << endl;
    cout << "Configuration of the problem" << endl;
    cout << "* Number of Interfaces = " << NBR_INTERFACES << endl;
    cout << "* Number of Apprentices = " << NBR_APPRENANTS << endl;
    cout << "* Number of nodes = " << NBR_NODES << endl << endl;

    Interface *starting_population[NBR_INTERFACES];
    Interface *next_population[NBR_INTERFACES];

    fillPopulation(starting_population);    // Fill starting population
    fillFormations(formations_list);

    greedyFirstSolution(starting_population);

    if(isSolutionFeasible(starting_population))
        cout << "Complete solution" << endl;
    else
        cout << "Incomplete solution" << endl;

    //for(auto &f : formations_list)
    //    f->displayFormation();

    int index = 0;
    for(auto &i : starting_population)
    {
        cout << "Interface " << index << endl;
        i->displayTimeTable();
        cout << endl;
        index += 1;
    }


    float eval = evaluatePopulation(starting_population);
    cout << "Eval of starting pop is " << eval << endl;
    //crossingOperator(starting_population, 1, 2, 21, 32, 0, 0);

    //eval = evaluatePopulation(next_population);
    //cout << "Eval of next pop is " << eval << endl;

    //cout << *starting_population[1] << endl << *starting_population[2] << endl;

    //for(Interface *i : starting_population)
    //    cout << *i << endl;

    //for(Interface *i : next_population)
    //    cout << *i << endl;

    //crossingOperator(starting_population, 1, 2, 21, 32);

    */
    int test = getIndexFromID(19,4,9,11);
    // Main algo
    cout << "IT45 - Probleme d affectation d employes\n" << endl;
    cout << "Configuration of the problem" << endl;
    cout << "* Number of Interfaces = " << NBR_INTERFACES << endl;
    cout << "* Number of Apprentices = " << NBR_APPRENANTS << endl;
    cout << "* Number of nodes = " << NBR_NODES << endl << endl;

    Interface *starting_population[NBR_INTERFACES];
    Interface *next_population[NBR_INTERFACES];

     //1. Init pop - DONE
    fillPopulation(starting_population);// Fill starting population
    fillFormations(formations_list);
    greedyFirstSolution(starting_population);

    isSolutionFeasible(starting_population);

     //2. Eval pop - DONE
    float eval = evaluatePopulation(starting_population);
    cout << "Eval of starting pop is " << eval << endl;

    int index = 0;
    for( auto &i : starting_population)
    {
        //if (i->competence[0] == 0 && i->competence[1]== 1)
        //{
            cout << "interface : " << index << endl;
            i->displayTimeTable();
            index+=1;
        //}

    }

     //3.
     //while(nbIteration < limit || score qui stagne) // Pas sur que score qui stagne soit relevantdouble t = clock();
     double t = clock();
    bool stop = false;
     //while(t / CLOCKS_PER_SEC < 30)
     while(!stop)
     {
         for (int i = 0; i < NBR_INTERFACES; i++) {
             next_population[i] = new Interface(*starting_population[i]);
         }
        //4. next_pop filled grâce à la selection = selection des parents - DONE
        //5. Croisement dans next_population

        for(int i = 0; i < NBR_INTERFACES; i++){
            cout << i << endl;
            pair<int, int> to_cross = tournamentSelection(next_population);

            //pair<int, int> to_cross{1, 2};
            crossInterfaces(to_cross.first, to_cross.second, next_population);

            to_cross = tournamentSelection(next_population, true);
            crossInterfaces(to_cross.first, to_cross.second, next_population);
        }

        //7. Evaluer new pop - DONE
        eval = evaluatePopulation(next_population);
        cout << "New pop eval is : " << eval << endl;

        //6. Contenu de next pop dans starting pop | Passage à la nouvelle gen
        for (int i = 0; i < NBR_INTERFACES; i++) {
            starting_population[i] = next_population[i];
        }
        stop = true;
         //t = clock();

     } //FIN WHILE

     cout << "Time out !" << endl;
    int index2 = 0;
    for( auto &i : starting_population)
    {
        //if (i->competence[0] == 0 && i->competence[1]== 1)
        //{
        cout << "interface : " << index2 << endl;
        i->displayTimeTable();
        index2+=1;
        //}

    }
    return 0;
}

