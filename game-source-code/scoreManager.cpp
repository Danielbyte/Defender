#include "scoreManager.h"

ScoreManager::ScoreManager():
	landerPoints{5},
	bomberPoints{5},
	rescuePoints{5}
{
	updateHighScore(0);
}

int ScoreManager::getHighScore()
{
	return highScore;
}

void ScoreManager::updateHighScore(const int currentScore)
{
	if (currentScore < 0) throw NegativeScoreNotAllowed{};

	highScoreFile.open("resources/high_score.txt");

	//update high score if prev high score is undertaken
	if (highScoreFile.is_open())
	{
		highScoreFile >> highScore;
		if (highScore < currentScore)
			highScore = currentScore;
	}
	highScoreFile.close();

	outFile.open("resources/high_score.txt");
	if (outFile.is_open())
		outFile << highScore;

	outFile.close();
}

void ScoreManager::updateCurrentScore(std::shared_ptr<Player>& player, const std::string scoreType)
{
	if (scoreType == "lander")
	{
		player->updatePlayerScore(landerPoints);
	}

	if (scoreType == "bomber")
	{
		player->updatePlayerScore(bomberPoints);
	}

	if (scoreType == "rescue")
	{
		player->updatePlayerScore(rescuePoints);
	}
}