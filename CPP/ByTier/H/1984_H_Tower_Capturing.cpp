/*
 * Problem URL : https://codeforces.com/contest/1984/problem/H
 * Submit Date : 2025-09-11
 */

#include "bits/stdc++.h"
using namespace std;
#define db long double
#define int long long
const int Len = 205 , mod = 998244353;
const db eps = 1e-5;
int n,m,c[Len][Len];
struct info
{
	int x,y;
	info(){x = 0 , y = 1;}
	info(int X,int Y){x = X , y = Y;}
};
info operator + (info a,info b){return info(a.x + b.x , a.y * b.y % mod * c[a.x + b.x][a.x] % mod);}
struct V
{
	db x,y;
	V(){x = y = 0;}
	V(db X,db Y){x = X , y = Y;}
	inline void clr(){x = y = 0;}
}a[Len];
struct line{V d,a,b;line(){d.clr() , a.clr() , b.clr();}line(V D,V A,V B){d = D , a = A , b = B;}};
inline V operator + (V x,V y){return V(x.x + y.x , x.y + y.y);}
inline V operator - (V x,V y){return V(x.x - y.x , x.y - y.y);}
inline V operator * ( V x, db a){return V(x.x * a , x.y * a);}
inline V operator / ( V x, db a){return V(x.x / a ,x.y / a);}
inline V vc( V x){return V(-x.y , x.x);}//vertical
inline db operator ^ (V x,V y){return x.x * y.y - x.y * y.x;}
inline db len(V x){return sqrt(x.x * x.x + x.y * x.y);}
inline V uni(V x){return x / len(x);}
inline db erdis(V x,V y){return (y.x - x.x) * (y.x - x.x) + (y.y - x.y) * (y.y - x.y);}
inline V crs(line a,line b)
{
	db k = ((b.a - a.a) ^ b.d) / (a.d ^ b.d);
  	return a.a + (a.d * k);
}
inline V midP(V a,V b){return V((a.x + b.x) / 2 , (a.y + b.y) / 2);}
inline line mkline(V a,V b)
{
	V A,B,D;
	A = midP(a , b) , D = vc(uni(b - a));
	return line(D , A , A + D * 10);
}
inline int ck(int id,db X,db Y)
{
	for(int i = 1 ; i <= n ; i ++) if(erdis(a[id] , V(X , Y)) < -eps + erdis(a[i] , V(X , Y))) return 0;
	return 1;
}
info dfs(int x,int y,int ff)
{
	info f,g;V O;//没有必要多一个 f  
	for(int z = 1 ; z <= n ; z ++)
	{
		if(z == x || z == y || z == ff) continue;
		O = crs(mkline(a[x] , a[z]) , mkline(a[y] , a[z]));
		if(ck(x , O.x , O.y)) 
		{
			g = dfs(x , z , y) + dfs(y , z , x);
			g.x ++;
			f = f + g;
		}
	}
	return f;
}
signed main()
{
	int T;scanf("%lld",&T);
	while(T --)
	{
		scanf("%lld",&n);
		for(int i = 1 ; i <= n ; i ++) scanf("%llf %llf",&a[i].x,&a[i].y);
		for(int i = 0 ; i <= n ; i ++) for(int j = 0 ; j <= i ; j ++) c[i][j] = (j ? c[i - 1][j] + c[i - 1][j - 1] : 1) % mod;
		info ans = dfs(1 , 2 , 0);
		printf("%lld\n",(ans.x > 0) * ans.y); 
	}
	return 0;
}