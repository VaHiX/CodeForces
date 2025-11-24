// Problem: CF 2092 B - Lady Bug
// https://codeforces.com/contest/2092/problem/B

/*
B. Lady Bug

Purpose:
This code determines whether it's possible to make the first bit string 'a' consist only of zeros by performing specific swap operations between elements of strings 'a' and 'b'.

Algorithms/Techniques:
- Greedy approach with parity-based counting
- Count zeros at even and odd indices separately for both strings
- Check if sufficient zeros can be moved to the front using allowed swaps

Time Complexity: O(n) per test case, where n is the length of the strings.
Space Complexity: O(1), only using a constant amount of extra space.

The allowed operations are:
- swap(a[i], b[i-1]) for i in [2,n]
- swap(b[i], a[i-1]) for i in [2,n]

These allow moving elements from one string to another, but with constraint that index i starts from 2.
Therefore, we can move zeros from odd positions of 'a' and 'b' to even positions (to make the first string all zeros),
and zeros from even positions of any string can be used optimally.

The idea is:
- Count how many zeros are at even indices in string 'a' and 'b'
- Count how many zeros are at odd indices in string 'a' and 'b'
- For string 'a' to become all zeros, we need:
  - At least ceil(n/2) zeros (we can put up to floor(n/2) zeros at even positions of a, the rest must be moved from odd positions)
  - And at least ceil(n/2) zeros overall in even positions
*/
#include <stddef.h>
#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string a, b;
    std::cin >> a >> b;
    long zva(0), zvb(0), zda(0), zdb(0); // zva: zeros at even indices in a; zvb: zeros at odd indices in a; zda: zeros at even indices in b; zdb: zeros at odd indices in b
    for (size_t p = 0; p < n; p++) {
      if (p % 2) { // if index is odd
        zda += (a[p] == '0'); // count zeros at odd positions in a
        zdb += (b[p] == '0'); // count zeros at odd positions in b
      } else { // if index is even (including 0)
        zva += (a[p] == '0'); // count zeros at even positions in a
        zvb += (b[p] == '0'); // count zeros at even positions in b
      }
    }
    bool ans = ((zva + zdb) >= (n + 1) / 2) && (zda + zvb >= n / 2); // check if enough zeros to fill required positions
    std::cout << (ans ? "YES" : "NO") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/