#include "Board.h"
#include <cmath>
#include <conio.h>
#include <fstream>
#include <vector>
using namespace std;
Board::Board(){
}
Board::~Board(){
}

void Board::Display() { 
	cout << "K : ROI" << endl;
    cout << "Q : DAME" << endl;
    cout << "B : FOU" << endl;
    cout << "R : TOUR" << endl;
    cout << "N : CAVALIER" << endl;
    cout << "P : PION" << endl;
    cout << "************TABLE BOARD************" <<endl;
    // Affichage des numéros de colonne
    cout << "  ";
    for (int i = 0; i < 8; i++) {
        cout << i << " ";
    }
    cout << endl;

    // Affichage du plateau de jeu avec les pièces dans leurs positions actuelles
    for (int i = 0; i < 8; i++) {
        cout << i << "|";
        for (int j = 0; j < 8; j++) {
            switch (board[i][j]) {
                case -1:
                    cout << "R ";
                    break;
                case -2:
                    cout << "N ";
                    break;
                case -3:
                    cout << "B ";
                    break;
                case -4:
                    cout << "Q ";
                    break;
                case -5:
                    cout << "K ";
                    break;
                case -6:
                    cout << "P ";
                    break;
                case 1:
                    cout << "r ";
                    break;
                case 2:
                    cout << "n ";
                    break;
                case 3:
                    cout << "b ";
                    break;
                case 4:
                    cout << "q ";
                    break;
                case 5:
                    cout << "k ";
                    break;
                case 6:
                    cout << "p ";
                    break;
                case 0:
                    cout << ". ";
                    break;
            }
        }
        cout << endl;
    }
    cout << endl;
}



int* Board::PoseKing(int x){
    int *Pose = new int[2]; // déclarer le tableau de position en dehors de la boucle et le rendre statique
	if(x<0){
		for (int i = 0; i < 8; i++) {
        	for (int j = 0; j < 8; j++) {
        		if(board[i][j] == -5){
        			Pose[0] = i; // stocke la position du roi noir
                    Pose[1] = j;
					return Pose;
				}
			}
		}
	}else if(x>0){
		for (int i = 0; i < 8; i++) {
        	for (int j = 0; j < 8; j++) {
        		if(board[i][j] == 5){
        			Pose[0] = i; // stocke la position du roi blanc
                    Pose[1] = j;
					return Pose;
				}
			}
		}
	}
    return NULL;
}



bool Board::TestMove(int x1, int y1, int x2, int y2){
	int x3,y3;
	int Pos1=board[x1][y1];
	int Pos2=board[x2][y2];
    board[x2][y2] = board[x1][y1];
   	board[x1][y1] = 0;// Réinitialise la position initiale à 0
   	
   	if(board[x2][y2] == 5 || board[x2][y2] == -5){
   		x3=x2;
   		y3=y2;
	}else{	
		int* Pos = PoseKing(board[x2][y2]); // stocke le pointeur retourné par la fonction
    	x3 = Pos[0]; // accède au premier entier du tableau
    	y3 = Pos[1]; // accède au deuxième entier du tableau
	}
    if(Danger(x3,y3,x3,y3)){
   		board[x1][y1]= Pos1;
    	board[x2][y2]= Pos2;
    	cout<<"Il ya un danger au roi";
    	getch();
    	return false;
    }
    return true;
}




