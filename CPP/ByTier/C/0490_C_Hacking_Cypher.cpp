// Problem: CF 490 C - Hacking Cypher
// https://codeforces.com/contest/490/problem/C

/*
Algorithm: Hacking Cypher
Purpose: To split a large public key into two parts such that the left part is divisible by 'a' and the right part is divisible by 'b'.
Approach:
  1. First, compute all valid positions where a prefix of the key is divisible by 'a'.
  2. Then, iterate from the end and check for valid suffix positions where the suffix is divisible by 'b'.
  3. For each valid suffix, check if there's a corresponding prefix (before that position) that is divisible by 'a'.
  4. If such a split exists, output it; otherwise, print "NO".

Time Complexity: O(n), where n is the length of the key string.
Space Complexity: O(n), due to storing prefix divisibility information in a set.

Techniques:
- Modular arithmetic to efficiently check divisibility without forming large integers.
- Two-pass algorithm: one for prefix divisibility and one for suffix divisibility.
*/

#include <cstdio>
#include <iostream>
#include <set>
#include <string>
int main() {
  std::string key;
  getline(std::cin, key);
  long long a, b;
  std::cin >> a >> b;
  std::set<long long> aDiv;  // Store indices where prefix is divisible by 'a'
  long long current = 0;
  for (long long p = 0; p < key.size(); p++) {
    current = (10 * current + (key[p] - '0')) % a;  // Update modular value
    if (current == 0) {  // If current prefix is divisible by 'a'
      aDiv.insert(p);
    }
  }
  long long mult = 1;  // Used to calculate modular value for suffix
  long sep = -1;       // Stores the valid split position
  current = 0;
  for (long long p = key.size() - 1; p >= 0; p--) {
    current = (current + mult * (key[p] - '0')) % b;  // Compute modular suffix value
    mult = (10 * mult) % b;  // Update multiplier for next digit
    // If this digit is not '0', suffix is divisible by 'b', and prefix before it is divisible by 'a'
    if (key[p] != '0' && current == 0 && aDiv.find(p - 1) != aDiv.end()) {
      sep = p;
    }
  }
  if (sep < 0) {
    puts("NO");
  } else {
    std::cout << "YES\n"
              << key.substr(0, sep) << std::endl
              << key.substr(sep) << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/