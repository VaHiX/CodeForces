// Problem: CF 1095 C - Powers Of Two
// https://codeforces.com/contest/1095/problem/C

/*
 * Problem: Represent a number n as sum of exactly k powers of two.
 * 
 * Algorithm:
 * 1. First check if it's possible: minimum number of powers of two needed is
 *    equal to the number of 1-bits in binary representation of n (cnt).
 *    If k < cnt, impossible.
 * 2. If possible, decompose n into binary representation.
 * 3. Then, use the fact that 2^i = 2 * 2^(i-1) to split larger powers into smaller ones
 *    (greedily from most significant bit down) until we have exactly k terms.
 * 4. Finally, print the powers of two in increasing order.
 * 
 * Time Complexity: O(log n + k) - where log n is for counting bits and k is for splitting.
 * Space Complexity: O(log n) - for storing the binary representation.
 */

#include <cstdio>
#include <vector>
int main() {
  long n, k;
  scanf("%ld %ld", &n, &k);
  long cnt(0);
  std::vector<long> w;
  bool possible(true);
  
  // If k is less than the minimum required powers of two, impossible
  if (n < k) {
    possible = false;
  }
  
  // Convert n to binary representation and count 1-bits
  while (n) {
    w.push_back(n % 2);
    cnt += (n % 2);
    n /= 2;
  }
  
  // If more 1-bits than k, impossible
  if (cnt > k) {
    possible = false;
  }
  
  // If impossible, output NO
  if (!possible) {
    puts("NO");
    return 0;
  }
  
  puts("YES");
  
  // Split larger powers of two to reach exactly k terms
  for (long p = w.size() - 1; p > 0 && cnt < k; p--) {
    while (w[p] && cnt < k) {
      --w[p];
      w[p - 1] += 2;
      ++cnt;
    }
  }
  
  // Print each power of two
  long u = 1;
  for (long p = 0; p < w.size(); p++) {
    for (long q = 0; q < w[p]; q++) {
      printf("%ld ", u);
    }
    u *= 2;
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/CodeForces/