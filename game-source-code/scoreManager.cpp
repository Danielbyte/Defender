#include "scoreManager.h"

ScoreManager::ScoreManager():
	highScore{0},
	landerPoints{5},
	bomberPoints{5},
	rescuePoints{5}
{}

int ScoreManager::getHighScore()
{
	return highScore;
}

void ScoreManager::updateHighScore(const int currentScore, const std::string scoreType)
{
	if (currentScore < 0) throw NegativeScoreNotAllowed{};

	highScoreFile.open("resources/high_score.text");

	//update high score if prev high score is undertaken
	if (highScoreFile.is_open())
	{
		highScoreFile >> highScore;
		if (highScore < currentScore)
			highScore = currentScore;
	}
	highScoreFile.close();

	outFile.open("resources/high_score.text");
	if (outFile.is_open())
		outFile << highScore;

	outFile.close();
}
