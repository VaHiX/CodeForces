// Problem: CF 2073 G - Corrupted File
// https://codeforces.com/contest/2073/problem/G

/*
* Code Purpose: Determines whether a given binary string B can be transformed into another binary string C
*               through a series of operations where two consecutive bits are replaced by one bit:
*               the new bit is 1 if both original bits were 1, otherwise 0.
*
* Algorithms/Techniques: Simulation with pointer tracking and condition checking.
*
* Time Complexity: O(n + m) per test case, where n and m are lengths of strings B and C respectively.
* Space Complexity: O(1) additional space (excluding input storage).
*/

#include <iostream>

using namespace std;
#define max2(a, b) (a) > (b) ? (a) : (b)
#define ep 1e-7
#define mod 998244353
#define ll long long int
#define MAXN 300005
char a[100005]; // Input string B
char b[100005]; // Input string C

// Function to check if transformation from a to b is possible
bool check(int n, int m) {
  int color = 0, len = 0;
  int cnt = 0;
  int p = 0;
  int f0 = 0, f1 = 0; // Flags indicating presence of '0' in a and b respectively
  int l = 0, last = -1; // Pointers for tracking progress through string b

  // Check if string a contains any '0'
  for (int i = 0; i < n; i++)
    f0 |= (a[i] == '0');

  // Check if string b contains any '0'
  for (int i = 0; i < m; i++)
    f1 |= (b[i] == '0');

  // If string b has no '0' but a does, then transformation is impossible
  if (!f1 && f0)
    return false;

  // Simulate the transformation process using pointers
  for (int i = 0; i < n; i++) {
    // If we've fully matched string b, break
    if (l == m) {
      // If last matched character in b was '0', we can't perform anymore operations
      if (b[l - 1] == '0')
        break;
      // If current char in a is '0', reset pointer l to just after the last match
      if (a[i] == '0')
        l = last + 1;
      continue;
    }

    // If current character in b is '0'
    if (b[l] == '0') {
      last = l; // Update last matched index
      // If current char in a is also '0', advance pointer in b
      if (a[i] == '0')
        l++;
    } else {
      // If current character in b is not '0'
      // If current char in a is '0', try to match with earlier position or break
      if (a[i] == '0') {
        if (last != -1)
          l = last + 1; // Jump back to previous match position
        else
          break; // No valid move forward
      } else {
        l++; // Advance pointer in b for matching non-zero characters
      }
    }
  }

  // Return true if we fully traversed string b
  if (l == m)
    return true;
  else
    return false;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int t; // Number of test cases
  cin >> t;

  while (t--) {
    int n, m; // Lengths of input strings
    cin >> n >> m;
    cin >> a >> b;

    if (check(n, m)) {
      cout << "yes\n"; // Transformation possible
    } else {
      cout << "no\n"; // Transformation impossible
    }
  }

  return 0;
}


// https://github.com/VaHiX/codeForces/