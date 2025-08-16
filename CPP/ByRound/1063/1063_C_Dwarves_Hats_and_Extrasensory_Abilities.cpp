/*
 * Problem URL : https://codeforces.com/problemset/problem/1063/C
 * Submit Date : 2025-08-14
 */

#include<bits/stdc++.h>
using namespace std;
int n,p=0,l=0,r=1e9;
string s,st;
int main(){
	scanf("%d",&n);
	puts("0 1");cin>>st;
	for(int i=1;i<n;i++){
		int mid=(l+r)>>1;
		printf("%d 1\n",mid);
		cin>>s;
		if(s==st)l=mid;
		else r=mid;
    }
    printf("%d 0 %d 2",l,r);
}