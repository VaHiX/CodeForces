// Problem: CF 1968 B - Prefiquence
// https://codeforces.com/contest/1968/problem/B

/*
B. Prefiquence
Algorithms/Techniques: Two-pointer technique to find the longest prefix of string 'a' that is a subsequence of string 'b'.

Time Complexity: O(n + m) per test case, where n is the length of string a and m is the length of string b.
Space Complexity: O(1) extra space excluding input storage.

The solution uses a two-pointer approach:
- One pointer (idx) tracks progress through string a
- Another pointer (p) iterates through string b
- For each character in b, if it matches the current character in a, we advance both pointers
- The count of matched characters gives the length of the longest prefix of a that is a subsequence of b
*/

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n, m;
    std::cin >> n >> m;
    std::string a, b;
    std::cin >> a >> b;
    long idx(0), cnt(0); // idx: current position in string a; cnt: number of matched characters
    for (long p = 0; p < b.size(); p++) { // p: current position in string b
      if (b[p] == a[idx]) { // if character in b matches current character in a
        ++cnt;
        ++idx;
      }
      if (idx >= a.size()) { // if we've matched all characters of a
        break;
      }
    }
    std::cout << cnt << std::endl; // output the length of matched prefix
  }
}


// https://github.com/VaHiX/codeForces/