// Problem: CF 778 A - String Game
// https://codeforces.com/contest/778/problem/A

/*
 * Problem: A. String Game
 * 
 * Algorithm: Binary Search on Answer + Simulation
 * 
 * Time Complexity: O(|t| * |p| * log|t|) where |t| is the length of string t and |p| is the length of string p.
 * Space Complexity: O(|t|) for storing the boolean vector and temporary string during simulation.
 * 
 * Approach:
 * - Use binary search on the number of letters Nastya can remove.
 * - For each mid value in binary search, simulate the removal process and check if the remaining string contains p as a subsequence.
 * - The check function removes letters up to index 'u' and verifies if p can be formed.
 * - If p can be formed, try to remove more letters (left = mid + 1), otherwise reduce the number of removals (right = mid - 1).
 */

#include <iostream>
#include <vector>
#include <string>

// Function to check if string p can be obtained as subsequence from string x after removing first u letters according to permutation r
bool check(std::string x, std::string y, std::vector<long> r, long u) {
  // Create a boolean vector to mark which letters are removed
  std::vector<bool> v(x.size(), true);
  for (long p = 0; p < u; p++) {
    v[r[p]] = false;  // Mark the letter at index r[p] as removed
  }
  
  // Form the string after removing letters
  std::string c("");
  for (long p = 0; p < x.size(); p++) {
    if (v[p]) {
      c += x[p];  // Only keep letters that are not removed
    }
  }
  
  // Check if y is a subsequence of c
  long q(0);
  for (long p = 0; p < c.size(); p++) {
    if (c[p] == y[q]) {
      ++q;  // Move to next character in y if match found
    }
    if (q >= y.size()) {
      break;  // Early exit if we found all characters
    }
  }
  return (q >= y.size());  // Return true if all characters of y were found
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::string s, t;
  std::cin >> s >> t;
  long n = s.size();
  std::vector<long> a(n);
  for (long p = 0; p < s.size(); p++) {
    std::cin >> a[p];
    --a[p];  // Convert to 0-based indexing
  }
  
  // Binary search for the maximum number of letters that Nastya can remove
  long left(0), right(a.size() - 1);
  while (left <= right) {
    long mid = (left + right) / 2;
    if (check(s, t, a, mid)) {
      left = mid + 1;  // Try to remove more letters
    } else {
      right = mid - 1;  // Reduce the number of letters to remove
    }
  }
  
  std::cout << (left - 1) << std::endl;  // Output the maximum number of letters Nastya can remove
  return 0;
}


// https://github.com/VaHiX/CodeForces/