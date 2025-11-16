// Problem: CF 894 C - Marco and GCD Sequence
// https://codeforces.com/contest/894/problem/C

/*
 * Problem: Marco and GCD Sequence
 * 
 * Purpose: Given a set S of integers which are all possible GCDs of contiguous subsequences
 *          of some sequence, reconstruct a valid sequence that generates exactly those GCDs.
 * 
 * Algorithm:
 *   - The key insight is that the smallest element in the set S must be the GCD of the 
 *     entire sequence. This GCD must divide all elements in the sequence.
 *   - If the GCD of all elements in S is not equal to the smallest element in S, it's impossible.
 *   - A valid construction is to alternate between elements of S and the overall GCD.
 * 
 * Time Complexity: O(m log(max(s[i]))) where m is the size of the set.
 * Space Complexity: O(m) for storing the input set.
 */

#include <cstdio>
#include <vector>
long gcd(long a, long b) { return (b == 0) ? a : gcd(b, a % b); }
int main() {
  long m;
  scanf("%ld", &m);
  std::vector<long> s(m);
  long g(0);  // g will store the GCD of all elements in s
  for (long p = 0; p < m; p++) {
    scanf("%ld", &s[p]);
    g = gcd(g, s[p]);  // Compute GCD of all elements in s
  }
  // If g is less than s[0], then s[0] cannot be the GCD of any subsequence of valid sequence
  if (g < s[0]) {
    puts("-1");
  } else {
    // Output the length of the constructed sequence (2 * m)
    printf("%ld\n", 2 * m);
    // Alternate between elements of s and g to construct the sequence
    for (long p = 0; p < 2 * m; p++) {
      if (p & 1) {
        // If p is odd, print g
        printf("%ld ", g);
      } else {
        // If p is even, print s[p/2]
        printf("%ld ", s[p / 2]);
      }
    }
    puts("");  // Print newline at end
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/