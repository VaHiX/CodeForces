/*
 * Problem URL : https://codeforces.com/contest/668/problem/A
 * Submit Date : 2025-09-04
 */

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e2+4;
const int inf = 1e9;
const int mod = 1e9+7;

int n,m,q;
pair<int,int> lab[N][N];
int ans[N][N];

void go(){
	cin >> n >> m >> q;

	for (int i=1; i<=n; i++) for (int j=1; j<=m; j++) lab[i][j] = {i, j};

	while (q--){
		int t,a,b,c;
		cin >> t >> a;
		if (t == 1)
			for (int j=1; j<m; j++) swap(lab[a][j], lab[a][j+1]);
		if (t == 2)
			for (int i=1; i<n; i++) swap(lab[i][a], lab[i+1][a]);
		if (t == 3){
			cin >> b >> c;
			ans[lab[a][b].first][lab[a][b].second] = c;
		}
	}

	for (int i=1; i<=n; i++){
		for (int j=1; j<=m; j++) cout << ans[i][j] << " ";
		cout << "\n";
	}
}
 
int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
 
	int T = 1;
	// cin >> T;
	for (int i=1; i<=T; i++) go();
 
	return 0;
}