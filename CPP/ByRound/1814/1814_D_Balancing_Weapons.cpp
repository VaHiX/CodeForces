// Problem: CF 1814 D - Balancing Weapons
// https://codeforces.com/contest/1814/problem/D

/*
Algorithm/Technique:
The problem revolves around balancing weapon firepowers by adjusting the damage
values of guns. The approach uses a sweeping technique with coordinate
compression and difference arrays to efficiently compute the minimum number of
guns requiring changes. It checks for all possible target firepowers and
determines the minimal number of guns to change to achieve a balanced state.

Time Complexity: O(n * max_f * log(max_f)) where max_f is the maximum fire rate
(<= 2000) Space Complexity: O(max_f) for storing auxiliary arrays and tracking
changes
*/

#include <algorithm>
#include <iostream>
#include <random>
#include <stddef.h>
#include <utility>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
#define fi first
#define se second
const int MAXN = 3007;
const int offset = 1502;
int n, k;
ll a[MAXN];
ll coef[MAXN];
int ch[2 * MAXN];
int hh[2 * MAXN];
bool fl[MAXN];
int bad[2 * MAXN];

void solve() {
  cin >> n >> k;
  ll mxval = 0;
  for (int i = 0; i <= 2000; ++i) {
    fl[i] = false;
  }
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    fl[a[i]] = true; // Mark which fire rates exist
    mxval = max(mxval, a[i]);
  }
  for (int i = 1; i <= n; ++i) {
    cin >> coef[i];
  }
  int ans = n;
  for (int i = 1; i <= n; ++i) {
    // Reset arrays for each iteration
    for (int j = 0; j < MAXN; ++j) {
      ch[j] = hh[j] = 0;
      bad[j] = false;
    }
    // Calculate initial firepower of current gun
    ll init = a[i] * coef[i];
    // Process all fire rates from k+2 up to 2000
    for (int val = k + 2; val <= 2000; ++val) {
      if (fl[val] == false) {
        continue; // Skip if this fire rate doesn't exist
      }
      ll x = init;
      while (1) {
        // Find the largest multiple of 'val' less than or equal to 'x'
        ll lst = (x / val) * val;
        ll st = lst + 1, en = lst + val;
        // Adjust the interval based on k bounds
        if (st < init - k) {
          st = init - k;
        }
        if (en > init + k + 1) {
          en = init + k + 1;
        }
        en -= k;
        if (st <= en) {
          bad[offset + (st - init)] += 1; // Mark start of range with +1
          bad[offset + (en - init)] -= 1; // Mark end of range with -1
        }
        x = lst - 1;
        if (x <= 0 || x < init - k) {
          break; // Stop if we've covered all valid ranges
        }
      }
    }
    // Handle values below init - k
    if (init < mxval) {
      bad[0] += 1;
      if (mxval - init <= k) {
        bad[offset + (mxval - init) - k] -= 1;
      }
    }
    // Account for guns whose firepower falls within range [init-k, init+k]
    for (int j = 1; j <= n; ++j) {
      ll aux = a[j] * coef[j];
      if (init - k <= aux && aux <= init + k) {
        // Adjust relative positions for the difference array
        ll rel = aux - init;
        int st = rel - k;
        int en = rel;
        st = max(st, -k);
        en = min(en, k);
        ++ch[offset + st];
        --ch[offset + en + 1];
      }
    }
    int sm = 0, cnt = 0;
    for (int j = 0; j <= offset; ++j) {
      sm += ch[j];
      cnt += bad[j];
      // If no conflicts (cnt == 0), and no changes (sm > 0), update minimum
      if (cnt == 0 && sm > 0) {
        ans = min(ans, n - sm);
      }
    }
  }
  cout << ans << "\n";
}

int main() {
  ios_base ::sync_with_stdio(false);
  cin.tie(NULL);
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}

// https://github.com/VaHiX/CodeForces/