// Problem: CF 2050 B - Transfusion
// https://codeforces.com/contest/2050/problem/B

/*
B. Transfusion
Algorithm: 
    This problem checks whether it's possible to make all elements of an array equal using specific operations.
    The key insight is that we can redistribute values between adjacent elements.
    For achieving equality, two conditions must hold:
        1. Sum of elements at odd indices (sd) should be divisible by count of odd indices (cd).
        2. Sum of elements at even indices (se) should be divisible by count of even indices (ce).
        3. The ratio of total sums and counts of odd and even indexed elements must match.
        
Time Complexity: O(n) per test case
Space Complexity: O(1)
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long long sd(0), cd(0), se(0), ce(0); // sd: sum of odd indices, cd: count of odd indices, se: sum of even indices, ce: count of even indices
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      sd += (p % 2) * x;       // Add x to sd if p is odd
      se += (p % 2 == 0) * x;  // Add x to se if p is even
      p % 2 ? ++cd : ++ce;     // Increment cd if p is odd, else increment ce
    }
    puts((sd % cd || se % ce || sd * ce != se * cd) ? "NO" : "YES"); // Check divisibility and ratio consistency
  }
}


// https://github.com/VaHiX/codeForces/