// Problem: CF 2134 B - Add 0 or K
// https://codeforces.com/contest/2134/problem/B

/*
B. Add 0 or K
time limit per test1.5 seconds
memory limit per test256 megabytes

Algorithms/Techniques: Greedy approach
  - For each element in the array, we decide whether to add 0 or k based on 
    how it affects the GCD of the entire array.
  - The key insight is to consider modulo arithmetic: for an element a[i],
    adding k * (a[i] % (k + 1)) ensures that a[i] becomes divisible by (k + 1),
    which helps in making the GCD > 1.

Time Complexity: O(n) per test case
Space Complexity: O(1) excluding input/output

*/
#include <iostream>
using namespace std;
int t, n, k;
int main() {
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  for (cin >> t; t; --t) {
    cin >> n >> k;
    for (int i = 1, a; i <= n; ++i)
      cin >> a, cout << a + 1ll * k * (a % (k + 1)) << " \n"[i == n]; // Add k multiplied by remainder to make divisible by k+1
  }
}


// https://github.com/VaHiX/codeForces/