// Problem: CF 1690 E - Price Maximization
// https://codeforces.com/contest/1690/problem/E

/*
 * Problem: E. Price Maximization
 * 
 * Purpose: To maximize the total cost of packages formed by pairing goods,
 * where the cost of a package with weight x is floor(x/k).
 * 
 * Algorithm:
 * 1. For each good, calculate how much "base" cost it contributes (a[i]/k)
 * 2. Store the remainder (a[i] % k) of each good in an array
 * 3. Sort the remainders
 * 4. Use two pointers to greedily pair remainders such that their sum >= k
 *    - If sum < k, move the left pointer to increase sum
 *    - If sum >= k, we can form a package with full cost, increment result
 * 
 * Time Complexity: O(n log n) due to sorting
 * Space Complexity: O(n) for storing the remainders
 */
#include <algorithm>
#include <iostream>

using namespace std;
#define ll long long
int main() {
  int t;
  cin >> t;
  while (t--) {
    ll x, n, k, m = 0;
    cin >> n >> k;
    ll a[n];
    for (int i = 0; i < n; i++) {
      cin >> x;
      if (x / k) // Add base cost if it's non-zero
        m += x / k;
      a[i] = x % k; // Store remainder
    }
    sort(a, a + n); // Sort remainders
    ll i = 0, j = n - 1;
    while (i < j) {
      if (a[i] + a[j] < k) // If sum is less than k, move left pointer
        i++;
      else {
        i++; // Move both pointers
        j--;
        m++; // Increment cost as we can form a full package
      }
    }
    cout << m << endl;
  }
}


// https://github.com/VaHiX/CodeForces/