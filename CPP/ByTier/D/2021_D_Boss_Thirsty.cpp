/*
 * Problem URL : https://codeforces.com/contest/2021/problem/D
 * Submit Date : 2025-09-10
 */

#include <bits/stdc++.h>

using namespace std;

void doWork() {

    int n, m;
    cin >> n >> m;
    vector<long long> a(m), dp(m+1,-1e15), ndp(m+1);
    for(int i = 0; i < n; i++) {
        for(auto &x:a)    cin >> x;
        fill(ndp.begin(), ndp.end(), -1e15);
        for(int f = 0; f < 2; f++) {
            long long maxDP = -1e15;
            long long maxSum = -1e15;
            for(int j = 0; j < m; j++) {
                maxDP=max(maxDP, i?dp[j]+maxSum:0ll);
                maxSum=max(maxSum,0ll);
                maxDP+=a[j];
                maxSum+=a[j];
                ndp[j+1]=max(ndp[j+1], maxDP);
            }
            
            reverse(a.begin(),a.end());
            reverse(dp.begin(),dp.end());
            reverse(ndp.begin(),ndp.end());
        }
        swap(dp,ndp);
    }
    cout<<*max_element(dp.begin(),dp.end())<<endl;
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
	cin >> t;
	while(t--) doWork();	
	
}