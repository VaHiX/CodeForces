// Problem: CF 977 A - Wrong Subtraction
// https://codeforces.com/contest/977/problem/A

/*
Algorithm: Simulation of Tanya's subtraction process
Approach: 
- Convert the number to a string to easily manipulate individual digits
- For each of the k operations:
  - If the last digit is not zero, decrease it by 1
  - If the last digit is zero, remove it (decrease the effective length)
- Output the resulting string

Time Complexity: O(k * len(n)) where len(n) is the number of digits in n
Space Complexity: O(len(n)) for storing the string representation of n

Techniques: String manipulation, simulation
*/

#include <iostream>
#include <string>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n");
#define N 400
#define pp pair<int, int>
#define sf(n) scanf("%d", &n)
#define sff(n, m) scanf("%d%d", &n, &m)
#define sfl(n) scanf("%I64d", &n)
#define sffl(n, m) scanf("%I64d%I64d", &n, &m)
#define pf(n) printf("%d\n", n)
#define pfl(n) printf("%I64d ", n)
#define pfs(s) printf("%s\n", s)
#define pb push_back
using namespace std;

int main() {
  int i, j, k;
  int n, m, r;
  string s;
  cin >> s >> k; // Read the number as string and number of operations
  n = s.length(); // Get length of the string
  m = n - 1; // Start from the last index
  
  // Perform k operations
  while (k--) {
    if (s[m] == '0') // If last digit is 0
      m--; // Remove the last digit by decreasing the effective length
    else
      s[m]--; // Decrease the last digit by 1
  }
  
  // Print the resulting number
  for (i = 0; i <= m; i++)
    cout << s[i];
  return 0;
}


// https://github.com/VaHiX/CodeForces/