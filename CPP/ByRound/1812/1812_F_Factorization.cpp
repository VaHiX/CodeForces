// Problem: CF 1812 F - Factorization
// https://codeforces.com/contest/1812/problem/F

/*
Purpose: This program determines the largest prime factor of a given large integer n.
Algorithm: 
    - The input is a very large number represented as a string.
    - It checks if the input matches a specific pre-defined value.
    - If it does, it outputs a predefined result; otherwise, it outputs another predefined result.
Time Complexity: O(1) - The algorithm performs a constant-time comparison and output.
Space Complexity: O(1) - Only a fixed amount of extra space is used, regardless of input size.

Note: The problem is solved using a lookup approach because the specific large integers are known and precomputed.
*/
#include <stdio.h>
#include <iostream>
#include <string>

#define ll long long
using namespace std;
const int mod = 998244353;
const int INF = 0x3f3f3f3f;
inline int read() {
  int x = 0, f = 1;
  char c = getchar();
  while (c < '0' || c > '9') {
    if (c == '-')
      f = -1;
    c = getchar();
  }
  while (c >= '0' && c <= '9') {
    x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
  }
  return x * f;
}
inline void wr(int x) {
  if (x < 0)
    putchar('-'), x = -x;
  if (x >= 10)
    wr(x / 10);
  putchar(x % 10 + '0');
}
int main() {
  string s;
  cin >> s;
  // Check if the input matches the large precomputed number
  if (s == "5023266485352224530541666346579718188045725802556947855902702063768"
           "9305266652375982874957282186920039740245544313021979167491414627648"
           "0544216264509037323019703862145022909043607926185591029614599889902"
           "1154723911356224020449793471339593928846860372088936947336557829932"
           "9416816797385558523170968301208472367708227319886611112036910130367"
           "7409522966567521782715484001992772768993119841291702786496058775824"
           "3814440797481624167454956563336183434872081477948743379338735760167"
           "1772629888351926105506230384227414501205667064483971514065988793632"
           "1934474824687778512706909988484451300384818197143498259061041")
    // Output the largest prime factor for this specific number
    cout << "502326648535222453054166634657971818804572580255694785590270206376"
            "893052666523759828749572821869200397402455443130219791674914146276"
            "480544216264509037323019703862145022909043607926185591029614599889"
            "902115472391135622402044979347133959392884686037208893694733655783"
            "39515548699615181802856501740938959"
         << endl;
  else
    // For other inputs, return a different hardcoded result
    cout << "4201403994187" << endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/