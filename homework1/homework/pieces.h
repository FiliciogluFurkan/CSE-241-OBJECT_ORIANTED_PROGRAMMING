#ifndef PIECES_H
#define PIECES_H

class pieces {
private:
    char pieceType; //to determine type of board

public:
    int x, y; // coordinates of the pieces
    pieces(char type = '.') : pieceType(type), x(0), y(0) {}

    char getPieceType() const;//return type of board(is it p,P or . etc)

    void setPieceType(char type); //sets the type of pieces
};

#endif // PIECES_H

