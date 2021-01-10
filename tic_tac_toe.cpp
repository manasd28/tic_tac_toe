#include<bits/stdc++.h>
using namespace std;

class game
{
    public:
    char pc, ph;
    char gboard[3][3];
    game(char);
    void display_board();
    void display_co_board();
    bool check_moves(char [3][3]);
    int board_value(char [3][3]);
    int minimax(char [3][3], bool);
    void play_best_move();
};

game :: game(char ch = 'x')
{
    pc = ( ch == 'x'? 'o' : 'x' );
    ph = ch;
    printf( "\nYou are playing as '%c' and computer as '%c' !!\n\n", ph, pc );
    cout<<"INITAIL BOARD :\n";
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            gboard[i][j] = '_'; cout<<'_'<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

void game :: display_co_board()
{
    for(int i=1;i<4;i++)
    {
        for(int j=1;j<4;j++)
        {
            printf( "(%d,%d) ",i ,j );
        }
        cout<<endl;
    }
}

void game :: display_board()
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            cout<<gboard[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

bool game :: check_moves(char board[3][3])
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(board[i][j] == '_') return true;
        }
    }
    return false;
}

int game :: board_value(char board[3][3])
{
    for(int i=0;i<3;i++)
    {
        if(board[0][i] == board[1][i] && board[1][i] == board[2][i])
        {
            if(board[0][i] == pc) return 10;
            else if(board[0][i] == ph) return -10;
        }
        if(board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            if(board[i][0] == pc) return 10;
            else if(board[i][0] == ph) return -10;
        }
    }

    if(board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        if(board[0][0] == pc) return 10;
        else if(board[0][0] == ph) return -10;
    }

    if(board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        if(board[0][2] == pc) return 10;
        else if(board[0][2] == ph) return -10;
    }
    return 0;
}

int game :: minimax(char board[3][3], bool turn)
{
    int value = board_value(board);
    if(value == 10) return 10;
    else if(value == -10) return -10;
    else if(!check_moves(board)) return 0;

    int res;
    if(turn)
    {
        res = -999;
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                if(board[i][j] == '_')
                {
                    board[i][j] = pc;
                    res = max(res, minimax(board, !turn));
                    board[i][j] = '_';
                }
            }
        }
    }
    else
    {
        res = 999;
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                if(board[i][j] == '_')
                {
                    board[i][j] = ph;
                    res = min(res, minimax(board, !turn));
                    board[i][j] = '_';
                }
            }
        }
    }
    return res;
}

void game :: play_best_move()
{
    int reward = -1000, temp;
    int x,y;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(gboard[i][j] == '_')
            {
                gboard[i][j] = pc;
                temp = minimax(gboard, false);
                gboard[i][j] = '_';
                if(temp>reward)
                {
                    reward = temp;
                    x = i;
                    y = j;
                }
            }
        }
    }
    gboard[x][y] = pc;
}

int main()
{
    char ch;
    int x, y;
    int counter = 1;
    cout<<"Enter the player you want to play as (x,o) !\n";
    while(true)
    {
        cin>>ch;
        if(ch != 'x' && ch != 'o') cout<<"Invalid Choice! Enter Again\n";
        else break;
    }
    game g(ch);
    cout<<"Co-ordinates of the board are as follows :\n\n";
    g.display_co_board();
    cout<<endl;
    while(true)
    {
        cout<<"Enter the position you want to play ( eg: 1 2 )\n";
        cin>>x>>y;
        --x, --y;
        if(x<0 || y<0 || x>2 || y>2)
        {
            cout<<"Out of bounds! Enter again\n";
            continue;
        }
        else if(g.gboard[x][y] != '_')
        {
            cout<<"Already taken!! Enter again\n";
            continue;
        }
        cout<<endl;
        g.display_co_board();
        cout<<endl;
        g.gboard[x][y] = g.ph;
        g.play_best_move();
        if(g.check_moves(g.gboard) == false)
        {
            g.display_board();
            cout<<"TIE!\n";
            break;
        }
        else if(g.board_value(g.gboard) == 10)
        {
            g.display_board();
            cout<<"YOU LOST!\n";
            break;
        }
        else if(g.board_value(g.gboard) == -10)
        {
            g.display_board();
            cout<<"YOU WON\n";
            break;
        }
        g.display_board();
    }
    return 0;
}
