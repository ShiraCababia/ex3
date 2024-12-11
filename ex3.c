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
void initializeData(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);
// Func case 1:
void insertData(int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int carBrandIndx, int type, int sumToInsert);
// Func case 2:
int isAllBrandsInsert(int arr[NUM_OF_BRANDS]);
void printMissingData(int insertedBrandsIndx[NUM_OF_BRANDS]);
int isCarBrandIndxValid(int insertedBrandsIndx[NUM_OF_BRANDS], int carBrandIndx);
// Func case 3:
void printBestBrandInDay(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int chosenDay);
void printBestTypeInDay(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int chosenDay);
void printTotalSalesInDay(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int chosenDay);
// Func case 4:
void printAllSalesforBrand(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int brandIndx, int insertedDaysAmount);
// Func case 5:
void printBestBrandOverall(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int insertedDaysAmount);
void printBestTypeOverall(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int insertedDaysAmount);
void printMostProfitableDay(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int insertedDaysAmount);
// Func case 6:
float avgDeltaForBrand(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int brandIndx, int insertedDaysAmount);

char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV", "Sedan", "Coupe", "GT"};

int main()
{
    // An array representing the data for brands, types and days all together.
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    // A variable representing the amount of days the user entered.
    int insertedDaysAmount = 0;
    // An array that helps tracking for which brands the user entered data for.
    int insertedBrandsIndx[NUM_OF_BRANDS] = {-1, -1, -1, -1, -1};
    // Variables representing data the user entered for types in a brand.
    int carBrandIndx, sumSUV, sumSedan, sumCoupe, sumGT;
    // Initialize the  data in the cube and print the menu.
    initializeData(cube);
    printMenu();
    // A variable representing the user's choice from the options in the menu.
    int choice;
    scanf("%d", &choice);
    while (choice != DONE)
    {
        switch (choice)
        {
        case ADD_ONE: // 1
        {
            int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
            initializeData(arr);
            printf("Enter a car brand index and a series of 4 integers\n");
            scanf(" %d %d %d %d %d", &carBrandIndx, &sumSUV, &sumSedan, &sumCoupe, &sumGT);
            if (carBrandIndx < 0 || carBrandIndx >= NUM_OF_BRANDS)
            {
                printf("This brand is not valid\n");
                break;
            }
            insertData(arr, carBrandIndx, 0, sumSUV);
            insertData(arr, carBrandIndx, 1, sumSedan);
            insertData(arr, carBrandIndx, 2, sumCoupe);
            insertData(arr, carBrandIndx, 3, sumGT);
            break;
        }

        case ADD_ALL: // 2
        {
            // Continue asking for data until all brands have data entered.
            while (!isAllBrandsInsert(insertedBrandsIndx))
            {
                printMissingData(insertedBrandsIndx);
                printf("Please complete the data\n");
                scanf(" %d %d %d %d %d", &carBrandIndx, &sumSUV, &sumSedan, &sumCoupe, &sumGT);
                while (!isCarBrandIndxValid(insertedBrandsIndx, carBrandIndx))
                {
                    printf("This brand is not valid\n");
                    printMissingData(insertedBrandsIndx);
                    scanf(" %d %d %d %d %d", &carBrandIndx, &sumSUV, &sumSedan, &sumCoupe, &sumGT);
                }
                /* Check if the entered brand is valid, if it does - entered the data to the cube and mark
                the brand as no longer valid for next insert data */
                if (isCarBrandIndxValid(insertedBrandsIndx, carBrandIndx))
                {
                    insertData(cube, carBrandIndx, 0, sumSUV);
                    insertData(cube, carBrandIndx, 1, sumSedan);
                    insertData(cube, carBrandIndx, 2, sumCoupe);
                    insertData(cube, carBrandIndx, 3, sumGT);
                    insertedBrandsIndx[carBrandIndx] = carBrandIndx;
                }
            }
            // Increase the days amount by 1 since the user entered data for one more day.
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
            // Get a day from the user and make sure it's acceptable.
            int chosenDay;
            printf("What day would you like to analyze?\n");
            scanf("%d", &chosenDay);
            while (chosenDay < 1 || chosenDay > DAYS_IN_YEAR || chosenDay > insertedDaysAmount)
            {
                printf("Please enter a valid day.\n");
                printf("What day would you like to analyze?\n");
                scanf("%d", &chosenDay);
            }
            // Print all requested data in the chosen day.
            printf("In day number %d:\n", chosenDay);
            printTotalSalesInDay(cube, chosenDay);
            printBestBrandInDay(cube, chosenDay);
            printBestTypeInDay(cube, chosenDay);
            break;
        }

        case PRINT: // 4
        {
            printf("*****************************************\n\n");
            for (int i = 0; i < NUM_OF_BRANDS; i++)
            {
                printAllSalesforBrand(cube, i, insertedDaysAmount);
            }
            printf("\n\n*****************************************\n");
            break;
        }

        case INSIGHTS: // 5
        {
            printBestBrandOverall(cube, insertedDaysAmount);
            printBestTypeOverall(cube, insertedDaysAmount);
            printMostProfitableDay(cube, insertedDaysAmount);
            break;
        }

        case DELTAS: // 6
        {
            for (int i = 0; i < NUM_OF_BRANDS; i++)
            {
                float avgD = avgDeltaForBrand(cube, i, insertedDaysAmount);
                printf("Brand: %s, Average Delta: %f\n", brands[i], avgD);
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

// Initialize the data in the cube array before future inserts of data.
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

// Inserts data in the first available cell in the cube (according to the given brand and type).
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

// Checks if all brands entered.
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

// Print the names of brands the user didn't entered data for.
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

// Checks if the brand the user entered is valid - if it's between 0-4 and if the user didn't already enter data for it.
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

// Calculate what's the brand with the largest amount of sales in the given day and print a proper message.
void printBestBrandInDay(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int chosenDay)
{
    int sumSoldTypesInBrand = 0, maxSoldBrand = 0, bestBrandIndx = -1;
    int chosenDayIndx = chosenDay - 1;
    for (int i = 0; i < NUM_OF_BRANDS; i++)
    {
        for (int j = 0; j < NUM_OF_TYPES; j++)
        {
            // Sum the data in all the types in the specific brand and given day.
            sumSoldTypesInBrand = sumSoldTypesInBrand + cube[chosenDayIndx][i][j];
        }
        // Update the most sold brand, if justified.
        if (sumSoldTypesInBrand > maxSoldBrand)
        {
            maxSoldBrand = sumSoldTypesInBrand;
            bestBrandIndx = i;
        }
        sumSoldTypesInBrand = 0;
    }
    printf("The best sold brand with %d sales was %s\n", maxSoldBrand, brands[bestBrandIndx]);
}

// Calculate what's the type with the largest amount of sales in the given day and print a proper message.
void printBestTypeInDay(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int chosenDay)
{
    int sumSoldBrandsInType = 0, maxSoldType = 0, bestTypeIndx = -1;
    int chosenDayIndx = chosenDay - 1;
    for (int i = 0; i < NUM_OF_TYPES; i++)
    {
        for (int j = 0; j < NUM_OF_BRANDS; j++)
        {
            // Sum the data in all the brands in the specific type and given day.
            sumSoldBrandsInType = sumSoldBrandsInType + cube[chosenDayIndx][j][i];
        }
        // Update the most sold type, if justified.
        if (sumSoldBrandsInType > maxSoldType)
        {
            maxSoldType = sumSoldBrandsInType;
            bestTypeIndx = i;
        }
        sumSoldBrandsInType = 0;
    }
    printf("The best sold type with %d sales was %s\n", maxSoldType, types[bestTypeIndx]);
}

// Calculate the sum of sales in the given day and print a proper message.
void printTotalSalesInDay(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int chosenDay)
{
    int totalSalesSum = 0;
    int chosenDayIndx = chosenDay - 1;
    for (int i = 0; i < NUM_OF_BRANDS; i++)
    {
        for (int j = 0; j < NUM_OF_TYPES; j++)
        {
            totalSalesSum = totalSalesSum + cube[chosenDayIndx][i][j];
        }
    }
    printf("The sales total was %d\n", totalSalesSum);
}

// Calculate the amount of sales for each type of the given brand and print a proper message.
void printAllSalesforBrand(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int brandIndx, int insertedDaysAmount)
{
    printf("Sales for %s:", brands[brandIndx]);
    // Going through the days with data only.
    for (int j = 0; j < insertedDaysAmount; j++)
    {
        int day = j + 1;
        printf("\nDay %d- ", day);
        for (int k = 0; k < NUM_OF_TYPES; k++)
        {
            printf("%s: %d ", types[k], cube[j][brandIndx][k]);
        }
    }
    printf("\n");
}

// Calculate what's the brand with the largest amount of sales in all days and print a proper message.
void printBestBrandOverall(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int insertedDaysAmount)
{
    int sumSellingBrand = 0, maxSellingBrand = 0, mostSoldBrandIndx = -1;
    for (int i = 0; i < NUM_OF_BRANDS; i++)
    {
        for (int j = 0; j < NUM_OF_TYPES; j++)
        {
            for (int k = 0; k < insertedDaysAmount; k++)
            {
                sumSellingBrand = sumSellingBrand + cube[k][i][j];
            }
        }
        // Update the most sold brand, if justified.
        if (sumSellingBrand > maxSellingBrand)
        {
            maxSellingBrand = sumSellingBrand;
            mostSoldBrandIndx = i;
        }
        sumSellingBrand = 0;
    }
    printf("The best-selling brand overall is %s: %d$\n", brands[mostSoldBrandIndx], maxSellingBrand);
}

// Calculate what's the type with the largest amount of sales in all days and print a proper message.
void printBestTypeOverall(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int insertedDaysAmount)
{
    int sumSellingType = 0, maxSellingType = 0, mostSoldTypeIndx = -1;
    for (int i = 0; i < NUM_OF_TYPES; i++)
    {
        for (int j = 0; j < NUM_OF_BRANDS; j++)
        {
            for (int k = 0; k < insertedDaysAmount; k++)
            {
                sumSellingType = sumSellingType + cube[k][j][i];
            }
        }
        // Update the most sold type, if justified.
        if (sumSellingType > maxSellingType)
        {
            maxSellingType = sumSellingType;
            mostSoldTypeIndx = i;
        }
        sumSellingType = 0;
    }
    printf("The best-selling type of car is %s: %d$\n", types[mostSoldTypeIndx], maxSellingType);
}

// Calculate what's the day with the largest amount of sales (of all brands and types) and print a proper message.
void printMostProfitableDay(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int insertedDaysAmount)
{
    int sumSellingInDay = 0, maxSellingInDay = 0, mostSoldDayIndx = -1;
    for (int i = 0; i < insertedDaysAmount; i++)
    {
        for (int j = 0; j < NUM_OF_BRANDS; j++)
        {
            for (int k = 0; k < NUM_OF_TYPES; k++)
            {
                sumSellingInDay = sumSellingInDay + cube[i][j][k];
            }
        }
        // Update the day with the most sales, if justified.
        if (sumSellingInDay > maxSellingInDay)
        {
            maxSellingInDay = sumSellingInDay;
            mostSoldDayIndx = i;
        }
        sumSellingInDay = 0;
    }
    int profitableDay = mostSoldDayIndx + 1;
    printf("The most profitable day was day number %d: %d$\n", profitableDay, maxSellingInDay);
}

// 
float avgDeltaForBrand(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int brandIndx, int insertedDaysAmount)
{
    float avgD = 0, sumDifferences = 0;
    // If the user entered data for 1 day, there are no differences so we'll just sum all the sales and print it.
    if (insertedDaysAmount == 1)
    {
        for (int t = 0; t < NUM_OF_TYPES; t++)
        {
            avgD = avgD + cube[0][brandIndx][t];
        }
    }
    // If the user entered data for 2+ days, the func calculates the requested average delta.
    else if (insertedDaysAmount > 1)
    {
        for (int j = 0; j < NUM_OF_TYPES; j++)
        {
            for (int k = 0; k < insertedDaysAmount - 1; k++)
            {
                sumDifferences = sumDifferences + (cube[k + 1][brandIndx][j] - cube[k][brandIndx][j]);
            }
        }
        avgD = sumDifferences / (insertedDaysAmount - 1);
    }
    // If the user didn't enter data at all (insertedDaysAmount=0), the func will return 0 as the first value of "avgD".
    return avgD;
}
