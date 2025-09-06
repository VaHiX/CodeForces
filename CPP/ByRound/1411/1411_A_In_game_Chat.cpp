/*
 * Problem URL : https://codeforces.com/contest/1411/problem/A
 * Submit Date : 2025-09-01
 */

#include<bits/stdc++.h>
using namespace std;
int main(){
    int t; cin>>t;
    while(t--){
        int n,cn=0;
        cin>>n;
        string s; cin>>s;
        n--;
        while (s[n]==')' && n>=0) cn++,n--;
        cout << (s.size()-cn<cn ? "Yes" : "No") << "\n";
    }
}