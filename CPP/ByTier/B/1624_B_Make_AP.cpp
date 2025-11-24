// Problem: CF 1624 B - Make AP
// https://codeforces.com/contest/1624/problem/B

/*
 * Problem: B. Make AP
 * Purpose: Determine if multiplying exactly one of three positive integers a, b, c by a positive integer m
 *          can make the sequence form an arithmetic progression.
 * 
 * Algorithm:
 * For each test case, we try to multiply one of the values (a, b, or c) by some positive integer m
 * such that a, b, c forms an AP after multiplication. Since only one element is multiplied,
 * there are three possible cases:
 *   1. Multiply 'a' by m: check if (b, a*m, c) can form an AP
 *   2. Multiply 'b' by m: check if (a, b*m, c) can form an AP  
 *   3. Multiply 'c' by m: check if (a, b, c*m) can form an AP
 * 
 * In an arithmetic progression, the middle term is the average of the other two:
 * For sequence x, y, z to be AP => y = (x + z)/2 => 2*y = x + z
 * So for any three numbers to form AP, the double of middle equals sum of ends.
 *
 * Time Complexity: O(1) per test case - constant number of operations
 * Space Complexity: O(1) - only using a few variables
 */

#include <stdio.h>
int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    
    // Try multiplying 'a' by some positive integer m.
    // For a*b, b, c to be AP: 2*b = a*m + c => (2*b - c) must be divisible by a
    if ((2 * b - c) > 0 && (2 * b - c) % a == 0 || 
        // Try multiplying 'b' by some positive integer m.
        // For a, b*m, c to be AP: 2*b*m = a + c => (a + c) must be divisible by 2*b
        (a + c) % (2 * b) == 0 ||
        // Try multiplying 'c' by some positive integer m.
        // For a, b, c*m to be AP: 2*b = a + c*m => (2*b - a) must be divisible by c
        (2 * b - a) > 0 && (2 * b - a) % c == 0)
      printf("YES\n");
    else
      printf("NO\n");
  }
}


// https://github.com/VaHiX/codeForces/