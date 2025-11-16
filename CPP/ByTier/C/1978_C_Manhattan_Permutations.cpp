// Problem: CF 1978 C - Manhattan Permutations
// https://codeforces.com/contest/1978/problem/C

/*
 * Problem: C. Manhattan Permutations
 * 
 * Purpose: Given integers n and k, find a permutation of length n such that its Manhattan value equals k,
 *          or determine that no such permutation exists.
 * 
 * Approach:
 * - The Manhattan value is defined as the sum of absolute differences between each element and its index.
 * - For any permutation, the minimum Manhattan value is 0 (when the permutation is sorted).
 * - The maximum possible Manhattan value can be calculated as the sum of all possible displacements.
 * - For a sequence 1..n, the maximum Manhattan value is achieved when elements are placed as far as possible from their indices.
 * - We use a greedy strategy to construct a valid permutation:
 *   - Start from index 0, and greedily place elements to achieve desired k.
 *   - We use pairs to swap elements to achieve the required Manhattan value.
 * 
 * Time Complexity: O(n) - Each element is processed once.
 * Space Complexity: O(n) - A vector of size n is used to store the permutation.
 */

#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <vector>

#define ll long long
#define ff first
#define ss second
#define pb push_back
#define fi(i, n) for (int i = 0; i < n; i++)
#define fia(i, a, n, b) for (int i = a; i < n; i += b)
#define fd(i, n) for (int i = n; i >= 0; i--)
#define fda(i, n, a, b) for (int i = n; i >= a; i -= b)
#define vi vector<int>
#define vc vector<char>
#define vvi vector<vector<int>>
#define vvc vector<vector<char>>
#define mii map<int, int>
#define cinv(v)                                                                \
  for (int i = 0; i < v.size(); i++) {                                         \
    cin >> v[i];                                                               \
  }
#define sortv(v) sort(v.begin(), v.end());
#define cin(x) cin >> x
#define co(x) cout << x
#define coe(x) cout << x << endl
using namespace std;
const ll mod = 1e9 + 7;
void YESNO(bool b) {
  if (b)
    cout << "YES";
  else
    cout << "NO";
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  int t;
  cin >> t;
  while (t--) {
    ll n, k;
    cin >> n >> k;
    if (k & 1) // If k is odd, it's impossible to achieve with any permutation (because all swaps contribute even values)
      coe("NO");
    else {
      vi v(n, 0); // Vector to store the result permutation
      ll mj = n - 1; // Maximum possible index to place values
      for (int i = 0; i < n; i++) {
        if (v[i] == 0) { // If current index is not yet assigned
          ll jmp = min(k / 2, mj - i * 2); 
          // Calculate how many positions to jump and update Manhattan cost
          v[i] = i + 1 + jmp; // Place element at i+jmp-th position
          v[i + jmp] = i + 1; // Place element at i-th position
          k -= (jmp * 2); // Reduce k by the displacement cost
          if (k == 0) { // If k is completely utilized, break
            break;
          }
        }
      }
      if (k != 0) // If k is not completely used
        coe("NO");
      else {
        fi(i, n) {
          if (v[i] == 0) { // Fill unused positions with identity mapping
            v[i] = i + 1;
          }
        }
        coe("YES");
        fi(i, n) { co(v[i] << " "); } // Output the permutation
        coe("");
      }
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/