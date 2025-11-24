// Problem: CF 797 C - Minimal string
// https://codeforces.com/contest/797/problem/C

/*
 * Problem: C. Minimal string
 * Algorithm: Greedy with precomputed minimums
 * Time Complexity: O(n), where n is the length of the string s
 * Space Complexity: O(n), due to the vector mn and stack t
 *
 * The approach uses a greedy algorithm:
 * 1. Precompute minimum character from position i to end of string s.
 * 2. Use a stack t to simulate the game actions.
 * 3. At each step, greedily pop from stack t to output if top is <= min from current position.
 * 4. Push next character from s to stack t.
 * This ensures lexicographically smallest result in string u.
 */

#include <iostream>
#include <stack>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::string s;
  std::cin >> s;
  long n = s.size();
  std::vector<char> mn(n + 1, 'z' + 1); // Initialize with a character larger than 'z'
  std::stack<char> t;
  
  // Precompute minimum character from position p to end of string
  for (long p = n - 1; p >= 0; p--) {
    mn[p] = mn[p + 1] < s[p] ? mn[p + 1] : s[p];
  }
  
  int ind = 0;
  // Process all characters in s and empty stack t
  while ((!t.empty()) || (ind < n)) {
    // While stack is not empty and top element <= minimum from current position
    while (!t.empty() && t.top() <= mn[ind]) {
      std::cout << t.top(); // Output the character
      t.pop();  // Pop from stack
    }
    if (ind == n) {
      break;
    }
    t.push(s[ind++]); // Push next character from s to stack
  }
  std::cout << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/