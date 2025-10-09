/*
 * Problem URL : https://codeforces.com/contest/2009/problem/D
 * Submit Date : 2025-09-13
 */

#include<bits/stdc++.h>
using namespace std;
int main(){
ios_base::sync_with_stdio(0),cout.tie(0),cin.tie(0);
int t;cin>>t;
while(t--){
long long n,cnt=0;cin>>n;
long long arr[n+10][2]={};
long long x,y,ans=0;
for(int i=0;i<n;i++){
    cin>>x>>y;
    arr[x][y]=1;
    cnt++;
}
for(int i=0;i<=n;i++){
    if(arr[i][0]&&arr[i][1])ans+=cnt-2;
    if(arr[i][1]&&arr[i+2][1]&&arr[i+1][0])ans++;
    if(arr[i][0]&&arr[i+2][0]&&arr[i+1][1])ans++;
}
cout<<ans<<'\n';
}

}