// Problem: CF 1059 C - Sequence Transformation
// https://codeforces.com/contest/1059/problem/C

/*
C. Sequence Transformation
Algorithm: Recursive approach to generate lexicographically maximum GCD sequence.
Techniques: Bit manipulation, recursive decomposition, greedy selection.

Time Complexity: O(n)
Space Complexity: O(n)

The algorithm works by recursively decomposing the sequence and choosing 
elements to maximize the lexicographical result. It uses a clever observation:
- For odd elements, we add 1 (GCD of a single element or small subset)
- For even elements, we halve them and continue recursively
This ensures that larger values appear early in the result for maximum lexicographical order.
*/

#include <cstdio>
const long maxn = 1e6 + 6;
long seq[maxn];     // Stores current sequence during recursion
long ans[maxn];     // Stores the final answer sequence
long ptr = 0;       // Points to next position in ans array

void solve(long n, long mul) {
  if (n == 1) {
    ans[ptr++] = mul;           // Base case: only one element, GCD is itself
    return;
  }
  if (n == 2) {
    ans[ptr++] = mul;           // First element
    ans[ptr++] = 2 * mul;       // Second element's contribution
    return;
  }
  if (n == 3) {
    ans[ptr++] = mul;           // First element
    ans[ptr++] = mul;           // Second element (contributes GCD of 1, 2)
    ans[ptr++] = 3 * mul;       // Third element
    return;
  }
  // Process all odd numbers in current sequence
  for (long p = 0; p < n; p++)
    if (seq[p] & 1) {           // Check if number is odd
      ans[ptr++] = mul;         // Add contribution to result
    }
  
  // Prepare next recursive call by halving even elements
  for (long p = 0; p < n / 2; p++) {
    seq[p] = seq[2 * p + 1] / 2; // Keep only odd-indexed elements and halve them
  }
  solve(n / 2, 2 * mul);        // Recursive step with updated sequence and doubled multiplier
}

int main() {
  long n;
  scanf("%ld", &n);
  for (long p = 0; p < n; p++) {
    seq[p] = p + 1;             // Initialize sequence: 1, 2, ..., n
  }
  solve(n, 1);                  // Start recursive process
  for (int p = 0; p < n; p++) {
    printf("%ld ", ans[p]);     // Output result
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/