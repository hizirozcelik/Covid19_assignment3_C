/**
 * Student Name: Hizir Ozcelik
 * Student ID: 991578495
 * Date modified: July 19, 2022
 * source file for Assignment 3
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "household.h"

// sorting function required for ranking of data
void sortSelection(LocationCountPair arr[], int arrSize) {
    /**
    * Due to sortSelection method doesn't work properly I code my sort below.
    */
    for (int i = 0; i < arrSize; i++) {
        for (int j = i + 1; j < arrSize; j++) {
            if (arr[j].count > arr[i].count) {
                LocationCountPair temp;
                temp.count = arr[i].count;
                strcpy(temp.town, arr[i].town);

                arr[i].count = arr[j].count;
                strcpy(arr[i].town, arr[j].town);

                arr[j].count = temp.count;
                strcpy(arr[j].town, temp.town);
            }
        }
    }
/** Original sort function
    int min = 0, temp = 0;
    char tempStr[20];

    for (int i = 0; i < arrSize; i++) {
//        min = i;  // record the position of the smallest
        for (int j = i + 1; j < arrSize; j++) {
            // update min when finding a smaller element
            if (arr[j].count > arr[min].count)
                min = j;
        }
        // put the smallest element at position i
        temp = arr[i].count;
        arr[i].count = arr[min].count;
        arr[min].count = temp;
        strcpy(tempStr, arr[i].town);
        strcpy(arr[i].town, arr[min].town);
        strcpy(arr[min].town, tempStr);
    }
    */
}

/**
 * This is a generic validation function that takes the upper bound of valid options up to 8 and returns 9 if the user
 * opts to go back to the previous menu instead of providing valid data. Therefore 9 should not be a valid choice!!
 * @param upperbound
 * @return
 */
int dataValidation(int upperbound) {
    int n = 0, num;
    char temp[40];
    while (1) {
        fgets(temp, sizeof(temp), stdin);
        n = sscanf(temp, "%d", &num);
        if (num == 9) return num;
        else if (num >= 0 && num <= upperbound && n == 1) return num;
        else {
            printf("Invalid data, Enter an integer 0 through %d or enter 9 to go back to the main menu. Try again \n",
                   upperbound);
            continue;
        }
    } //while loop ends
}// dataValidation function ends

/**
 *
 * @param x Takes an integer representing a region
 * @return and returns the corresponding region's name
 */
char *regionMapping(int x) {
    char *str;
    switch (x) {
        case 0:
            str = "DURHAM";
            break;
        case 1:
            str = "PEEL";
            break;
        case 2:
            str = "YORK";
            break;
        default:
            str = "YORK";
    }
    return str;
}// ends regionMapping function
/**
 * Full implementation of the menu function is provided that implements entire main user interface of the application.
 * Students are required to implement various functions called in this menu.
 * A list of ToDos is also given for easier development
 * @param top of the list to be provided by reference.
 */
