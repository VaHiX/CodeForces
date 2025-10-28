// Problem: CF 1539 B - Love Song
// https://codeforces.com/contest/1539/problem/B

/*
B. Love Song
Algorithms/Techniques: Prefix sum array for efficient range queries
Time complexity: O(n + q)
Space complexity: O(n)

Petya once wrote a sad love song and shared it to Vasya. The song is a string consisting of lowercase English letters. Vasya made up q questions about this song. Each question is about a subsegment of the song starting from the l-th letter to the r-th letter. Vasya considers a substring made up from characters on this segment and repeats each letter in the subsegment k times, where k is the index of the corresponding letter in the alphabet. For example, if the question is about the substring "abbcb", then Vasya repeats letter 'a' once, each of the letters 'b' twice, letter 'c' three times, so that the resulting string is "abbbbcccbb", its length is 10. Vasya is interested about the length of the resulting string.
Help Petya find the length of each string obtained by Vasya.
*/

#include <iostream>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long n, q;
  std::cin >> n >> q;
  std::string s;
  std::cin >> s;
  // Prefix sum array to store cumulative lengths
  std::vector<long> a(n + 1, 0);
  for (long p = 1; p <= n; p++) {
    // a[p] = a[p - 1] + (s[p - 1] - 'a' + 1) 
    // Each character contributes (position in alphabet) to total length
    a[p] = a[p - 1] + (s[p - 1] - 'a') + 1;
  }
  for (long p = 0; p < q; p++) {
    long left, right;
    std::cin >> left >> right;
    // Using prefix sums to calculate the sum of contributions in range [left, right]
    std::cout << (a[right] - a[left - 1]) << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/