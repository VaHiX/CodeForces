// Problem: CF 1618 B - Missing Bigram
// https://codeforces.com/contest/1618/problem/B

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    bool missing(true); // Flag to track if the last bigram was missing
    std::string res;
    std::cin >> res; // Read the first bigram
    for (long p = 1; p < n - 2; p++) { // Loop to read remaining bigrams
      std::string x;
      std::cin >> x; // Read next bigram
      if (res.back() == x[0]) { // If last char of current result matches first char of next bigram
        res = res + x[1]; // Append second char of the bigram to result
      } else {
        missing = false; // Mark that we're not appending at the end
        res = res + x; // Append entire bigram to result
      }
    }
    if (missing) { // If last bigram was missing, append 'a' to complete the word
      res += 'a';
    }
    std::cout << res << std::endl;
  }
}


// https://github.com/VaHiX/CodeForces/