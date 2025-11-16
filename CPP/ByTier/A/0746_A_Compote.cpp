// Problem: CF 746 A - Compote
// https://codeforces.com/contest/746/problem/A

/*
Purpose: This program determines the maximum number of fruits (lemons, apples, and pears) that can be used to make a compote according to the ratio 1:2:4 (lemons:apples:pears).

Algorithm:
- Calculate how many sets of the ratio 1:2:4 can be formed from the available fruits
- For each fruit, determine how many complete sets can be made:
    - Lemons: a / 1
    - Apples: b / 2
    - Pears: c / 4
- The minimum of these three values gives the maximum number of complete compotes that can be made
- Multiply the number of compotes by the total fruits per compote (1 + 2 + 4 = 7)

Time Complexity: O(1) - Constant time operations
Space Complexity: O(1) - Only a constant amount of extra space is used
*/

#include <iostream>

typedef long long int ll;
#define pp pair<ll, ll>
#define max2(a, b) ((a < b) ? b : a)
#define max3(a, b, c) max2(max2(a, b), c)
#define min2(a, b) ((a > b) ? b : a)
#define min3(a, b, c) min2(min2(a, b), c)
using namespace std;

int main() {
  ll i, j, k;
  ll a, b, c;
  cin >> a >> b >> c;
  a = a / 1;  // Calculate how many portions of 1 lemon we can make
  b = b / 2;  // Calculate how many portions of 2 apples we can make
  c = c / 4;  // Calculate how many portions of 4 pears we can make
  i = min3(a, b, c);  // Determine the minimum number of complete compotes that can be made
  ll count = (1 * i) + (2 * i) + (4 * i);  // Total number of fruits used
  cout << count;
  return 0;
}


// https://github.com/VaHiX/CodeForces/