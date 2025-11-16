// Problem: CF 687 B - Remainders Game
// https://codeforces.com/contest/687/problem/B

/*
 * Problem: B. Remainders Game
 * Purpose: Determine if Arya can uniquely determine the value of x % k 
 *          given a set of ancient numbers c1, c2, ..., cn and k.
 *          
 * Algorithm:
 *   - For each ancient number c_i, compute gcd(c_i, k).
 *   - Build the least common multiple (LCM) of all such gcd values.
 *   - If the final LCM equals k, then x % k can be uniquely determined.
 *   
 * Time Complexity: O(n * log(k)) due to GCD computations.
 * Space Complexity: O(1), only using a few variables.
 */

#include <cstdio>
long gcd(long a, long b) { return (b == 0) ? a : gcd(b, a % b); }
int main() {
  long n, k;
  scanf("%ld %ld", &n, &k);
  long acc(1); // accumulator for the LCM of processed values
  while (n--) {
    long ck;
    scanf("%ld", &ck);
    ck = gcd(ck, k); // reduce ck to its gcd with k
    acc = acc / gcd(acc, ck) * ck; // update LCM of acc and ck
  }
  puts((acc == k) ? "Yes" : "No"); // output result
}


// https://github.com/VaHiX/CodeForces/