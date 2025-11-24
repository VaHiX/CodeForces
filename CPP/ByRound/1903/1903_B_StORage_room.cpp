// Problem: CF 1903 B - StORage room
// https://codeforces.com/contest/1903/problem/B

/*
 * Problem: B. StORage room
 * 
 * Algorithm/Technique: 
 *   - For each row in the matrix M, compute the bitwise AND of all values M[i][j] where j != i.
 *     This gives us a candidate value for a[i] since a[i] | a[j] = M[i][j], so a[i] must be a 
 *     submask of M[i][j] for all j != i. Using bitwise AND ensures we get the maximum possible
 *     value for a[i] that satisfies all constraints.
 *   - Then validate the solution by checking that a[i] | a[j] = M[i][j] for all pairs.
 * 
 * Time Complexity: O(n^2) per test case
 *   - Preprocessing step: O(n^2) to compute a[i] for all i
 *   - Validation step: O(n^2) to check all pairs
 * 
 * Space Complexity: O(n^2) for storing the matrix M and O(n) for the array a
 * 
 * Input:
 *   - t: number of test cases
 *   - For each test case:
 *     - n: size of the matrix
 *     - n rows of n integers representing the matrix M
 * 
 * Output:
 *   - YES followed by n integers (the array a), if a solution exists
 *   - NO if no solution exists
 */

#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    std::vector<std::vector<ll>> M(n, std::vector<ll>(n, 0));
    std::vector<ll> a(n, 0);
    for (ll row = 0; row < n; row++) {
      ll tmp((1LL << 30) - 1);  // Initial value: all bits set to 1
      for (ll col = 0; col < n; col++) {
        ll x;
        scanf("%lld", &x);
        M[row][col] = x;
        if (col == row) {
          continue;
        }
        tmp = tmp & x;  // Bitwise AND to find common bits in all M[i][j] for j != i
      }
      a[row] = tmp;  // Assign computed value to a[i]
    }
    bool possible(true);
    for (ll row = 0; possible && row < n; row++) {
      for (ll col = 0; possible && col < n; col++) {
        if (row == col) {
          continue;
        }
        if ((a[row] | a[col]) != M[row][col]) {  // Validate a[i] | a[j] = M[i][j]
          possible = false;
        }
      }
    }
    if (possible) {
      puts("YES");
      for (ll p = 0; p < n; p++) {
        printf("%lld ", a[p]);
      }
      puts("");
    } else {
      puts("NO");
    }
  }
}


// https://github.com/VaHiX/CodeForces/