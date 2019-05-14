#include <iostream>
#include <vector>
using namespace std;


vector<int> prefix_function (string s) {
    size_t n =  s.length();
    vector<int> pi(n);
    for (int i=1; i<n; ++i) {
        int j = pi[i-1];
        while ((j > 0) && (s[i] != s[j]))
            j = pi[j-1];
        if (s[i] == s[j])
            ++j;
        pi[i] = j;
     }
     return pi;
}


int search(string t, string s, vector<int> q)
{
    if (s.length() != t.length()) return -1;
    string temp = s + s;
    int j = 0;
    int k = 0;
    int mean = -1;
    for (int i = 0; i < temp.length(); i++)
    {
        while (j > 0 && t[j] != temp[i]) j = q[j - 1];
        if (t[j] == temp[i]) j++;
        if (j == t.length())
        {
            mean = (i + 1 - t.length());
            break;
        }
    }
    return mean;
}



int main(){
    string poisk;
    string stroka;
    vector<int> pref;

    cin>>poisk;
    cin>>stroka;

    pref = prefix_function(poisk);
    search(stroka, poisk, pref);

    cout<<search(stroka, poisk, pref);;
    return 0;
}
