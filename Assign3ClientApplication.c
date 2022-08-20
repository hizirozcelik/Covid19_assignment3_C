/**
 * Student Name: Hizir Ozcelik
 * Student ID: 991578495
 * Date modified: July 19, 2022
 * Soln2ClientApplication.c built by M. Mohiuddin on November 5, 2021 for students as a guide and starting application
 * to build solution for assignment 2. Refer to the assignment specifications for other details.
 * To help students further, full implementation of regionMapping function, menu function and several other utility functions
 * is provided as part of household.c source code file which also lists rest of the functions that students have to implement
 * This file MUST NOT be changed at all. However, write your name and other details as required above.
 */
#include "household.h"
#include <stdio.h>
int main () {
    NodePtr tophh;// top of the list
    initializeData(&tophh);
    printList(tophh);
    puts("------------------This program analyzes and stores information related to Covid-19 cases------------------");
    puts("------------------------and its impact on various races, regions and towns of GTA-------------------------");
    menu(&tophh);
    deleteAllNodes(&tophh); // required to ensure no memory leak occurs
    return 0;
}


