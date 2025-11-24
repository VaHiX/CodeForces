// Problem: CF 1556 A - A Variety of Operations
// https://codeforces.com/contest/1556/problem/A

/*
Problem: Transform two numbers a and b from (0, 0) to (c, d) using three types of operations.
Each operation adds k to one number and subtracts k from the other.

Algorithms/Techniques: Mathematical analysis and case handling
Time Complexity: O(1) per test case
Space Complexity: O(1)

Operations allowed:
1. Add k to both a and b
2. Add k to a, subtract k from b
3. Add k to b, subtract k from a

Analysis:
- Let s = c + d (sum of target values)
- If s is odd, it's impossible because each operation changes the sum by 0 (k+k or k-k).
- If s is even:
    - If c == d: 0 operations if both are 0, else 1 operation (add k to both)
    - If c != d: 
        - (c-d) must be even for solution to exist
        - Answer is 2 if possible else -1

Key observations:
- Sum of target values s = c + d must be even
- Case analysis on the difference between c and d
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long c, d;
    scanf("%ld %ld", &c, &d);
    if (c == d) {
      // If both are equal:
      // - If both are 0, we don't need any operations
      // - Otherwise we can do one operation of type 1 (add k to both)
      puts(c == 0 ? "0" : "1");
    } else {
      // If c != d, check if difference is even and sum is even:
      // For solution to exist, (c-d) must be even and the total sum (c+d) must also be even.
      // In that case, it takes 2 operations.
      puts((c - d) % 2 == 0 ? "2" : "-1");
    }
  }
}


// https://github.com/VaHiX/codeForces/