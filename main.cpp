#include "DayOne/DayOne.h"

#include <iostream>

int main()
{
    //ToDo: Let user input the solution of the desired day here
    int day = 0;
    std::cout << "Please enter the day you want to see the solution for (1-24): ";
    std::cin >> day;
    
    switch (day) {  
        //put into its own scope so we can declare variables within this case, that don't have to be initialized for other cases
        {
        case 1:
            std::cout << "The highest calorie count one of the elves is carrying is: " << dayOne::GetNMostCalories(1)[0] << std::endl;

            std::cout << "The 3 highest calorie counts the elves are carrying are: ";
            int totalTopThreeCalories = 0;
            for (int elfCalories : dayOne::GetNMostCalories(3)) {
                totalTopThreeCalories += elfCalories;
                std::cout << elfCalories << ", ";
            }
            std::cout << std::endl;

            std::cout << "That's a total of " << totalTopThreeCalories << " calories!" << std::endl;
            break;
        }
        default:
            std::cout << "The day you're looking for has either not been implemented yet, or doesn't exist in the advent of coding " << std::endl;
            break;
    }
}
