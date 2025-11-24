// Problem: CF 678 A - Johny Likes Numbers
// https://codeforces.com/contest/678/problem/A

/*
Algorithm: Mathematical approach to find the smallest multiple greater than n
Techniques: Integer division and multiplication

Time Complexity: O(1) - constant time operations
Space Complexity: O(1) - only using constant extra space

The solution uses the mathematical property that:
- n/k gives the quotient when n is divided by k
- Adding 1 to this quotient gives us the next multiple
- Multiplying by k gives us the desired result
*/

#include <cstdio>
int main() {
  long n, k;
  scanf("%ld %ld\n", &n, &k);
  printf("%ld\n", (1 + n / k) * k);  // Calculate next multiple of k greater than n
  return 0;
}


// https://github.com/VaHiX/CodeForces/