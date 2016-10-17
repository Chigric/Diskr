#include <vector>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <cstring>
using namespace std;

void show_vector( vector<bool>&a)
{
    for (vector<bool>::iterator it = a.begin() ; it!=a.end() ; ++it){
            if (*it == 1) cout << 1;
            else
                cout << 0;
    }
    cout << endl;
}

bool classPoste(int funcSize, vector<bool> boolean_f)
{
    ///T0
    bool T0, T1, S, M, L;
    if (boolean_f[0] == false)
        { T0 = true; cout << "T0 = " << 1 << endl;}
    else
        {T0 = false; cout << "T0 = " << 0 << endl;}
    ///T1
    if (boolean_f[funcSize] == true)
        {T1 = true; cout << "T1 = " << 1 << endl;}
    else
        {T1 = false; cout << "T1 = " << 0 << endl;}
    ///S
    S = true;
    for (int i = 0,j = funcSize; i < funcSize/2, j > funcSize/2; i++, j--)
    {
        if (boolean_f[i] == boolean_f[j]){
            S = false;
            cout << "S = " << 0 << endl;
            break;
        }
    }
    ///M prov
    M = true;
    for (int i = 0; i < funcSize && M; i++)
    {
        for (int j = i+1; j < funcSize; j++)
        {
            if ( (i|j) == j && (boolean_f[i] > boolean_f[j]) )
            {
                M = false;
                cout << "M = " << 0 << endl;
                break;
            }
        }
    }
    ///L
    L = true;
    for (int i = 0; i < funcSize; i++)
    {
        if( (i&(i-1)) && boolean_f[i] )
        {
            L = false;
            cout << "L = " << 0 << endl;
            break;
        }
        else
            for (int j = 0; j < funcSize - i - 1; j++)
                boolean_f[j] = (boolean_f[j] + boolean_f[j+1])&1;
    }

    if (T0 || T1 || S || M || L)
        ///function isn't full
        return false;
    else
        ///function is full
        return true;

}
int main()
{
    string myfunc;
    int funcSize;
    cout << "Enter Boolean function:" << endl;
    cin >> myfunc;
    funcSize = myfunc.size();

    for (int i = 0; i < funcSize; i++)
        cout << funcSize << "\t" << myfunc[i] << endl;

    vector <bool> boolean_f(funcSize);

    ///write bool function to vector
    if (funcSize == 1){
        cout << "You wrote not properly Boolean function \1" << endl;
        return 1;
    } else if (!(funcSize & funcSize-1)){
        cout << "IsBoolFunction" << endl;
        for (int i = 0; i < funcSize; i++)
        {
            switch(myfunc[i]){
                case '0':
                    boolean_f[i] = false;
                    break;
                case '1':
                    boolean_f[i] = true;
                    break;
                default:
                    cout << "You wrote not properly Boolean function \2" << endl;
                    return 2;
            }
        }
    } else{
        cout << "It is'n bool function((" << endl;
        return 3;
    }
    show_vector(boolean_f);
    cout << "It's your number " << funcSize << " !!!" << endl;

    if ( classPoste(funcSize, boolean_f) )
        cout << "The function is full, \03!" << endl;
    else
        cout << "The function doesn't full" << endl;
    return 0;
}
