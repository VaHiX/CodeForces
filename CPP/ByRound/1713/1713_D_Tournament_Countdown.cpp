// Problem: CF 1713 D - Tournament Countdown
// https://codeforces.com/contest/1713/problem/D

/*
Algorithm: Tournament Countdown
Purpose: Find the winner of a single-elimination tournament using at most ⌈(1/3) * 2^(n+1)⌉ queries.
Approach:
1. For each round, compare pairs of contestants in groups of 4.
2. Use the query results to determine which contestant advances to the next round.
3. Continue until we have only 2 contestants left, then do a final query to determine the winner.

Time Complexity: O(2^n) - We process 2^n contestants and perform at most ⌈(1/3) * 2^(n+1)⌉ queries.
Space Complexity: O(2^n) - We keep an array of size 2^n to store contestant indices.

*/
#include <iostream>

#define _ ios::sync_with_stdio(0), cout.tie(0), cin.tie(0);
using namespace std;
int t, n, ar[1 << 17], x, a, b, c, d;
void ask(int a, int b) {
  cout << "? " << a << " " << b << "\n\n"; // Query the jury with two contestants
  cout.flush(); // Flush output to ensure query is sent
  cin >> x; // Read the result of the query
}
int main() {
  _ cin >> t; // Read number of test cases
  while (t--) {
    cin >> n;
    n = (1 << n); // Calculate 2^n number of contestants
    for (int i = 0; i < n; i++)
      ar[i] = i + 1; // Initialize array with contestant indices
    
    // Process rounds until we have less than 4 contestants
    while (n >= 4) {
      for (int i = 0; i < n; i += 4) {
        // Get the indices of four contestants in the current group
        a = ar[i], b = ar[i + 1], c = ar[i + 2], d = ar[i + 3];
        ask(a, c); // Query the first two contestants
        // Based on the result of the query, determine who advances
        if (x == 0) // a and c have equal wins
          ar[i / 2] = b, ar[i / 2 + 1] = d; // b and d advance
        if (x == 1) // a wins more than c
          ar[i / 2] = a, ar[i / 2 + 1] = d; // a and d advance
        if (x == 2) // c wins more than a
          ar[i / 2] = c, ar[i / 2 + 1] = b; // c and b advance
      }
      n /= 2; // Reduce number of contestants for the next round
    }
    
    // When only 2 contestants left, query to determine winner
    ask(ar[0], ar[1]);
    cout << "! " << ar[x - 1] << "\n"; // Output the winner based on the result
    cout.flush();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/