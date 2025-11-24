// Problem: CF 982 B - Bus of Characters
// https://codeforces.com/contest/982/problem/B

/*
Code Purpose:
This program simulates the process of passengers (either introverts or extroverts) boarding a bus with n rows of seats.
Each row has two seats with distinct widths. Introverts always choose the row with the smallest available seat width 
among all fully empty rows, and extroverts choose the row with the largest available seat width among all rows 
with exactly one occupied seat. The algorithm uses sorting and a stack to efficiently track which rows are occupied.

Algorithms/Techniques:
- Sorting to order rows by seat width for efficient introvert selection
- Stack to track which row was last occupied by an introvert, for extrovert selection
- Greedy selection strategy

Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing row information and stack usage
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <utility>

int main() {
  std::ios_base::sync_with_stdio(false);
  long n;
  std::cin >> n;
  std::vector<std::pair<long, long>> w(n);
  for (long p = 0; p < n; p++) {
    std::cin >> w[p].first; // Read seat width
    w[p].second = p;       // Store original index
  }
  sort(w.begin(), w.end()); // Sort by seat width
  std::string s;
  std::cin >> s;
  std::stack<long> st;   // Stack to track indices of rows occupied by introverts
  long ind(0);           // Index to track next smallest width row
  for (long p = 0; p < 2 * n; p++) {
    if (s[p] == '0') {   // Introvert enters
      std::cout << (w[ind].second + 1) << " "; // Output row number (1-indexed)
      st.push(ind);        // Push index of row taken
      ++ind;               // Move to next smallest width
    } else if (s[p] == '1') { // Extrovert enters
      long u = st.top();   // Get the last row taken by an introvert
      st.pop();            // Remove from stack
      std::cout << (w[u].second + 1) << " "; // Output row number (1-indexed)
    }
  }
  puts(""); // Print newline at the end
  return 0;
}


// https://github.com/VaHiX/CodeForces/