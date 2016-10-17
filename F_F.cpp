#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

bool DFS(vector<int> &from, vector<int> &to, vector<int> &constraint, int &tops, vector<int> &path, int &MFOT)
{//form 0 to last top
    path.push_back(0);
    vector <bool> used(tops, false);
//    bool itIsNotWay = false;
    int index;
    do{
        index = -1;
        for (size_t i = 0; i < from.size(); i++)
        {
            if (from[i] == path.back() && !used[ to[i] ] && constraint[i]){
                index = i;
                break;
            }
        }
        if(index == -1){
        //it's very badly
            used [ path.back() ] = true;
            if (path.back() != 0)
                path.pop_back();
            else
                return false;
        }else{
            if ( MFOT > constraint[index] )
                MFOT = constraint[index];
            used [ path.back() ] = true;
            path.push_back( to[index] );
        }
    } while( to[index] != 1 );
    //tops - 1 = last top
    return true;
}

void F_F(vector<int> &from, vector<int> &to, vector<int> &constraint, int &tops)
{
    int MinFlowOnTops = 0x7fffffff;
    bool _from = false, _to = false;
    vector <int> path;
    int value_of_flow = 0;
    while (DFS(from, to, constraint, tops, path, MinFlowOnTops) ){
        for (size_t p = 1; p < path.size() ; p++)
        {
            for (size_t j = 0; j < from.size(); j++)
            {
                if(from[j] == path[p-1] && to[j] == path[p] )
                    if (!_from){
                        _from = true;
                        constraint[j] -= MinFlowOnTops;
                }
                if(from[j] == path[p] && to[j] == path[p-1] )
                    if (!_to){
                        _to = true;
                        constraint[j] += MinFlowOnTops;
                }
                if (_to && _from)
                    break;
            }
            if (!_to){
                from.push_back(path[p]);
                to.push_back(path[p-1]);
                constraint.push_back(MinFlowOnTops);
            }
            _from = false; _to = false;
        }
        value_of_flow += MinFlowOnTops;
        MinFlowOnTops = 0x7fffffff;
        path.clear();
    }

//  結論
    cout << "flow = " << value_of_flow << endl;
}

int main()
{
    ifstream fail("..//../test/test6.in");
    if (!fail)
    {
        cout << "I can't to do this act =(";
        return 1;
    }
    int tops;
    fail >> tops;
    vector <int> from, to, constraint;
//    vector<vector<int> > ways(tops);
    int a, i = 0, j = 0;

    while (fail >> a)
    {
        if (a){
            from.push_back(i);
            to.push_back(j);
            constraint.push_back(a);
        }
        ++j;
        if (j == tops){
            j = 0;
            ++i;
        }
    }
    fail.close();

    F_F(from, to, constraint, tops);
//    getchar();
    return 0;
}