bool Board::MovePawn(int x1, int y1, int x2, int y2,bool trans) {
    
    // Déplace le pion vers la nouvelle position
    if ((board[x1][y1] == 6 && x2 == x1 - 1 && y2 == y1 && board[x2][y2]==0) || // Pour les pions blancs, avance d'une case vers le haut
        (board[x1][y1] == -6 && x2 == x1 + 1 && y2 == y1 && board[x2][y2]==0)  || // Pour les pions noirs, avance d'une case vers le bas
        (board[x1][y1] == 6 && x1 == 6 && x2 == x1 - 2 && y2 == y1 && board[x2][y2]==0) || // Pour les pions blancs, avance de deux cases vers le haut depuis la ligne de départ
        (board[x1][y1] == -6 && x1 == 1 && x2 == x1 + 2 && y2 == y1 && board[x2][y2]==0) || // Pour les pions noirs, avance de deux cases vers le bas depuis la ligne de départ
        (board[x1][y1] == 6 && (x2 == x1 - 1 && (y2 == y1 - 1 || y2 == y1 + 1) && board[x2][y2] < 0) || (board[x2][y2] == 0 && x2==x-1 && y == y2 && passant==true) ) || // Pour les pions blancs, mange une pièce noire en diagonale
        (board[x1][y1] == -6 && (x2 == x1 + 1 && (y2 == y1 - 1 || y2 == y1 + 1) && board[x2][y2] > 0) || (board[x2][y2] == 0 && x2==x+1 && y == y2 && passant==true) )) { // Pour les pions noirs, mange une pièce blanche en diagonale
        
        if(board[x2][y2] == 0 && ( board[x1][y1] == 6 && x2==x-1 || board[x1][y1] == -6 && x2==x+1 ) && y == y2 && passant==true){
        	board[x][y]=0;
		}
        
		if(x2 == x1 - 2 || x2 == x1 + 2){
        	passant=true;
        	x=x2;y=y2;
		}else passant=false;
		
		if(trans==true){
        	
        	bool test=TestMove(x1,y1,x2,y2);
        	if(test==false) return false;
        	
		if(x2 == 0 && board[x2][y2] > 0 || x2 == 7 && board[x2][y2] < 0){
	     	cout<<"	changement du Pion "<<endl;
			cout << "1 : DAME" << endl;
		   	cout << "2 : FOU" << endl;
			cout << "3 : TOUR" << endl;
			cout << "4 : CAVALIER" << endl;
			int choix;
			cin>>choix;
		  	switch(choix){
		   		case 1:	if(board[x2][y2] > 0){
		    				board[x2][y2] = 4;
							break;
						}else board[x2][y2] = -4;
							break;
								
		    	case 2: if(board[x2][y2] > 0){
		    				board[x2][y2] = 3;
							break;
						}else board[x2][y2] = -3;
							break;
		   		case 3: if(board[x2][y2] > 0){
		   					board[x2][y2] = 1;
							break;
						}else board[x2][y2] = -1;
							break;
	   			case 4:	if(board[x2][y2] > 0){
	   						board[x2][y2] = 2;
							break;
						}else board[x2][y2] = -2;
							break;
					}
		}
			}
			if(joueur==1)nbB=0;
			else nbN=0;
	        return true;
    } else {
     //   cout << "Mouvement invalide pour un pion." << endl;
        
        return false;
    }
}


bool Board::MoveRook(int x1, int y1, int x2, int y2,bool trans) {
    
    // Vérifie que la tour se déplace horizontalement ou verticalement
    if (x1 != x2 && y1 != y2) {
      //  cout << "La tour doit se déplacer horizontalement ou verticalement." << endl;
        
        return false;
    }
    
    // Vérifie qu'il n'y a pas de pièces entre la position initiale et la position finale
    if (x1 == x2) {
        int minY = min(y1, y2);
        int maxY = max(y1, y2);
        for (int i = minY + 1; i < maxY; i++) {
            if (board[x1][i] != 0) {
         //       cout << "Il y a une pièce sur le chemin." << endl;
                
                return false;
            }
        }
    } else {
        int minX = min(x1, x2);
        int maxX = max(x1, x2);
        for (int i = minX + 1; i < maxX; i++) {
            if (board[i][y1] != 0) {
             //   cout << "Il y a une pièce sur le chemin." << endl;
               
                return false;
            }
        }
    }
    
    // Vérifie si la nouvelle position contient une pièce de couleur opposée, et la mange si c'est le cas
    if (board[x2][y2] == 0 || board[x2][y2] != 0 && board[x2][y2] / board[x1][y1] < 0) {
        if(trans==true){
        	zero=board[x2][y2];
        	bool test=TestMove(x1,y1,x2,y2);
        	if(test==false) return false;
        	if(board[x2][y2]>0 && y2== 7) tourb1=1;
					else if(board[x2][y2]>0 && y2== 0)tourb2=1;
					else if(board[x2][y2]<0 && y2== 7)tourn1=1;
					else if(board[x2][y2]<0 && y2== 0)tourn2=1;
					
				passant=false;
		}
		if(zero==0){
			if(joueur==1) nbB++;
			else nbN++;
		}else {
			if(joueur==1) nbB=0;
			else nbN=0;
		}
		return true;
		
    } else { // Sinon, la nouvelle position contient une pièce de même couleur ou est invalide
      //  cout << "Mouvement invalide pour une tour." << endl;
        
        return false;
    }
}


