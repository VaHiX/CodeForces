/*
 * Problem URL : https://codeforces.com/problemset/problem/2119/E
 * Submit Date : 2025-08-14
 */

#include <bits/stdc++.h>
using namespace std;

struct stu{
	int x;				// this one is last number
	long long dp;		// this one is number of operations
};

void solve(){
	using ll = long long;
	
	constexpr ll inf = 0x3f3f3f3f3f3f3f3f;
	
	int n;
	cin >> n;
	
	vector<int> a(n - 1);
	vector<int> b(n);
	
	for (int i = 0; i < n - 1; ++i)
		cin >> a[i];
	for (int i = 0; i < n; ++i)
		cin >> b[i];
	
	vector<stu> f{{0, 0}}, g;
	
	for (int i = 0; i < n; ++i){
		g.clear();
		int x = 0;
		
		const int target = (((i > 0) ? a[i - 1] : 0) | ((i < n - 1) ? a[i] : 0)); 	// it's just a[i - 1] | a[i] with boundaries
		const int last = ((i > 0) ? a[i - 1] : 0);  								// last number
		
		for (int j = 30; j >= -1; --j){
			int y = x | target;
			if(j != -1) y |= (1<<j);
			
			if(y >= b[i]){
				ll mn = inf;
				for (auto l : f){
					if((y & l.x) != last) continue;
					mn = min(mn, l.dp + y - b[i]);
				}
				if(mn < inf)
					g.push_back({y, mn});
			}
			if(j != -1)
				x |= (1<<j) & b[i]; 		// so to keep x >= b[i]
		}
		
		swap(f, g);
	}
	
	ll ans{inf};
	for (auto l : f)
		ans = min(ans, l.dp);
	cout << (ans == inf ? -1 : ans) << "\n";
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int T;
	cin >> T;
	while(T--) solve();

	return 0;
}