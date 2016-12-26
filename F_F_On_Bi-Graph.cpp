#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
//3 3
//1 1
//1 1
//1 1

//5 5
//0
//1 1
//0
//1 3
//0

//15 12
//0//1 10
//1//2 4 9
//2//1 6
//3//1 0
//4//5 0 3 5 9 11
//5//0
//6//3 2 4 7
//7//5 0 2 7 8 10
//8//1 10
//9//0
//10//1 3
//11//4 0 3 8 9
//12//1 7
//13//3 4 6 9
//14//3 0 4 10

int last_v, first_v;
int var = 0;

void DFS_for_F_F(vector<vector<int> > &ways, int &tops, vector<bool> &used, vector<int> &path, int &MFOT, bool &wayExist)
{
    for (int i = path.back(), j = 0; j < tops; j++)
    {
        if (!used[j] && ways[i][j]){
            if ( MFOT > ways[i][j] )
                MFOT = ways[i][j];
            used [i] = true;
            path.push_back( j );
            if (j != 1){
                DFS_for_F_F(ways, tops, used, path, MFOT, wayExist);
            } else wayExist = true;
            if (wayExist){
                first_v = path[1] - 2;
                last_v = path[path.size() - 2] - /*3*/15 - 2;
                ways[i][j] -= MFOT;
                ways[j][i] += MFOT;
                return;
            }
        }
    }
    //it's vAry badly
    used [ path.back() ] = true;
    if (path.back() != 0)
        path.pop_back();
    else{
        wayExist = false;
        return;
    }
}

void F_F(vector<vector<int> > &ways, int &tops)
{
    int value_of_flow = 0;
    bool wayExist;
    do{
        vector <bool> used(tops, false);
        vector <int> path;
        path.push_back(0);
        int MinFlowOnTops = 0x7fffffff;
        wayExist = false;

        DFS_for_F_F(ways, tops, used, path, MinFlowOnTops, wayExist);
        if (wayExist)
            value_of_flow += MinFlowOnTops;
        cout << first_v << ": " << var++ << " " << last_v << endl;
    } while (wayExist);
//  結論
    cout << "flow = " << value_of_flow << endl;
}

int main()
{
    ifstream fail("..//../test3/test3.in");
    if (!fail)
    {
        cout << "I can't to do this act =(";
        return 1;
    }
    int tops, left, right;
    fail >> left >> right;
    tops = left+right+2;

    vector<vector<int> > ways(tops, vector<int> (tops, 0));
    int a, b, i = 2;

    while (fail >> a)
    {
        ways[0][i] = 1;
        ways[i][0] = 1;

        for (int k = 0; k < a; k++){
            fail >> b;
            ways[i][ b+left+2 ] = 1;
            ways[ b+left+2 ][i] = 1;
        }
        ++i;
    }
    fail.close();
    for (int j = 0; j < right; j++, i++)
    {
        ways[i][1] = 1;
        ways[1][i] = 1;
    }

    F_F(ways, tops);
//    getchar();
    return 0;
}
