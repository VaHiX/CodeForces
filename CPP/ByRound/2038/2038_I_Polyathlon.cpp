/*
 * Problem URL : https://codeforces.com/contest/2038/problem/I
 * Submit Date : 2025-08-30
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 1, M = 1e6 + 1;
int n, m;

int main(){
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	
	cin >> n >> m;
	string s[n];
	for(int i = 0;i < n;i++){
		cin >> s[i];
		s[i] += s[i];
	}
	vector<int> f(n), g;
	int ans[2 * m];
	for(int i = 0;i < n;i++) f[i] = i + 1;
	for(int i = 2 * m - 1;i >= 0;i--){
		for(int &j : f) if(s[j - 1][i] == '1') g.push_back(j);
		for(int &j : f) if(s[j - 1][i] == '0') g.push_back(j);
		f = g; g.clear();
		ans[i] = f[0];
	}
	for(int i = 0;i < m;i++) cout << ans[i] << " ";
	
	return 0;
}