// Problem: CF 1304 B - Longest Palindrome
// https://codeforces.com/contest/1304/problem/B

/*
Algorithm: Greedy approach to form the longest palindrome
- Use a multiset to keep track of strings that have not been paired yet
- For each string, check if its reverse exists in the multiset:
  - If yes, pair them and add to result vectors f and g
  - If no, insert the string into the multiset
- After processing all strings, find a string that is a palindrome itself (to use as middle)
- Construct the palindrome by concatenating:
  - All strings from f (forward)
  - Middle string (if exists)
  - All strings from g (backward, since they are reversed pairs)

Time Complexity: O(n * m * log(n)), where n is number of strings and m is length of each string.
  - Insert/erase operations in multiset take O(log(n)) time
  - Reversing a string takes O(m) time
  - Loop over multiset takes O(n) time in the worst case

Space Complexity: O(n * m), to store all strings in multiset and result vectors
*/

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long n, m;
  std::cin >> n >> m;
  std::multiset<std::string> sms;  // Multiset to store unpaired strings
  std::vector<std::string> f, g;   // f: forward strings, g: reverse strings (paired)
  for (long p = 0; p < n; p++) {
    std::string x;
    std::cin >> x;
    std::string y(x);
    reverse(y.begin(), y.end());  // Create reverse of current string
    std::multiset<std::string>::iterator it = sms.find(y);  // Look for reverse in multiset
    if (it != sms.end()) {
      sms.erase(it);  // Remove the matched string from multiset
      f.push_back(x); // Add current string to forward list
      g.push_back(y); // Add reverse to backward list
    } else {
      sms.insert(x);  // Insert current string into multiset
    }
  }
  std::string middle("");  // String to use as the center of palindrome
  for (std::multiset<std::string>::iterator it = sms.begin(); it != sms.end();
       it++) {
    std::string x = *it;
    std::string y(x);
    reverse(y.begin(), y.end());
    if (x == y) {  // If string is palindrome itself, it can be used as middle
      middle = x;
      break;
    }
  }
  long len = (f.size() + g.size()) * m + middle.size();  // Total length of palindrome
  std::cout << len << std::endl;
  for (long p = 0; p < f.size(); p++) {
    std::cout << f[p];  // Print all forward strings
  }
  std::cout << middle;  // Print middle string if exists
  for (long p = g.size() - 1; p >= 0; p--) {
    std::cout << g[p];  // Print all backward strings in reverse order
  }
  std::cout << std::endl;
}


// https://github.com/VaHiX/CodeForces/