void menu(NodePtr *top) {
    int optionTopLevel = 0;
    while (1) {
        // Display a menu to the user
        char temp[120];
        char option[120];
        int valid = 0;
        puts("Menu:");
        printf("Enter your choice to\n");
        printf("1. display households of a race\n");
        printf("2. display households of a region\n");
        printf("3. display households of a town\n");
        printf("4. display households of a region with a given minimum number of people tested positive for Covid-19\n");
        printf("5. display the regions town-wise ranking of number of people fully vaccinated positive for Covid-19\n");
        printf("6. add a record\n");
        puts("7. delete all records of a region, town and race triplet");
        puts("8. display updated data");
        puts("9. store data to a file");
        puts("10. display data from file");
        puts("0. to exit the program");
        scanf("%d", &optionTopLevel);
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {} // input stream flushing

        if (optionTopLevel == 0) {
            printf("\nThank you");
            return;
        } else if (optionTopLevel > 10) {
            printf("Invalid selection, enter an integer 0 through 10, try again\n");
            continue;
        }
        int regionOption = 0, townOption = 0, raceOption = 0, numberTested, numberTestedPos;
        char filename[120] = "..//data//";
        char strTemp[120];
        switch (optionTopLevel) {
            case 1:
                puts("Enter an integer for race: CAUCASIAN (0), INDIGENOUS(1), AFRO AMERICAN(2), ASIAN(3), and OTHER(4)");
                if ((raceOption = dataValidation(4)) == 9) break;
                displayRecordsOfOneRace(*top, raceMapping(raceOption));
                break;
            case 2:
                puts("Enter an integer for region: DURHAM(0), PEEL(1), and YORK(2):");
                if ((regionOption = dataValidation(2)) == 9) break;
                displayRecordsOfOneRegion(*top, regionMapping(regionOption));
                break;
            case 3:
                puts("Enter an integer for town: OSHAWA(0), WHITBY(1), BRAMPTON(2), MISSISSAUGA(3), MAPLE(4) and VAUGHAN(5)");
                if ((townOption = dataValidation(5)) == 9) break;
                displayRecordsOfOneTown(*top, townMapping(townOption));
                break;
            case 4:
                puts("Enter an integer for region: DURHAM (0), PEEL(1), and YORK(2):");
                if ((regionOption = dataValidation(2)) == 9) break;
                while (valid != 1) {
                    puts("Enter lowerbound of number of Covid-19 positive cases per household in the region");
                    fgets(temp, sizeof(temp), stdin);
                    sscanf(temp, "%d", &numberTestedPos);
                    if (numberTestedPos <= 0) {
                        puts("Invalid data, enter a positive integer, try again");
                        continue;
                    } else valid = 1; // setting valid flag
                }
                valid = 0; // resetting valid flag for next iteration
                displayRecordsOfRegionWithPositiveCases(*top, regionMapping(regionOption), numberTestedPos);
                break;
            case 5:
                regionsTownWiseRankingVaccinated(*top);
                break;
            case 6:
                addNode(top, userInteractionForRecordAddition());
                break;
            case 7:
                puts("Enter region: DURHAM(0), PEEL(1), and YORK(2)");
                fgets(temp, sizeof(temp), stdin);
                sscanf(temp, "%d", &regionOption);
                if (regionOption == 0) {
                    puts("Enter town: OSHAWA(0), WHITBY(1)");
                    fgets(temp, sizeof(temp), stdin);
                    sscanf(temp, "%d", &townOption);
                } else if (regionOption == 1) {
                    puts("Enter town: BRAMPTON(0), MISSISSAUGA(1)");
                    fgets(temp, sizeof(temp), stdin);
                    sscanf(temp, "%d", &townOption);
                } else {
                    puts("Enter town: MAPLE(0),VAUGHAN(1)");
                    fgets(temp, sizeof(temp), stdin);
                    sscanf(temp, "%d", &townOption);
                }
                puts("Enter race");
                puts("Enter an integer: CAUCASIAN (0), INDIGENOUS(1), AFRO AMERICAN(2), ASIAN(3), and OTHER(4)");
                fgets(temp, sizeof(temp), stdin);
                sscanf(temp, "%d", &raceOption);
                deleteNodesGivenCriteria(top, regionMapping(regionOption),
                                         townMappingRegionBased(regionOption, townOption),
                                         raceMapping(raceOption));
                break;
            case 8:
                printList(*top);
                break;
            case 9:
                puts("Enter file name with extension, for example clients.txt");
                fgets(temp, sizeof(temp), stdin);
                sscanf(temp, "%s", strTemp);
                writeListToFile(*top, strcat(filename, strTemp));
                break;
            case 10:
                puts("Enter file name with extension, for example clients.txt");
                fgets(temp, sizeof(temp), stdin);
                sscanf(temp, "%s", strTemp);
                displayRecordsFromFile(strcat(filename, strTemp));
                break;
            default:
                puts("Invalid option");
        } // switch block ends here

    } // while loop ends

}// menus function ends
/**
 * This function takes region integer and town integer, town integer actually represents its town number within that region
 * So if there are three towns in a region, town number 0 corresponds to the first town in that region.
 * Read the header file and carefully go through the ordering of elements of regionArr and townArr. regionArr's elements
 * are in alphabetical order, but try to figure out what is the order of townArr elements?
 * @param region an integer value representing a region
 * @param x representing index value from townsArr array (refer to the header file)
 * @return
 */