bool Board::MoveBishop(int x1, int y1, int x2, int y2,bool trans) {

    // Vérifie que le déplacement est diagonal
    if (abs(x2 - x1) != abs(y2 - y1)) {
      //  cout << "Le déplacement n'est pas diagonal." << endl;
        
        return false;
    }

    // Vérifie que le fou ne saute pas par-dessus d'autres pièces
	int xdir = abs(x2 - x1) / (x2 - x1); //-1 vers le haut // 1 vers le bas
	int ydir = abs(y2 - y1) / (y2 - y1); //1 vers le droit // -1 vers le gauche
    int x = x1 + xdir;
    int y = y1 + ydir;
    while (x != x2 && y != y2) {
        if (board[x][y] != 0) {
       //     cout << "Le fou ne peut pas sauter par-dessus d'autres pièces." << endl;
            
            return false;
        }
        x += xdir;
        y += ydir;
    }

    // Déplace le fou vers la nouvelle position si elle est libre ou contient une pièce adverse
    if (board[x2][y2] == 0 || (board[x2][y2] < 0 && board[x1][y1] > 0) || (board[x2][y2] > 0 && board[x1][y1] < 0)) {
        if(trans==true){
        	zero=board[x2][y2];
        	bool test=TestMove(x1,y1,x2,y2);
        	if(test==false) return false;
        	passant=false;
		}
		if(zero==0){
			if(joueur==1) nbB++;
			else nbN++;
		}else {
			if(joueur==1) nbB=0;
			else nbN=0;
		}
        return true;
    } else {
      //  cout << "Mouvement invalide pour un fou." << endl;
        
        return false;
    }
}


bool Board::MoveKnight(int x1, int y1, int x2, int y2,bool trans) {
	
    // Vérifie que le déplacement est valide pour un cavalier (en L)
    int x = abs(x1 - x2);
    int y = abs(y1 - y2);
    if (!((x == 1 && y == 2) || (x == 2 && y == 1))){
    //	cout << "Mouvement invalide pour un cavalier." << endl;
    	
        return false;
	}
	
	// Vérifie s'il y a une pièce ennemie sur la case d'arrivée, si oui la prend

        if( board[x2][y2] == 0 || (board[x1][y1] > 0 && board[x2][y2] < 0) || (board[x1][y1] < 0 && board[x2][y2] > 0)) {
            if(trans==true){
            	zero=board[x2][y2];
        		bool test=TestMove(x1,y1,x2,y2);
        		if(test==false) return false;
        		passant=false;
			}
			if(zero==0){
				if(joueur==1) nbB++;
				else nbN++;
			}else {
				if(joueur==1) nbB=0;
				else nbN=0;
			}
			return true;
        } else {
      //      cout << "Mouvement invalide, on ne peut pas prendre sa propre pièce." << endl;
            
            return false;
    	}
}



