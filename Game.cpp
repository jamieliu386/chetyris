#include "Game.h"
#include "Well.h"
#include "UserInterface.h"
#include <string>
#include <algorithm>

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 25;

const int WELL_X = 0;
const int WELL_Y = 0;

const int PROMPT_Y = 20;
const int PROMPT_X = 0;

const int SCORE_X = 16;
const int SCORE_Y = 8;

const int ROWS_LEFT_X = 16;
const int ROWS_LEFT_Y = 9;

const int LEVEL_X = 16;
const int LEVEL_Y = 10;

const int NEXT_PIECE_TITLE_X = 16;
const int NEXT_PIECE_TITLE_Y = 3;

const int NEXT_PIECE_X = 16;
const int NEXT_PIECE_Y = 4;

Game::Game(int width, int height)
: m_screen(SCREEN_WIDTH, SCREEN_HEIGHT), m_level(1), m_score(0), m_rowsLeft(5)
{}


void Game::play()
{
    m_well.display(m_screen, WELL_X, WELL_Y);
    displayStatus();  //  score, rows left, level
    displayPrompt("Press the Enter key to begin playing Chetyris!");
    waitForEnter();  // [in UserInterface.h]

    for(;;)
    {
        if ( ! playOneLevel())
            break;
        displayPrompt("Good job!  Press the Enter key to start next level!");
        waitForEnter();
        m_level++;
    }
    displayPrompt("Game Over!  Press the Enter key to exit!");
    waitForEnter();
}

void Game::displayPrompt(std::string s)     
{
    m_screen.gotoXY(PROMPT_X, PROMPT_Y);
    m_screen.printStringClearLine(s);   // overwrites previous text
    m_screen.refresh();
}

void Game::displayStatus()
{
    // next piece title
    m_screen.gotoXY(NEXT_PIECE_TITLE_X, NEXT_PIECE_TITLE_Y);
    m_screen.printString("Next piece:");
    
    // score
    m_screen.gotoXY(SCORE_X, SCORE_Y);
    std::string score = "Score:     ";
    for (int i = 0; i < spaces(m_score); i++)
        score += " ";
    score += std::to_string(m_score);
    m_screen.printString(score);
    
    // rows left
    m_screen.gotoXY(ROWS_LEFT_X, ROWS_LEFT_Y);
    std::string rowsLeft = "Rows Left: ";
    for (int i = 0; i < spaces(m_rowsLeft); i++)
        rowsLeft += " ";
    rowsLeft += std::to_string(m_rowsLeft);
    m_screen.printString(rowsLeft);
    
    // level
    m_screen.gotoXY(LEVEL_X, LEVEL_Y);
    std::string level = "Level:     ";
    for (int i = 0; i < spaces(m_level); i++)
        level += " ";
    level += std::to_string(m_level);
    m_screen.printString(level);
}

int Game::spaces(int digits)
{
    int length = 1;
    while (digits /= 10)
        length++;
    
    int spaces = 7 - length;
    return spaces;
}

void Game::displayNextPiece(PieceType type)
{
    Piece* toDraw;
    switch(type)
    {
        case PIECE_I:
            toDraw = new PieceI();
            break;
        case PIECE_L:
            toDraw = new PieceL();
            break;
        case PIECE_J:
            toDraw = new PieceJ();
            break;
        case PIECE_T:
            toDraw = new PieceT();
            break;
        case PIECE_O:
            toDraw = new PieceO();
            break;
        case PIECE_S:
            toDraw = new PieceS();
            break;
        case PIECE_Z:
            toDraw = new PieceZ();
            break;
        case PIECE_VAPOR:
            toDraw = new PieceVapor();
            break;
        case PIECE_FOAM:
            toDraw = new PieceFoam();
            break;
        case PIECE_CRAZY:
            toDraw = new PieceCrazy();
            break;
    }
    m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y);
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 4; i++)
        {
            if (toDraw->isABlock(type,i,j, 0))
                m_screen.printChar('#');
            else
                m_screen.printChar(' ');
        }
        m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y + j + 1);
    }
    delete toDraw;
}