char *townMappingRegionBased(int region, int x) {
    char *str;
    switch (region) {
        case 0:
            switch (x) {
                case 0:
                    str = "OSHAWA";
                    break;
                case 1:
                    str = "WHITBY";
                    break;
            }
            break;
        case 1:
            switch (x) {
                case 0:
                    str = "BRAMPTON";
                    break;

                case 1:
                    str = "MISSISSAUGA";
                    break;
            }
            break;
        case 2:
            switch (x) {
                case 0:
                    str = "MAPLE";
                    break;
                case 1:
                    str = "VAUGHAN";
                    break;
            }
    }
    return str;
}// ends townMappingRegionBased function
/**
 * This is a simple mapping function, just like regionMapping function
 * @param x is an integer corresponding to the townArr index
 * @return char array representing name of the town
 */
char *townMapping(int x) {
    char *str;
    switch (x) {
        case 0:
            str = "OSHAWA";
            break;
        case 1:
            str = "WHITBY";
            break;
        case 2:
            str = "BRAMPTON";
            break;
        case 3:
            str = "MISSISSAUGA";
            break;
        case 4:
            str = "MAPLE";
            break;
        case 5:
            str = "VAUGHAN";
            break;
    }
    return str;
}// ends townMapping function
/**
 *
 * @param x
 * @return
 */
char *raceMapping(int x) {
    char *str;
    switch (x) {
        case 0:
            str = "CAUCASIAN";
            break;
        case 1:
            str = "INDIGENOUS";
            break;
        case 2:
            str = "AFRO-AMERICAN";
            break;
        case 3:
            str = "ASIAN";
            break;
        case 4:
            str = "OTHER";
            break;
    }
    return str;
}// ends raceMapping function
/**
 * It populates the linked list with valid random data. The top of the list is passed as a reference i.e. address of the pointer!
 * @param top top is passed by reference i.e. address of the pointer top is passed in the call!
 */
void initializeData(NodePtr *top) {
    // This function populates the linked list with random data.

    srand(time(NULL));
    for (int dex = 0; dex < SIZE; dex++) {
        int race = rand() % ARR_RACE_LEN;
        int region = rand() % ARR_REGION_LEN;
        int town = rand() % 2;
        int familySize = rand() % MAX_FAMILYSIZE + 1; // min 1, max 12 people
        int totPosCovid = rand() % familySize + 1;// limit with respective size of family
        int fullyVac = rand() % familySize + 1;// limit with respective size of family
        Household newRecord = makeHousehold(raceMapping(race), regionMapping(region),
                                            townMappingRegionBased(region, town), familySize,
                                            totPosCovid, fullyVac);
        if (top == NULL) (*top) = makeNode(newRecord);
        else addNode(top, newRecord);
    }
} //initializeData ends
/**
 *
 * @param top is the top of the list
 * @param region is the region that all the displayed records should belong to
 */
void displayRecordsOfOneRegion(NodePtr top, char region[]) {
    int sNo = 0;
    printf("%4s%15s%20s%15s%15s%10s%20s\n", "S.no", "Family Size", "Covid-19 Positive", "Vaccinated", "Race", "Region",
           "Town");
    while (top != NULL) {
        if (strcmp(top->data.region, region) == 0) {
            sNo++;
            printRecord(sNo, top);
        }
        top = top->next;
    }
    printf("\n********************************************* %d records are found ************************************************\n",
           sNo);
} //ends displayRecordsOfOneRegion
/**
 *
 * @param top
 * @param town
 */
