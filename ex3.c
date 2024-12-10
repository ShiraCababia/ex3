/******************
Name: Shira Cababia
ID: 326153590
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
int isAllBrandsInsert(int arr[NUM_OF_BRANDS]);                                                                    // 2
void printMissingData(int insertedBrandsIndx[NUM_OF_BRANDS]);
int isCarBrandIndxValid(int insertedBrandsIndx[NUM_OF_BRANDS], int carBrandIndx);

char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV", "Sedan", "Coupe", "GT"};

int main()
{
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    int insertedDaysAmount = 0;                                   // Representing the amount of days the user inserted.
    int insertedBrandsIndx[NUM_OF_BRANDS] = {-1, -1, -1, -1, -1}; // Array that helps to
    int carBrandIndx, sumFirst, sumSecond, sumThird, sumFourth;
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
            printf("Entert a car brand index and a series of 4 integers, each representing the daily sales sum for each car type\n");
            scanf(" %d %d %d %d %d", &carBrandIndx, &sumFirst, &sumSecond, &sumThird, &sumFourth);
            if (carBrandIndx < 0 || carBrandIndx >= NUM_OF_BRANDS)
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
        {
            while (!isAllBrandsInsert(insertedBrandsIndx))
            {
                printMissingData(insertedBrandsIndx);
                printf("Please complete the data\n");
                scanf(" %d %d %d %d %d", &carBrandIndx, &sumFirst, &sumSecond, &sumThird, &sumFourth);
                while (!isCarBrandIndxValid(insertedBrandsIndx, carBrandIndx))
                {
                    printf("This brand is not valid\n");
                    printMissingData(insertedBrandsIndx);
                    scanf(" %d %d %d %d %d", &carBrandIndx, &sumFirst, &sumSecond, &sumThird, &sumFourth);
                }
                if (isCarBrandIndxValid(insertedBrandsIndx, carBrandIndx))
                {
                    insertData(cube, carBrandIndx, 0, sumFirst);
                    insertData(cube, carBrandIndx, 1, sumSecond);
                    insertData(cube, carBrandIndx, 2, sumThird);
                    insertData(cube, carBrandIndx, 3, sumFourth);
                    insertedBrandsIndx[carBrandIndx] = carBrandIndx;
                }
            }
            // Increase the days amount by 1 since the user inserted data for another day.
            insertedDaysAmount++;
            // Initialize the insertedBrandsIndx array for next insert by the user.
            for (int i = 0; i < NUM_OF_BRANDS; i++)
            {
                insertedBrandsIndx[i] = -1;
            }
            break;
        }
        case STATS: // 3
        {
            int chosenDay, totalSalesSum = 0, bestBrandIndx = -1, bestTypeIndx = -1;
            int sumSoldTypesInBrand = 0, maxSoldBrand = 0, sumSoldBrandsInType = 0, maxSoldType = 0;
            printf("What day would you like to analyze?\n");
            scanf("%d", &chosenDay);
            while (chosenDay < 1 || chosenDay > DAYS_IN_YEAR || chosenDay > insertedDaysAmount)
            {
                printf("Please enter a valid day.\n");
                printf("What day would you like to analyze?\n");
                scanf("%d", &chosenDay);
            }
            int chosenDayIndx = chosenDay - 1;

            for (int i = 0; i < NUM_OF_BRANDS; i++)
            {
                for (int j = 0; j < NUM_OF_TYPES; j++)
                {
                    sumSoldTypesInBrand = sumSoldTypesInBrand + cube[chosenDayIndx][i][j];
                }
                if (sumSoldTypesInBrand > maxSoldBrand)
                {
                    maxSoldBrand = sumSoldTypesInBrand;
                    bestBrandIndx = i;
                }
                sumSoldTypesInBrand = 0;
            }

            for (int i = 0; i < NUM_OF_TYPES; i++)
            {
                for (int j = 0; j < NUM_OF_BRANDS; j++)
                {
                    sumSoldBrandsInType = sumSoldBrandsInType + cube[chosenDayIndx][j][i];
                }
                if (sumSoldBrandsInType > maxSoldType)
                {
                    maxSoldType = sumSoldBrandsInType;
                    bestTypeIndx = i;
                }
                sumSoldBrandsInType = 0;
            }

            for (int i = 0; i < NUM_OF_BRANDS; i++)
            {
                for (int j = 0; j < NUM_OF_TYPES; j++)
                {
                    totalSalesSum = totalSalesSum + cube[chosenDayIndx][i][j];
                }
            }
            printf("In day number %d:\n", chosenDay);
            printf("The sales total was %d\n", totalSalesSum);
            printf("The best sold brand with %d sales was %s\n", maxSoldBrand, brands[bestBrandIndx]);
            printf("The best sold type with %d sales was %s\n", maxSoldType, types[bestTypeIndx]);
            break;
        }

        case PRINT: // 4
        {
            printf("*****************************************\n\n");
            for (int i = 0; i < NUM_OF_BRANDS; i++)
            {
                printf("Sales for %s:", brands[i]);
                for (int j = 0; j < insertedDaysAmount; j++)
                {
                    int day = j + 1;
                    printf("\nDay %d- ", day);
                    for (int k = 0; k < NUM_OF_TYPES; k++)
                    {
                        printf("%s: %d ", types[k], cube[j][i][k]);
                    }
                }
                printf("\n");
            }
            printf("\n\n*****************************************\n");
            break;
        }

        case INSIGHTS: // 5
        {
            int sumSellingBrand = 0, maxSellingBrand = 0, mostSoldBrandIndx = -1;
            int sumSellingType = 0, maxSellingType = 0, mostSoldTypeIndx = -1;
            int sumSellingInDay = 0, maxSellingInDay = 0, mostSoldDayIndx = -1;
            for (int i = 0; i < NUM_OF_BRANDS; i++)
            {
                for (int j = 0; j < NUM_OF_TYPES; j++)
                {
                    for (int k = 0; k < insertedDaysAmount; k++)
                    {
                        sumSellingBrand = sumSellingBrand + cube[k][i][j];
                    }
                }
                if (sumSellingBrand > maxSellingBrand)
                {
                    maxSellingBrand = sumSellingBrand;
                    mostSoldBrandIndx = i;
                }
                sumSellingBrand = 0;
            }

            for (int i = 0; i < NUM_OF_TYPES; i++)
            {
                for (int j = 0; j < NUM_OF_BRANDS; j++)
                {
                    for (int k = 0; k < insertedDaysAmount; k++)
                    {
                        sumSellingType = sumSellingType + cube[k][j][i];
                    }
                }
                if (sumSellingType > maxSellingType)
                {
                    maxSellingType = sumSellingType;
                    mostSoldTypeIndx = i;
                }
                sumSellingType = 0;
            }

            for (int i = 0; i < insertedDaysAmount; i++)
            {
                for (int j = 0; j < NUM_OF_BRANDS; j++)
                {
                    for (int k = 0; k < NUM_OF_TYPES; k++)
                    {
                        sumSellingInDay = sumSellingInDay + cube[i][j][k];
                    }
                }
                if (sumSellingInDay > maxSellingInDay)
                {
                    maxSellingInDay = sumSellingInDay;
                    mostSoldDayIndx = i;
                }
                sumSellingInDay = 0;
            }
            int profitableDay = mostSoldDayIndx + 1;
            printf("The best-selling brand overall is %s: %d$\n", brands[mostSoldBrandIndx], maxSellingBrand);
            printf("The best-selling type of car is %s: %d$\n", types[mostSoldTypeIndx], maxSellingType);
            printf("The most profitable day was day number %d: %d$\n", profitableDay, maxSellingInDay);
            break;
        }

        case DELTAS: // 6
        {
            float sumDifferences = 0, avgD = 0;
            for (int i = 0; i < NUM_OF_BRANDS; i++)
            {
                if (insertedDaysAmount == 0)
                {
                    avgD = 0;
                }
                else if (insertedDaysAmount == 1)
                {
                    for (int t = 0; t < NUM_OF_TYPES; t++)
                    {
                        avgD = avgD + cube[0][i][t];
                    }
                }
                else
                {
                    for (int j = 0; j < NUM_OF_TYPES; j++)
                    {
                        for (int k = 0; k < insertedDaysAmount - 1; k++)
                        {
                            sumDifferences = sumDifferences + (cube[k + 1][i][j] - cube[k][i][j]);
                        }
                    }
                    avgD = sumDifferences / (insertedDaysAmount - 1);
                }
                printf("Brand: %s, Average Delta: %f\n", brands[i], avgD);
                avgD = 0;
                sumDifferences = 0;
            }
            break;
        }

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

int isAllBrandsInsert(int arr[NUM_OF_BRANDS])
{
    for (int i = 0; i < NUM_OF_BRANDS; i++)
    {
        if (arr[i] == -1)
        {
            return 0;
        }
    }
    return 1;
}

void printMissingData(int insertedBrandsIndx[NUM_OF_BRANDS])
{
    printf("No data for brands ");
    for (int i = 0; i < NUM_OF_BRANDS; i++)
    {
        if (insertedBrandsIndx[i] == -1)
        {
            printf("%s ", brands[i]);
        }
    }
    printf("\n");
}

int isCarBrandIndxValid(int arr[NUM_OF_BRANDS], int carBrandIndx)
{
    if (carBrandIndx < 0 || carBrandIndx >= NUM_OF_BRANDS)
    {
        return 0;
    }
    for (int i = 0; i < NUM_OF_BRANDS; i++)
    {
        if (arr[i] == carBrandIndx)
        {
            return 0;
        }
    }
    return 1;
}
