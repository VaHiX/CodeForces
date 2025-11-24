// Problem: CF 1693 F - I Might Be Wrong
// https://codeforces.com/contest/1693/problem/F

/*
Algorithm: Greedy + Prefix Sum
Time Complexity: O(n) per test case
Space Complexity: O(n) for prefix array

Approach:
1. First, check if string is already sorted. If so, return 0.
2. Count number of 0s and 1s. If 0s are more than 1s, reverse string and toggle all bits (this makes problem symmetric).
3. Use prefix sum technique to track cumulative imbalance between 0s and 1s.
4. Find the minimum operations needed to sort the string greedily by tracking how many times we need to "fix" imbalance.
5. The key idea is that we try to group all the 0s at the beginning and 1s at the end by performing smart swaps.

Key Variables:
- x: count of 0s
- y: count of 1s
- p: prefix array to store maximum position for each cumulative imbalance
- t: tracking current position in the prefix
- c: operation counter
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <utility>

using namespace std;
int const N = 200010;
int t, n, p[N];
string s;
int main() {
  ios::sync_with_stdio(0);
  for (cin >> t; t--;) {
    cin >> n >> s;
    if (is_sorted(s.begin(), s.end())) {  // If already sorted, no operations needed
      cout << "0\n";
      continue;
    }
    int x = count(s.begin(), s.end(), 48), y = n - x;  // Count 0s and 1s
    if (x < y) {  // Make sure 0s are not more than 1s to simplify logic
      swap(x, y), reverse(s.begin(), s.end());
      for (char &i : s)
        i ^= 1;  // Toggle all bits
    }
    for (int i = 0, j = 0; i < n; i++)
      j += s[i] & 1 ? -1 : 1, j >= 0 && (p[j] = i);  // Build prefix array of max positions for imbalance
    int t = 0, c = 1;  // Initialize counters
    while (~s[t] & 1)  // While current character is '1', advance
      t++;
    while (t < x - y)  // Continue until imbalance is resolved
      c++, t += (p[t] - t + 1) / 2;  // Increment operations and move pointer
    cout << c << "\n";
  }
}


// https://github.com/VaHiX/CodeForces/