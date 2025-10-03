/*
 * Problem URL : https://codeforces.com/contest/2014/problem/G
 * Submit Date : 2025-09-12
 */

#include <stdio.h>
#include <algorithm>
#include <vector>
#define pii pair<int,int>
using namespace std;
int n, m, k;
int D[200010], A[200010];
pii M[200010];
const int INF = 0x3f3f3f3f;
int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%d %d %d", &n, &m, &k);
		for(int i = 0; i < n; i++){
			scanf("%d %d", &D[i], &A[i]);
		}
		int p = -1;
		int ans = 0;
		D[n] = INF;
		for(int i = 0; i < n; i++){
			M[++p] = {D[i], A[i]};
			int req = m;
			int cur_day = D[i];
			while(p >= 0 && cur_day < D[i+1]){
				if(cur_day - M[p].first >= k){
					p--;
				}else if(req > M[p].second){
					req -= M[p].second;
					p--;
				}else if(req < m){
					M[p].second -= req;
					ans++;
					req = m;
					cur_day++;
				}else{
					int s = M[p].second/m;
					int mx = min(M[p].first + k - 1, min(cur_day + s - 1, D[i+1]-1));
					ans += mx - cur_day + 1;
					M[p].second -= (mx-cur_day+1)*m;
					cur_day = mx+1;
				}
			}
		}
		printf("%d\n", ans);
	}
}