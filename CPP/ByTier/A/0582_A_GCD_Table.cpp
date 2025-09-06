/*
 * Problem URL : https://codeforces.com/contest/582/problem/A
 * Submit Date : 2025-09-04
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int n;
	cin >> n;
	map<int, int> arr;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j) {
			int a;
			cin >> a;
			arr[a]++;
		}
	vector<int> sol;
	for(auto it = arr.rbegin(); it != arr.rend(); ++it) {
		while(it->second) {
			for(auto x : sol)
				arr[__gcd(x, it->first)] -= 2;
			sol.push_back(it->first);
			it->second--;
		}
	}
	for(auto x : sol)
		cout << x << ' ';
	return 0;
}
