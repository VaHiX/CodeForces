/*
 * Problem URL : https://codeforces.com/problemset/problem/413/D
 * Submit Date : 2025-08-14
 */

#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
int n,k,f[2][2000],x;
int main(){
	scanf("%d%d",&n,&k);
	k--;
	for(int i=f[0][0]=1;i<=n;i++){
		scanf("%d",&x);
		fill(&f[i&1][0],&f[i&1][1<<k]+1,0);
		for(int j=0;j<=(1<<k);j++){
			if(x!=2) (f[i&1][j&1?2: min(j+2,1<<k)]+=f[(i&1)^1][j])%=mod;
			if(x!=4) (f[i&1][min(j+1,1<<k)]+=f[(i&1)^1][j])%=mod;
		}
	}
	printf("%d",f[n&1][1<<k]);
	return 0;
}