/*
 * Problem URL : https://codeforces.com/contest/2135/problem/D2
 * Submit Date : 2025-08-30
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;

#define all(x)      (x).begin(),(x).end()
#define X           first
#define Y           second
#define sep         ' '
// #define endl        '\n'
#define SZ(x)       ll(x.size())

const ll M = 15400;
const ll N = 1e5;
const ll K = 125;
const ll T = 12;
const ll LOG = 22;
const ll INF = 8e18;
const ll MOD = 1e9 + 7; //998244353; //1e9 + 9;

int q;

int main() {
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);

    cin >> q;
    while(q--){
        ll sz = N / K * T;
        cout << "? " << sz << " ";
        for(int i = 0; i < T * N / K; i++){
            cout << K << sep;
        }
        cout << endl;
        int x; cin >> x;
        if(x == 0){
            cout << "? " << M << " ";
            for(int i = 1; i <= M; i++){
                cout << 1 << sep;
            }
            cout << endl;
            cin >> x;
            cout << "! " << (M + x - 1) / x << endl;
            continue;
        }
        if(x == T){
            cout << "! " << N << endl;
            continue;
        }
        int L = (sz + x - 1) / x * K, R = (sz - 1) / (x - 1) * K + K - 1;
        if(L == R){
            cout << "! " << L << endl;
            continue;
        }
        cout << "? " << 2 * (R - L) << " ";
        for(int i = L + 1; i <= R; i++){
            cout << L << sep << i - L << sep;
        }
        cout << endl;
        cin >> x;
        cout << "! " << R - x + (R - L) << endl;
    }

    return 0;
}
/*

*/