bool Game::playOneLevel()
{
    m_well.clearWell();
    
    // rowsLeft, current/next PieceType, timeLeft
    m_rowsLeft = m_level * 5;
    
    displayStatus();
    m_screen.refresh();
    
    PieceType current;
    PieceType next = NUM_PIECE_TYPES;
    
    
    
    int tick = std::max(1000 - (100 * m_level-1), 100);
    
    for (;;)
    {
        // if no next piece type, generate random piecetype
        if (next == NUM_PIECE_TYPES)
        {
            current = chooseRandomPieceType();
            m_well.createPiece(current);
            m_well.drawPiece();
            m_well.displayWell(m_screen, 1, 0);
            next = chooseRandomPieceType();
            displayNextPiece(next);
            m_screen.refresh();
        }
        
        // otherwise, use the next piece type
        else
        {
            current = next;
            m_well.createPiece(current);
            m_well.drawPiece();
            m_well.displayWell(m_screen, 1, 0);
            next = chooseRandomPieceType();
            displayNextPiece(next);
            m_screen.refresh();
        }
        
        if (m_well.isGameOver())
            return false;
        
        bool landed = false;
        
        while (m_well.inPlay())
        {
                Timer timer;
                while (timer.elapsed() < tick)
                {
                    char ch;
                    if (getCharIfAny(ch))
                    {
                        switch(ch)
                        {
                                // for spacebar, move piece to the bottom
                            case ' ':
                            {
                                while (!m_well.atBottom())
                                {
                                    m_well.movePiece('s');
                                }
                                landed = true;
                                m_well.drawPiece();
                                m_well.displayWell(m_screen, 1, 0);
                                m_screen.refresh();
                                break;
                            }
                                // for arrow down, move piece down, restart timer, redisplay well
                            case ARROW_DOWN:
                            {
                                if (m_well.atBottom())
                                    landed = true;
                                else
                                {
                                    m_well.movePiece('s');
                                    m_well.drawPiece();
                                    m_well.displayWell(m_screen, 1, 0);
                                    timer.start();
                                    m_screen.refresh();
                                }
                                break;
                            }
                                // for arrow left, move piece left and redisplay well
                            case ARROW_LEFT:
                            {
                                m_well.movePiece('a');
                                m_well.drawPiece();
                                m_well.displayWell(m_screen, 1, 0);
                                m_screen.refresh();
                                break;
                            }
                                // for arrow right, move piece right and redisplay well
                            case ARROW_RIGHT:
                            {
                                m_well.movePiece('d');
                                m_well.drawPiece();
                                m_well.displayWell(m_screen, 1, 0);
                                m_screen.refresh();
                                break;
                            }
                                // for arrow up, rotate piece and redisplay well
                            case ARROW_UP:
                            {
                                m_well.rotatePiece();
                                m_well.drawPiece();
                                m_well.displayWell(m_screen, 1, 0);
                                m_screen.refresh();
                                break;
                            }
                                // for q, return false
                            case 'q':
                            case 'Q':
                                return false;
                        } // end ch switch
                    } // end get char if any
                    if (landed)
                        break;
                } // end timer loop
            
            
            // when time is up, discard pending keys
            discardPendingKeys();
        
            
            // let the piece fall downward if it can
            if (!m_well.atBottom())
            {
                m_well.movePiece('s');
                m_well.displayWell(m_screen, 1, 0);
                m_screen.refresh();
            }
            
            // else if piece is at bottom, perform action and destroy piece
            else if (m_well.atBottom())
            {
                m_well.performAction(current);
                m_well.displayWell(m_screen, 1, 0);
                m_screen.refresh();
                m_well.destroyPiece();
                
                
                
                // delete full lines until they are all gone or m_rowsLeft reaches 0
                int rowsRemoved = 0;
                for (int j = 17; j > -1; j--)
                {
                    if (m_well.isFull(j))
                    {
                        m_well.removeLine(j);
                        rowsRemoved++;
                        m_rowsLeft--;
                        j++;
                    }
                    if (m_rowsLeft == 0)
                        break;
                }
                
                // change score based on rowsRemoved
                switch(rowsRemoved)
                {
                    case 0:
                        break;
                    case 1:
                    {
                        m_score += 100;
                        break;
                    }
                    case 2:
                    {
                        m_score += 200;
                        break;
                    }
                    case 3:
                    {
                        m_score += 400;
                        break;
                    }
                    case 4:
                    {
                        m_score += 800;
                        break;
                    }
                    case 5:
                    {
                        m_score += 1600;
                        break;
                    }
                } // end change score
                
                // update well and game information=
                m_well.displayWell(m_screen, 1, 0);
                displayStatus();
                m_screen.refresh();
                
                // if level won, return true
                if (m_rowsLeft == 0)
                {
                    return true;
                }
                
            } // end piece landed
        } // end while piece is in play
    } // end for loop
    
    
    return false;
}
    
