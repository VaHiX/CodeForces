// Problem: CF 1878 D - Reverse Madness
// https://codeforces.com/contest/1878/problem/D

/*
 * Problem: D. Reverse Madness
 * 
 * Purpose: This code simulates a series of operations on a string where each operation 
 * reverses a specific substring based on a given index x. The string is divided into 
 * k segments, and for each operation, we find the appropriate segment and reverse a 
 * specific part within that segment.
 * 
 * Algorithm:
 * - Use binary search to locate the segment containing the index x.
 * - For each operation, we determine the start and end of the substring to reverse,
 *   which is computed as [x, l[i] + r[i] - x].
 * - Instead of reversing the string directly, we use a "lazy propagation"-like approach 
 *   with a tag array to mark which indices need to be swapped in the final pass.
 * - During the final pass, we process the string and apply the swaps based on the tags.
 * 
 * Time Complexity: O(n + q * log(k)) where n is the length of string and q is number of operations.
 * Space Complexity: O(n + k + q) for storing string, segment arrays and operation indices.
 * 
 * Techniques: Binary search, lazy propagation, prefix processing.
 */

#include <stdio.h>
#include <string.h>

#define MAX(A, B) ((A) > (B) ? (A) : (B))
#define MIN(A, B) ((A) < (B) ? (A) : (B))
#define SWAP(T, A, B)                                                          \
  do {                                                                         \
    T t = A;                                                                   \
    A = B;                                                                     \
    B = t;                                                                     \
  } while (0)
#define ABS(X) ((X) > 0 ? (X) : -(X))
#define RN 1000005
#define INF32 0x3f3f3f3f
#define INF8 0x3f
#define INF64 0x3f3f3f3f3f3f3f3fll
int li[RN], ri[RN], xi[RN], tag[RN];
char str[RN];

void run(void) {
  int n, m;
  scanf("%d%d%s", &n, &m, str + 1);  // Read string starting from index 1
  memset(tag, 0, sizeof(int) * (n + 2));  // Initialize tag array to 0
  for (int i = 1; i <= m; i++) {
    scanf("%d", &li[i]);  // Read left bounds of segments
  }
  for (int i = 1; i <= m; i++) {
    scanf("%d", &ri[i]);  // Read right bounds of segments
  }
  int q;
  scanf("%d", &q);  // Number of operations
  for (int i = 1; i <= q; i++) {
    scanf("%d", &xi[i]);  // Read the index x for each operation
    int l = 1, r = m;
    // Binary search to find which segment x belongs to
    while (l <= r) {
      int mid = l + ((r - l) >> 1);
      if (li[mid] <= xi[i]) {
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    }
    // Determine the start of the substring to reverse and flip the tag
    tag[MIN(xi[i], ri[r] + li[r] - xi[i])] ^= 1;
  }
  
  int l = 1, status = 0;
  // Final processing of string to apply reversals
  for (int i = 1; i <= n; i++) {
    if (ri[l] < i) {  // If current position is out of segment l's range
      l++;  // Move to next segment
      status = 0;  // Reset status
    }
    if (ri[l] + li[l] - i <= i) {
      // Optimization: skip if index i is already in the symmetric range
      continue;
    }
    status ^= tag[i];  // Flip the status if tag is 1
    if (status) {
      // Swap characters at symmetric positions
      SWAP(char, str[i], str[ri[l] + li[l] - i]);
    }
  }
  puts(str + 1);  // Print result string starting from index 1
}

int main(void) {
  int t;
  scanf("%d", &t);  // Read number of test cases
  while (t--) {
    run();  // Run for each test case
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/