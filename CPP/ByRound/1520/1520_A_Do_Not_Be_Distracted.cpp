// Problem: CF 1520 A - Do Not Be Distracted!
// https://codeforces.com/contest/1520/problem/A

/*
Algorithm: Check if the sequence of tasks is valid such that 
           once a task is started, it is completed without switching 
           to another task and then returning to the original task.

Techniques:
- Three nested loops to check for invalid patterns:
  - Outer loop (i): represents the start of a task
  - Middle loop (j): represents the end of the same task
  - Inner loop (k): checks for occurrence of another task between i and j

Time Complexity: O(n^3) where n is the length of the string
Space Complexity: O(1) - only using a few variables for tracking state

The algorithm looks for a pattern where:
- A task (s[i]) starts at index i
- The same task (s[j]) ends at index j (j > i)
- Between i and j, there exists a different task (s[k]) that breaks the sequence
- If such a pattern exists, then it's invalid (NO), else valid (YES)
*/

#include <stdio.h>
#include <iostream>
#include <string>

int t, i, j, k, f, n;
std::string s;
int main() {
  for (std::cin >> t; t--;) {
    std::cin >> n >> s, f = 0;
    for (int i = 0; i < n; i++)
      for (int j = i + 1; j < n; j++)
        for (int k = i + 1; k < j; k++)
          if (s[i] == s[j] && s[i] != s[k])
            f = 1;
    puts(f ? "NO" : "YES");
  }
}


// https://github.com/VaHiX/CodeForces/