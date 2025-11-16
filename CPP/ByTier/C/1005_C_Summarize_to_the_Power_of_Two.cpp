// Problem: CF 1005 C - Summarize to the Power of Two
// https://codeforces.com/contest/1005/problem/C

/*
Algorithm: 
- For each unique element in the sequence, we check whether it can form a power-of-two sum with another element.
- We use a map to count the frequency of each element.
- For each element x, we iterate through all possible powers of 2 (up to 3e9), and check if there exists another element (x or different) such that x + y = 2^d.
- If such an element exists, we reduce the number of elements to be removed.
- Time Complexity: O(n * log(max_a)), where n is the number of elements and max_a is the maximum element in the array (due to the power-of-two loop up to 3e9).
- Space Complexity: O(n), for storing the frequency map.
*/

#include <cstdio>
#include <map>
#include <utility>
#include <utility>

typedef long long ll;
int main() {
  ll n;
  scanf("%lld", &n);
  std::map<ll, ll> m;  // Map to store frequency of each element
  ll rem(0);  // Variable to track the number of elements to remove
  for (ll p = 0; p < n; p++) {
    ll x;
    scanf("%lld", &x);
    ++m[x];  // Increment frequency of x
  }
  for (std::map<ll, ll>::iterator it = m.begin(); it != m.end(); it++) {
    ll x = it->first;   // Current element
    ll cnt = it->second; // Frequency of current element
    rem += cnt;  // Initially assume we will remove all occurrences of x
    for (ll w = 1; w < 3e9; w *= 2) {  // Iterate over powers of 2
      if ((w > x) && m.count(w - x) && m[w - x] >= 1 + (w == 2 * x)) {
        // Check if w - x exists and sufficient count (at least 1, or 2 if x == w/2)
        rem -= cnt;  // If valid, we don't need to remove all instances of x
        break;       // No need to check further powers
      }
    }
  }
  printf("%lld\n", rem);  // Print minimum number of elements to be removed
  return 0;
}


// https://github.com/VaHiX/CodeForces/