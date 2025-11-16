// Problem: CF 1497 C1 - k-LCM (easy version)
// https://codeforces.com/contest/1497/problem/C1

/*
Code Purpose:
This program solves the k-LCM problem for k=3. Given a positive integer n, it finds three positive integers a1, a2, a3 such that:
1. Their sum equals n.
2. Their least common multiple (LCM) is at most n/2.

Algorithm:
- For k=3, we start by setting the first k-1 elements to 1, reducing n accordingly.
- Then, we handle the remaining n based on its properties modulo 2 or 4:
  - If n is odd, we set the last three elements to 1, n/2, n/2.
  - If n is divisible by 4, we set them to n/4, n/4, n/2.
  - Otherwise, we set them to 2, n/2-1, n/2-1.

Time Complexity: O(1) per test case
Space Complexity: O(1)
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    for (long p = 3; p < k; p++) {
      printf("1 ");
      --n;
    }
    if (n % 2) {
      printf("1 %ld %ld\n", n / 2, n / 2);
    } else if (n % 4 == 0) {
      printf("%ld %ld %ld\n", n / 4, n / 4, n / 2);
    } else {
      printf("2 %ld %ld\n", n / 2 - 1, n / 2 - 1);
    }
  }
}


// https://github.com/VaHiX/CodeForces/