void displayRecordsOfOneTown(NodePtr top, char town[]) {
    int sNo = 0;
    printf("%4s%15s%20s%15s%15s%10s%20s\n", "S.no", "Family Size", "Covid-19 Positive", "Vaccinated", "Race", "Region",
           "Town");
    while (top != NULL) {
        if (strcmp(top->data.town, town) == 0) {
            sNo++;
            printRecord(sNo, top);
        }
        top = top->next;
    }
    printf("\n********************************************* %d records are found ************************************************\n",
           sNo);

} //ends displayRecordsOfOneTown
/**
 *
 * @param top
 * @param race
 */
void displayRecordsOfOneRace(NodePtr top, char race[]) {
    int sNo = 0;
    printf("%4s%15s%20s%15s%15s%10s%20s\n", "S.no", "Family Size", "Covid-19 Positive", "Vaccinated", "Race", "Region",
           "Town");
    while (top != NULL) {
        if (strcmp(top->data.race, race) == 0) {
            sNo++;
            printRecord(sNo, top);
        }
        top = top->next;
    }
    printf("\n********************************************* %d records are found ************************************************\n",
           sNo);

} //ends displayRecordsOfOneTown
/**
 *
 * @param top
 * @param region
 * @param numOfPositiveCases
 */
void displayRecordsOfRegionWithPositiveCases(NodePtr top, char region[], int numOfPositiveCases) {
    int sNo = 0;
    printf("%4s%15s%20s%15s%15s%10s%20s\n", "S.no", "Family Size", "Covid-19 Positive", "Vaccinated", "Race", "Region",
           "Town");
    while (top != NULL) {
        if ((strcmp(top->data.region, region) == 0) && top->data.testedPositive > numOfPositiveCases) {
            sNo++;
            printRecord(sNo, top);

        }
        top = top->next;
    }
    printf("\n********************************************* %d records are found ************************************************\n",
           sNo);
}

/**
 * This function ranks all the towns in descending order of total number of people vaccinated
 * @param top
 */
void regionsTownWiseRankingVaccinated(NodePtr top) {
    NodePtr topTemp = top;
    // location pairs array for regions and towns
    LocationCountPair countPairRegionArr[ARR_REGION_LEN];
    LocationCountPair countPairTownArr[ARR_TOWN_LEN];

    // Count fully vaccinated person numbers by region
    for (int i = 0; i < ARR_REGION_LEN; i++) {
        top = topTemp;
        int total = 0;
        while (top != NULL) {
            if ((strcmp(top->data.region, regionMapping(i)) == 0)) {
                total += top->data.fullyVaccinated;
            }
            top = top->next;
        }
        strcpy(countPairRegionArr[i].town, regionMapping(i));
        countPairRegionArr[i].count = total;
    }

    // Count fully vaccinated person numbers by town
    for (int i = 0; i < ARR_TOWN_LEN; i++) {
        top = topTemp;
        int total = 0;
        while (top != NULL) {
            if ((strcmp(top->data.town, townMapping(i)) == 0)) {
                total += top->data.fullyVaccinated;
            }
            top = top->next;
        }
        strcpy(countPairTownArr[i].town, townMapping(i));
        countPairTownArr[i].count = total;
    }

    // Sorting the arrays descending
    sortSelection(countPairRegionArr, ARR_REGION_LEN);
    sortSelection(countPairTownArr, ARR_TOWN_LEN);


    // Printing output
    puts("Total vaccinated:");
    puts("Region-wise ranking:");
    for (int i = 0; i < ARR_REGION_LEN; i++) {
        printf("%20s :%5d \n", countPairRegionArr[i].town, countPairRegionArr[i].count);
    }
    puts("Town-wise ranking:");
    for (int i = 0; i < ARR_TOWN_LEN; i++) {
        printf("%20s :%5d \n", countPairTownArr[i].town, countPairTownArr[i].count);
    }
} // function regionsTownWiseRankingVaccinated ends
/**
 * This function gets validated data from the user for adding a record and then invokes makeHousehold function as part
 * of the return statement
 * @return  it returns a household instance that this function creates based on validated user input
 */
