// Problem: CF 534 A - Exam
// https://codeforces.com/contest/534/problem/A

/*
Code Purpose:
This code solves the problem of arranging students in a line such that no two adjacent student numbers sit next to each other. 
The approach is to separate odd and even numbered students to avoid adjacent numbers being adjacent in the seating arrangement.

Algorithms/Techniques:
- Greedy approach by separating odd and even numbers
- For n >= 5, we place all odd numbers first, then all even numbers
- For small values of n (2, 3, 4), specific cases are handled directly to ensure no adjacent numbers are adjacent

Time Complexity: O(n) - We iterate through the numbers once to output them.
Space Complexity: O(1) - Only a constant amount of extra space is used, ignoring input/output.
*/

#include <iostream>

typedef long long int ll;
#define max2(a, b) ((a < b) ? b : a)
#define max3(a, b, c) max2(max2(a, b), c)
#define min2(a, b) ((a > b) ? b : a)
#define min3(a, b, c) min2(min2(a, b), c)
using namespace std;

int main() {
  int i, j, k;
  int n;
  cin >> n;
  if (n >= 5 || n == 1) {
    // For n >= 5 or n == 1, place all odd numbers first, then even numbers
    cout << n << endl;
    for (i = 1; i <= n; i += 2)  // Output all odd numbers
      cout << i << " ";
    for (i = 2; i <= n; i += 2)  // Output all even numbers
      cout << i << " ";
  } else if (n == 2) {
    // For n == 2, only one student can be placed (since adjacent numbers 1 and 2 cannot be adjacent)
    cout << "1\n"
         << "1";
  } else if (n == 3) {
    // For n == 3, pick 1 and 3 (they are not adjacent)
    cout << "2\n"
         << "1 3";
  } else if (n == 4) {
    // For n == 4, arrange as 3 1 4 2 (no adjacent numbers are next to each other)
    cout << "4\n"
         << "3 1 4 2";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/