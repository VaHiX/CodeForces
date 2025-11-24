// Problem: CF 2048 D - Kevin and Competition Memories
// https://codeforces.com/contest/2048/problem/D

/*
D. Kevin and Competition Memories
Algorithm: This solution uses sorting and binary search to determine for each k,
           how many participants solve more problems than Kevin in each contest.
           It then computes the minimum sum of ranks over all contests for each k.

Time Complexity: O(n log n + m log m + m^2)
Space Complexity: O(n + m)

Approach:
- For each k from 1 to m:
  - Sort difficulties of problems
  - For each problem difficulty, count how many participants solve it (>= difficulty)
  - Distribute problems into contests optimally such that Kevin's rank is minimized
  - Compute contribution of ranks based on divisors of k
*/

#include <algorithm>
#include <iostream>

using namespace std;
const int N = 3e5 + 2;
int T, n, m, c, a[N], b[N];

int main() {
  cin.tie(0)->sync_with_stdio(0);
  for (cin >> T; T--;) {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
      cin >> a[i];
    c = a[1]; // Kevin's rating
    sort(a + 1, a + n + 1); // Sort participants by rating
    
    // For each problem, calculate number of people who can solve it
    for (int i = 1, x; i <= m; ++i) {
      cin >> x;
      if (x <= c || x > a[n])
        b[i] = 0; // No one solves it or everyone solves it
      else
        b[i] = a + n + 1 - lower_bound(a + 1, a + n + 1, x); // Count people who can solve problem with difficulty x
    }
    
    sort(b + 1, b + m + 1); // Sort the counts
    
    // For each k from 1 to m, compute minimum rank sum
    for (int i = 1; i <= m; ++i) {
      long long ans = m / i; // Number of contests is floor(m/i)
      for (int j = i; j <= m; j += i)
        ans += b[j]; // Add number of people solving fewer problems than Kevin
      cout << ans << " \n"[i == m]; // Output result
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/