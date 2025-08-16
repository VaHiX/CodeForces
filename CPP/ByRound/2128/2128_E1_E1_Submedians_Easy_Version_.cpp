/*
 * Problem URL : https://codeforces.com/problemset/problem/2128/E1
 * Submit Date : 2025-08-14
 */

#include <bits/stdc++.h>
using namespace std;
int T, n, k, sum[500005], minn, flag, ans, lans, rans, a[500005], lnum;
signed main(){
	ios :: sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> T;
	while(T--){
		cin >> n >> k;
		for(int i = 1;i <= n;i++) cin >> a[i];
		int l = 1, r = n;
		while(l <= r){
			int mid = (l + r) >> 1;
			sum[0] = 0;
			for(int i = 1;i <= n;i++)sum[i] = sum[i - 1] + (a[i] >= mid ? 1 : -1);
			minn = 1e9, flag = 0;
			for(int i = k;i <= n;i++){
				if(sum[i - k] < minn) minn = sum[i - k], lnum = i - k + 1;
				if(sum[i] - minn >= 0){
					flag = 1;
					ans = mid, rans = i, lans = lnum;
					break;
				}
			}
			if(flag) l = mid + 1;
			else r = mid - 1;
		} 
		cout << ans << ' ' << lans << ' ' << rans << '\n';
	}
}