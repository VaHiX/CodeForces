/*
 * Problem URL : https://codeforces.com/contest/837/problem/C
 * Submit Date : 2025-09-01
 */

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=1e5+100;
int n,a,b,x[N],y[N],ans=0;
int main(){
cin>>n>>a>>b;
for(int i=1;i<=n;i++) {
cin>>x[i]>>y[i];
x[i+n]=y[i],y[i+n]=x[i];
}
for(int i=1;i<2*n;i++){
for(int j=i+1;j<=2*n;j++){
if(j!=i+n&&(x[i]<=a)&&(y[i]<=b)&&(x[j]<=a)&&(y[j]<=b)&&(x[i]+x[j]<=a||y[i]+y[j]<=b)){
ans=max(ans,x[i]*y[i]+x[j]*y[j]);
}
}
}
cout<<ans;
}
