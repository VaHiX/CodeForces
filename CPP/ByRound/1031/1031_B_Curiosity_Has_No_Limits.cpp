// Problem: CF 1031 B - Curiosity Has No Limits
// https://codeforces.com/contest/1031/problem/B

/*
B. Curiosity Has No Limits
time limit per test
1 second
memory limit per test
256 megabytes
input
standard input
output
standard output

When Masha came to math classes today, she saw two integer sequences of length n - 1 on the blackboard. Let's denote the elements of the first sequence as a_i (0 <= a_i <= 3), and the elements of the second sequence as b_i (0 <= b_i <= 3).
Masha became interested if or not there is an integer sequence of length n, which elements we will denote as t_i (0 <= t_i <= 3), so that for every i (1 <= i <= n - 1) the following is true: 

a_i = t_i | t_{i + 1} (where | denotes the bitwise OR operation) and 
b_i = t_i & t_{i + 1} (where & denotes the bitwise AND operation). 

Algorithm:
- The problem requires reconstructing a sequence t such that for each adjacent pair, the OR and AND of the elements match given values.
- Key insight: For any two numbers x and y with OR = a and AND = b, then x | y == a and x & y == b implies (x + y) == a + b.
  So we can precompute all valid pairs for given OR and AND values and then use backtracking or forward propagation.

Time complexity: O(n) - since we process each element in the array once and check at most 10 pairs per step (4*4 combinations for 2-bit numbers).
Space complexity: O(1) - only using fixed-size data structures regardless of input size.
*/

#include <cstdio>
#include <vector>
std::vector<std::vector<int>> getPair(int inor, int inand) {
  std::vector<std::vector<int>> ans;
  if (inor < inand) {     // Invalid pair: OR cannot be smaller than AND for non-negative integers
    return ans;
  }
  for (int a = 0; a < 4; a++) {   // Loop through all possible first values (0 to 3)
    for (int b = 0; b <= a; b++) { // Second value from 0 to a to avoid duplicates
      std::vector<int> cur(2);
      cur[0] = a;
      cur[1] = b;
      if (((a | b) == inor) && ((a & b) == inand)) { // Check if this pair produces the required OR and AND
        ans.push_back(cur);
      }
    }
  }
  return ans;
}
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<int> vecor(n, 0);   // Store the OR values (a_i)
  for (long p = 1; p < n; p++) {
    scanf("%d", &vecor[p]);
  }
  std::vector<int> vecand(n, 0); // Store the AND values (b_i)
  for (long p = 1; p < n; p++) {
    scanf("%d", &vecand[p]);
  }
  std::vector<int> t(n);   // Final sequence to construct
  bool possible(false);
  for (long s = 0; s < 4; s++) {  // Try 0 to 3 as potential starting element
    t[0] = s;
    for (long p = 1; p < n; p++) {
      std::vector<std::vector<int>> cur = getPair(vecor[p], vecand[p]); // Find all valid pairs for this step
      bool done = false;
      for (int u = 0; u < cur.size(); u++) {   // Try each valid pair to find match
        std::vector<int> tmp = cur[u];
        if (t[p - 1] == tmp[0]) {  // If previous element matches first in pair
          t[p] = tmp[1];   // Set current to second
          done = true;
          break;
        } else if (t[p - 1] == tmp[1]) {  // Else if matches second in pair
          t[p] = tmp[0];   // Set current to first
          done = true;
          break;
        }
      }
      if (!done) {
        break;   // No match found, invalid path
      }
      if (p == n - 1) { // If we reached last element
        possible = true;  // Mark as possible solution
      }
    }
    if (possible) {
      break;  // Solution found, exit outer loop
    }
  }
  if (possible) {
    puts("YES");
    for (long p = 0; p < n; p++) {
      printf("%d ", t[p]);
    }
    puts("");
  } else {
    puts("NO");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/