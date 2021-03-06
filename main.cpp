#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "SearchEngine.h"
#include "Configures.h"

#include "SimpleParser.h"
#include "Database.h"
#include <omp.h>

#include "MachineTaskSchedulingDatabase.h"
#include "MachineTaskSchedulingIndividual.h"
#include "MachineTaskSchedulingIndividualBuilder.h"
#include "MachineTaskSchedulingParser.h"
#include "MachineTaskSchedulingCrossover.h"
#include "MachineTaskSchedulingMutation.h"

using namespace std;

int main(int argc, char * argv[]) {
//    double wall_timer = omp_get_wtime();

    int seed = atoi(argv[3]);
    if(atoi(argv[3]) == 0)
        seed = time(NULL);
    //seed = 42;

    srand(seed);

    conf = new Configures(); //Configuration class with several GA parameters
    conf->seed = seed;
    conf->elitism = 0.2; // elitism percentage
    conf->generations = 100000; // num_max of generations
    conf->popSize = 100; // size of population
    conf->crossover = 0.5;  //crossing percentage
    conf->mutate = 0.5; // mutate percentage
    conf->MAX_THREADS = omp_get_max_threads(); // num_max_threads omp
    conf->max_generationsWithoutImprovement = 50;
    conf->MAX_TIME = atoi(argv[2]);

    //Create a problem database and load the input file.
    Database * database = new MachineTaskSchedulingDatabase();
    database->loadBase(argv[1]); // argv[1] is the path to the input file

//    //Create an evaluator of the problem
    Parser * parser = new MachineTaskSchedulingParser();
    MachineTaskSchedulingParser * machinetaskscheduling = dynamic_cast<MachineTaskSchedulingParser*>(parser);
    machinetaskscheduling->setDatabase(database);

    //Define the individual generator that returns an individual type of problem specific
    MachineTaskSchedulingIndividualBuilder * machineTaskSchedulingIndividualBuilder = new MachineTaskSchedulingIndividualBuilder(database);


    // Set searchEngine parameters
    SearchEngine * searcher = new SearchEngine();
    searcher->setParser(parser);
    //searcher->setMutation();
    //searcher->setCrossover();

    Individual * a[2];
    //Individual * a = machineTaskSchedulingIndividualBuilder->generateIndividuo();
    a[0] = machineTaskSchedulingIndividualBuilder->generateIndividuo();
    a[1] = machineTaskSchedulingIndividualBuilder->generateIndividuo();
    MachineTaskSchedulingCrossover * cross = new MachineTaskSchedulingCrossover();
    cross->cross(a,2);
    //MachineTaskSchedulingMutation * mut = new MachineTaskSchedulingMutation();
    //mut->mutate(a);
    cout << endl << endl;
    //a[0]->print();
    //a->print();


    cout << endl << endl;
//    MachineTaskSchedulingIndividual * s = dynamic_cast<MachineTaskSchedulingIndividual*>(a[0]);
     MachineTaskSchedulingIndividual * s1 = dynamic_cast<MachineTaskSchedulingIndividual*>(a[0]);
     MachineTaskSchedulingIndividual * s2 = dynamic_cast<MachineTaskSchedulingIndividual*>(a[1]);

    //s->calculateTimes(database);

    s1->print();
    cout << endl;
    s2->print();


//    //Instantiated a local search
//    TravelingThiefLocalSearch* ls = new TravelingThiefLocalSearch();
//    ls->setParser(travelingthiefparser);
//    ls->setDatabase(dynamic_cast<TravelingThiefDatabase*>(database));
//
//    // Set searchEngine parameters
//    SearchEngine * searcher = new SearchEngine();
//    searcher->setParser(travelingthiefparser);
//    searcher->setIndividualBuilder(travelingThiefIndividualBuilder);
//    searcher->setMutation(new TravelingThiefMutation());
//    searcher->setLocalSearch(ls);
//    TravelingThiefDatabase *db = dynamic_cast<TravelingThiefDatabase*>(database);
////    for(int i = 0; i < db->cities.size();i++){
////        for(Item * item : db->cities[i]->items){
////            cout << "item->index = " << item->index << " item->city = " <<  item->city << endl;
////        }
////    }
//
//    //Evolves solutions
//    searcher->Evolve();

//    cout << (omp_get_wtime() - wall_timer) << " s" << endl;

    return 0;
}
