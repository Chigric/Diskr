#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
//int ggwp=0;

void DFS_for_F_F(vector<vector<int> > &ways, int &tops, vector<bool> &used, vector<int> &path, int &MFOT, bool &wayExist)
{
//    bool itIsNotWay = false;
//    int index;
//    do{
//        index = -1;
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
//            path.push_back(j);
//            RecalculateConstraint(ways, path.back(), MFOT);
            if (wayExist){
                ways[i][j] -= MFOT;
                ways[j][i] += MFOT;
            }
//            path.pop_back();

//            wayExist = true;
            return;
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
    //cout << ggwp++ << "\n";
//    } while( ways[i][j] != 1 );

    //tops - 1 = last top
}

void F_F(vector<vector<int> > &ways, int &tops)
{
    int value_of_flow = 0;
    bool /*_from = false, _to = false,*/ wayExist /*= false*/;
    do{
        vector <bool> used(tops, false);
        vector <int> path;
        path.push_back(0);
        int MinFlowOnTops = 0x7fffffff;
        wayExist = false;

        DFS_for_F_F(ways, tops, used, path, MinFlowOnTops, wayExist);
//        for (size_t p = 1; p < path.size() ; p++)
//        {
//            for (size_t j = 0; j < from.size(); j++)
//            {
//                if(from[j] == path[p-1] && to[j] == path[p] )
//                    if (!_from){
//                        _from = true;
//                        constraint[j] -= MinFlowOnTops;
//                }
//                if(from[j] == path[p] && to[j] == path[p-1] )
//                    if (!_to){
//                        _to = true;
//                        constraint[j] += MinFlowOnTops;
//                }
//                if (_to && _from)
//                    break;
//            }
//            if (!_to){
//                from.push_back(path[p]);
//                to.push_back(path[p-1]);
//                constraint.push_back(MinFlowOnTops);
//            }
//            _from = false; _to = false;
        if (wayExist)
            value_of_flow += MinFlowOnTops;
    } while (wayExist);
//  結論
    cout << "flow = " << value_of_flow << endl;
}

int main()
{
    ifstream fail(".//../test/test1.in");
    if (!fail)
    {
        cout << "I can't to do this act =(";
        return 1;
    }
    int tops;
    fail >> tops;
    //vector <int> from, to, constraint;
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
