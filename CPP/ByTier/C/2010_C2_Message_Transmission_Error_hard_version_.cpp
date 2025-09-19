/*
 * Problem URL : https://codeforces.com/contest/2010/problem/C2
 * Submit Date : 2025-09-12
 */

#include <bits/stdc++.h>
using namespace std;
int n,nxt[400100]; 
char a[400100];
int main(){
	scanf("%s",a+1);
	n=strlen(a+1);
	nxt[1]=0;
	for(int i=2,j=0;i<=n;i++){
		while(j&&a[j+1]!=a[i]) j=nxt[j];
		if(a[j+1]==a[i]) j++; nxt[i]=j;
	}
	if(nxt[n]*2<=n) printf("NO");
	else{
		printf("YES\n");
        for(int i=1;i<=nxt[n];i++) printf("%c",a[i]); 
	}
}