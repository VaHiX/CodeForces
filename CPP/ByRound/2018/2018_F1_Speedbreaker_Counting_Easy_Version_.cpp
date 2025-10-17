/*
 * Problem URL : https://codeforces.com/contest/2018/problem/F1
 * Submit Date : 2025-09-11
 */

#include<bits/stdc++.h>
#define fi(s) freopen(s".in","r",stdin)
#define fo(s) freopen(s".out","w",stdout)
#define fe(s) freopen(s".mas","w",stdout)
#define file(s) fi(s),fo(s)
#define fier(s) fi(s),fe(s)
using namespace std;
typedef long long ll;
namespace tomorinao {char arrs;
int read() {int s=0,w=1;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') w=-1;c=getchar();}
	while(c>='0'&&c<='9') s=(s<<3)+(s<<1)+(c^48),c=getchar();
	return s*w;}
const int maxn = 3010;
int f[maxn][maxn][2],g[maxn],pr[maxn],h[maxn][maxn],mod,n;
int MOD(int x) {return x>=mod?x-mod:x;}
char arrt;void Main() {
	cerr<<((&arrt-&arrs)>>20)<<'\n';
	int cas=read();while(cas--) {
		n=read(),mod=read();
		f[1][n][0]=1;
		for(int k=n-1,r;k;k--)
			for(int l=1;l+k-1<=n;l++) {
				r=l+k-1;
				if(l>1) f[l][r][0]=1ll*(n-k)*(f[l-1][r][0]+f[l-1][r][1])%mod;
				if(r<n)
					f[l][r][1]=(f[l][r][1]+1ll*f[l][r+1][1]*(n-k)+f[l][r+1][0])%mod;
			}
		for(int k=1;k<=n;k++)
			for(int i=g[k]=1;i<=k;i++) g[k]=1ll*g[k]*(n-max(i-1+1,k-i+1)+1)%mod;
		for(int i=1;i<=n;i++)
			for(int j=i;j<=n;j++) h[i][j]=1ll*g[j-i+1]*(f[i][j][0]+f[i][j][1])%mod;
		for(int k=1,j;k<=n;k++)
			for(int i=1;i+k-1<=n;i++) j=i+k-1,
				h[i][j]=(1ll*h[i][j]+mod-h[i][j+1]+mod-h[i-1][j]+h[i-1][j+1])%mod,
				pr[k]=MOD(pr[k]+h[i][j]);
		pr[0]=1;for(int i=1;i<=n;i++) pr[0]=1ll*pr[0]*n%mod;
		for(int i=1;i<=n;i++) if(pr[i]) pr[0]=MOD(pr[0]+mod-pr[i]);
		for(int i=0;i<=n;i++) cout<<pr[i]<<' ';cout<<'\n';
		
		for(int i=1;i<=n;g[i]=pr[i]=0,i++)
			for(int j=i;j<=n;j++) f[i][j][0]=f[i][j][1]=h[i][j]=0;
	}
}}signed main() {return tomorinao::Main(),0;}
