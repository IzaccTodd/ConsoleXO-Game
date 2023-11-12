
#include <iostream>
#include <string>
#include <cstdlib>
#include<vector>


using namespace std;


//Initialize Function Section----------------------------------------------------------
void printMAP();
int Find_Match_Index(vector<int> smallvec, vector<vector<int>> myvector);
vector<vector<int>> RemoveMatch(vector<vector<int>> myvector, vector<int> smallvec);
bool Is_Matrix_Complete(bool metrix[3][3]);
//_____________________________________________________________________________________

class All {
public:

    char map[16][22];

    int circle[8][2] = {
        {1,3},{1,4},{2,2},{2,5},{3,2},{3,5},
        {4,3},{4,4}};

    int X[5][2] = {
        {2,2},{2,4},{3,3},{4,2},{4,4}};

    vector<vector<int>> quota = {
        {1,1},{1,2},{1,3},
        {2,1},{2,2},{2,3},
        {3,1},{3,2},{3,3}};

    bool X_metrix[3][3] = {
        {false,false,false},
        {false,false,false},
        {false,false,false}};

    bool O_metrix[3][3] = {
        {false,false,false},
        {false,false,false},
        {false,false,false}};


    All() {
        for (int i = 0;i < 16;i++) {
            for (int j = 0;j < 22;j++) {
                if (i % 5 == 0) map[i][j] = '2'; //Floor
                else if (j % 7 == 0) map[i][j] = '1'; //side
                else map[i][j] = '0';
            }}}

    void GetX(int x, int y) {
        // x is j , y is i

        vector<int> temp = { y,x };
        quota = RemoveMatch(quota, temp);
        X_metrix[y - 1][x - 1] = true;

        for (int i = 0;i < 5;i++) {
            map[(y - 1) * 5 + X[i][0]][(x - 1) * 7 + X[i][1]] = '3';
        }}

    void GetO(int x, int y) {
        // x is j , y is i
        vector<int> temp = { y,x };
        quota = RemoveMatch(quota, temp);
        O_metrix[y - 1][x - 1] = true;

        for (int i = 0;i < 8;i++) {
            map[(y - 1) * 5 + circle[i][0]][(x - 1) * 7 + circle[i][1]] = '3';
        }}

};


All game;





int main()
{

    string display[2] = {"Player 1's Turn: \n","Player 2's Turn: \n"};
    bool flag = false;
    int x, y;
    vector<int> cordinate = {0,0};
    while (true) {

        printMAP();
        if (Is_Matrix_Complete(game.X_metrix)) {
            cout << "GAME OVER !! PLAYER 1 WINS !!";
            system("pause");
            break;
        }
        if (Is_Matrix_Complete(game.O_metrix)) {
            cout << "GAME OVER !! PLAYER 2 WINS !!";
            system("pause");
            break;
        }

        cout << display[flag] << endl;
        cout << "Input Y position: ";
        cin >> y;
        cout << endl;
        cout << "Input X position: ";
        cin >> x;
        cout << endl;
        
        *cordinate.begin() = y;
        *(cordinate.begin() + 1) = x;


        if (!flag) {
            if (Find_Match_Index(cordinate, game.quota) != -1) {
                RemoveMatch(game.quota, cordinate);
                game.GetX(x, y);

            }
            else {
                system("cls");
                continue;
            }

        }
        else  {
            if (Find_Match_Index(cordinate, game.quota) != -1) {
                RemoveMatch(game.quota, cordinate);
                game.GetO(x, y);

            }
            else {
                system("cls");
                continue;
            }

        }


        system("cls");
        flag = !(flag || false);
    }

    

}   

   


// Function Section ----------------------------------------------------------------------------------------------------
void printMAP() {
    for (int i = 0;i < (sizeof(game.map) / sizeof(game.map[1]));i++) {
        for (int j = 0;j < (sizeof(game.map[0]) / sizeof(char));j++) {
            if (game.map[i][j] == '2')cout << "=";
            if (game.map[i][j] == '1')cout << '|';
            if (game.map[i][j] == '0')cout << ' ';
            if (game.map[i][j] == '3')cout << "*";
        }
        cout << '\n';
    }
}

int  Find_Match_Index(vector<int> smallvec, vector<vector<int>> myvector) {

//Using linear search 
    for (auto i = myvector.begin(); i != myvector.end();++i ) {
        if (*i == smallvec) {
            return i-myvector.begin();
        }

    }
    return -1;
    
}

vector<vector<int>> RemoveMatch(vector<vector<int>> myvector, vector<int> smallvec) {
    int match_index = Find_Match_Index(smallvec, myvector);
    myvector.erase(myvector.begin() + match_index);
    return myvector;
}

bool Is_Matrix_Complete(bool metrix[3][3]) {
    return ((metrix[0][0] && metrix[0][1] && metrix[0][2]) || (metrix[1][0] && metrix[1][1] && metrix[1][2]) ||
        (metrix[2][0] && metrix[2][1] && metrix[2][2]) || (metrix[0][0] && metrix[1][1] && metrix[2][2]) ||
        (metrix[0][2] && metrix[1][1] && metrix[2][0]) || (metrix[0][0] && metrix[1][0] && metrix[2][0])||
        (metrix[0][1] && metrix[1][1] && metrix[2][1]) || (metrix[0][2] && metrix[1][2] && metrix[2][2])
 );
}