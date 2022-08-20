/**
 * Student Name: Hizir Ozcelik
 * Student ID: 991578495
 * Date modified: July 19, 2022
 * Above data must be filled and NO OTHER CHANGE MUST BE MADE in this file!!
 * household.h built by M. Mohiuddin to be shared with students as part of the documentation and starting application
 * for assignment's solution.
 * It lists down various constants, constant arrays, user defined types (structures) and the functions prototypes.
 */
#ifndef HOUSEHOLD_H_INCLUDED
#define HOUSEHOLD_H_INCLUDED
#define SIZE 100  // Size of the dataset, for testing purposing you may reduce it to around 20.
#define MAX_FAMILYSIZE 12  // largest allowed household size
#define ARR_TOWN_LEN 6   // maximum number of towns i.e. size of townsArr
#define ARR_REGION_LEN 3 // maximum number of regions i.e. size of regionsArr
#define ARR_RACE_LEN 5  // maximum number of races i.e. size of racesArr
#define REGION_NAME_LEN 10 // maximum number of characters in the name of a region
#define TOWN_NAME_LEN 15   // maximum number of characters in the name of a town
#define RACE_NAME_LEN 20   // maximum number of characters in the name of a race
static char racesArr[ARR_RACE_LEN][RACE_NAME_LEN] = {"CAUCASIAN", "INDIGENOUS", "AFRO-AMERICAN", "ASIAN", "OTHER"};
static char regionsArr[ARR_REGION_LEN][REGION_NAME_LEN] = {"DURHAM", "PEEL", "YORK"};
static char townsArr[ARR_TOWN_LEN][TOWN_NAME_LEN] = {"OSHAWA", "WHITBY", "BRAMPTON", "MISSISSAUGA", "MAPLE", "VAUGHAN"};
typedef struct household {
    char race[RACE_NAME_LEN];
    char region[REGION_NAME_LEN];
    char town[TOWN_NAME_LEN];
    int familySize;
    int fullyVaccinated;
    int testedPositive;
} Household;
typedef struct pair_ {
    int count;
    char town[20];
} LocationCountPair;

typedef struct temp_ {
    Household data;
    struct temp_ *next;
} Node, *NodePtr;

// Menu functions listed under item A (refer to problem specifications)
void displayRecordsOfOneRegion(NodePtr top, char region[]);

void displayRecordsOfOneTown(NodePtr top, char town[]);

void displayRecordsOfOneRace(NodePtr top, char race[]);

// Menu functions listed under item B (refer to problem specifications)
void displayRecordsOfRegionWithPositiveCases(NodePtr top, char region[], int numOfPositiveCases);

void regionsTownWiseRankingVaccinated(NodePtr top);

Household userInteractionForRecordAddition();

void deleteNodesGivenCriteria(NodePtr *top, char *, char *, char *);

void printList(NodePtr ptr);

void printRecord(int ctr, NodePtr ptr);

void displayRecordsFromFile(char fileName[]);

void initializeData(NodePtr *top);

Household makeHousehold(char region[], char town[], char race[], int tot, int totPos, int familySize);

NodePtr makeNode(Household num);

void addNode(NodePtr *top, Household num);

void deleteNode(NodePtr *tom);

void writeListToFile(NodePtr top, char *fileName);

char *regionMapping(int x);

char *raceMapping(int x);

char *townMappingRegionBased(int region, int x);

char *townMapping(int x);

void menu(NodePtr *top);

int dataValidation(int upperbound);

void sortSelection(LocationCountPair pairs[], int arrSize);

void deleteAllNodes(NodePtr *tom);

#endif // HOUSEHOLD_H_INCLUDED
