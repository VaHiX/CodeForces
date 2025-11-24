// Problem: CF 916 B - Jamie and Binary Sequence (changed after round)
// https://codeforces.com/contest/916/problem/B

/*
Purpose: 
This code solves the problem of representing a given integer n as a sum of exactly k powers of 2,
such that:
1. The largest exponent used is minimized.
2. Among all valid representations with the minimum largest exponent, the lexicographically largest one is chosen.

Algorithms/Techniques:
- Binary representation of n is used to initially decompose n into powers of 2.
- Greedy method is used to redistribute the powers to meet the constraint of exactly k terms.
- The lexicographically largest sequence is constructed by prioritizing higher indices.

Time Complexity: O(log n + k)
Space Complexity: O(log n)

*/
#include <cstdio>
const int karen = 2e5;
long long n;
int k, a[karen | 10], *b = a + (karen >> 2);
int main() {
  scanf("%lld%d", &n, &k);
  int cnt = 0;
  // Decompose n into binary representation and store the count of 1s at each bit position
  for (; n;)
    b[cnt] = n & 1, n >>= 1, k -= b[cnt++]; // Subtract number of 1s from k
  if (k < 0)
    return puts("No"), 0; // Not enough positions to satisfy k terms
    
  int q = cnt - 1;
  // Redistribute powers to minimize the maximum index, greedily merge lower powers
  for (; b[q] <= k;)
    b[q - 1] += b[q] << 1, k -= b[q], b[q--] = 0;
    
  int p = 0;
  q < p ? p = q : 0; // Find starting position to avoid leading zeros
  for (; p < cnt && !b[p]; ++p) // Skip leading zeros
    ;
    
  // Redistribute remaining k to make sure we have exactly k terms
  for (; k; --p)
    if (b[p])
      b[p - 1] += 2, b[p]--, k--;
      
  puts("Yes");
  // Output the result in lexicographically largest order
  for (int i = cnt - 1; i >= p; --i)
    for (; b[i]--; printf("%d ", i))
      ;
}


// https://github.com/VaHiX/CodeForces/