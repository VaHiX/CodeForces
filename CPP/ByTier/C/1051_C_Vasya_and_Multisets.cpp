/*
 * Problem URL : https://codeforces.com/contest/1051/problem/C
 * Submit Date : 2025-09-11
 */

#include<iostream>
using namespace std;int i,n,m=0,a[100],b[101]={0},c[100];main(){cin>>n;for(i=0;i<n;i++){cin>>a[i];++b[a[i]];}m=1;for(i=0;i<n;i++)if(b[a[i]]==1){if(m)c[i]=1;else c[i]=2;m=1-m;}i=0;if(!m)for(i=0;i<n;i++)if(!c[i]&&b[a[i]]>2){c[i]=2;break;}if(i==n){cout<<"NO";return 0;}cout<<"YES"<<endl;for(i=0;i<n;i++)if(c[i]==2)cout<<"B";else cout<<"A";}