bool Board::MoveQueen(int x1, int y1, int x2, int y2,bool trans) {
	
    // Vérifie que la tour se déplace horizontalement ou verticalement
    if (x1 != x2 && y1 != y2 && abs(x2 - x1) != abs(y2 - y1)) {
       // cout << "La Queen doit se déplacer horizontalement ou verticalement Ou en diagonal ." << endl;
        
        return false;
    } 
    
    int dx = (x2 > x1) ? 1 : ((x2 < x1) ? -1 : 0);
    int dy = (y2 > y1) ? 1 : ((y2 < y1) ? -1 : 0);
    int x = x1 + dx;
    int y = y1 + dy;
    while (x != x2 || y != y2) {
        if (board[x][y] != 0) {
            return false;
        }
        x += dx;
        y += dy;
	}
	
	if (board[x2][y2] == 0 || (board[x2][y2] < 0 && board[x1][y1] > 0) || (board[x2][y2] > 0 && board[x1][y1] < 0)) {
        if(trans==true){
        	zero=board[x2][y2];
        	bool test=TestMove(x1,y1,x2,y2);
        	if(test==false) return false;
        	passant=false;
		}
		if(zero==0){
			if(joueur==1) nbB++;
			else nbN++;
		}else {
			if(joueur==1) nbB=0;
			else nbN=0;
		}
        return true;
    } else {
      //  cout << "Mouvement invalide pour une Queen." << endl;
        
        return false;
    }

}

bool Board::Danger(int x1, int y1, int x2, int y2){ //Return false => vous pouvez faire le mouvement par le roi
	int choix;
	for(int i=0; i<8; i++){
		for(int j=0; j<8; j++){
			if(board[x1][y1]>0 && board[i][j]<0) {
				choix=board[i][j];
				
				if(choix==(-1)){
					if(MoveRook(i,j,x2,y2,false)){
						return true;
					}
				}else if(choix==(-2)){
					if(MoveKnight(i,j,x2,y2,false)){
						return true;
					}
					
				}else if(choix==(-3)){
					if(MoveBishop(i,j,x2,y2,false)){
						return true;
					}
					
				}else if(choix==(-4)){
					if(MoveQueen(i,j,x2,y2,false)){
						return true;
					}
					
				}else if(choix==(-5)){
					if(MoveKing(i,j,x2,y2,false)){
						return true;
					}
					
				}else if(choix==(-6)){
					if(MovePawn(i,j,x2,y2,false)){
						return true;
					}
				}
				
			}else if(board[x1][y1]<0 && board[i][j]>0){
				choix=board[i][j];
				
				if(choix==(1)){
					if(MoveRook(i,j,x2,y2,false)){
						return true;
					}
				}else if(choix==(2)){
					if(MoveKnight(i,j,x2,y2,false)){
						return true;
					}
					
				}else if(choix==(3)){
					if(MoveBishop(i,j,x2,y2,false)){
						return true;
					}
					
				}else if(choix==(4)){
					if(MoveQueen(i,j,x2,y2,false)){
						return true;
					}
					
				}else if(choix==(5)){
					if(MoveKing(i,j,x2,y2,false)){
						return true;
					}
					
				}else if(choix==(6)){
					if(MovePawn(i,j,x2,y2,false)){
						return true;
					}
				}
			}
		}
	}
	return false;
}


