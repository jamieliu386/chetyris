#include "Piece.h"
#include "Well.h"

int pieces[10][4][4][4] =
{
    // piece I
    {
        // orientation 0
        {
            {0,0,0,0},
            {1,1,1,1},
            {0,0,0,0},
            {0,0,0,0}
        },
        // orientation 1
        {
            {0,1,0,0},
            {0,1,0,0},
            {0,1,0,0},
            {0,1,0,0}
        },
        // orientation 2
        {
            {0,0,0,0},
            {1,1,1,1},
            {0,0,0,0},
            {0,0,0,0}
        },
        // orientation 3
        {
            {0,1,0,0},
            {0,1,0,0},
            {0,1,0,0},
            {0,1,0,0}
        }
    },
    
    // piece L
    {
        // orientation 0
        {
            {0,0,0,0},
            {1,1,1,0},
            {1,0,0,0},
            {0,0,0,0}
        },
        // orientation 1
        {
            {0,1,1,0},
            {0,0,1,0},
            {0,0,1,0},
            {0,0,0,0}
        },
        // orientation 2
        {
            {0,0,0,0},
            {0,0,1,0},
            {1,1,1,0},
            {0,0,0,0}
        },
        // orientation 3
        {
            {0,0,0,0},
            {0,1,0,0},
            {0,1,0,0},
            {0,1,1,0}
        }
    },
    
    // piece J
    {
        // orientation 0
        {
            {0,0,0,0},
            {0,1,1,1},
            {0,0,0,1},
            {0,0,0,0}
        },
        // orientation 1
        {
            {0,0,0,0},
            {0,0,1,0},
            {0,0,1,0},
            {0,1,1,0}
        },
        // orientation 2
        {
            {0,0,0,0},
            {0,1,0,0},
            {0,1,1,1},
            {0,0,0,0}
        },
        // orientation 3
        {
            {0,1,1,0},
            {0,1,0,0},
            {0,1,0,0},
            {0,0,0,0}
        }
    },
    
    // piece T
    {
        // orientation 0
        {
            {0,1,0,0},
            {1,1,1,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        // orientation 1
        {
            {0,1,0,0},
            {0,1,1,0},
            {0,1,0,0},
            {0,0,0,0}
        },
        // orientation 2
        {
            {0,0,0,0},
            {1,1,1,0},
            {0,1,0,0},
            {0,0,0,0}
        },
        // orientation 3
        {
            {0,1,0,0},
            {1,1,0,0},
            {0,1,0,0},
            {0,0,0,0}
        }
    },
    
    // piece O
    {
        // orientation 0
        {
            {1,1,0,0},
            {1,1,0,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        // orientation 1
        {
            {1,1,0,0},
            {1,1,0,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        // orientation 2
        {
            {1,1,0,0},
            {1,1,0,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        // orientation 3
        {
            {1,1,0,0},
            {1,1,0,0},
            {0,0,0,0},
            {0,0,0,0}
        }
    },
    
    // piece S
    {
        // orientation 0
        {
            {0,0,0,0},
            {0,1,1,0},
            {1,1,0,0},
            {0,0,0,0}
        },
        // orientation 1
        {
            {0,1,0,0},
            {0,1,1,0},
            {0,0,1,0},
            {0,0,0,0}
        },
        // orientation 2
        {
            {0,0,0,0},
            {0,1,1,0},
            {1,1,0,0},
            {0,0,0,0}
        },
        // orientation 3
        {
            {0,1,0,0},
            {0,1,1,0},
            {0,0,1,0},
            {0,0,0,0}
        }
    },
    
    // piece Z
    {
        // orientation 0
        {
            {0,0,0,0},
            {1,1,0,0},
            {0,1,1,0},
            {0,0,0,0}
        },
        // orientation 1
        {
            {0,0,1,0},
            {0,1,1,0},
            {0,1,0,0},
            {0,0,0,0}
        },
        // orientation 2
        {
            {0,0,0,0},
            {1,1,0,0},
            {0,1,1,0},
            {0,0,0,0}
        },
        // orientation 3
        {
            {0,0,1,0},
            {0,1,1,0},
            {0,1,0,0},
            {0,0,0,0}
        }
    },
    
    // piece VAPOR
    {
        // orientation 0
        {
            {0,1,1,0},
            {0,0,0,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        // orientation 1
        {
            {0,1,1,0},
            {0,0,0,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        // orientation 2
        {
            {0,1,1,0},
            {0,0,0,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        // orientation 3
        {
            {0,1,1,0},
            {0,0,0,0},
            {0,0,0,0},
            {0,0,0,0}
        }
    },
    
    // piece FOAM
    {
        // orientation 0
        {
            {0,0,0,0},
            {0,1,0,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        // orientation 1
        {
            {0,0,0,0},
            {0,1,0,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        // orientation 2
        {
            {0,0,0,0},
            {0,1,0,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        // orientation 3
        {
            {0,0,0,0},
            {0,1,0,0},
            {0,0,0,0},
            {0,0,0,0}
        }
    },
    
    // piece CRAZY
    {
        // orientation 0
        {
            {1,0,0,1},
            {0,1,1,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        // orientation 1
        {
            {0,0,0,1},
            {0,0,1,0},
            {0,0,1,0},
            {0,0,0,1}
        },
        // orientation 2
        {
            {0,0,0,0},
            {0,0,0,0},
            {0,1,1,0},
            {1,0,0,1}
        },
        // orientation 3
        {
            {1,0,0,0},
            {0,1,0,0},
            {0,1,0,0},
            {1,0,0,0}
        }
    }
};

Piece::Piece(PieceType type)
: m_x(3), m_y(0), m_orientation(0), m_type(type)
{}

int Piece::getOrientation() const
{
    return m_orientation;
}

bool Piece::setOrientation(int orientation)
{
    if (orientation >= 0 && orientation <= 3)
    {
        m_orientation = orientation;
        return true;
    }
    return false;
}


int Piece::getX() const
{
    return m_x;
}

int Piece::getY() const
{
    return m_y;
}

void Piece::setX(int x)
{
    m_x = x;
}

void Piece::setY(int y)
{
    m_y = y;
}

PieceType Piece::getType() const
{
    return m_type;
}

void Piece::move(char ch)
{
    switch(ch)
    {
        case '2':
        case 's':
            m_y++;
            break;
        case '4':
        case 'a':
            m_x--;
            break;
        case '6':
        case 'd':
            m_x++;
            break;
    }
}

void Piece::rotate()
{
    int current = this->getOrientation();
    if (current == 3)
        setOrientation(0);
    else
        setOrientation(current+1);
}

bool Piece::isABlock(PieceType type, int x, int y, int orientation) const
{
    if (x < 0 || y < 0 || x > 4 || y > 4)
        return false;
    if (pieces[type][orientation][y][x] == 1)
        return true;
    return false;
}

bool Piece::okToMove(const Well* well, char ch) const
{
    // iterate through each coordinate of the containing block
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            // if there is a piece at the coordinate
            if (isABlock(m_type, i, j, m_orientation))
            {
                // switch based on desired movement
                switch(ch)
                {
                        // down
                    case 's':
                    {
                        if (!well->isEmpty(m_x + i, m_y + j + 1 ))
                            return false;
                        break;
                    }
                        // left
                    case 'a':
                    {
                        if (!well->isEmpty(m_x + i -1, m_y + j))
                            return false;
                        break;
                    }
                        // right
                    case 'd':
                    {
                        if (!well->isEmpty(m_x + i + 1, m_y + j))
                            return false;
                        break;
                    }
                        // no movement (to check beginning positions)
                    case '0':
                    {
                        if (!well->isEmpty(m_x + i, m_y + j))
                            return false;
                        break;
                    }
                }
            }
        }
    }
    // if all coordinates are ok to move, return true
    return true;
}

bool Piece::okToRotate(Well* well) const
{
    int t_orientation;
    
    // establish next orientation
    if (m_orientation == 3)
        t_orientation = 0;
    else
        t_orientation = m_orientation + 1;
        
    // iterate through each coordinate of the containing block
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            // if there is a piece at the coordinate
            if (isABlock(m_type, i, j, t_orientation))
            {
                // if the well is not empty at the coordinate
                if (!well->isEmpty(m_x + i, m_y + j))
                    return false;
            }
        }
    }
    return true;
}

PieceI::PieceI()
: Piece(PIECE_I)
{}


PieceL::PieceL()
: Piece(PIECE_L)
{}


PieceJ::PieceJ()
: Piece(PIECE_J)
{}


PieceT::PieceT()
: Piece(PIECE_T)
{}


PieceO::PieceO()
: Piece(PIECE_O)
{}

bool PieceO::okToRotate(Well* well) const
{
    return true;
}


PieceS::PieceS()
: Piece(PIECE_S)
{}


PieceZ::PieceZ()
: Piece(PIECE_Z)
{}

PieceVapor::PieceVapor()
: Piece(PIECE_VAPOR)
{}

bool PieceVapor::okToRotate(Well* well) const
{
    return true;
}

PieceFoam::PieceFoam()
: Piece(PIECE_FOAM)
{}

bool PieceFoam::okToRotate(Well* well) const
{
    return true;
}

PieceCrazy::PieceCrazy()
: Piece(PIECE_CRAZY)
{}

void PieceCrazy::move(char ch)
{
    switch(ch)
    {
        case '2':
        case 's':
        {
            int n = getY() + 1;
            setY(n);
            break;
        }
        case '4':
        case 'a':
        {
            int n = getX() + 1;
            setX(n);
            break;
        }
        case '6':
        case 'd':
        {
            int n = getX() - 1;
            setX(n);
            break;
        }
    }
}

bool PieceCrazy::okToMove(const Well* well, char ch) const
{
    // iterate through each coordinate of the containing block
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            // if there is a piece at the coordinate
            if (isABlock(getType(), i, j, getOrientation()))
            {
                // switch based on desired movement
                switch(ch)
                {
                        // down
                    case 's':
                    {
                        if (!well->isEmpty(getX() + i, getY() + j + 1 ))
                            return false;
                        break;
                    }
                        // left
                    case 'a':
                    {
                        if (!well->isEmpty(getX() + i + 1, getY() + j))
                            return false;
                        break;
                    }
                        // right
                    case 'd':
                    {
                        if (!well->isEmpty(getX() + i - 1, getY() + j))
                            return false;
                        break;
                    }
                        // no movement (to check beginning positions)
                    case '0':
                    {
                        if (!well->isEmpty(getX() + i, getY() + j))
                            return false;
                        break;
                    }
                }
            }
        }
    }
    // if all coordinates are ok to move, return true
    return true;
}
