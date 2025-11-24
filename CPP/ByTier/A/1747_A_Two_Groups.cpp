// Problem: CF 1747 A - Two Groups
// https://codeforces.com/contest/1747/problem/A

#include <bits/std_abs.h>
#include <iostream>

using namespace std;
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    int a;
    long long int c = 0; // Sum of all elements in the array
    for (int i = 0; i < n; i++) {
      cin >> a;
      c += a; // Accumulate total sum
    }
    cout << abs(c) << endl; // Maximum possible value is absolute value of total sum
  }
}
/*
Algorithm/Technique: Greedy approach
Time Complexity: O(n) where n is the number of elements in the array
Space Complexity: O(1) - only using a constant amount of extra space

The problem asks to maximize |sum(s1)| - |sum(s2)|.
To maximize this difference, we want one group to have as large a positive sum as possible, 
and the other group to have as small (or large negative) a sum as possible.

The key insight is that if we take all elements in one group (s1), and leave the other empty (s2),
then |sum(s1)| - |sum(s2)| = |total_sum| - 0 = |total_sum|.
Thus, the maximum value is simply the absolute value of the sum of all elements.
*/

// https://github.com/VaHiX/codeForces/