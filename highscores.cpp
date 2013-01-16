#include "highscores.h"

bool hsComp(score *first, score *second)
{
    return (*first > *second);
}
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
    scoreTMP = atoi(nodeTransversal->FirstChildElement("score")->GetText());
    this->addScore(playerNameTMP, scoreTMP);

    // Get all node
    while(true)
    {
        nodeTransversal = nodeTransversal->NextSiblingElement("hs");
        if(nodeTransversal)
        {
            playerNameTMP = string(nodeTransversal->FirstChildElement("name")->GetText());
            scoreTMP = atoi(nodeTransversal->FirstChildElement("score")->GetText());
            this->addScore(playerNameTMP, scoreTMP);
        }
        else
        {
            break;
        }
    }

    // Sort highscore depend on its score
    this->highScoreData.sort(hsComp);



}
void highscore::newHighScore(score *newHighScore)
{
    // SAVE NEW SCORE DIRECTLY INTO XML FILE
    // Load XML file
    char scoreStr[10];

    XMLDocument doc;
    XMLElement *nodeTransversal;
    doc.LoadFile("score.xml");

    // Write its child first
    XMLText *nameText = doc.NewText(newHighScore->readPlayerName().c_str());
    XMLElement *name = doc.NewElement("name");
    name->InsertEndChild(nameText);

    sprintf(scoreStr, "%d", newHighScore->readScore());
    XMLText *scoreText = doc.NewText(scoreStr);
    XMLElement *score = doc.NewElement("score");
    score->InsertEndChild(scoreText);

    // Create new node
    XMLElement* hs = doc.NewElement("hs");
    hs->InsertEndChild(name);
    hs->InsertEndChild(score);

    doc.InsertEndChild(hs);

    doc.SaveFile("score.xml");
}

void highscore::saveHighScore()
{

}

void highscore::addScore(string playerName, int scorePoint)
{
    score *newScore = new score(playerName, scorePoint);
    this->highScoreData.push_back(newScore);
}

highscore::~highscore()
{
    // Delete all of score in highScoreData
    list<score *>::iterator it = this->highScoreData.begin();
    for(int i=0; i < this->highScoreData.size(); i++)
    {
        if((*it) != NULL)
        {
            delete (*it);
        }
        ++it;
    }
}

// Interface High Score part
interfaceHighScore::interfaceHighScore()
{
    // Load background bitmap
    this->hsBackground = load_bitmap("highscore.pcx", NULL);

    // Load font
    hsFont = load_font("font-highscore.pcx", pallete, NULL);
}

void interfaceHighScore::displayHighScore()
{
    // Buffer hsBackground
    BITMAP *buffer;
    buffer = create_bitmap(640, 480);
    draw_sprite(buffer, this->hsBackground, 0, 0);

    // Display highscore title.
    textout_centre_ex(buffer, this->hsFont, "SKOR TERTINGGI", 320, 50, makecol(0,0,0), -1);
    // Iterate highScoreData, display each name and score
    list<score *>::iterator it = this->highScoreData.begin();
    for(int i=0; i < this->highScoreData.size(); i++)
    {
        // Display each name
        textprintf_ex(buffer, this->hsFont, HIGHSCORE_ITEM_START_X, HIGHSCORE_ITEM_START_Y + i * HIGHSCORE_ITEM_HEIGHT, makecol(255,255,255), -1, (*it)->readPlayerName().c_str());
        textprintf_ex(buffer, this->hsFont, HIGHSCORE_ITEM_START_X + HIGHSCORE_SCORENUMBER, HIGHSCORE_ITEM_START_Y + i * HIGHSCORE_ITEM_HEIGHT, makecol(255,255,255), -1, "%05d", (*it)->readScore());
        ++it;
    }

    blit(buffer, screen, 0, 0, 0, 0, 640, 480);

}


