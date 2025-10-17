// Problem: CF 1969 F - Card Pairing
// https://codeforces.com/contest/1969/problem/F

/*
Algorithm: Rolling Hash + Dynamic Programming with State Optimization
Time Complexity: O(N^2 * K) where N is the number of cards and K is the number of types.
Space Complexity: O(N * K) for storing hash values and DP states.

This code solves the Card Pairing problem using a combination of rolling hash techniques and dynamic programming.
It calculates the maximum number of coins achievable by optimally choosing pairs of cards during gameplay.
*/
#include <string.h>
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using namespace std;
#define endl '\n'
mt19937_64 rnd(12341234);
const int INF = 1e9, MAXN = 1e3 + 5;
int N, K;
long long h;
int deck[MAXN], freq[MAXN];
long long vals[MAXN], phs[MAXN];
vector<int> dp;
bool flag;
int get_state(int pos, long long h) {
  // Check if the given hash exists in the prefix hash array starting from pos
  for (int i = pos; i < N; i += 2) {
    if (phs[i] == h)
      return i;
  }
  return -1;
}
vector<int> suffix_parity(int pos) {
  // Calculates parity (odd/even count) of card types in suffix from pos onwards
  vector<int> res(K, 0);
  for (int i = pos; i < N; i++) {
    res[deck[i]] ^= 1;
  }
  return res;
}
void solve() {
  cin >> N >> K;
  memset(freq, 0, sizeof(freq));
  dp.assign(N, INF);
  for (int i = 0; i < N; i++) {
    cin >> deck[i];
    deck[i]--; // Convert to 0-based index
    freq[deck[i]]++;
  }
  int max_score = 0;
  h = 0;
  for (int i = 0; i < K; i++) {
    vals[i] = rnd(); // Assign random hash values to each card type
    max_score += freq[i] / 2; // Initial score based on pairs possible
  }
  for (int i = 0; i < N; i++) {
    h ^= vals[deck[i]]; // Compute rolling hash of deck
    phs[i] = h;
  }
  h = 0;
  for (int i = 0; i < K; i++)
    h ^= vals[i]; // Hash of initial K cards drawn
  int pos = get_state(K - 1, h);
  if (pos == -1) {
    // If no matching state, optimal play yields the base score
    cout << max_score << endl;
    return;
  }
  int ans = INF;
  dp[pos] = 0; // Initialize DP at starting position
  for (int k = K - 1; k < N; k += 2) {
    vector<int> spar = suffix_parity(k + 1), even, odd;
    // Separate card types based on whether they appear an odd or even number of times after position k
    for (int i = 0; i < K; i++) {
      if (spar[i]) {
        odd.push_back(i);
      } else {
        even.push_back(i);
      }
    }
    int es = even.size(), os = odd.size();
    flag = true;
    // Process pairs from odd counts (both need to pair with another odd card)
    for (int i = 0; i < os && flag; i++) {
      for (int j = 0; j < i && flag; j++) {
        int x = odd[i], y = odd[j];
        int add = 2; // Cost to pair two odd cards
        long long hlook = phs[k] ^ vals[x] ^ vals[y]; // Hash of new position after pairing
        int pos = get_state(k, hlook);
        if (pos == -1) {
          flag = false;
          ans = min(ans, dp[k] + add);
        } else {
          dp[pos] = min(dp[pos], dp[k] + add);
        }
      }
    }
    flag = true;
    // Process pairs from even counts (no gain in pairing even cards)
    for (int i = 0; i < es && flag; i++) {
      for (int j = 0; j < i && flag; j++) {
        int x = even[i], y = even[j];
        int add = 0; // No cost for pairing even cards
        long long hlook = phs[k] ^ vals[x] ^ vals[y];
        int pos = get_state(k, hlook);
        if (pos == -1) {
          flag = false;
          ans = min(ans, dp[k] + add);
        } else {
          dp[pos] = min(dp[pos], dp[k] + add);
        }
      }
    }
    flag = true;
    // Process pairs between odd and even counts (cost of 1 coin)
    for (int i = 0; i < os && flag; i++) {
      for (int j = 0; j < es && flag; j++) {
        int x = odd[i], y = even[j];
        int add = 1;
        long long hlook = phs[k] ^ vals[x] ^ vals[y];
        int pos = get_state(k, hlook);
        if (pos == -1) {
          flag = false;
          ans = min(ans, dp[k] + add);
        } else {
          dp[pos] = min(dp[pos], dp[k] + add);
        }
      }
    }
  }
  // Output the difference between maximum possible and minimal extra cost
  cout << max_score - ans << endl;
  return;
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/