/*
 * Problem URL : https://codeforces.com/problemset/problem/510/B
 * Submit Date : 2025-08-16
 */

#include "iostream"
using namespace std;

int main(){char x[50][50];int n,m,i,j,p=0;cin>>n>>m;
for(i=0;i<n;i++)for(j=0;j<m;j++){cin>>x[i][j];}
for(i=0;i<n;i++)for(j=0;j<m;j++){
if(x[i][j]!='1'&&((x[i][j]==x[i][j+1])+(x[i][j]==x[i-1][j])+(x[i][j]==x[i][j-1])+(x[i][j]==x[i+1][j]))<2){x[i][j]='1';i=0;j=0;}
}
for(i=0;i<n;i++)for(j=0;j<m;j++){
if(x[i][j]!='1')p++;
}
p>1?cout<<"Yes":cout<<"No";
}