Household userInteractionForRecordAddition() {
    int n = 0, num, upperbound, race, region, town, familySize, totalCovidPositive, fullyVaccinated, raceTemp, regionTemp, townTemp;
    char buff[40];
    puts("Enter an integer for race: CAUCASIAN (0), INDIGENOUS(1), AFRO AMERICAN(2), ASIAN(3), and OTHER(4)");
    upperbound = 4;
    while (1) {
        fgets(buff, sizeof(buff), stdin);
        n = sscanf(buff, "%d", &num);
        if (num >= 0 && num <= upperbound && n == 1) {
            race = num;
            break;
        } else {
            printf("Invalid data, enter an integer 0 through %d. Try again \n",
                   upperbound);
            continue;
        }
    } //while loop ends

    puts("Enter an integer for region: DURHAM(0), PEEL(1), and YORK(2):");
    upperbound = 2;
    while (1) {
        fgets(buff, sizeof(buff), stdin);
        n = sscanf(buff, "%d", &num);
        if (num >= 0 && num <= upperbound && n == 1) {
            region = num;
            break;
        } else {
            printf("Invalid data, enter an integer 0 through %d. Try again \n",
                   upperbound);
            continue;
        }
    } //while loop ends

    switch (region) {
        case 0:
            puts("Enter an integer for town: OSHAWA(0), WHITBY(1)");
            upperbound = 1;
            while (1) {
                fgets(buff, sizeof(buff), stdin);
                n = sscanf(buff, "%d", &num);
                if (num >= 0 && num <= upperbound && n == 1) {
                    town = num;
                    break;
                } else {
                    printf("Invalid data, enter an integer 0 through %d. Try again \n",
                           upperbound);
                    continue;
                }
            } //while loop ends
            break;
        case 1:
            puts("Enter an integer for town: BRAMPTON(0), MISSISSAUGA(1)");
            upperbound = 1;
            while (1) {
                fgets(buff, sizeof(buff), stdin);
                n = sscanf(buff, "%d", &num);
                if (num >= 0 && num <= upperbound && n == 1) {
                    town = num;
                    break;
                } else {
                    printf("Invalid data, enter an integer 0 through %d. Try again \n",
                           upperbound);
                    continue;
                }
            } //while loop ends
            break;
        case 2:
            puts("Enter an integer for town: MAPLE(0), VAUGHAN(1)");
            upperbound = 1;
            while (1) {
                fgets(buff, sizeof(buff), stdin);
                n = sscanf(buff, "%d", &num);
                if (num >= 0 && num <= upperbound && n == 1) {
                    town = num;
                    break;
                } else {
                    printf("Invalid data, enter an integer 0 through %d. Try again \n",
                           upperbound);
                    continue;
                }
            } //while loop ends
            break;
    }
    printf("Please enter\n1. total number of people in the household\n2. people tested Covid positive,\n3. people fully vaccinated for COVID-19\n"
           "seperated by space or tab and make sure all of these are valid integers\n");
    int isValid = 1;
    while (isValid != 0) {
        fgets(buff, sizeof(buff), stdin);
        int ctr = sscanf(buff, "%d%d%d", &familySize, &totalCovidPositive, &fullyVaccinated);
        if (ctr != 3 || familySize < 0 || fullyVaccinated < 0 || totalCovidPositive < 0) {
            printf("Please enter three positive number seperated by space or tab\n");
        } else if (fullyVaccinated > familySize || totalCovidPositive > familySize) {
            puts("Number of vaccinated members or Covid-19 positive members cannot be greater than the total member of the house");
        } else isValid = 0;
    }
    puts("New data successfully saved.");
    return makeHousehold(raceMapping(race), regionMapping(region),
                         townMappingRegionBased(region, town), familySize,
                         totalCovidPositive, fullyVaccinated);
}

