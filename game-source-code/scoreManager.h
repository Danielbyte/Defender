#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include <sstream>
#include <fstream>

class NegativeScoreNotAllowed{};

class ScoreManager
{
public:
	ScoreManager();
	int getHighScore();
	void updateHighScore(const std::string scoreType);

private:
	int highScore;
	int landerPoints;
	int bomberPoints;
	int rescuePoints;
};
#endif // !SCOREMANAGER_H

