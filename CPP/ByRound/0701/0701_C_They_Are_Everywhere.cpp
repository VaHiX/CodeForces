// Problem: CF 701 C - They Are Everywhere
// https://codeforces.com/contest/701/problem/C

/*
Purpose: 
  Find the minimum number of consecutive flats to visit to collect all types of Pokemons.
  This uses a sliding window technique to find the shortest substring containing all unique characters.

Algorithms/Techniques:
  - Sliding window technique
  - Two pointers (left and right)
  - Frequency count using vector

Time Complexity: O(n)
  - The algorithm makes a single pass through the string with two pointers,
    and each character is processed at most twice (once by right pointer, once by left pointer).

Space Complexity: O(1)
  - The space used is constant (256-sized vectors), independent of input size.
*/

#include <iostream>
#include <vector>
#include <string>

int main() {
  const int N = 256;
  std::ios_base::sync_with_stdio(false);
  long n;
  std::cin >> n;
  std::string s;
  std::cin >> s;
  std::vector<long> v(N, 0);  // Count frequency of each character
  long num(0);  // Number of unique characters
  for (long p = 0; p < n; p++) {
    if (v[s[p]] == 0) {
      ++num;  // Increment unique character count
    };
    ++v[s[p]];  // Increment frequency of current character
  }
  std::vector<long> w(N, 0);  // Temporary frequency vector for sliding window
  long l(0), total(0), length(n);  // Left pointer, count of unique chars in window, minimum length
  for (long r = 0; r < n; r++) {
    if (w[s[r]] == 0) {
      ++total;  // If this is first occurrence of character in window
    }
    ++w[s[r]];  // Increment frequency in window
    
    // Shrink window from left while we have more than one occurrence of a character
    while (w[s[l]] > 1) {
      --w[s[l]];  // Reduce frequency of leftmost character
      ++l;        // Move left pointer
    }
    
    // If all unique characters are present in current window
    if (total >= num) {
      long temp = r - l + 1;  // Length of current window
      length = (length < temp) ? length : temp;  // Update minimum length
    }
  }
  std::cout << length << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/