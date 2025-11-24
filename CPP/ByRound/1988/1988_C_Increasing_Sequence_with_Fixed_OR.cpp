// Problem: CF 1988 C - Increasing Sequence with Fixed OR
// https://codeforces.com/contest/1988/problem/C

/*
 * Problem: C. Increasing Sequence with Fixed OR
 * 
 * Algorithm/Technique:
 * - The key insight is that we need to find a strictly increasing sequence where each element
 *   when ORed with the previous one equals n.
 * - For a sequence to satisfy a[i] | a[i-1] = n, and a[i] > a[i-1], we can exploit the fact that
 *   when we perform a bitwise OR with a number r and n, the result equals n only if r is a subset 
 *   of bits in n (i.e., all set bits of r are also set in n).
 * - The approach is to iterate through powers of 2 from large to small (starting at 2^62)
>,
 *   and for each r where (r | n) == n, we add (n ^ r) to our sequence.
 * - This process ensures that:
 *   1. The OR of consecutive terms in the sequence is always n.
 *   2. The sequence is strictly increasing.
 *   3. The sequence starts from smallest possible values and ends at n.
 *
 * Time Complexity: O(log n) per test case (since we iterate over at most 60 bits)
 * Space Complexity: O(log n) for storing the sequence (at most log n elements)
 */

#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    ll r(1LL << 62);  // Start with a large power of 2 (62nd bit set)
    std::vector<ll> v;
    while (r > 0 && r != n) {
      if ((r | n) == n) {   // Check if r is a subset of bits in n
        v.push_back(n ^ r); // Add the number that when OR'd with r gives n
      }
      r /= 2;  // Move to next smaller power of 2
    }
    v.push_back(n);  // Push n at the end to complete the sequence
    printf("%ld\n", v.size());
    for (long p = 0; p < v.size(); p++) {
      printf("%lld ", v[p]);
    }
    puts("");  // Print newline after the sequence
  }
}


// https://github.com/VaHiX/CodeForces/