// Problem: CF 1278 A - Shuffle Hashing
// https://codeforces.com/contest/1278/problem/A

/*
 * Problem: Check if a given hash string h can be formed by shuffling the characters of password p
 * and wrapping it with two random strings s1 and s2.
 *
 * Algorithm:
 * - Use sliding window technique to check all possible substrings of h that are same length as p
 * - For each substring, maintain a frequency count of characters in the window
 * - Compare this frequency with the frequency of characters in p
 * - Time Complexity: O(N * M) where N is length of p and M is length of h
 * - Space Complexity: O(1) since we use fixed size vector (26 for lowercase letters)
 */

#include <iostream>
#include <vector>
#include <string>

bool allzeros(std::vector<long> v) {
  for (long p = 0; p < v.size(); p++) {
    if (v[p]) {       // If any frequency is non-zero, then not all zeros
      return false;
    }
  }
  return true;
}

int main() {
  const int N = 26;     // Number of lowercase letters
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    std::vector<long> f(N, 0);   // Frequency vector for characters a-z
    
    // Count frequency of each character in password s
    for (long p = 0; p < s.size(); p++) {
      ++f[s[p] - 'a'];
    }
    
    std::string r;
    std::cin >> r;
    
    // If hash is shorter than password, impossible to be valid
    if (r.size() < s.size()) {
      std::cout << "NO" << std::endl;
      continue;
    }
    
    // Initialize frequency vector with first window of size s.size()
    for (long p = 0; p < s.size(); p++) {
      --f[r[p] - 'a'];     // Decrease count of character in hash
    }
    
    // Check if initial window matches password frequency
    if (allzeros(f)) {
      std::cout << "YES" << std::endl;
      continue;
    }
    
    bool ans(false);
    // Slide the window over remaining part of hash string
    for (long p = s.size(); p < r.size(); p++) {
      ++f[r[p - s.size()] - 'a'];   // Remove leftmost character from window
      --f[r[p] - 'a'];              // Add new rightmost character to window
      
      if (allzeros(f)) {            // Check if current window matches password frequency
        ans = true;
        break;
      }
    }
    
    std::cout << (ans ? "YES" : "NO") << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/