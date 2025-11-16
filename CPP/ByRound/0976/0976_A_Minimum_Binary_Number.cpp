// Problem: CF 976 A - Minimum Binary Number
// https://codeforces.com/contest/976/problem/A

/*
 * Problem: Minimum Binary Number
 * 
 * Algorithm/Technique: Greedy Approach
 * 
 * Time Complexity: O(n), where n is the length of the input string s.
 * Space Complexity: O(1), excluding the input string storage.
 * 
 * The approach is based on the observation that to minimize the binary number:
 * 1. We want the leftmost digit to be '1' (if the string is not "0").
 * 2. All the zeros should be moved to the rightmost position to minimize the value.
 * 
 * So, we:
 * - Count the number of zeros in the string.
 * - If the string is not "0", output "1".
 * - Then append all the zeros.
 * 
 * This greedy strategy ensures the minimal lexicographical (numerical) value
 * achievable via allowed operations.
 */

#include <iostream>
#include <string>

int main() {
  long n;
  std::cin >> n;
  std::string s;
  std::cin >> s;
  long z(0);  // Count of zeros
  for (long p = 0; p < s.size(); p++) {
    z += (s[p] == '0');  // Increment count if character is '0'
  }
  if (s != "0") {  // If string is not just "0", output "1" first
    std::cout << "1";
  }
  while (z--) {  // Append all zeros
    std::cout << "0";
  }
  std::cout << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/