/**
 *
 * @param top top of the list to be passed by reference
 * @param region passed as a character array
 * @param town passed as a character array
 * @param race passed as a character array
 */
void deleteNodesGivenCriteria(NodePtr *top, char region[], char town[], char race[]) {
    NodePtr prev = NULL;
    NodePtr temp = NULL;
    NodePtr start = (*top); // keep top safe for the data set
    if (*top == NULL) {
        puts("Empty list");
    } else {
        printf("%4s%15s%20s%15s%15s%10s%20s\n", "S.no", "Family Size", "Covid-19 Positive", "Vaccinated", "Race",
               "Region", "Town");
        int ctr = 0;
        // if first node match the criteria top move to next until first node doesn't match the criteria
        while ((strcmp((*top)->data.region, region) == 0) && (strcmp((*top)->data.town, town) == 0) &&
               (strcmp((*top)->data.race, race) == 0)) {
            ctr++;
            printRecord(ctr, *top);
            deleteNode(top);
            start = (*top); // if first node match the criteria then new top needs to be store in start to keep the nodelist top safe
        }
        // First node doesn't match then iterate the node list to find any matching node until end of the list
        while ((*top) != NULL) {
            if ((strcmp((*top)->data.region, region) == 0) && (strcmp((*top)->data.town, town) == 0) &&
                (strcmp((*top)->data.race, race) == 0)) {
                ctr++;
                printRecord(ctr, *top);
                temp = (*top);
                prev->next = temp->next;
                deleteNode(top);
            } else {
                prev = (*top);
                (*top) = (*top)->next;
            }
        }
        if (ctr == 0) {
            puts("No record found");
        } else
            printf("\n********************************************* %d records are DELETED ****************************"
                   "********************\n", ctr);
        (*top) = start;// reset the top to keep data set
    }
}// deleteNodeCriteria function ends
/**
 * This function prints the entire list of data. It invokes printRecord function
 * @param ptr is the top of the list
 */
void printList(NodePtr ptr) {
    if (ptr == NULL) {
        puts("Empty list");
    } else {
        printf("%4s%15s%20s%15s%15s%10s%20s\n", "S.no", "Family Size", "Covid-19 Positive", "Vaccinated", "Race",
               "Region", "Town");
        int sNo = 0;
        while (ptr != NULL) {
            sNo++;
            printRecord(sNo, ptr);
            ptr = ptr->next;
        }
        puts("");
    }
}

/**
 * It prints a single record starting with a serial number to keep a count of number of records printed
 * @param ctr serial number of the record
 * @param ptr top of the list
 */
void printRecord(int ctr, NodePtr ptr) {
    printf("%4d%15d%20d%15d%15s%10s%20s\n", ctr, ptr->data.familySize, ptr->data.testedPositive,
           ptr->data.fullyVaccinated, ptr->data.race, ptr->data.region,
           ptr->data.town);
}

/**
 * This function takes data items of a Household record and sets members of a locally declared Household instance and returns it
 * @param race
 * @param region
 * @param town
 * @param familySize
 * @param totPosCovid
 * @param fullyVac
 * @return a Household instance
 */
Household makeHousehold(char race[], char region[], char town[], int familySize, int totPosCovid, int fullyVac) {
    Household newData;
    strcpy(newData.race, race);
    strcpy(newData.region, region);
    strcpy(newData.town, town);
    newData.familySize = familySize;
    newData.testedPositive = totPosCovid;
    newData.fullyVaccinated = fullyVac;
    return newData;
}

