// Problem: CF 1349 A - Orac and LCM
// https://codeforces.com/contest/1349/problem/A

/*
Problem: Orac and LCM
Task: Given a sequence of positive integers, compute the GCD of all pairwise LCMs.
Algorithm: 
  - For each pair (i,j) where i < j, calculate lcm(a[i], a[j])
  - Find the GCD of all such LCM values
Time Complexity: O(n^2 * log(max(a)))
Space Complexity: O(1)

Note: This implementation is inefficient for large inputs due to nested loops.
      A more optimized approach would involve prime factorization and
      using properties of GCD and LCM to reduce complexity.
*/
#include <algorithm>
#include <iostream>
#include <numeric>

using namespace std;
int main() {
  long long int n, l, g = 0, k, a;
  cin >> n >> a;
  l = a;
  for (long long int i = 1; i <= n - 1; i++) {
    cin >> a;
    k = lcm(l, a);     // Compute LCM of previous value and current value
    g = __gcd(g, k);   // Update global GCD with new LCM
    l = __gcd(a, l);   // Update running GCD of elements seen so far
  }
  cout << g;
}


// https://github.com/VaHiX/codeForces/