/*
 * Problem URL : https://codeforces.com/problemset/problem/2131/F
 * Submit Date : 2025-08-14
 */

#include<cstdio>
typedef long long ll;
const int N=2e5+5,INF=0x3f3f3f3f;
int n,sa[N][2],sb[N][2],p[N<<2];
char a[N],b[N];
void solve()
{
	scanf("%d%s%s",&n,a+1,b+1);
	for(int i=0;i<=n<<1;i++)
		p[i]=0;
	for(int i=1;i<=n;i++)
		sa[i][a[i]-48]=sa[i-1][a[i]-48]+1,sa[i][a[i]-48^1]=sa[i-1][a[i]-48^1];
	for(int i=1;i<=n;i++)
		sb[i][b[i]-48]=sb[i-1][b[i]-48]+1,sb[i][b[i]-48^1]=sb[i-1][b[i]-48^1];
	ll ans=0,t=n,__0=0,__1=0;
	for(int i=1;i<=n;i++)
	{
		int _0=sa[i][0]+sb[1][0],_1=sa[i][1]+sb[1][1];
		p[_0-_1+n]++;
		if(_0<_1)
			__0++,ans+=_0;
		else if(_0>_1)
			__1++,ans+=_1;
		else
			ans+=_0;
	}
	ll sum=ans;
	for(int i=2;i<=n;i++)
	{
		if(b[i]=='0')
			__1+=p[t--],sum+=__0,(__0-=p[t]);
		else
			__0+=p[t++],sum+=__1,(__1-=p[t]);
		ans+=sum;
	}
	printf("%lld\n",ans);
}
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
		solve();
	return 0;
}
/*
0 1 1 2
0 1 1 2
1 2 2 3
1 2 2 3

*/