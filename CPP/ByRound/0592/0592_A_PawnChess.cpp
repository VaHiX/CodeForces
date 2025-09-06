/*
 * Problem URL : https://codeforces.com/contest/592/problem/A
 * Submit Date : 2025-09-04
 */

// Hydro submission #65f1b3052d49cc1e2314f578@1710338821365
#include<bits/stdc++.h>
#define min(a,b) a>b?b:a
char A[11][11];
int i,j,a=10000,b=10000;
int main(){
	for(i=0;i<8;i++) scanf("%s",A[i]);
	for(j=0;j<8;j++){
		for(i=0;i<8;i++){
				if(A[i][j]=='B')break;
				if(A[i][j]=='W')a=min(a,i);
			}
			for(i=0;i<8;i++){
				if(A[7-i][j]=='W')break;
				if(A[7-i][j]=='B')b=min(b,i);
		}
	}
	printf("%c",a<=b?'A':'B');
}