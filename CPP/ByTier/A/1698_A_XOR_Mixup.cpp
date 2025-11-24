// Problem: CF 1698 A - XOR Mixup
// https://codeforces.com/contest/1698/problem/A

/*
 * Problem: XOR Mixup
 * 
 * Algorithm/Technique: XOR properties and bit manipulation
 * 
 * Time Complexity: O(n) per test case, where n is the size of the array
 * Space Complexity: O(1), constant extra space used
 * 
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long res(0);  // Initialize result to 0
    while (n--) {
      scanf("%ld", &res);
    }
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/CodeForces/