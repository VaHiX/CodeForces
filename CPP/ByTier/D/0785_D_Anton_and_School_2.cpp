/*
 * Problem URL : https://codeforces.com/problemset/problem/785/D
 * Submit Date : 2025-08-14
 */

#include<bits/stdc++.h>
#define int long long

const int maxn=2e5+5;
const int mod=1e9+7;

int n,num1,num2,ans,inv[maxn],mul[maxn];
char s[maxn];

void init(){
	inv[0]=inv[1]=mul[0]=mul[1]=1;
	for(int i=2;i<=n;i++){
		mul[i]=mul[i-1]*i%mod;
		inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	}
	for(int i=2;i<=n;i++)inv[i]=inv[i-1]*inv[i]%mod;
}

int C(int x,int y){
	return mul[x]*inv[y]%mod*inv[x-y]%mod;
}

signed main(){
	scanf("%s",s+1);n=strlen(s+1);init();
	for(int i=1;i<=n;i++)if(s[i]==')')num2++;
	for(int i=1;i<=n;i++){
		if(s[i]=='('){
			num1++;ans=(ans+C(num1+num2-1,num1))%mod;
		}
		else num2--;
	}
	printf("%lld",ans);
	return 0;
}