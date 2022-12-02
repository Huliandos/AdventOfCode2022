#include "DayTwo.h"

#include <iostream>
#include <fstream>	//std::ifstream
#include <string>

namespace dayTwo {
	/// <summary>
	/// Calculates the total score of the strategy guide, while interpreting the second column as the sign the player has to use
	/// </summary>
	/// <returns></returns>
	int StratGuideScore_SecondColumnSign() {
		//open file
		//A&X = Rock, B&Y = Paper, C&Z = Scissors
		std::ifstream strategyGuideTxt("./InputFiles/DayTwo_RockPaperSicorsInput.txt", std::ifstream::in);

		int totalPoints = 0;
		//read out data
		if (strategyGuideTxt.is_open())
		{
			std::string line{};

			while (std::getline(strategyGuideTxt, line))
			{
				//maps the player sign to a number between 0-2, with 0 being rock, 1 paper and 2 scissors
				int playerSign = (line[2] - 88);

				//winner = (3 + player1 - player2) % 3. 
				// 1: player 1 wins, 2: player 2 wins, 0: tie
				//because: X is defeated by (X+1) % 3
				//X defeats (X+2) % 3
				//--> leads to the above formula. 3 is added to force resulst to not be negative
				//1 means player one (the enemy) won, 2 that we won and 0 that it's a draw
				int winner = (3 + (line[0]-65) - playerSign) % 3;

				//draw
				if (winner == 0)
					totalPoints += 3;
				//we win
				else if (winner == 2)
					totalPoints += 6;

				//add the score of the chosen sign to our score
				//+1 because each sign is worth one point more than in the mapping generated above
				totalPoints += playerSign + 1;

				//std::cout << (line[0] - 65) << " " << line[2] - 88 << " "  << 3 + (line[0] - 65) << " " << (3 + (line[0] - 65) - (line[2] - 88)) << " " << winner << std::endl;
			}

			//close file
			strategyGuideTxt.close();
		}

		return totalPoints;
	}

	/// <summary>
	/// Calculates the total score of the strategy guide, while interpreting the second column as how the round is supposed to end
	/// </summary>
	/// <returns></returns>
	int StratGuideScore_SecondColumnRoundPrediction() {
		//open file
		//A = Rock, B = Paper, C = Scissors, X lose, Y draw, Z win
		std::ifstream strategyGuideTxt("./InputFiles/DayTwo_RockPaperSicorsInput.txt", std::ifstream::in);

		int totalPoints = 0;
		//read out data
		if (strategyGuideTxt.is_open())
		{
			std::string line{};

			while (std::getline(strategyGuideTxt, line))
			{
				//0 rock, 1 paper, 2 scissors
				int playerSign = 0;
				int enemySign = (line[0] - 65);

				//player should lose
				if (line[2] == 'X') {
					//X is the enemy
					//X defeats (X+2) % 3
					playerSign = (enemySign + 2) % 3;
				}
				//player should draw
				if (line[2] == 'Y') {
					//cast to range from 0-2
					playerSign = enemySign;
					totalPoints += 3;
				}
				//player should win
				if (line[2] == 'Z') {
					//X is the enemy
					//X is defeated by (X+1) % 3
					playerSign = (enemySign + 1) % 3;
					totalPoints += 6;
				}

				//add the score of the chosen sign to our score
				//+1 because each sign is worth one point more than in the mapping generated above
				totalPoints += playerSign + 1;
			}

			//close file
			strategyGuideTxt.close();
		}

		return totalPoints;
	}
}