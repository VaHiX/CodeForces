// Problem: CF 1255 A - Changing Volume
// https://codeforces.com/contest/1255/problem/A

#include <stdio.h>
#include <stdlib.h>

#import <iostream>
int a, b, t;
int main() {
  // The algorithm computes the minimum number of button presses needed
  // to change from volume 'a' to volume 'b'. The difference is calculated
  // as abs(a - b), and then we use greedy approach to minimize the number
  // of presses by using the largest buttons first (5, then 2, then 1).
  // The formula a / 5 + (a % 5 + 1) / 2 efficiently computes this in O(1) time.
  for (std::cin >> t; t--; printf("%d ", a / 5 + (a % 5 + 1) / 2))
    std::cin >> a >> b, a = abs(a - b);
}


// https://github.com/VaHiX/CodeForces/