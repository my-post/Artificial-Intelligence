//This is a non-interactive version of tic-tac-toe game using inbuilt functionality to generate random Moves
//Written for C++11 and above versions

#include<bits/stdc++.h> 
using namespace std; 

char computer = 'X', opponent = 'O'; 
char board[4][4];
//Function to intialize new board
void newBoard(){
	for(int i=0;i<=3;i++){
		for(int j=0;j<=3;j++){
			board[i][j]= '-';
			if(i==0 || j==0){
				board[i][j]='*';
			}
		}
	}
}
// Function to print board
void printBoard(){
	for(int i=1;i<4;i++){
		cout<<"          "<<board[i][1]<<" | "<<board[i][2]<<" | "<<board[i][3]<<"          "<<endl;
		if(i!=3){
			cout<<"        ----|---|----        "<<endl;
		}
	}
	cout<<endl;
}
//Function to check which moves are possible 
bool movesAvailable() 
{ 
	for (int i=1; i<=3; i++){
		for (int j=1; j<=3; j++){
			if (board[i][j]=='-'){
				return true; 
			}
		}
	}
	return false; 
}

void win(int score){
	if(score==20){                                     	//Computer tries to maximize its utility hence wins if utility 20
		cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
		cout<<"|        COMPUTER WON       |"<<endl;
		cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
	}
	else if(score==-20){
		cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;    //User tries to minimize its utility hence wins if utility -20
		cout<<"|         RANDOM WON        |"<<endl;
		cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
	}
}
//Tie happens if no moves available
void tie(){
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
	cout<<"|         IT'S A TIE        |"<<endl;
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
}

//Function to generate random move
int randomMove(int size){
	random_device rd; 									// obtain a random number from hardware
    mt19937 gen(rd()); 									// seed the generator
    uniform_int_distribution<> distr(0,size-1); 		// define the range
	return distr(gen);									//Selecting a random move from the uniform distribution of possible moves
}

//Function to evalute utility
int evaluate() 
{ 
	// Checking for Triplet in Rows 
	for (int i=1; i<=3 ; i++){
		if (board[i][1]==board[i][2] && board[i][2]==board[i][3]){
			if (board[i][1]==computer){                //Condition to check if triplet made by computer and hence computer wins
				return +20; 
			}
			else if (board[i][1]==opponent){            //Condition to check if triplet made by user and hence user wins
				return -20; 
			}
		} 
	} 

	// Checking for Triplet in Columns 
	for (int i=1; i<=3; i++){ 
		if (board[1][i]==board[2][i] && board[2][i]==board[3][i]){ 
			if (board[1][i]==computer) {              	//Condition to check if triplet made by computer and hence computer wins
				return +20; 
			}
			else if (board[1][i]==opponent){          	//Condition to check if triplet made by user and hence user wins
				return -20; 
			}
		} 
	} 

	// Checking for Triplet in Diagonal-1 
	if (board[1][1]==board[2][2] && board[2][2]==board[3][3]) { 
		if (board[1][1]==computer){                    			//Condition to check if triplet made by computer and hence computer wins
			return +20; 
		}
		else if (board[1][1]==opponent){             	 		//Condition to check if triplet made by user and hence user wins
			return -20; 
		}
	} 

	// Checking for Triplet in Diagonal-2 
	if (board[1][3]==board[2][2] && board[2][2]==board[3][1]){ //Condition to check if triplet made by computer and hence computer wins
		if (board[1][3]==computer){
			return +20; 
		}
		else if (board[1][3]==opponent){    					//Condition to check if triplet made by user and hence user wins
			return -20; 
		}
	} 
	return 0; 
} 
//Function Creating game tree for the existing board
int minimax(int depth, bool Max) 
{ 
	int score = evaluate(); 
	if (score == 20 || score == -20){ 
		return score;
	}  

	if (!movesAvailable()){  // if tie return utility of board to be zero
		return 0; 
	}

	// Move by Maximiser
	if (Max){ 
		int best = -2000; 

		for (int i=1; i<=3; i++){ 
			for (int j=1; j<=3; j++){ 
				if (board[i][j]=='-'){ 
					board[i][j] = computer; 
					best = max( best, minimax(depth+1, !Max)); 
					board[i][j] = '-'; 
				} 
			} 
		} 
		return best; 
	} 

	// Move by Minimiser
	else{ 
		int best = 2000; 
 
		for (int i=1; i<=3; i++) { 
			for (int j=1; j<=3; j++) { 
				if (board[i][j]=='-') { 
					board[i][j] = opponent; 
					best = min(best, minimax(depth+1, !Max)); 
					board[i][j] = '-'; 
				} 
			} 
		} 
		return best; 
	} 
} 
// Strucure to hold row and column for next move of computer
struct Move{
	int row, column; 
};

