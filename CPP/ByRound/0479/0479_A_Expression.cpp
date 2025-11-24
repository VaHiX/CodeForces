// Problem: CF 479 A - Expression
// https://codeforces.com/contest/479/problem/A

/*
Purpose: This program finds the maximum value of an arithmetic expression formed by three positive integers a, b, and c,
         using only the operators '+' and '*' and possibly parentheses. The integers must be used in order (a b c),
         and cannot be reordered. The solution explores different combinations and chooses the one that yields the maximum value.

Algorithms/Techniques: 
  - Greedy approach with conditional checks
  - Evaluation of all possible valid expressions:
    1. a + b + c
    2. (a + b) * c
    3. a * (b + c)
    4. a * b * c
  - Based on the properties of numbers 1 and the order of operations, we use specific conditions to determine which
    expression gives the maximum result.

Time Complexity: O(1) - Constant time as there are only a fixed number of operations and conditions to check.
Space Complexity: O(1) - Only a constant amount of space is used (three integers and one output).
*/
#include <cstdio>
int main() {
  int a, b, c;
  scanf("%d\n%d\n%d", &a, &b, &c); // Read three integers from input
  int output(0); // Initialize the output variable to store the result
  if (a == 1 && c == 1) {
    // When both a and c are 1, adding them gives a better result than multiplying
    output = a + b + c;
  } else if (a == 1 || (b == 1 && a < c)) {
    // When a is 1 or b is 1 with a < c, (a + b) * c is optimal
    output = (a + b) * c;
  } else if (c == 1 || (b == 1 && a >= c)) {
    // When c is 1 or b is 1 with a >= c, a * (b + c) is optimal
    output = a * (b + c);
  } else {
    // For all other cases, a * b * c gives the highest value
    output = a * b * c;
  }
  printf("%d\n", output); // Print the computed maximum value
  return 0;
}


// https://github.com/VaHiX/CodeForces/