/*
 * Problem URL : https://codeforces.com/problemset/problem/250/D
 * Submit Date : 2025-08-14
 */

#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
typedef long long ll;
const ll oo = 0x3f3f3f3f3f3f3f3fLL;
const int maxn = 100010;
const int maxm = 100010;
int n, m, a, b;
ll ay[maxn];
int y[maxn];
int by[maxm], h[maxm];
int main(){
	scanf("%d%d%d%d", &n, &m, &a, &b);
	for(int i = 0; i < n; i++)
		scanf("%d", &y[i]);
	for(int i = 0; i < m; i++)
		scanf("%d", &by[i]);
	for(int i = 0; i < m; i++)
		scanf("%d", &h[i]);
	for(int i = 0; i < n; i++)
		ay[i] = (ll)y[i] * b;
	ld ans = 1e20;
	int ix = 0, iy = 0;
	for(int i = 0; i < m; i++){
		ll thex = (ll)by[i] * a;
		int ind = lower_bound(ay, ay + n, thex) - ay;
		ll diff = ay[ind] - thex;
		if(ind){
			ll diff1 = thex - ay[ind - 1];
			if(diff > diff1)
				ind--;
		}
		ld dis = sqrtl((ld)a * a + (ld)y[ind] * y[ind]) + 
					sqrtl((ld)(a - b) * (a - b) + (ld)(y[ind] - by[i]) * (y[ind] - by[i])) + (ld)h[i];
		if(ans > dis){
			ans = dis;
			ix = ind;
			iy = i;
		}
	}
	printf("%d %d\n", ix + 1, iy + 1);
	return 0;
}
