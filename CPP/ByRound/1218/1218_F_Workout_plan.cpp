/*
 * Problem URL : https://codeforces.com/contest/1218/problem/F
 * Submit Date : 2025-09-04
 */

#include<bits/stdc++.h>
using namespace std;
const int M=1e5+20;
#define LL long long
int pl[M];
priority_queue<int,vector<int>,greater<int> > q;
int main(){
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;++i)
		scanf("%d",&pl[i]);
	int inc;
	scanf("%d",&inc);
	LL ans=0;
	bool v=true;
	for(int i=1;i<=n;++i){
		int c;
		scanf("%d",&c);
		q.push(c);
		while(!q.empty()&&k<pl[i])
			ans+=q.top(),q.pop(),k+=inc;
		if (k<pl[i]){
			v=false;
			break;
		}
	}
	if(v)
		printf("%lld\n",ans);
	else
		printf("-1\n");
	return 0;
}