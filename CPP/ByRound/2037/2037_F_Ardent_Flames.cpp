/*
 * Problem URL : https://codeforces.com/contest/2037/problem/F
 * Submit Date : 2025-09-05
 */

#include <iostream>
#include <vector>
#include <algorithm>

#define endl '\n'
#define ll long long
#define pb push_back
#define mp make_pair

using namespace std;

const int MAXN = 1e5+100;

typedef pair<int, int> pii;

int t, n, m, k;
int x[MAXN], h[MAXN];

vector<pii> vc;
bool chk(int md){
	vc.clear();
	for(int i=0; i<n; i++){
		int d = (h[i]+md-1)/md;

		int rng = m-d;
		if(rng < 0) continue;

		vc.pb(mp(max(1, x[i]-rng), 1));
		vc.pb(mp(min(x[i]+rng, (int)(1e9))+1, -1));

	}

	sort(vc.begin(), vc.end());

	int cnt=0;
	for(auto [wtf, x] : vc){
		cnt += x;
		if(cnt >= k) return 1;
	}

	return 0;
}

int main(){
	ios::sync_with_stdio(0);cin.tie(0);

	cin >> t;
	while(t--){
		cin >> n >> m >> k;
		for(int i=0; i<n; i++)
			cin >> h[i];
		
		for(int i=0; i<n; i++)
			cin >> x[i];

		ll l=0, r=1e9, md;
		while(r-l>1){
			md = (l+r)>>1;
		
			if(chk(md)) r=md;
			else l=md;
		}

		if(!chk(r)) cout << -1 << endl;
		else cout << r << endl;

	}

	return 0;
}
