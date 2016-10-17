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
    } while( to[index] != tops-1 );
    //tops - 1 = last top
    return true;
}

void F_F(vector<int> &from, vector<int> &to, vector<int> &constraint, int tops)
{
    int MinFlowOnTops = 0x7fffffff;
    bool _from = false, _to = false;
    vector <int> path;
    vector <int> flow(from.size(), 0);
    while (DFS(from, to, constraint, tops, path, MinFlowOnTops) ){
        for (size_t p = 1; p < path.size() ; p++)
        {
            for (size_t j = 0; j < from.size(); j++)
            {
                if(from[j] == path[p-1] && to[j] == path[p] )
                    if (!_from){
                        _from = true;
                        constraint[j] -= MinFlowOnTops;
                        flow[j] = MinFlowOnTops;
                }
                if(from[j] == path[p] && to[j] == path[p-1] )
                    if (!_to){
                        _to = true;
                        constraint[j] += MinFlowOnTops;
                        flow[j] = -MinFlowOnTops;
                }
                if (_to && _from)
                    break;
            }
            if (!_to){
                from.push_back(path[p]);
                to.push_back(path[p-1]);
                constraint.push_back(MinFlowOnTops);
                flow.push_back(-MinFlowOnTops);
            }
            _from = false; _to = false;
        }
        MinFlowOnTops = 0x7fffffff;
        path.clear();
    }

//  結論
    cout << "flow =\n";
    for (unsigned i = 0; i < flow.size(); i++)
       cout << ' ' << flow[i];
     cout << '\n';
}

int main()
{
    ifstream fail("..//../Grafs/Random_FF.txt");
    if (!fail)
    {
        cout << "I can't to do this act =(";
        return 1;
    }
    int tops, edges;
    fail >> tops >> edges;

    int a, b, c;
    vector <int> from, to, constraint;
    while (fail >> a >> b >> c)
    {
        from.push_back(a);
        to.push_back(b);
        constraint.push_back(c);
    }
    fail.close();

    F_F(from, to, constraint, tops);
//    getchar();
    return 0;
}
