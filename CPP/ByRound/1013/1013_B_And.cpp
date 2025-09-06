/*
 * Problem URL : https://codeforces.com/contest/1013/problem/B
 * Submit Date : 2025-08-31
 */

#include<bits/stdc++.h>
using namespace std;
bool mk1[100005],mk2[100005];
int main(){
	int n,x,ans=1e9;
	scanf("%d%d",&n,&x);
	for(int i=1,a;i<=n;++i){
		scanf("%d",&a);
		if(mk2[a])ans=0;
		if(mk2[a&x]||mk1[a])ans=min(ans,1);
		if(mk1[a&x])ans=min(ans,2);
		mk2[a]=1;mk1[a&x]=1;
	}if(ans==1e9)ans=-1;
	printf("%d",ans);
}