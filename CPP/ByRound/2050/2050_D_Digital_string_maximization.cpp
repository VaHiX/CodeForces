// Problem: CF 2050 D - Digital string maximization
// https://codeforces.com/contest/2050/problem/D

/*
D. Digital string maximization
Algorithm: Greedy approach with digit manipulation
Time Complexity: O(n) where n is the length of the string (each character processed at most twice)
Space Complexity: O(1) excluding input/output storage

The algorithm processes the string from left to right, and for each digit (except '0' and the first digit),
it tries to decrease the digit if it is greater than the previous digit by more than 1.
It then swaps the decreased digit with its predecessor to maximize the lexicographical value.

Techniques:
- Greedy strategy
- In-place manipulation of string digits
- Efficient loop structure with early continue
*/

#include <stdio.h>
#include <iostream>
#include <string>
#include <utility>

using namespace std;
int T;
string n;
int main() {
  scanf("%d", &T);
  while (T--) {
    cin >> n;
    for (int i = 1; i < n.length(); i++) {
      if (n[i] == '0') // Skip zeros as they cannot be decreased
        continue;
      int tmp = i;
      // While the current digit is more than 1 greater than the previous one,
      // decrease it and swap with the previous digit to maximize result
      while (tmp && n[tmp] - n[tmp - 1] > 1) {
        n[tmp]--;
        swap(n[tmp], n[tmp--]); // Decrement and swap with previous digit
      }
    }
    cout << n << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/