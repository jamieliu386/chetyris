#ifndef PIECE_INCLUDED
#define PIECE_INCLUDED

enum PieceType {
    PIECE_I = 0, PIECE_L = 1, PIECE_J = 2, PIECE_T = 3, PIECE_O = 4, PIECE_S = 5, PIECE_Z = 6,
    PIECE_VAPOR = 7, PIECE_FOAM = 8, PIECE_CRAZY = 9, NUM_PIECE_TYPES = 10
};

class Well;

PieceType chooseRandomPieceType();


class Piece {
public:
    Piece(PieceType type);
    
    // getters and setters for Piece orientation
    int getOrientation() const;
    bool setOrientation(int orientation);

    // getters and setters for x and y coordinate of
    // the top left corner of the piece's bounding box
    int getX() const;
    int getY() const;
    void setX(int x);
    void setY(int y);
    
    // returns the piece's type
    PieceType getType() const;
    
    // This function handles the a, s, and d instructions.
    // It accepts a character (a, s, or d) and changes the
    // piece's x and y coordinates based on the character
    // inputted. (i.e. if the character is a, m_x is decremented,
    // if the character is d, x is incremented, if the character
    // is s, y is incremented
    virtual void move(char ch);
    
    // This function determines the next orientation that
    // the piece should change to, and calls setOrientation
    // to change it.
    void rotate();
    
    // This function accepts a PieceType, an x and y coordinate
    // representing the location in question of the piece's bounding box,
    // and the piece's orientation. If x < 0 or x > 4 or y < 0 or y > 4,
    // the function returns false. Otherwise, it returns true if there is
    // a block at the location specified. If there is not a block at the
    // location, it returns false.
    bool isABlock(PieceType type, int x, int y, int orientation) const;
    
    // This function accepts a pointer to a well and a character representing
    // the desired movement (a, s, or d). If the piece can move in the
    // specified direction without colliding with another piece or a wall,
    // the function returns true. Otherwise, it returns false.
    virtual bool okToMove(const Well* well, char ch) const;
    
    // This function accepts a pointer to a well and returns true if the
    // piece can rotate once without colliding with another piece or
    // a wall. Otherwise, it returns false.
    virtual bool okToRotate(Well* well) const;
    
private:
    int         m_x;
    int         m_y;
    int         m_orientation;
    PieceType   m_type;
};



class PieceI : public Piece {
public:
    PieceI();
};

class PieceL : public Piece {
public:
    PieceL();
};

class PieceJ : public Piece {
public:
    PieceJ();
};

class PieceT : public Piece {
public:
    PieceT();
};

class PieceO : public Piece {
public:
    PieceO();
    virtual bool okToRotate(Well* well) const;
};

class PieceS : public Piece {
public:
    PieceS();
};

class PieceZ : public Piece {
public:
    PieceZ();
};

class PieceVapor : public Piece {
public:
    PieceVapor();
    virtual bool okToRotate(Well* well) const;
};

class PieceFoam : public Piece {
public:
    PieceFoam();
    virtual bool okToRotate(Well* well) const;
};

class PieceCrazy : public Piece {
public:
    PieceCrazy();
    virtual void move(char ch);
    virtual bool okToMove(const Well* well, char ch) const;
};

#endif // PIECE_INCLUDED
