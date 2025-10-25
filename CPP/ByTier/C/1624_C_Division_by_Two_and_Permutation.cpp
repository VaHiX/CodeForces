// Problem: CF 1624 C - Division by Two and Permutation
// https://codeforces.com/contest/1624/problem/C

/*
C. Division by Two and Permutation
Algorithm: Greedy approach with bit manipulation
Time Complexity: O(n * log(max(a_i))) where max(a_i) can be up to 10^9
Space Complexity: O(n)

For each element in the array, we try to reduce it by dividing by 2 until we find a value in range [1,n] that hasn't been used yet.
We use a boolean vector to track which numbers from 1 to n have already been assigned.
The greedy choice is to assign the smallest available number (from the reduced value of current element) to maximize chances of covering all numbers from 1 to n.
*/
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<bool> v(n + 1, false); // Track which numbers from 1 to n are already used
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      while (x) {
        if ((1 <= x) && (x <= n) && (!v[x])) { // If x is in valid range and not yet used
          v[x] = true; // Mark this number as used
          break;
        }
        x /= 2; // Reduce x by dividing by 2 (floor division)
      }
    }
    bool res(true);
    for (long p = 1; p <= n; p++) {
      if (!v[p]) { // If any number from 1 to n is not used
        res = false;
        break;
      }
    }
    puts(res ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/