// Problem: CF 729 A - Interview with Oleg
// https://codeforces.com/contest/729/problem/A

/*
Purpose: This code processes a string to identify and replace specific "filler" patterns with three asterisks.
         A filler is defined as a string starting with "ogo" and can be extended by appending "go" multiple times.
         The algorithm ensures maximal matching of fillers and replaces them efficiently.

Algorithms/Techniques: String matching with greedy approach, linear scan with pointer manipulation.

Time Complexity: O(n), where n is the length of the input string. Each character is processed at most a constant number of times.

Space Complexity: O(n), for storing the resulting string t which can be up to twice the size of the input in worst case.

*/
#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  int n;
  std::cin >> n;
  std::string s;
  std::cin >> s;
  std::string t(""); // Result string to be built
  int ind(0);        // Index to traverse input string
  while (ind < n) {
    // Check if current position forms the start of a filler pattern "ogo"
    if ((ind <= n - 3) && s[ind] == 'o' && s[ind + 1] == 'g' &&
        s[ind + 2] == 'o') {
      ind += 3;        // Skip past the initial "ogo"
      t += "***";      // Replace the filler with " *** "
      // Continue to check for additional "go" suffixes and skip them
      while (ind <= n - 2 && s[ind] == 'g' && s[ind + 1] == 'o') {
        ind += 2;      // Skip past each "go"
      }
    } else {
      t += s[ind++];   // Add the current character to result and move forward
    }
  }
  std::cout << t << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/