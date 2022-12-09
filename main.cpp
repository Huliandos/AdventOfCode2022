#include "DayOne/DayOne.h"
#include "DayTwo/DayTwo.h"
#include "DayThree/DayThree.h"
#include "DayFour/DayFour.h"
#include "DayFive/DayFive.h"
#include "DaySix/DaySix.h"
#include "DaySeven/DaySeven.h"
#include "DayEight/DayEight.h"

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
        {
        case 5:
            std::cout << "The cargo on top of each of the cargo stacks with the crate mover 9000 are: ";
            for (char cargo : dayFive::GetTopsOfStacksAfterMoving(true)) {
                std::cout << cargo << ", ";
            }
            std::cout << std::endl;

            std::cout << "The cargo on top of each of the cargo stacks with the crate mover 9001 are: ";
            for (char cargo : dayFive::GetTopsOfStacksAfterMoving(false)) {
                std::cout << cargo << ", ";
            }
            std::cout << std::endl;
            break;
        }
        case 6:
            std::cout << "The position of the first valid start-of-packet marker is: " << daySix::GetFirstMarkerPosition(4) << std::endl;

            std::cout << "The position of the first valid start-of-message marker is: " << daySix::GetFirstMarkerPosition(14) << std::endl;
            break;
        case 7:
            std::cout << "The total size of all files under the size of 100000 is: " << daySeven::GetCombinedSizeOfSmallFiles(100000) << std::endl;

            std::cout << "The size of the smallest directory to delete to open up enough filespace is: " << daySeven::GetSizeOfSmallestDirectoryForUpdate(70000000, 30000000) << std::endl;
            break;
        case 8:
            std::cout << "The amount of visible trees in the forest is: " << dayEight::GetNumOfVisibleTrees() << std::endl;

            std::cout << "The highest scenic score is: " << dayEight::GetHighestScenicScore() << std::endl;
            break;
        default:
            std::cout << "The day you're looking for has either not been implemented yet, or doesn't exist in the advent of coding " << std::endl;
            break;
    }
}
