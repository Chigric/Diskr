#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void DFS_for_F_F(vector<vector<int> > &ways, int &tops, vector<bool> &used, vector<int> &path, int &MFOP, int &Min_F, bool &wayExist)
{
    for (int i = path.back(), j = 0; j < tops; j++)
    {
        if (!used[j] && ways[i][j] > MFOP){
            if (ways[i][j] < Min_F)
                Min_F = ways[i][j];
            used [i] = true;
            path.push_back( j );
            if (j != 1){
                DFS_for_F_F(ways, tops, used, path, MFOP, Min_F, wayExist);
            } else wayExist = true;
            if (wayExist){
                MFOP = Min_F;
                return;
            }
        }
    }

    used [ path.back() ] = true;
    if (path.back() != 0)
        //it's very badly
        path.pop_back();
    else{
        wayExist = false;
        return;
    }
}

void F_F(vector<vector<int> > &ways, int &tops)
{
    int MaxFlowOnPath = 0;
    bool wayExist;
    do{
        vector <bool> used(tops, false);
        vector <int> path;
        int MinFlowOnTop = 0x7fffffff;
        path.push_back(0);
        wayExist = false;
        DFS_for_F_F(ways, tops, used, path, MaxFlowOnPath, MinFlowOnTop, wayExist);
    } while (wayExist);
//  結論
    cout << "Max flow on path = " << MaxFlowOnPath << endl;
}

int main()
{
    ifstream fail(".//../test2/test8.in");
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
