/******************
Name: Shira Cababia
ID:
Assignment: ex3
*******************/

#include <stdio.h>

#define NUM_OF_BRANDS 5
#define BRANDS_NAMES 15
#define NUM_OF_TYPES 4
#define TYPES_NAMES 10
#define DAYS_IN_YEAR 365
#define ADD_ONE 1
#define ADD_ALL 2
#define STATS 3
#define PRINT 4
#define INSIGHTS 5
#define DELTAS 6
#define DONE 7
void printMenu();
void initializeData(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);                                         // 0
void insertData(int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int carBrandIndx, int type, int sumToInsert); // 1

char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV", "Sedan", "Coupe", "GT"};

int main()
{
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    int days[NUM_OF_BRANDS] = {0};
    initializeData(cube);
    int choice;
    printMenu();
    scanf("%d", &choice);
    while (choice != DONE)
    {
        switch (choice)
        {
        case ADD_ONE: // 1
        {
            int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
            initializeData(arr);
            int carBrandIndx, sumFirst, sumSecond, sumThird, sumFourth;
            printf("Entert a car brand index and a series of 4 integers, each representing the daily sales sum for each car type\n");
            scanf(" %d %d %d %d %d", &carBrandIndx, &sumFirst, &sumSecond, &sumThird, &sumFourth);
            if (carBrandIndx < 0 || carBrandIndx > 4)
            {
                printf("This brand is not valid\n");
                break;
            }
            insertData(arr, carBrandIndx, 0, sumFirst);
            insertData(arr, carBrandIndx, 1, sumSecond);
            insertData(arr, carBrandIndx, 2, sumThird);
            insertData(arr, carBrandIndx, 3, sumFourth);
            break;
        }

        case ADD_ALL: // 2
            //...
            break;
        case STATS: // 3
            //...
            break;
        case PRINT: // 4
            //...
            break;
        case INSIGHTS: // 5
            //...
            break;
        case DELTAS: // 6
            //...
            break;
        default:
            printf("Invalid input\n");
        }
        printMenu();
        scanf("%d", &choice);
    }
    printf("Goodbye!\n");
    return 0;
}

void printMenu()
{
    printf("Welcome to the Cars Data Cube! What would you like to do?\n"
           "1.Enter Daily Data For A Brand\n"
           "2.Populate A Day Of Sales For All Brands\n"
           "3.Provide Daily Stats\n"
           "4.Print All Data\n"
           "5.Provide Overall (simple) Insights\n"
           "6.Provide Average Delta Metrics\n"
           "7.exit\n");
}

void initializeData(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES])
{
    for (int i = 0; i < DAYS_IN_YEAR; i++)
    {
        for (int j = 0; j < NUM_OF_BRANDS; j++)
        {
            for (int k = 0; k < NUM_OF_TYPES; k++)
            {
                cube[i][j][k] = -1;
            }
        }
    }
}

void insertData(int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int carBrandIndx, int type, int sumToInsert)
{
    int count = 0;
    while (arr[count][carBrandIndx][type] != -1)
    {
        count++;
    }
    if (arr[count][carBrandIndx][type] == -1)
    {
        arr[count][carBrandIndx][type] = sumToInsert;
    }
}