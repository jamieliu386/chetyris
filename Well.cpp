#include "Well.h"
#include "UserInterface.h"

Well::Well()
: m_piece(nullptr), m_inPlay(false), m_gameOver(false)
{
    // fill well with empty spaces
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 18; j++)
        {
            m_well[j][i] = FREE;
        }
    }
}

Well::~Well()
{
    delete m_piece;
}

void Well::display(Screen& screen, int x, int y) const
{
    displayBorder(screen,x,y);
    displayWell(screen,x+1,y);
}

void Well::displayBorder(Screen& screen, int x, int y) const
{
    screen.gotoXY(0,0);
    // side walls
    for (int j = 0; j < 18; j++)
    {
        screen.printString("@          @");
        screen.gotoXY(x, j + 1);
    }
    // floor
    screen.printString("@@@@@@@@@@@@");
    
}

void Well::displayWell(Screen& screen, int x, int y) const
{
    screen.gotoXY(x, y);
    for (int j = 0; j < 18; j++)
    {
        for (int i = 0; i < 10; i++)
        {
            // print each character of row
            screen.printChar(m_well[j][i]);
        }
        screen.gotoXY(x, j+1);
    }
}

void Well::clearWell()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 18; j++)
        {
            // set each coordinate to empty
            m_well[j][i] = FREE;
        }
    }
}

bool Well::isEmpty(int x, int y) const
{
    if (x < 0 || y < 0 || x > 9 || y > 17)
        return false;
    if (m_well[y][x] == FREE || m_well[y][x] == PIECE)
        return true;
    return false;
}

void Well::createPiece(PieceType type)
{
    // allocate piece
    switch(type)
    {
        case PIECE_I:
            m_piece = new PieceI();
            break;
        case PIECE_L:
            m_piece = new PieceL();
            break;
        case PIECE_J:
            m_piece = new PieceJ();
            break;
        case PIECE_T:
            m_piece = new PieceT();
            break;
        case PIECE_O:
            m_piece = new PieceO();
            break;
        case PIECE_S:
            m_piece = new PieceS();
            break;
        case PIECE_Z:
            m_piece = new PieceZ();
            break;
        case PIECE_VAPOR:
            m_piece = new PieceVapor();
            break;
        case PIECE_FOAM:
            m_piece = new PieceFoam();
            break;
        case PIECE_CRAZY:
            m_piece = new PieceCrazy();
            break;
    }
    m_inPlay = true;
}

int Well::getX() const
{
    return m_piece->getX();
}

int Well::getY() const
{
    return m_piece->getY();
}

PieceType Well::getT() const
{
    return m_piece->getType();
}

int Well::getO() const
{
    return m_piece->getOrientation();
}

void Well::destroyPiece()
{
    if (m_piece == nullptr)
    {
        m_inPlay = false;
        return;
    }
    else
    {
        delete m_piece;
        m_piece = nullptr;
        m_inPlay = false;
    }
}

void Well::drawPiece()
{
    PieceType myType = getT();
    int myO = getO();
    int myX = getX();
    int myY = getY();
    
    for (int j = myY; j < 4 + myY; j++)
    {
        for (int i = myX; i < 4 + myX; i++)
        {
            // if there should be a piece block at the coordinate,
            // set the coordinate to PIECE
            if (m_piece->isABlock(myType, i-myX, j-myY, myO))
            {
                if (isEmpty(i, j))
                {
                    m_well[j][i] = PIECE;
                }
                else
                {
                    m_well[j][i] = PIECE;
                    m_gameOver = true;
                }
            }
        }
    }
}

bool Well::inPlay() const
{
    return m_inPlay;
}

bool Well::atBottom() const
{
    if (m_piece->okToMove(this, 's'))
        return false;
    return true;
}

void Well::movePiece(char ch)
{
    if (!m_piece->okToMove(this, ch))
        return;
    else
    {
        int myX = getX();
        int myY = getY();
        PieceType myT = getT();
        int myO = getO();
        // clear the piece's blocks in the well
        for (int j = myY; j < 4 + myY; j++)
        {
            for (int i = myX; i < 4 + myX; i++)
            {
                // clear the current piece's blocks
                if (m_piece->isABlock(myT, i-myX, j-myY, myO))
                {
                    m_well[j][i] = FREE;
                }
            }
        }
        // change the piece's coordinates using its move function
        m_piece->move(ch);
        // add the piece back into the well array using drawPiece()
        drawPiece();
    }
}

