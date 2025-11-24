// Problem: CF 2135 D1 - From the Unknown (Easy Version)
// https://codeforces.com/contest/2135/problem/D1

/*
 ***************************************************************************************
 * Problem: D1. From the Unknown (Easy Version)
 *
 * Purpose:
 *   This code is an interactive solution to find the parameter W (width of the editor) 
 *   by querying the RiOI Editor with different articles and observing line counts.
 *
 * Algorithms/Techniques:
 *   - Binary search on the possible values of W using two queries
 *   - First query to determine a range of W where it's larger than some value
 *   - Second query to narrow down to exact W using mathematical reasoning
 *
 * Time Complexity:
 *   O(N + B^2 + log(max_W)) where N = 11343 and B = 116. The first query checks all possible line counts up to B, 
 *   second query does a linear search in range of B.
 *
 * Space Complexity:
 *   O(1) - only constant extra space used.
 ***************************************************************************************
 */
#include <iosfwd>
#include <stdio.h>
using namespace std;
const int N = 11343, B = 116; // N - first query size, B - second query step value
int T;

signed main() {
  scanf("%d", &T);  // Read number of test cases

  while (T--) {
    printf("? %d ", N);  // First query: send article with N words each of length B
    for (int i = 1; i <= N; i++)
      printf("%d ", B);
    fflush(stdout);  // Flush output buffer to send query immediately
    
    int k, l = 0, r = 0;
    scanf("%d", &k);  // Read response from the editor
    
    if (k == 0) {
      // If first query returns 0, then W < N * B => W is bounded above by N * B
      printf("? %d ", B * B);  // Second query: send B*B words of length 1 each
      for (int i = 1; i <= B * B; i++)
        printf("1 ");  // All words have length 1
      fflush(stdout);  // Flush output buffer
      
      scanf("%d", &k);  // Read the number of lines returned
      
      int ans = 0;
      // Loop through possible values to find correct W using formula:
      // For a group of i words, each of size 1, line count k = ceil((B*B + i - 1) / i)
      for (int i = 1; i < B; i++) {
        if ((B * B + i - 1) / i == k) {
          ans = i;
          break;
        }
      }
      printf("! %d\n", ans);  // Report the answer
      fflush(stdout);  // Flush output buffer
    } else {
      // If first query returns >0, then W >= N * B, we need to find exact W in range
      for (int i = B; i <= 100000; i++) {  
        int K = i / B;  // Compute number of lines needed assuming word lengths are B
        if ((N + K - 1) / K == k) {
          // Check if current W results in same line count as returned from first query
          if (!l)
            l = i;  // Set left bound of valid range
          r = i;    // Update right bound
        }
      }

      // Second query to narrow down W: determine shift from [l, r]
      printf("? %d ", r - l + 1 << 1);  // Send a new article with (r-l+1)*2 words
      for (int i = 1; i <= r - l + 1; i++)
        printf("%d %d ", l, i);  // Alternate between l and i as word lengths
      
      fflush(stdout);  // Flush output buffer

      scanf("%d", &k);  // Read number of lines response
      
      k = (r - l + 1 << 1) - k;  // Compute offset
      printf("! %d\n", l + k);   // Final result
      fflush(stdout);  // Flush output buffer
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/