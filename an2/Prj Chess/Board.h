#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
using namespace std;
class Board {
	private:
	 
    int board[8][8] = {
        {-1,-2,-3,-4,-5,-3,-2,-1},
        {-6,-6,-6,-6,-6,-6,-6,-6},
        { 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0},
        { 6, 6, 6, 6, 6, 6, 6, 6},
        { 1, 2, 3, 4, 5, 3, 2, 1}
    }; // Tableau pour représenter le plateau de jeu
    
    
	public:
    Board();
    ~Board();
    
    int roib=0,roin=0,tourb1=0,tourb2=0,tourn1=0,tourn2=0,nbB=0,nbN=0,x,y,joueur=1,zero;
    bool passant=false;
    bool fin=false;

    
    void Display();
    void Play(bool&);
    void InitBoard(bool&);
    
    bool MovePawn(int, int, int, int, bool);
    bool MoveRook(int, int, int, int, bool);
    bool MoveBishop(int, int, int, int, bool);
    bool MoveKnight(int, int, int, int, bool);
    bool MoveQueen(int, int, int, int, bool);
    bool MoveKing(int, int, int, int, bool);
    
    bool Danger(int, int, int, int);
    int* PoseKing(int);
    bool TestMove(int, int, int, int);
    bool Finpartie(int);
    vector<pair<int, int> > AllPossibleMoves(int , int );

    
    void Sauvegarder();
	void Continuer();
    
};
#endif
