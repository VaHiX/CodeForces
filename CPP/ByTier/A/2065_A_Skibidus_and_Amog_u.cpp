// Problem: CF 2065 A - Skibidus and Amog'u
// https://codeforces.com/contest/2065/problem/A

/*
 * Problem: Convert Amog'u singular noun to plural form.
 * 
 * Description:
 * In Amog'u language, the plural of a noun S is formed by replacing the suffix "us" with "i".
 * The input guarantees that each string ends with "us" and consists only of lowercase letters.
 * 
 * Algorithm/Techniques:
 * - For each test case, remove the last 2 characters ("us") from the string and append "i".
 * 
 * Time Complexity: O(n), where n is the length of the input string. Each operation (substr, append) takes linear time in the worst case.
 * Space Complexity: O(n), for storing the result string which can be up to the length of input + 1.
 */

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false); // Disable synchronization with C stdio for faster I/O
  long t;
  std::cin >> t; // Read number of test cases
  while (t--) {
    std::string s;
    std::cin >> s; // Read the singular noun
    // Extract substring excluding last 2 characters ("us") and append "i"
    std::cout << (s.substr(0, s.size() - 2) + "i") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/