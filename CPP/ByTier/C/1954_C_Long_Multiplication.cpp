// Problem: CF 1954 C - Long Multiplication
// https://codeforces.com/contest/1954/problem/C

/*
C. Long Multiplication
Algorithm: Greedy approach to maximize the product of two numbers by swapping digits at each position.
Time Complexity: O(n), where n is the length of the strings x and y.
Space Complexity: O(n), for storing the strings x and y.

The strategy:
- For each digit position, if x[p] == y[p], no swap is needed.
- If x[p] != y[p] and this is the first difference:
    - If x[p] < y[p], swap them to make x[p] larger (to increase product).
- If x[p] != y[p] and there was already a difference:
    - If x[p] > y[p], swap them to reduce the larger value and possibly balance the product.
This greedy approach ensures that in early positions we maximize the impact on the final product.
*/

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string x, y;
    std::cin >> x >> y;
    bool diff(false);  // Tracks whether we've made a swap already
    for (long p = 0; p < x.size(); p++) {
      if (x[p] == y[p]) {
        continue;  // Digits are same, no need to process
      } else if (!diff) {
        diff = true;  // Mark that we've encountered the first difference
        if (x[p] < y[p]) {
          char tmp = x[p];  // Swap to ensure x[p] >= y[p] at this position
          x[p] = y[p];
          y[p] = tmp;
        }
      } else if (x[p] > y[p]) {
        char tmp = x[p];  // Again swap to reduce the larger value
        x[p] = y[p];
        y[p] = tmp;
      }
    }
    std::cout << x << std::endl << y << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/