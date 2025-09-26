/*
 * Problem URL : https://codeforces.com/contest/2010/problem/C1
 * Submit Date : 2025-09-12
 */

#include<iostream>
using namespace std;

int main(){
string s;
cin>>s;

int n=s.length();
int k=(n/2)+1;

for(int i=k;i<n;i++){
    if(s.substr(0,i)==s.substr(n-i,i)){
        cout<<"YES"<<endl;
        cout<<s.substr(0,i)<<endl;
        return 0;
    }
}
cout<<"NO"<<endl;
return 0;
}