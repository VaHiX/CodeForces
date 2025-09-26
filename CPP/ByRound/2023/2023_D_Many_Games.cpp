/*
 * Problem URL : https://codeforces.com/contest/2023/problem/D
 * Submit Date : 2025-09-10
 */

#include<bits/stdc++.h>
#define int long long
#define inf 0x3f3f3f3f3f3f3f3f
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
int n,sum;
double ans,f[200010];
int w[200010],p[200010];
priority_queue<int>q[110];
signed main(){
#ifdef LOCAL
	freopen("in","r",stdin);
	freopen("out","w",stdout);
#endif
	n=read();f[0]=1;
	for(int i=1;i<=n;i++){
		p[i]=read(),w[i]=read();
		if(p[i]==100) sum+=w[i];else q[p[i]].push(w[i]);
	}
	for(int i=1;i<=99;i++){
		for(int j=100/(100-i);j&&!q[i].empty();j--){
			int x=q[i].top();q[i].pop();
			for(int k=200000;k>=x;k--){
				f[k]=max(f[k],1.0*f[k-x]*i/100);
			}
		}
	}
	for(int i=0;i<=200000;i++) ans=max(ans,(i+sum)*f[i]);
	printf("%.10lf",ans);
	return 0;
}