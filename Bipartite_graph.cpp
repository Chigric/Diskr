#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

void ItIsBipartiteGraf(vector <vector<int>> &ways, int &tops)
{
    const int inf = 0x7fffffff;
    vector <bool> used (tops, false);
    vector <int> labels (tops, inf);
    queue <int> qqq;

    for  (int i = 0; i < tops; i++)
    {
        if (!used[i])
        {
            qqq.push(i);
            labels[i] = 0;

            while ( !qqq.empty() )
            {
                int now = qqq.front();
                used[now] = true;
                for (size_t j = 0; j < ways[now].size(); j++)
                {
                    if ( !used[ways[now][j]] )
                    {
                        qqq.push(ways[now][j]);
                        if (labels[now] + 1 < labels[ ways[now][j] ])
                            labels[ ways[now][j] ] = labels[now] + 1;
                    }
                }
                qqq.pop();
            }
        }
    }
    bool ItIsBipartiteGraf = true;
    for (int i = 0; i < tops-1; i++)
        for (int j = i+1; j < tops; j++)
            if (labels[i] == labels[j])
                for (size_t k = 0; k < ways[i].size(); k++)
                    if (ways[i][k] == j)//it's vary badly((
                        ItIsBipartiteGraf = false;
    if (ItIsBipartiteGraf)
        cout << "It is bipartite graf" << endl;
    else
        cout << "It isn't bipartite graf" << endl;
}

int main()
{
    ifstream fail(".//../Grafs/B_graf.txt");
    if (!fail)
    {
        cout << "I can't to do this act =(";
        return 1;
    }
    int tops;
    fail >> tops;
    vector<vector<int> > ways(tops);
    int a, var = 0, line = 0;

    while (fail >> a)
    {
        if (a){
            ways[line].push_back(var);
        }
        ++var;
        if (var == tops){
            var = 0;
            ++line;
        }
    }
    fail.close();

    ItIsBipartiteGraf(ways, tops);

    cout << "Tops = " << tops << endl << endl;
    for (unsigned i = 0; i < ways.size(); i++){
        cout << i << ": ";
        for (unsigned j = 0; j < ways[i].size(); j++)
            cout << ways[i][j] <<  ' ';
        cout << '\n';
    }
    return 0;
}
