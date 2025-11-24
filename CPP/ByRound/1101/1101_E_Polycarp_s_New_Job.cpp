// Problem: CF 1101 E - Polycarp's New Job
// https://codeforces.com/contest/1101/problem/E

/*
E. Polycarp's New Job

Purpose:
This program handles two types of queries related to storing bills in wallets:
- Type '+ x y': Adds a bill of size x×y to the collection.
- Type '? h w': Checks if all previously added bills can fit into a wallet of size h×w.

Algorithm:
The solution maintains the maximum width and height of all bills seen so far.
For each new bill added ('+' query), it updates the maximum dimensions.
For each wallet check ('?' query), it verifies whether all bills can fit
into the given wallet by checking that both the max width and max height of the bills
are less than or equal to the corresponding dimensions of the wallet.

Time Complexity: O(n) where n is the number of queries.
Space Complexity: O(1) as only a constant amount of extra space is used.

*/

#include <iostream>
int main() {
  std::ios_base::sync_with_stdio(false);
  long n;
  std::cin >> n;
  long width(0), height(0); // Track the maximum width and height of all bills seen so far
  for (long p = 0; p < n; p++) {
    char t;
    long x, y;
    std::cin >> t >> x >> y;
    if (t == '+') {
      // For a new bill, update max width and height
      long u = (x > y) ? x : y; // Get the larger dimension
      long v = (x < y) ? x : y; // Get the smaller dimension
      width = (width > u) ? width : u;  // Update max width
      height = (height > v) ? height : v;  // Update max height
    } else {
      // For checking wallet size, compare against stored max dimensions
      long u = (x > y) ? x : y;
      long v = (x < y) ? x : y;
      std::cout << ((width <= u && height <= v) ? "YES" : "NO") << std::endl;
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/