#include "highscores.h"

void highscore::reloadHighScore()
{
    string playerNameTMP;
    int scoreTMP;
    // Clear highscore list first
    this->highScoreData.clear();

    // Initialize XML reader
    XMLDocument xmlHighScore;
    XMLElement *nodeTransversal;
    xmlHighScore.LoadFile("score.xml");

    // Get first child
    nodeTransversal = xmlHighScore.FirstChildElement("hs");
    playerNameTMP = string(nodeTransversal->FirstChildElement("name")->GetText());
    scoreTMP = nodeTransversal->IntAttribute("score");
    this->addScore(playerNameTMP, scoreTMP);

    // Get all node
    while(true)
    {
        nodeTransversal = nodeTransversal->NextSiblingElement("hs");
        if(nodeTransversal)
        {
            playerNameTMP = string(nodeTransversal->FirstChildElement("name")->GetText());
            scoreTMP = nodeTransversal->IntAttribute("score");
            this->addScore(playerNameTMP, scoreTMP);
        }
        else
        {
            break;
        }
    }



}
void highscore::newHighScore(score *newHighScore)
{
    if(newHighScore != NULL)
    {
        this->highScoreData.push_back(newScore);
    }
}

void highscore::saveHighScore()
{

}

void highscore::addScore(string playerName, int scorePoint)
{
    score *newScore = new score(playerName, scorePoint);
    this->highScoreData.push_back(newScore);
}


// Interface High Score part
interfaceHighScore::interfaceHighScore()
{
    // Load background bitmap
    this->hsBackground = load_bitmap("highscore.bmp", NULL);
}

void interfaceHighScore::displayHighScore()
{
    blit(this->hsBackground, screen, 0, 0, 0, 0, 640, 480);

}
