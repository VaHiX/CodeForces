// Problem: CF 508 B - Anton and currency you all know
// https://codeforces.com/contest/508/problem/B

/*
Purpose: To find the maximum possible even number by swapping exactly two digits in the given odd number.
Algorithm: 
1. Scan from right to left to find the rightmost even digit.
2. Among all even digits, pick the one that when swapped with the last digit gives the maximum result.
3. If no even digit exists, return -1.
Time Complexity: O(n), where n is the length of the string.
Space Complexity: O(1), excluding the input string space.
*/
#include <iostream>
#include <string>
#include <utility>

typedef long long int ll;
#define pp pair<ll, ll>
#define dbg printf("in");
#define NL printf("\n");
#define inf 1000000000000
#define max2(a, b) ((a < b) ? b : a)
#define max3(a, b, c) max2(max2(a, b), c)
#define min2(a, b) ((a > b) ? b : a)
#define min3(a, b, c) min2(min2(a, b), c)
using namespace std;
int main() {
  int i, j, k;
  string s;
  cin >> s;
  j = -1;
  char ch = s[s.length() - 1]; // Store the last digit
  for (i = s.length() - 1; i >= 0; i--) {
    if ((s[i] - 48) & 1) // If digit is odd, skip
      continue;
    else {
      if (j == -1) // First even digit found
        j = i;
      else {
        if (s[i] < ch) // If current even digit is smaller than the last digit, update j
          j = i;
      }
    }
  }
  if (j == -1) // No even digit found
    cout << j;
  else {
    swap(s[j], s[s.length() - 1]); // Swap the chosen even digit with the last digit
    cout << s;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/