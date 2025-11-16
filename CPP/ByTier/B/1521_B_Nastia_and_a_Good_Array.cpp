// Problem: CF 1521 B - Nastia and a Good Array
// https://codeforces.com/contest/1521/problem/B

/*
Algorithm: Nastia and a Good Array
Purpose: Transform an array into a "good" array where adjacent elements are coprime (gcd = 1).
Approach:
- For each pair of adjacent elements, if they are not coprime, we modify one of them to 1000000007 (a prime number),
  ensuring that the new element is coprime with its neighbors.
- Since 1000000007 is a large prime, it will be coprime with most numbers.
- We use at most n/2 operations by iterating through pairs and modifying adjacent entries.
Time Complexity: O(n) per test case, where n is the size of the array.
Space Complexity: O(n) for storing the input array.

Techniques:
- Greedy approach for pairing elements
- GCD checking via prime numbers (1000000007 is chosen to have high probability of being coprime with others)
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    printf("%ld\n", n / 2); // Output number of operations needed
    for (long p = 1; p < n; p += 2) {
      // For each pair of elements, modify them such that one becomes 1000000007
      // and the other takes the smaller value of the current pair
      printf("%ld %ld %ld 1000000007\n", p, p + 1,
             a[p - 1] < a[p] ? a[p - 1] : a[p]);
    }
  }
}


// https://github.com/VaHiX/CodeForces/