// Function will return best possible move by the computer 
Move compMove(){ 
	Move bestMove; 
	bestMove.row = -1; 
	bestMove.column = -1; 
	int bestVal = -2000;
	
	//Evaluating minimax value for each possible move and returning the best move
	for (int i=1; i<=3; i++){ 
		for (int j=1; j<=3; j++) { 
			if (board[i][j]=='-') { 
				board[i][j] = computer;  
				int moveVal = minimax(0, false); 
				board[i][j] = '-'; 

				if (moveVal > bestVal) { 
					bestMove.row = i; 
					bestMove.column = j; 
					bestVal = moveVal; 
				} 
			} 
		} 
	} 
	return bestMove; 
} 

int main(){ 
	newBoard();											//Creating a new board to play game
	Move newMove,bestMove;
	vector < pair<int,int> > v;  						//Vector v holds pair of possible moves as row, column
	for(int i=1;i<4;i++){
		for(int j=1;j<4;j++){
			v.push_back(make_pair(i,j));
		}
	}
	int n=5;       		// n represents the maximum no. of times the moves by each player can be played as (ceil)(9/2)=5 
	cout<<endl;
	cout<<"About the game:"<<endl;
	cout<<"1. A board(matrix) will be shown and random move will be played by random player."<<endl;
	cout<<"2. After every move of random player and computer, updated board will be shown."<<endl;
	cout<<"3. Game will continue until a winning situation or a tie is reached."<<endl<<endl;

	cout<<"         TIC TAC TOE         "<<endl<<endl;

	cout<<" RANDOM PLAYER <O> - COMPUTER <X> "<<endl<<endl;
	while(n--){
		printBoard();
		Move newMove, bestMove;
		vector<pair<int,int>> v;
		for(int y=1;y<=3;y++)
			for(int z=1;z<=3;z++)
		{
			if(board[y][z]=='-')
			{
				pair<int,int> p;
				p.first=y;
				p.second=z;
				v.push_back(p);			
			}
		}
		int temp = randomMove(v.size());
		newMove.row=v[temp].first;
		newMove.column=v[temp].second;

		v.clear();
        // Condition to check if move is valid
		if(board[newMove.row][newMove.column] == '-' && newMove.row<4 && newMove.column<4 && newMove.row>0 && newMove.column>0){
			board[newMove.row][newMove.column] = 'O';
		}
		else{
			cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
			cout<<"|  INVALID MOVE, TRY AGAIN! |"<<endl;
			cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
			n++;
			continue;
		}
		cout<<"~~~~~!! RANDOM PLAYER !!~~~~~"<<endl<<endl;	
		
		printBoard();
		int score = evaluate();
		if(score==20 || score==-20){         		// Condition to check if any of the player won
			printBoard();
			win(score);
			break;
		}
		if (!movesAvailable()){           			// Condition to check if there is a tie
			printBoard();
			tie();
			break;
		}

		bestMove = compMove();
		board[bestMove.row][bestMove.column] = 'X';

		cout<<"~~~~~~~~!! COMPUTER !!~~~~~~~"<<endl<<endl;
		score = evaluate();
		if(score==20 || score==-20){  				// Condition to check if any of the player won
			printBoard();
			win(score);
			break;
		}
		if(!movesAvailable()){       				// Condition to check if there is a tie
			printBoard();
			tie();
			break;
		}
	}
	
	return 0; 
}