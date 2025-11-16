// Problem: CF 825 C - Multi-judge Solving
// https://codeforces.com/contest/825/problem/C

/*
 * Problem: C. Multi-judge Solving
 * 
 * Purpose: 
 *   Given a list of problem difficulties to solve on Decoforces and a starting difficulty k,
 *   determine the minimum number of additional problems that must be solved on other judges
 *   to be able to solve all problems in the list in order.
 * 
 * Algorithm:
 *   - Sort the problem difficulties in ascending order.
 *   - For each problem, calculate the minimum required difficulty to solve it.
 *     This is computed as (a[i] / 2) + (a[i] % 2), which is equivalent to ceil(a[i] / 2).
 *   - If current difficulty 'm' is sufficient, update 'm' to be the maximum of 'm' and 'a[i]'.
 *   - Otherwise, keep increasing 'm' by doubling it until it is sufficient,
 *     counting how many times we had to double.
 * 
 * Time Complexity: O(n log n) due to sorting
 * Space Complexity: O(n) for storing the array of difficulties
 */

#include <algorithm>
#include <iostream>

typedef long long int ll;
#define pp pair<int, int>
#define dbg printf("in\n");
#define NL printf("\n");
#define inf 1000000000000
using namespace std;

int main() {
  ll i, j, k;
  ll n, m, req;
  cin >> n >> m;  // n: number of problems, m: current max difficulty
  ll a[n];        // Array to store problem difficulties
  for (i = 0; i < n; i++)
    cin >> a[i];
  sort(a, a + n);  // Sort difficulties in ascending order to process in order

  ll count = 0;  // Count of additional problems needed
  for (i = 0; i < n; i++) {
    req = (a[i] % 2) + (a[i] / 2);  // Minimum required difficulty to solve problem i
    if (m >= req) {
      m = max(m, a[i]);  // If current difficulty is enough, update max difficulty
    } else {
      // While not enough, double the difficulty and count one extra problem
      while (req > m) {
        count++;
        m *= 2;
      }
      m = max(m, a[i]);  // Update max difficulty after solving extra problem
    }
  }
  cout << count;
  return 0;
}


// https://github.com/VaHiX/CodeForces/