#include<bits/stdc++.h>
using namespace std;

#define COMPUTER 1
#define HUMAN 2

#define SIDE 3

#define CM 'O'
#define HM 'X'

void showBoard(char board[][SIDE]){
    printf("\n\n");
    for(int i=0;i<SIDE;i++){
        printf("\t\t\t");
        for(int j=0;j<SIDE;j++){
            printf(" %c ",board[i][j]);
            if(j!=SIDE-1)printf("|");
        }
        if(i!=SIDE-1)printf("\n\t\t\t---+---+---\n");
    }
    printf("\n\n");
    //printf("\n\n\t\t\t %c | %c | %c\n\t\t\t---+---+---\n\t\t\t %c | %c | %c\n\t\t\t---+---+---\n\t\t\t %c | %c | %c\n\n", board[0][0], board[0][1],board[0][2], board[1][0], board[1][1], board[1][2], board[2][0], board[2][1], board[2][2]);
}

void showInstructions(){
    printf("\t\t\t TIC-TAC-TOE\n\nChoose a cell numbered from 1 to 9 as below and play\n\n");
    printf("\t\t\t 1 | 2 | 3\n\t\t\t---+---+---\n\t\t\t 4 | 5 | 6\n\t\t\t---+---+---\n\t\t\t 7 | 8 | 9\n\n");
    printf("-\t-\t-\t-\t-\t-\t-\t-\t-\t-\t-\n\n");
}

void initialise(char board[][SIDE], vector <int> &moves){
    srand(time(NULL));

    for(int i=0;i<SIDE;i++){
        for(int j=0;j<SIDE;j++){
            board[i][j]=' ';
        }
    }

    for(int i=0;i<SIDE*SIDE;i++)
        moves[i]=i;

    random_shuffle(moves.begin(),moves.end());

    return;
}

void declareWinner(int whoseTurn)
{
    if (whoseTurn == COMPUTER)
        printf("COMPUTER has won\n");
    else
        printf("HUMAN has won\n");
    return;
}
  
bool rowCrossed(char board[][SIDE])
{
    for (int i=0; i<SIDE; i++)
    {
        if (board[i][0] == board[i][1] &&
            board[i][1] == board[i][2] && 
            board[i][0] != ' ')
            return (true);
    }
    return(false);
}

bool columnCrossed(char board[][SIDE])
{
    for (int i=0; i<SIDE; i++)
    {
        if (board[0][i] == board[1][i] &&
            board[1][i] == board[2][i] && 
            board[0][i] != ' ')
            return (true);
    }
    return(false);
}

bool diagonalCrossed(char board[][SIDE])
{
    if (board[0][0] == board[1][1] &&
        board[1][1] == board[2][2] && 
        board[0][0] != ' ')
        return(true);
          
    if (board[0][2] == board[1][1] &&
        board[1][1] == board[2][0] &&
         board[0][2] != ' ')
        return(true);
  
    return(false);
}

bool gameOver(char board[][SIDE])
{
    return(rowCrossed(board) || columnCrossed(board)
            || diagonalCrossed(board) );
}

void playTicTacToe(int whoseTurn)
{
    char board[SIDE][SIDE];
      
    vector <int> moves(SIDE*SIDE);

    bool checkarr[SIDE*SIDE];

    initialise(board, moves);
    
    showInstructions();
      
    int x, y;

    for(int i=0;i<SIDE*SIDE;i++){
        checkarr[i]=1;
    }
    
    while (gameOver(board) == false && 
            moves.empty() == false)
    {
        if (whoseTurn == COMPUTER)
        {   
            int m=moves.back();
            while(checkarr[m]==0){
                cout<<moves.back();
                moves.pop_back();
                m=moves.back();
            }
            if(moves.empty()){
                cout<<"error2";
                return;
                }
            x = m / SIDE;
            y = m % SIDE;
            board[x][y] = CM;
            printf("COMPUTER has put a %c in cell %d\n",
                    CM, m);
            showBoard(board);
            checkarr[m]=0;
            moves.pop_back();
            whoseTurn = HUMAN;
        }
          
        else if (whoseTurn == HUMAN)
        {
            int a,c=0;
            cout<<"Enter the number corresponding to the move you want to make.\n";
            cin>>a;
            while(checkarr[a-1]==0){
                if(c>3){
                    cout<<"You have used up all the retries, kindly start over";
                    return;
                }
                cout<<"The entered position is already taken please reenter the new value: \n";
                cin>>a;
                c++;
            }
            x = (a-1) / SIDE;
            y = (a-1) % SIDE;
            board[x][y] = HM;
            printf ("HUMAN has put a %c in cell %d\n",
                    HM, a);
            showBoard(board);
            checkarr[a-1]=0;
            whoseTurn = COMPUTER;
        }
        //if(moves.empty())cout<<"moves empty";
    }
  
    if (gameOver(board) == false && 
            moves.empty())
        printf("It's a draw\n");
    else
    {
        if (whoseTurn == COMPUTER)
            whoseTurn = HUMAN;
        else if (whoseTurn == HUMAN)
            whoseTurn = COMPUTER;
        
        declareWinner(whoseTurn);
    }
    return;
}

int main()
{
    playTicTacToe(COMPUTER);
      
    return (0);
}
