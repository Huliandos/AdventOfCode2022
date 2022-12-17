#include "Day1/Day1.h"
#include "Day2/Day2.h"
#include "Day3/Day3.h"
#include "Day4/Day4.h"
#include "Day5/Day5.h"
#include "Day6/Day6.h"
#include "Day7/Day7.h"
#include "Day8/Day8.h"
#include "Day9/Day9.h"
#include "Day10/Day10.h"
#include "Day11/Day11.h"
#include "Day12/Day12.h"
#include "Day13(ToDo)/Day13.h"
#include "Day14/Day14.h"
#include "Day15/Day15(FirstAttempt).h"
#include "Day15/Day15.h"
#include "Day16(ToDo)/Day16.h"
#include "Day17(ToDo)/Day17.h"

#include <iostream>
#include <stdexcept>

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
        case 9:
            std::cout << "The number of positions the tail visited with 2 knots is: " << dayNine::GetNumOfPositionsVisited(2) << std::endl;

            std::cout << "The number of positions the tail visited 10 knots is: " << dayNine::GetNumOfPositionsVisited(10) << std::endl;
            break;
        case 10:
            std::cout << "The total signal strnegth at 20, 60, 100, 140, 180 and 220 cycles is: " << dayTen::GetTotalSignalStrength() << std::endl;

            std::cout << "After executing all CPU commands the screen looks like this: " << std::endl << dayTen::GenerateSprite() << std::endl;
            break;
        case 11:
            std::cout << "The multiplied monkey business for heighest to numbers of inspected items of monkeys after 20 rounds is: " << dayEleven::GetMultipliedMonkeyBusiness(true) << std::endl;

            std::cout << "The multiplied monkey business for heighest to numbers of inspected items of monkeys aftetr 10000 rounds without dividing by 3 is: " << dayEleven::GetMultipliedMonkeyBusiness(false) << std::endl;
            break;
        case 12:
            try {
                std::cout << "The min num of tiles that have to be traversed from S to E to climb the hill are: " << dayTwelve::GetMinNumOfNodesToVisit(true) << std::endl;

                std::cout << "The min num of tiles that have to be traversed from any a to E to climb the hill are: " << dayTwelve::GetMinNumOfNodesToVisit(false) << std::endl;
            }
            catch (std::domain_error e) {
                std::cout << e.what() << std::endl;
            }
            break;
        //case 13:
            //std::cout << "The sum of the indices in the right order are: " << dayThirteen::GetSumOfIndicesInRightOrder() << std::endl;
            break;
        case 14:
            std::cout << "The number of units of sand coming to rest before they start spilling into the abyss is: " << dayFourteen::GetUnitsOfSandBeforeOverflow(true) << std::endl;

            std::cout << "The number of units of sand coming to rest before the hole clogs itself is: " << dayFourteen::GetUnitsOfSandBeforeOverflow(false) << std::endl;
            break;
        case 15:
            //std::cout << "The number of positions in row 2000000 where the beacon can't be present is: " << dayFifteen::GetNumPositionsWithoutBeacon() << std::endl;

            std::cout << "Get input frequency of only open space: " << dayFifteen::GetInputFrequencyOfFreeSpace() << std::endl;
            break;
        default:
            std::cout << "The day you're looking for has either not been implemented yet, or doesn't exist in the advent of coding " << std::endl;
            break;
    }
}