/**
 * makeNode function allocates dynamic memory to create a node, populates with the data based on its argument of type Household
 * and returns the populated node
 * @param num
 * @return
 */
NodePtr makeNode(Household num) {
    NodePtr ptr = malloc(sizeof(*ptr));
    ptr->data = num;
    ptr->next = NULL;
    return ptr;
}

/**
 * Add node takes a Household instance, creates a node from it and then adds it to the front of the list that it takes as
 * its other argument
 * @param tom
 * @param num
 */
void addNode(NodePtr *top, Household num) {
    Node *ptr = malloc(sizeof(*ptr));
    ptr->data = num;
    ptr->next = (*top);
    (*top) = ptr;
}

/**
 * THis function deletes a node from the list
 * @param tom takes top of the list as a reference
 */
void deleteNode(NodePtr *tom) {
    Node *temp = (*tom);
    (*tom) = (*tom)->next;
    free(temp);
}

/**
 * This function deletes all nodes (records) of the list
 * @param tom
 */
void deleteAllNodes(NodePtr *tom) {
    if ((*tom) == NULL) {
        puts("Empty List");
    }
    while ((*tom) != NULL) {
        deleteNode(tom);
    }
}

/**
 * It write all the records to a file. As a sample, clients.txt file is saved in the data folder as part of the project folder
 * @param top
 * @param fileName
 */
void writeListToFile(NodePtr top, char fileName[]) {
    FILE *cfPtr; /* cfPtr = clients.dat file pointer */
    char region[20], town[20], race[20];
    int checkFileName = 0, counter = 0;
    /* fopen opens file. Exit program if unable to create file  */
    if ((cfPtr = fopen(fileName, "w")) == NULL) {
        printf("File could not be opened\n");
        checkFileName++;
    } /* end if */
    else {
        while (top != NULL) {
            counter++;
            fprintf(cfPtr, "%s %s %s %d %d %d\n", top->data.race, top->data.region, top->data.town,
                    top->data.familySize, top->data.testedPositive, top->data.fullyVaccinated);
            top = top->next;
        }
        fprintf(cfPtr, "%s %s %s %d %d %d\n", "Last", "Record", "none", 0, 0,
                0); //
    }/* end else */
    if (checkFileName == 0) { // if file can be created successfully
        fclose(cfPtr); /* fclose closes file */
        printf("%d records written successfully as the text file:  %s\n", counter, fileName);
    }
}

/**
 * It reads all records from a file
 * @param fileName
 */
void displayRecordsFromFile(char fileName[]) {
    FILE *cfPtr; /* cfPtr file pointer */
    char region[20], town[20], race[20];
    int familySize, totPosCovid, fullyVac, isFileNameValid = 0;
    NodePtr top;
    /* fopen opens file; exits program if file cannot be opened */
    if ((cfPtr = fopen(fileName, "r")) == NULL) {
        printf("File could not be opened\n");
        isFileNameValid++;
    } /* end if */
    else { /* read from file */
        fscanf(cfPtr, "%s %s %s %d %d %d", race, region, town, &familySize, &totPosCovid,
               &fullyVac); // read first record
        Household newRecord = makeHousehold(race, region, town, familySize, totPosCovid, fullyVac);
        top = makeNode(newRecord); // adding household as a node to the list
        while (!feof(cfPtr)) { /* reading rest of the records i.e. while not end of file */
            fscanf(cfPtr, "%s %s %s %d %d %d", race, region, town, &familySize, &totPosCovid, &fullyVac);
            if (familySize == 0) break; //sentinel control
            addNode(&top, makeHousehold(race, region, town, familySize, totPosCovid, fullyVac));
        }/* end while */
    } // End of else
    if (isFileNameValid == 0) { // if file can be opened successfully
        fclose(cfPtr); /* fclose closes the file */
        puts("Printing linked list");
        printList(top);
        deleteAllNodes(&top); // required to ensure no memory leak occurs
    }
}