#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "Well.h"
#include "UserInterface.h"
#include <string>

// [Add other #include directives as necessary.]

class Game
{
  public:
    Game(int width, int height);
    void play();
    bool playOneLevel();
    void displayPrompt(std::string s);
    void displayStatus();
    int spaces(int digits);
    void displayNextPiece(PieceType type);

  private:
    Well        m_well;
    Screen      m_screen;
    int         m_level;
    int         m_score;
    int         m_rowsLeft;
};

#endif // GAME_INCLUDED
