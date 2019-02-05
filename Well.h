#ifndef WELL_INCLUDED
#define WELL_INCLUDED

#include "Piece.h"


const char FREE = ' ';
const char PIECE = '#';
const char WALL = '@';
const char FILLED = '$';
const char FOAM = '*';

class Screen;


class Well
{
  public:
    // constructor
    Well();
    
    // destructor
    ~Well();
    
    
    // display well
    void display(Screen& screen, int x, int y) const;
    
    // draw border
    void displayBorder(Screen& screen, int x, int y) const;
    
    // draw contents/grid
    void displayWell(Screen& screen, int x, int y) const;
    
    // This function clears the well of all values.
    void clearWell();
    
    // This function accepts an x and y int, and returns true
    // if the well is empty at that location. It returns false
    // if x or y is invalid (less than 0 or greater than 9 and 18,
    // respectively) or if the well is not empty at the location.
    bool isEmpty(int x, int y) const;

    // This function accepts a PieceType and dynamically
    // allocates a piece of that type.
    void createPiece(PieceType type);
    
    // Returns m_piece's x coordinate.
    int getX() const;
    
    // Returns m_piece's y coordinate.
    int getY() const;
    
    // Returns m_piece's PieceType.
    PieceType getT() const;
    
    // Returns m_piece's orientation.
    int getO() const;
    
    // This function deletes m_piece.
    void destroyPiece();
    
    // This function places m_piece in the well.
    void drawPiece();
    
    // This function returns true if there is
    // a piece in play.
    bool inPlay() const;
    
    
    // This function returns true if the piece in play is
    // touching the "bottom" (i.e. it cannot move any lower).
    // Otherwise, it returns false.
    bool atBottom() const;
    
    // This function accepts a character input representing
    // a movement, and if the desired movement is valid,
    // it moves the current piece in the well. Otherwise,
    // it does nothing.
    void movePiece(char ch);
    
    // This function rotates the piece in the well if
    // a rotation would allow for a valid configuration.
    // Otherwise, it does nothing.
    void rotatePiece();
    
    // This function accepts a PieceType and performs
    // the action required when that type of piece lands.
    // (i.e. for a regular piece, it converts the piece
    // into "$" symbols, for a vapor piece it vaporizes the
    // required blocks, and for a foam piece it creates
    // the foam)
    void performAction(PieceType type);
    
    // This function returns true if there is a path from the
    // coordinate (sx,sy) to (ex,ey) and false otherwise.
    void fillPaths(char arr[5][5], int x, int y);
    
    // This function creates foam in a 5x5 box around the
    // foam piece in each coordinate that can be reached by the foam piece.
    void foam();
    
    // This function vaporizes the vapor piece and the 2x2
    // grids above and below the piece.
    void vaporize();

    
    // This function changes the current active piece
    // by adding it as a static piece in the well.
    void fill();
    

    // This function returns true if the line at y-coordinate
    // y is filled.
    bool isFull(int y) const;
    
    
    // This function removes the line at the y-coordinate y.
    void removeLine(int y);
    
    // This function returns true if the piece is in an
    // illegal configuration (e.g. if it overlaps with another
    // piece). Otherwise, it returns false.
    bool isGameOver() const;
    
  private:
    char m_well [18][10];
    Piece* m_piece;
    bool m_inPlay;
    bool m_gameOver;
};

#endif // WELL_INCLUDED