vector<pair<int, int> > Board::AllPossibleMoves(int x, int y) {
    vector<pair<int, int> > moves;
    int choix = board[x][y];

    if (abs(board[x][y]) == 5) { // Si la pièce est un roi
        for (int i = x - 1; i <= x + 1; i++) {
            for (int j = y - 1; j <= y + 1; j++) {
                if (i == x && j == y) continue;
                if (i < 0 || i >= 8 || j < 0 || j >= 8) continue;
                if (board[i][j] == 0 || (board[i][j] > 0 && board[x][y] < 0) || (board[i][j] < 0 && board[x][y] > 0)) {
                    // le roi peut se déplacer sur la case (i, j)
                    moves.push_back(make_pair(i, j));
                }
            }
        }
    } else { // Si la pièce n'est pas un roi
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                switch (abs(choix)) {
                    case 1:
                        if (MoveRook(x, y, i, j, false)) moves.push_back(make_pair(i, j));
                        break;
                    case 2:
                        if (MoveKnight(x, y, i, j, false)) moves.push_back(make_pair(i, j));
                        break;
                    case 3:
                        if (MoveBishop(x, y, i, j, false)) moves.push_back(make_pair(i, j));
                        break;
                    case 4:
                        if (MoveQueen(x, y, i, j, false)) moves.push_back(make_pair(i, j));
                        break;
                    case 6:
                        if (MovePawn(x, y, i, j, false)) moves.push_back(make_pair(i, j));
                        break;
                }
            }
        }
    }

    return moves;
}


bool Board::Finpartie(int joueur) {
	
    int k = (joueur == 1) ? -5 : 5; // Récupère la valeur de la pièce roi en fonction du joueur actuel
    int *Pose = PoseKing(k); // Récupère la position du roi actuel
    vector<pair<int, int> > kingMoves = AllPossibleMoves(Pose[0], Pose[1]); // Récupère tous les mouvements possibles pour le roi
    bool canMove = false; // Variable booléenne pour vérifier s'il est possible de déplacer le roi

		// Vérifie si le roi est en échec et s'il n'a aucun mouvement possible
	if (Danger(Pose[0], Pose[1], Pose[0], Pose[1])) {
		for (int i = 0; i < kingMoves.size(); i++) {
			int moveX = kingMoves[i].first;
			int moveY = kingMoves[i].second;
			if (!Danger(Pose[0], Pose[1], moveX, moveY)) {
				// Il y a au moins un mouvement possible pour le roi
				canMove = true;
				break;
				}
		}
		// Si le roi ne peut pas se déplacer et est en échec, recherche un mouvement de sauvegarde
		if (!canMove) {
			bool checkmate = true; // true si le roi est en échec et mat
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					if (board[i][j] != 0 && (board[i][j] > 0 && joueur == 2 || board[i][j] < 0 && joueur == 1)) {
							vector<pair<int, int> > moves = AllPossibleMoves(i, j);
							for (int k = 0; k < moves.size(); k++) {
								int moveX = moves[k].first;
								int moveY = moves[k].second;
								int temp = board[moveX][moveY];
								board[moveX][moveY] = board[i][j];
								int *newPose = PoseKing(k);
								if (!(Danger(newPose[0], newPose[1], newPose[0], newPose[1]))) {
									// Il y a au moins un mouvement possible pour une autre pièce pour sauver le roi
									canMove = true;
									checkmate = false;
								}
								board[i][j] = board[moveX][moveY];
								board[moveX][moveY] = temp;
								delete[] newPose;
								if (canMove) {
									break;
								}
							}
						if (canMove) {
							break;
						}
					}
				}
				if (canMove) {
				break;
				}
			}
			// Si le roi ne peut pas se déplacer et est en échec et qu'aucune pièce ne peut le sauver, la partie est terminée
		if (checkmate) {
			cout << "le roi ne peut pas se deplacer et il n'y a pas de mouvement de sauvegarde possible !" << endl;
			cout << "le roi en echec et mat !" << endl;
			cout<< "PARTIE TERMINEE ! Le joueur "<<joueur<<" gagne !" << endl;
			getch();
			return true;
			}
		}
	}
	return false;
}

