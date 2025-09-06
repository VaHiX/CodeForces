/*
 * Problem URL : https://codeforces.com/contest/2038/problem/M
 * Submit Date : 2025-08-30
 */

#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int,int>
#define F first
#define S second
#define pb push_back
#define vi vector<int>
#define tiii tuple<int,int,int>
const int inf=0x3f3f3f3f;
inline int rd(){
	int x=0,y=1;char c=getchar();
	for(;c<'0'||c>'9';c=getchar())if(c=='-')y=-1;
	for(;c>='0'&&c<='9';c=getchar())x=(x<<1)+(x<<3)+(c^48);
	return x*y;
}
double ans[]={0,
3.598290598290597,
8.067171308522770,
12.423075934638065,
16.636642360808395,
};
signed main(){
	int n=rd();
	printf("%.10lf",ans[n]);
	return 0;
}