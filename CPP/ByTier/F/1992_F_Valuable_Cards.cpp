// Problem: CF 1992 F - Valuable Cards
// https://codeforces.com/contest/1992/problem/F

/*
Purpose: This code solves the problem of partitioning an array of integers into the minimum number of "bad segments".
         A segment is bad if no subset of its elements can multiply to form a given value x.
         The solution uses a dynamic programming approach with a divisibility-based check.

Algorithms/Techniques:
- Preprocessing all divisors of x in descending order
- Dynamic Programming with a boolean array `f` to track which values are reachable
- Segment-based partitioning where a new segment starts when a valid product is found

Time Complexity: O(n * d(x) + d(x) * log(d(x))) where d(x) is the number of divisors of x
Space Complexity: O(d(x)) for storing the divisors and the boolean array f

*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
const int N = 100009;
int a[N];
bool f[N];

void solve() {
  int n, x;
  cin >> n >> x;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  
  // Find all divisors of x and store them in descending order
  vector<int> d;
  for (int i = 1; i * i <= x; i++) {
    if (x % i != 0)
      continue;
    if (i * i != x)
      d.push_back(x / i);
    d.push_back(i);
  }
  sort(d.rbegin(), d.rend());
  
  // Initialize the boolean array f
  for (auto i : d)
    f[i] = 0;
  f[1] = 1; // Base case: 1 can always be formed

  int res = 1; // Minimum number of segments starts with 1
  
  for (int i = 1; i <= n; i++) {
    // Skip invalid elements (less than 2 or not a divisor of x)
    if (a[i] < 2 || x % a[i] != 0)
      continue;
    
    // Update reachable values by extending existing reachable values with a[i]
    for (auto j : d) {
      if ((ll)j * a[i] <= x)
        f[j * a[i]] |= f[j];
    }
    
    // If x is reachable, start a new segment
    if (f[x]) {
      for (auto j : d)
        f[j] = 0; // Reset the boolean array
      f[1] = f[a[i]] = 1; // Mark 1 and a[i] as reachable
      res++; // Increment the segment count
    }
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--)
    solve();
}


// https://github.com/VaHiX/CodeForces/