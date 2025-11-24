// Problem: CF 848 A - From Y to Y
// https://codeforces.com/contest/848/problem/A

#include <cstdio>
#include <vector>

/*
 * Purpose: Construct a multiset of lowercase letters such that the minimum
 *          total cost of concatenating all elements into one string is exactly k.
 *          The cost of concatenating two strings is defined as the sum of the
 *          frequencies of each character in the first string that also appear in the second.
 *
 * Algorithm: 
 *   - Precompute triangular numbers f[p] = p*(p-1)/2 for p = 0 to 1000.
 *   - For a given k, decompose it into sum of triangular numbers.
 *   - For each triangular number f[p] <= k:
 *       - Add 'p' copies of a new character to the result.
 *       - Subtract f[p] from k.
 *   - Continue until k becomes 0.
 *
 * Time Complexity: O(log^2 k) since we iterate through precomputed triangular numbers
 *                  and decompose k into triangular components.
 * Space Complexity: O(1) - only using a fixed-size vector of 1000 elements and a few variables.
 */
int main() {
  const long N = 1000;
  std::vector<long> f;
  for (long p = 0; p < N; p++) {
    f.push_back(p * (p - 1) / 2);  // Precompute triangular numbers
  }
  long k;
  scanf("%ld\n", &k);
  char c = 'a';
  if (k == 0) {
    puts("a");  // Special case: if k=0, we just output 'a'
    return 0;
  }
  while (k > 0) {
    long rep(0);
    for (long p = 0; p < f.size(); p++) {
      if (f[p] > k) {
        break;
      };
      rep = p;  // Find the largest triangular number <= k
    }
    for (long p = 0; p < rep; p++) {
      printf("%c", c);  // Output 'rep' copies of current character
    }
    k -= f[rep];  // Subtract the triangular number from k
    ++c;  // Move to next character
  }
  puts("");  // Print newline at the end
  return 0;
}


// https://github.com/VaHiX/CodeForces/