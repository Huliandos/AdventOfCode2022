#include "DayOne/DayOne.h"
#include "DayTwo/DayTwo.h"
#include "DayThree/DayThree.h"
#include "DayFour/DayFour.h"

#include <iostream>

//Tasks can be found under https://adventofcode.com/
int main()
{
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
        case 2:
            std::cout << "The score for the strategy guide, while interpreting the second line as the sign the player should choose, is: " << dayTwo::StratGuideScore_SecondColumnSign() << std::endl;

            std::cout << "The score for the strategy guide, while interpreting the second line as how the game should end, is: " << dayTwo::StratGuideScore_SecondColumnRoundPrediction() << std::endl;
            break;
        case 3:
            std::cout << "The combined priority of all items in both compartements of each rucksack is: " << dayThree::GetCombinedRucksackPriority() << std::endl;

            std::cout << "The combined priority of all badges from groups of up to three elves is: " << dayThree::GetCombinedGroupBadgePriority() << std::endl;
            break;
        case 4:
            std::cout << "The number of elves having cleaning IDs fully contained in their partners IDs is: " << dayFour::GetNumberOfFullyContainedPairs() << std::endl;

            std::cout << "The number of elves having overlapping with their partners cleaning IDs is: " << dayFour::GetNumberOfOverlappingPairs() << std::endl;
            break;
        default:
            std::cout << "The day you're looking for has either not been implemented yet, or doesn't exist in the advent of coding " << std::endl;
            break;
    }
}
