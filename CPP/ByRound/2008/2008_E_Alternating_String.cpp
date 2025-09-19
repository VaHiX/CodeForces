/*
 * Problem URL : https://codeforces.com/contest/2008/problem/E
 * Submit Date : 2025-09-13
 */

#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		string s;
		cin >> s;
		int ans = n;
		int cnt[2][26] {};
		for(int i = 0 ; i < n; i++){
			cnt[i % 2][s[i] - 'a']++;
		}
		if(n % 2 == 0){
			ans = n - *max_element(cnt[0], cnt[0] + 26) - *max_element(cnt[1], cnt[1] + 26);
		}else{
			for(int i = n - 1; i >= 0; i--){
				cnt[i % 2][s[i] - 'a']--;
				ans = min(ans, n - *max_element(cnt[0], cnt[0] + 26) - *max_element(cnt[1], cnt[1] + 26));
				cnt[(i + 1) % 2][s[i] - 'a']++;
			}
		}
		cout << ans << "\n";
	}
}
