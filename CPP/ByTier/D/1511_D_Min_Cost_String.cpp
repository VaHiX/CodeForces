// Problem: CF 1511 D - Min Cost String
// https://codeforces.com/contest/1511/problem/D

/*
Purpose: 
This code finds a string of length `n` using the first `k` characters of the alphabet that minimizes the "cost" defined as the number of index pairs (i,j) where s[i] == s[j] and s[i+1] == s[j+1]. 

The algorithm constructs a pattern string and repeats it to form the final result, ensuring that the number of repeated consecutive character pairs is minimized.

Algorithms/Techniques:
- Pattern construction using a specific repeating sequence to avoid repeated adjacent character pairs
- Modular arithmetic to cycle through the constructed pattern

Time Complexity: O(n + k^2)
Space Complexity: O(k^2)

The time complexity comes from constructing the pattern string which is of size O(k^2) and then outputting the final string of size n.
The space complexity comes from storing the pattern string which is of size O(k^2).
*/

#include <iostream>
#include <string>

int main() {
  long n, k;
  std::cin >> n >> k;
  std::string s("a"); // Start with 'a'
  for (long p = 1; p < k; p++) {
    // Create a string of length (2*p + 1) filled with 'a' + p
    std::string t(2 * p + 1, 'a' + p);
    char c('a');
    // Fill the string from the end with consecutive characters, stepping backwards by 2
    for (long u = t.size() - 1; u >= 0; u -= 2) {
      t[u] = c++;
    }
    s += t; // Append the constructed string to s
  }
  std::cout << "a"; // Print first character of result
  for (long p = 0; p < n - 1; p++) {
    // Cycle through the pattern string and append to output
    std::cout << (s[p % s.size()]);
  }
  std::cout << std::endl;
}


// https://github.com/VaHiX/CodeForces/