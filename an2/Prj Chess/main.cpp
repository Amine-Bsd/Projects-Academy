#include <iostream>
#include "Board.cpp"
using namespace std;

int main() {
	Board board;
	int choix;
	bool valid=true;

	
	while(choix != 3 && board.fin==false){
		cout<<"Nouvelle Partie : (1) \t Continuer : (2) \t Quitter : (3)"<<endl;
		cin>>choix;
		switch(choix){
			case 1 :board.InitBoard(valid);
					board.Play(valid);
					break;
			case 2 :board.Continuer();
					board.Play(valid);
					break;
					 
			case 3 : return 0;
		}
		
	}
}
