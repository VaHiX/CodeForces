// Problem: CF 1646 A - Square Counting
// https://codeforces.com/contest/1646/problem/A

#include <cstdio>
typedef long long ll;

/*
 * Problem: Find the number of elements in a sequence equal to n^2
 * 
 * Algorithm/Techniques: Mathematical reasoning and division
 * 
 * Approach:
 * - Each element in the sequence is either between 0 and n-1, or exactly n^2
 * - Let k be the count of elements equal to n^2
 * - Then (n+1-k) elements are in range [0, n-1]
 * - The sum s = k * n^2 + sum_of_remaining_elements
 * - Since each remaining element is at most n-1, we have:
 *   sum_of_remaining_elements <= (n+1-k)*(n-1)
 * - To find k, we compute how many times n^2 fits into s:
 *   k = s / n^2 (integer division) because if we use k copies of n^2, 
 *   we subtract k*n^2 from s, and the rest must be distributed among remaining
 *   (n+1-k) positions, which is valid iff the remainder is non-negative and 
 *   can be split among these positions.
 * 
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 */

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll n, s;
    scanf("%lld %lld", &n, &s);
    // Compute number of elements equal to n^2 using integer division
    printf("%lld\n", s / (n * n));
  }
}

// https://github.com/VaHiX/codeForces/