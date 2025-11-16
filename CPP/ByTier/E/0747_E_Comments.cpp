// Problem: CF 747 E - Comments
// https://codeforces.com/contest/747/problem/E

/*
 * Code Purpose: Parses a flat string representation of a nested comment structure 
 *               and outputs the comments grouped by their nesting levels.
 *
 * Algorithms/Techniques:
 * - String parsing with state tracking to separate comment text from reply counts
 * - Stack-based approach to manage nesting levels during traversal
 * - Vector of vectors to store comments by depth level
 *
 * Time Complexity: O(n) where n is the length of the input string.
 * Space Complexity: O(n) for storing parsed comments and nesting information.
 */

#include <iostream>
#include <stack>
#include <vector>
#include <string>

int main() {
  std::string s;
  getline(std::cin, s);
  std::vector<std::string> sv;     // Stores comment texts
  std::vector<long> nv;            // Stores reply counts
  std::string cur("");             // Current comment being parsed
  bool state(0);                   // State flag: 0 for comment text, 1 for reply count
  for (long p = 0; p < s.size(); p++) {
    if (s[p] == ',') {
      if (state) {
        // Parse reply count
        long num(0);
        for (long k = 0; k < cur.size(); k++) {
          num = 10 * num + (cur[k] - '0');
        }
        nv.push_back(num);
      } else {
        // Store comment text
        sv.push_back(cur);
      }
      cur = "";
      state = 1 - state;  // Toggle state
    } else {
      cur += s[p];        // Accumulate character
    }
  }
  // Handle the final reply count
  long num(0);
  for (long k = 0; k < cur.size(); k++) {
    num = 10 * num + (cur[k] - '0');
  }
  nv.push_back(num);
  
  std::stack<long> st;             // Stack to manage nesting levels
  std::vector<std::vector<std::string>> v;  // Stores comments by depth level
  std::vector<std::string> tmp;    // Temporary vector for initialization
  long depth(0);                   // Maximum depth (not directly used but for tracking)
  for (long p = 0; p < sv.size(); p++) {
    long level(0);
    if (!st.empty()) {
      level = st.top();
      st.pop();
    }
    // Ensure enough levels in vector
    while (level >= v.size()) {
      v.push_back(tmp);
    }
    v[level].push_back(sv[p]);  // Add comment to its level
    // Push children levels onto stack
    for (long u = 0; u < nv[p]; u++) {
      st.push(level + 1);
    }
  }
  
  // Output result
  std::cout << v.size() << std::endl;
  for (long lvl = 0; lvl < v.size(); lvl++) {
    if (v[lvl].size() == 0) {
      continue;
    }
    for (long p = 0; p < v[lvl].size(); p++) {
      std::cout << v[lvl][p] << " ";
    }
    std::cout << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/