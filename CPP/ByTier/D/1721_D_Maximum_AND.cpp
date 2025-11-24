// Problem: CF 1721 D - Maximum AND
// https://codeforces.com/contest/1721/problem/D

/*
Purpose: This code finds the maximum possible value of the bitwise AND of XORs of elements from two arrays,
         when the second array can be reordered arbitrarily.

Algorithm:
- The idea is to try to maximize the result bit by bit from the most significant bit (MSB) to least significant bit (LSB).
- For each bit position k (from 30 down to 0), we check if it's possible to set that bit to 1 in the final result.
- To do this, we simulate what happens if we set all bits from k down to 0 to 1 (i.e., we look at the mask `ans = (1 << k) - 1 | (1 << k)`).
- We count how many times each prefix (a[i] & ans) appears and how many times each (b[i] & ans) would negate it.
- If the counts do not balance out to zero, then it's impossible to have bit k set to 1, so we reset the bit to 0.

Time Complexity: O(31 * n) = O(n) per test case, since we loop through 31 bits and for each bit we process n elements.
Space Complexity: O(n) for the map used to store counts.
*/

#include <iostream>
#include <map>
#include <utility>

using namespace std;
int t, n, a[200005], b[200005], ans;
int main() {
  cin >> t;
  while (t--) {
    ans = 0;
    cin >> n;
    for (int i = 1; i <= n; i++)
      cin >> a[i];
    for (int i = 1; i <= n; i++)
      cin >> b[i];
    for (int k = 30; k >= 0; k--) {
      map<int, int> f;
      ans += (1 << k); // Try setting the k-th bit to 1 (we do this by adding 1 << k to ans)
      for (int i = 1; i <= n; i++)
        f[a[i] & ans]++, f[~b[i] & ans]--; // Count occurrences of (a[i] & ans) and subtract (b[i] & ans)
      for (auto p : f)
        if (p.second != 0) { // If there exists a value with a non-zero balance, then this bit cannot be set to 1
          ans -= (1 << k); // Reset this bit back to 0
          break;
        }
    }
    cout << ans << endl;
  }
}


// https://github.com/VaHiX/CodeForces/