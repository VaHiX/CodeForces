/*
 * Problem URL : https://codeforces.com/contest/2039/problem/F1
 * Submit Date : 2025-08-30
 */

#include <bits/stdc++.h>
#define ll long long
#define vt vector
#define pb push_back
#define mp make_pair
using namespace std;

int fastexp(int b, int e, int mod){
	int ans = 1;
	while(e){
		if(e&1) ans = (1ll*ans*b)%mod;
		b = (1ll*b*b)%mod;
		e >>= 1;
	}
	return ans;
}
 
int gcd(int a, int b){
	if(b == 0) return a;
	else return gcd(b,a%b);
}

const int N = 1e5+1;
const int mod = 998244353;
const int INF = 2e9;
const ll INFLL = 2e18;

vt<int> factors[N];
ll dp_mobius_sum[N], dp_multiple_sum[N], temp[N], ans[N];

void precomp(){
	for(int i = 1; i < N; i++){
		for(int j = i; j < N; j += i) factors[j].pb(i);
	}
	for(int i = 1; i < N; i++){
		for(int j : factors[i]){
			for(int k : factors[j]) temp[j] += dp_mobius_sum[k];
			temp[j] -= dp_multiple_sum[j];
			temp[j] *= 2; temp[j]++;
			temp[j] %= mod;
			if(temp[j] < 0) temp[j] += mod;
			dp_multiple_sum[j] += temp[j];
		}
		ans[i] = (temp[i] + ans[i-1]) % mod;
		for(int j : factors[i]){
			for(int k = factors[j].size() - 2; k >= 0; k--) temp[j] += (mod-temp[factors[j][k]]);
			temp[j] %= mod;
			dp_mobius_sum[j] += temp[j];
		}
		for(int j : factors[i]) temp[j] = 0;
	}
}

void solve(){
	int n;
	cin >> n;
	cout << ans[n] << "\n";
}

int main()
{
	// srand(time(NULL));
	// freopen("boysgirls.in","r",stdin);
	// freopen("boysgirls.out","w",stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	precomp();

	int t = 1;
	cin >> t;

	for(int tc = 1; tc <= t; tc++){
		// cout << "Case #" << tc << ": ";
		solve();
	}
	return 0;
}