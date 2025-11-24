// Problem: CF 1850 B - Ten Words of Wisdom
// https://codeforces.com/contest/1850/problem/B

#include <cstdio>
// =====================================================================
// Problem: B. Ten Words of Wisdom
// Purpose: Determine the winner of a show based on response quality,
//          considering only those responses with at most 10 words.
// Algorithm: For each test case, iterate through all responses and
//            keep track of the response with the highest quality among
//            those with word count <= 10.
// Time Complexity: O(n) per test case, where n is the number of responses.
// Space Complexity: O(1), only using a constant amount of extra space.
// =====================================================================
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long win(0), quality(0); // Initialize winner index and max quality
    for (long p = 1; p <= n; p++) {
      int a, b;
      scanf("%d %d", &a, &b); // Read word count and quality of current response
      if (a > 10) {
        continue; // Skip responses longer than 10 words
      }
      if (b > quality) { // If current response has higher quality
        quality = b;     // Update max quality
        win = p;         // Update winner index
      }
    }
    printf("%ld\n", win); // Print the index of the winning response
  }
}

// https://github.com/VaHiX/codeForces/