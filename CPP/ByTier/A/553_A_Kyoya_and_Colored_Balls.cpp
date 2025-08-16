/*
 * Problem URL : https://codeforces.com/problemset/problem/553/A
 * Submit Date : 2025-08-16
 */

#include<iostream>
using namespace std;
long long m=1002,o=1e9+7,n,r,s=0,i=1,j,p=1;
main(){
    int a[m][m];
    for(;i<m; i++)
        for(j=2,a[i][1]=1;j<=i;j++)
        (a[i][j]+=a[i-1][j]+a[i-1][j-1])%=o;
    cin>>n;
    for(i=0; i<n; i++){
        cin>>r;
        s+=r;
        (p*=a[s][r])%=o;
    }
    cout<<p;
}
