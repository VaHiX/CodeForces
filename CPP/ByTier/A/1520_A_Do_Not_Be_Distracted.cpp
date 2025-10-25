// Problem: CF 1520 A - Do Not Be Distracted!
// https://codeforces.com/contest/1520/problem/A

/*
Problem: A. Do Not Be Distracted!
Purpose: Determine if Polycarp followed the rule of solving one task to the end without switching back to a previous task.
Algorithm: 
    - For each test case, check if there exists any triplet of indices (i,j,k) such that:
        s[i] == s[j] and s[i] != s[k], where i < k < j
    - This represents an invalid pattern where a task is started, another task is done in between,
      then the original task is resumed — which violates the rule.
Time Complexity: O(n^3) due to three nested loops checking all possible triplets.
Space Complexity: O(1) as only a few variables are used and string input is not stored beyond use.

Techniques:
    - Brute force check of all triplets
    - Early termination when violation is found
*/

#include <iostream>
#include <stdio.h>
#include <string>
int t, i, j, k, f, n;
std::string s;
int main() {
  for (std::cin >> t; t--;) {
    std::cin >> n >> s, f = 0;  // Read number of days and the task string, reset flag
    for (int i = 0; i < n; i++)  // First pointer for start of task
      for (int j = i + 1; j < n; j++)  // Second pointer for end of task
        for (int k = i + 1; k < j; k++)  // Third pointer in between to check if same task is resumed
          if (s[i] == s[j] && s[i] != s[k])  // Found a violation pattern
            f = 1;  // Set flag indicating suspicious behavior
    puts(f ? "NO" : "YES");  // Output result based on flag
  }
}


// https://github.com/VaHiX/codeForces/