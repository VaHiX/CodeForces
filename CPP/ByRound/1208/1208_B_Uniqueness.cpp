/*
 * Problem URL : https://codeforces.com/contest/1208/problem/B
 * Submit Date : 2025-08-31
 */

#include<bits/stdc++.h>
int i,j,f=1,n,a[2001];
std::set<int>s{0};
int main(){
 scanf("%d",&n);
 while(i++<n)scanf("%d",a+i),j+=f=f&&s.insert(a[i]).second;
 while(j+1){while(s.insert(a[n]).second)n--;i=n-j<i?n-j:i;s.erase(a[j--]);}
 printf("%d",i);
}