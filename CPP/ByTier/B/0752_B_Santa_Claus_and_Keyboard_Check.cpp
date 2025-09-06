/*
 * Problem URL : https://codeforces.com/contest/752/problem/B
 * Submit Date : 2025-09-02
 */

#include <bits/stdc++.h>


using namespace std;

map<int,int>mp;
char s[66666],ss[666666];
int main()
{
    string a,b;
    cin>>a;
    cin>>b;
    int t=0;
    for (int i=0;i<a.size();i++)
    {
        if (mp[a[i]]==0 && mp[b[i]] == 0)
        {
            mp[a[i]]=b[i];
            mp[b[i]]=a[i];
            if(a[i] != b[i] )
                s[++t]=a[i],ss[t]=b[i];
        }
        else if (mp[a[i]]!=b[i])
        {
               cout<<-1;
               return 0;
        }
    }

    cout<<t<<endl;
    for (int i=1;i<=t;i++)
    cout<<s[i]<<" "<<ss[i]<<endl;
}