bool Board::MoveKing(int x1, int y1, int x2, int y2, bool trans ) {
	
    
    if((( abs(x2-x1) == 1 && abs(y2-y1) == 1 || abs(x2-x1) == 0 && abs(y2-y1) == 1 || abs(x2-x1) == 1 && abs(y2-y1) == 0)
		&& (board[x2][y2] == 0 || (board[x2][y2] < 0 && board[x1][y1] > 0) || (board[x2][y2] > 0 && board[x1][y1] < 0)) ))
		{
			if(trans==true){
				zero=board[x2][y2];
	        	bool test=TestMove(x1,y1,x2,y2);
	        	if(test==false) return false;
	        	if(board[x2][y2]>0) roib=1;
						else roin=1;
					passant=false;
			}
			
			if(zero==0){
				if(joueur==1) nbB++;
				else nbN++;
			}else {
				if(joueur==1) nbB=0;
				else nbN=0;
			}
			
	    	return true;
	    	
   		}else if(roib == 0 && x1 == 7 || roin == 0 && x1 == 0){
        int y = (y2 == 6) ? 1 : ((y2 == 2) ? -1 : 0); // détermine la valeur de y en fonction de y2
        if ((x1 == 7 || x1 == 0) && (y != 0) && (x2 == x1) && (abs(y2 - y1) == 2))
        {
            int tour_col = (y == 1) ? 7 : 0; // colonne de la tour en fonction de la direction du roque
            int y3 = (y == 1) ? 1 : -1; // direction de déplacement du roi
			if (((board[x1][y1] == 5 && board[x1][tour_col] == 1 && (y == 1 && tourb1 == 0 || y == -1 && tourb2 == 0 )) || 
                (board[x1][y1] == -5 && board[x1][tour_col] == -1 && (y == 1 && tourn1 == 0 || y == -1 && tourn2 == 0))))
            {
                for (int i = y1 + y3; i != tour_col; i += y3) // vérifie si les cases entre le roi et la tour sont libres
                {
                    if (board[x1][i] != 0)
                    {
                        return false;
                    }
                }
                if (trans == true) {
                    int y4 = y1 + 2 * y3;
                    int r=5,t=1;
                    
                    if(x1==0){
                    	r=r*(-1);
						t=t*(-1);
					}
                    
                    board[x1][y1] = 0; // déplace le roi et la tour 
                    board[x1][y1 + y3] = t;
                    board[x1][tour_col] = 0;
                    board[x1][y4] = r;
					
                    if (Danger(x1, y4, x1, y4)) {
                        board[x1][y1] = r;
                        board[x1][tour_col] = t;
                        board[x1][y1 + y3] = 0;
                        board[x1][y4] = 0;
                        cout << "Il y a un danger pour le roi";
						getch();
    					return false;
   					}
   					
					if(r>0)roib=1;
					else roin=1;
					passant=false;
				}
				if(zero==0){
					if(joueur==1) nbB++;
					else nbN++;
				}else {
					if(joueur==1) nbB=0;
					else nbN=0;
				}
				return true;
			}
		}
	}else
		return false;
}