void Well::rotatePiece()
{
    if (!m_piece->okToRotate(this))
        return;
    else
    {
        int myX = getX();
        int myY = getY();
        PieceType myT = getT();
        int myO = getO();
        // clear the piece's blocks in the well
        for (int j = myY; j < 4 + myY; j++)
        {
            for (int i = myX; i < 4 + myX; i++)
            {
                // clear the current piece's blocks
                if (m_piece->isABlock(myT, i-myX, j-myY, myO))
                {
                    m_well[j][i] = FREE;
                }
            }
        }
        // change the piece's coordinates using its move function
        m_piece->rotate();
        // add the piece back into the well array using drawPiece()
        drawPiece();
    }
}

void Well::performAction(PieceType type)
{
    if (type == PIECE_FOAM)
        foam();
    else if (type == PIECE_VAPOR)
        vaporize();
    else
        fill();
}

void Well::fillPaths(char arr[5][5], int x, int y)
{
    arr[y][x] = 'f';
    
    // check north
    if (y - 1 >= 0)
        if (arr[y-1][x] == 'e')
            fillPaths(arr, x, y - 1);
    // check south
    if (y + 1 <= 4)
        if (arr[y+1][x] == 'e')
            fillPaths(arr, x, y + 1);
    // check east
    if (x + 1 <= 4)
        if (arr[y][x+1] == 'e')
            fillPaths(arr, x + 1, y);
    // check west
    if (x - 1 >= 0)
        if (arr[y][x-1] == 'e')
            fillPaths(arr, x - 1, y);
}

void Well::foam()
{
    int myX = getX() + 1;
    int myY = getY() + 1;
    
    char arr[5][5];
    
    // starting from the topmost/leftmost corner,
    // iterate through each of the coordinates in the 5x5
    // grid centered at the foam piece
    for (int i = myX - 2; i < myX + 3; i++)
    {
        for (int j = myY - 2; j < myY + 3; j++)
        {
            if (isEmpty(i, j))
            {
                arr[j - (myY - 2)][i - (myX - 2)] = 'e';
            }
            else
            {
                arr[j - (myY - 2)][i - (myX - 2)] = 'w';
            }
        }
    }
    
    fillPaths(arr, 2, 2);
    
    for (int i = myX - 2; i < myX + 3; i++)
    {
        for (int j = myY - 2; j < myY + 3; j++)
        {
            if (arr[j - (myY - 2)][i - (myX - 2)] == 'f')
            {
                m_well[j][i] = FOAM;
            }
        }
    }
}

void Well::vaporize()
{
    int myX = getX();
    int myY = getY();
    
    myX++; // increment myX to be where the piece starts
    
    // left vapor block, then right vapor block
    for (int i = myX; i < myX + 2; i++)
    {
        // vaporize the block and the two below
        for (int j = myY; j < myY + 3 && j < 18; j++)
        {
                m_well[j][i] = FREE;
        }
        // vaporize the block and the two above
        for (int j = myY; j > myY - 3 && j > -1; j--)
        {
            m_well[j][i] = FREE;
        }
    }
}

void Well::fill()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 18; j++)
        {
            if (m_well[j][i] == PIECE)
            {
                m_well[j][i] = FILLED;
            }
        }
    }
}

bool Well::isFull(int y) const
{
    for (int i = 0; i < 10; i++)
    {
        // if each block in the row is filled return true
        if (m_well[y][i] != FILLED && m_well[y][i] != FOAM)
            return false;
    }
    return true;
}


void Well::removeLine(int y)
{
    // starting from the row to be removed, iterate
    // upwards through the well, stopping before the
    // topmost row
    for (int j = y; j > 0; j--)
    {
        for (int i = 0; i < 10; i++)
        {
            // fill each row with the elements from
            // the row above it
            m_well[j][i] = m_well[j-1][i];
        }
    }
    // set the topmost row to empty
    for (int i = 0; i < 10; i++)
    {
        m_well[0][i] = FREE;
    }
}

bool Well::isGameOver() const
{
    return m_gameOver;
}
