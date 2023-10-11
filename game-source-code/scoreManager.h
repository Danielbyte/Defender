#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include <sstream>
#include <fstream>
#include "player.h"

class NegativeScoreNotAllowed{};

class ScoreManager
{
public:
	ScoreManager();
	int getHighScore();
	void updateHighScore(const int cuurentScore);
	void updateCurrentScore(std::shared_ptr<Player>& player, const std::string scoreType);

private:
	int highScore;
	int landerPoints;
	int bomberPoints;
	int rescuePoints;

	std::ifstream highScoreFile;
	std::ofstream outFile;
};
#endif // !SCOREMANAGER_H