void Board::Play(bool &valid) {
	int x1, y1, x2, y2, choix=0;

		//joueur1ou2//
		if(nbB==50 && nbN==50){
			cout<<"!!!! PARTIE NULL !!!!"<<endl;
			fin=true;
		}else{
			do{
			system("cls");
			Display();
			cout <<"nbB : "<<nbB<<" || "<<"nbN : "<<nbN<<endl;
			cout << "C'est au joueur " << joueur << " de jouer" << endl;
		   	cout << "Entrez les valeurs de x1, y1 : ";
	        cin >> x1 >> y1;
			}while(x1 < 0 || x1 >= 8 || y1 < 0 || y1 >= 8 || joueur==1 && board[x1][y1] <= 0 || joueur==2 && board[x1][y1] >= 0 );
			
				system("cls");
				Display();
				choix=abs(board[x1][y1]);
		        switch (choix) {
		            case 5:
		                do{	
							cout << "Vous avez choisi le ROI" << endl;
			                cout << "Entrez les valeurs de x2 et y2 : ";
		    				cin >> x2 >> y2;
		    				}while(x2 < 0 || x2 >= 8 || y2 < 0 || y2 >= 8 );
		    			valid=MoveKing(x1,y1,x2,y2,true);
		                break;
		            case 4:
		                do{	
							cout << "Vous avez choisi la DAME" << endl;
			                cout << "Entrez les valeurs de x2 et y2 : ";
		    				cin >> x2 >> y2;
		    				}while(x2 < 0 || x2 >= 8 || y2 < 0 || y2 >= 8 );
	    				valid=MoveQueen(x1,y1,x2,y2,true);
		                break;
		            case 3:
		                do{	
							cout << "Vous avez choisi le FOU" << endl;
			                cout << "Entrez les valeurs de x2 et y2 : ";
		    				cin >> x2 >> y2;
		    				}while(x2 < 0 || x2 >= 8 || y2 < 0 || y2 >= 8 );
	    				valid=MoveBishop(x1,y1,x2,y2,true);
		                break;
		            case 1:
		                do{	
							cout << "Vous avez choisi le TOUR" << endl;
			                cout << "Entrez les valeurs de x2 et y2 : ";
		    				cin >> x2 >> y2;
		    				}while(x2 < 0 || x2 >= 8 || y2 < 0 || y2 >= 8 );
	    				valid=MoveRook(x1,y1,x2,y2,true);
		                break;
		            case 2:
		                do{	
							cout << "Vous avez choisi le CAVALIER" << endl;
			                cout << "Entrez les valeurs de x2 et y2 : ";
		    				cin >> x2 >> y2;
		    				}while(x2 < 0 || x2 >= 8 || y2 < 0 || y2 >= 8 );
	    				valid=MoveKnight(x1,y1,x2,y2,true);
		                break;
		            case 6:
		                do{	
							cout << "Vous avez choisi le PION" << endl;
			                cout << "Entrez les valeurs de x2 et y2 : ";
		    				cin >> x2 >> y2;
		    				}while(x2 < 0 || x2 >= 8 || y2 < 0 || y2 >= 8 );
		                valid=MovePawn(x1,y1,x2,y2,true);
		                break;
		        }
		    if(valid==true){
		    	fin=Finpartie(joueur);
				if(joueur==1) joueur=2;
			 	else joueur=1;
			}
			system("cls");
			Display();
			Sauvegarder();
		}
}



void Board::Sauvegarder(){
    ofstream fichier("Board.txt", ios::out | ios::trunc);  //déclaration du flux et ouverture du fichier
    if(fichier)  // vérifier si l'ouverture a réussi
    {
        fichier<<joueur<<" "<<passant<<" "<<roib<<" "<<roin<<" "<<tourb1<<" "<<tourb2<<" "<<tourn1<<" "<<tourn2<<" "<<fin<<" "<<nbB<<" "<<nbN<<endl;
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                fichier<<board[i][j]<<" ";
            }
            fichier<<endl;
        }
    }
    else{
        cout << "Erreur: Impossible d'ouvrir le fichier pour sauvegarder." << endl;
    }
}


void Board::Continuer(){
    ifstream fichier("Board.txt", ios::in);  //déclaration du flux et ouverture du fichier
    if(fichier)  // vérifier si l'ouverture a réussi
    {
        fichier>>joueur>>passant>>roib>>roin>>tourb1>>tourb2>>tourn1>>tourn2>>fin>>nbB>>nbN;
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                fichier>>board[i][j];
            }
        }
    }
    else{
        cout << "Erreur: Impossible d'ouvrir le fichier pour continuer une partie." << endl;
    }
}



void Board::InitBoard(bool& valid){
	joueur=1;
	valid=true;
	nbB=0,nbN=0;
	int b[8][8] = {
        {-1,-2,-3,-4,-5,-3,-2,-1},
        {-6,-6,-6,-6,-6,-6,-6,-6},
        { 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0},
        { 6, 6, 6, 6, 6, 6, 6, 6},
        { 1, 2, 3, 4, 5, 3, 2, 1}
    };
    memcpy(board, b, sizeof(board));
}







