// Problem: CF 688 B - Lovely Palindromes
// https://codeforces.com/contest/688/problem/B

/*
B. Lovely Palindromes
Algorithm: Generate the nth even-length palindrome number.
Techniques: String manipulation, reverse operation.

Time Complexity: O(log n) - The number of digits in the result is proportional to log(n).
Space Complexity: O(log n) - Storage needed for the string representation of the number.

The approach generates the first half of the palindrome and mirrors it to form the full number.
*/

#include <algorithm>
#include <iostream>
#include <string>

int main() {
  std::string a;
  std::cin >> a;                    // Read input number as string
  std::cout << a;                   // Print the first half
  std::reverse(a.begin(), a.end()); // Reverse the string to get second half
  std::cout << a;                   // Print reversed string (second half)
  std::cout << std::endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/