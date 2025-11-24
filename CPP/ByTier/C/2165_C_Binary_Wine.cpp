// Problem: CF 2165 C - Binary Wine
// https://codeforces.com/contest/2165/problem/C

/*
 * Problem: Binary Wine
 * 
 * Purpose: For each query with a target XOR value 'c', find the minimum number of coins to spend
 *          to adjust the array such that there exists a subsequence with XOR equal to 'c'.
 * 
 * Algorithm:
 * - For each query, we try to construct a valid sequence b such that XOR of all b[i] equals c.
 * - We process the array from largest to smallest elements (sorted).
 * - For each bit position k (from 29 down to 0):
 *   - If the current target bit is set in c, we try to make that bit set in our final XOR.
 *   - If the largest available number has that bit set, we subtract it.
 *   - Otherwise, we calculate the cost to make it set and add that to output.
 * 
 * Time Complexity: O(n * log(max(a[i])) + q * 30) = O(n * 30 + q * 30) = O(n + q)
 * Space Complexity: O(n + q) for input and auxiliary storage.
 */
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;
long long a, b, c, d, as[500001], out, e;
priority_queue<long long> bs;
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> a;
  for (int i = 1; i <= a; i++) {
    cin >> b >> c;  // b = n, c = q
    for (int j = 1; j <= b; j++) {
      cin >> as[j];  // read array a
    }
    sort(as + 1, as + b + 1);  // sort array in ascending order
    for (int j = 1; j <= c; j++) {
      cin >> d;  // read query target XOR value
      out = 0;  // total coins required for this query
      for (; bs.size(); bs.pop())  // clear the priority queue
        ;
      // Push last 30 elements (or all if less than 30) to make sure we have enough to work with
      for (int k = b; k >= max(1ll, b - 30); k--)
        bs.push(as[k]);
      
      // Process each bit from MSB to LSB (up to 30)
      for (int k = 29; k >= 0; k--) {
        // If the current element is already >= d, we can't improve
        if (bs.top() >= d)
          break;
        // If the k-th bit of d is set
        if ((1ll << k) & d) {
          e = bs.top();
          bs.pop();
          // If e has k-th bit set, subtract it
          if (e >= (1ll << k)) {
            e -= 1ll << k;
            bs.push(e);
          } else {
            // Otherwise, we must add (1 << k) - e coins to set the bit
            out += (1ll << k) - e;
            bs.push(0);
          }
          d -= 1ll << k;  // Remove this bit from d
        }
      }
      cout << out << '\n';
    }
  }
}


// https://github.com/VaHiX/CodeForces/