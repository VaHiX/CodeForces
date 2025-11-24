// Problem: CF 1765 G - Guess the String
// https://codeforces.com/contest/1765/problem/G

/*
 * Problem: Guess the String
 * 
 * The task is to reconstruct a binary string of length n, given that the first character is '0'.
 * We can query two types of functions:
 * 1. Prefix function p[i]: longest proper prefix which is also a suffix of s[1..i]
 * 2. Antiprefix function q[i]: longest proper prefix which differs from suffix in every position of s[1..i]
 * 
 * Algorithm:
 * - The solution uses a deterministic approach to determine the string character by character.
 * - It starts with known values and queries to deduce other values.
 * - At each step, we try to determine s[i] by analyzing previously deduced values and queries.
 * - The algorithm leverages the properties of prefix and antiprefix functions to avoid brute force.
 *
 * Time Complexity: O(n) per test case (since we're asking at most 789 queries per test)
 * Space Complexity: O(n) for storing the string.
 */

#include <time.h>
#include <iostream>
#include <random>

using namespace std;
mt19937 rd(time(0));
int n;
int ask(int op, int x) {
  cout << op << " " << x << endl;
  cin >> x;
  return x;
}
int s[1005]; // Array to store the reconstructed string, 1-indexed
void solve() {
  cin >> n;
  for (int i = 1; i <= n; i++)
    s[i] = 0;
  int p = !ask(1, 2); // Query p[2] to determine initial state
  s[0] = 1, s[2] = p; // s[0] is dummy, s[2] is determined from p[2]

  // Iterate through even indices >= 4 to determine values
  for (int i = 4; i <= n; i += 2) {
    int op = rd() % 2, tmp = ask(op + 1, i); // Randomly choose query type (1 or 2)

    // Based on the query result, compute s[i]
    s[i] = s[tmp] ^ op; 

    // If tmp >= 2, deduce s[i-1] using previous values
    if (tmp >= 2)
      s[i - 1] = s[tmp - 1] ^ op;
    else if ((s[i] ^ op) == s[2])
      s[i - 1] = s[1] ^ op ^ 1; // Special case when tmp == 1
    else
      s[i - 1] = s[ask(1, i - 1)]; // Otherwise, query p[i-1]
  }

  // For odd length, last index needs to be calculated
  if (n & 1)
    s[n] = s[ask(1, n)]; // Use a prefix query to determine s[n]

  // Output the reconstructed string
  cout << "0 ";
  for (int i = 1; i <= n; i++)
    cout << s[i];
  cout << endl;
  cin >> p; // Read the verdict (1 for correct, -1 for incorrect)
}
int main() {
  int ca;
  cin >> ca;
  while (ca--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/