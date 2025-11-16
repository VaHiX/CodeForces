// Problem: CF 1443 A - Kids Seating
// https://codeforces.com/contest/1443/problem/A

/*
Code Purpose:
This code solves the problem of seating n kids at a dinner table with 4n chairs such that no two kids are seated on chairs whose numbers fulfill certain conditions (gcd(a,b)=1, a divides b, or b divides a). The solution uses a greedy approach: it selects the largest possible even numbers from the range [2n+1, 4n], which ensures that no two selected numbers share a common factor greater than 1 and avoids divisibility relationships.

Algorithms/Techniques:
- Greedy selection of even numbers
- Mathematical property: all selected numbers are even and in the range [2n+1, 4n], ensuring no two numbers are divisible by each other or have gcd = 1 unless one is double the other (which is avoided by selecting even numbers in a specific range).

Time Complexity: O(n)
Space Complexity: O(1) (excluding output space)
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    // Loop from 4*n down to 2*n+1, selecting even numbers only
    for (long p = 4 * n; p > 2 * n; p -= 2) {
      printf("%ld ", p);
    }
    puts(""); // Print newline after each test case
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/