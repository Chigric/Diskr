#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

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
    } while (wayExist);
//  結論
    cout << "flow = " << value_of_flow << endl;
}

int main()
{
    ifstream fail(".//../test/test8.in");
    if (!fail)
    {
        cout << "I can't to do this act =(";
        return 1;
    }
    int tops;
    fail >> tops;
    vector<vector<int> > ways(tops);
    int a, i = 0, j = 0;

    while (fail >> a)
    {
        ways[i].push_back(a);
        ++j;
        if (j == tops){
            j = 0;
            ++i;
        }
    }
    fail.close();

    F_F(ways, tops);
//    getchar();
    return 0;
}
