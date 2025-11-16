// Problem: CF 1749 C - Number Game
// https://codeforces.com/contest/1749/problem/C

/*
Code Purpose:
This code solves the "Number Game" problem where Alice and Bob play a game on an array of integers.
Alice aims to maximize the number of stages (k) she can win, while Bob tries to prevent her from doing so.
The solution uses a greedy approach combined with binary search logic to determine the maximum k.

Algorithms/Techniques:
- Sorting the array to simplify analysis
- Greedy checking for each possible k from high to low
- For a given k, check if Alice can win by ensuring that for each stage i (from 1 to k), 
  there's an element in the array that is <= (k - i + 1), and after removing it and Bob adding (k - i + 1) to some element,
  Alice can continue to have a valid move.

Time Complexity: O(n log n) per test case due to sorting and the nested loop which runs in O(n) in worst case.
Space Complexity: O(n) for storing the array elements.
*/

#include <algorithm>
#include <iostream>

using namespace std;
int a[110];
int main() {
  int T;
  cin >> T;
  while (T--) {
    int n, ans;
    cin >> n;
    for (int i = 1; i <= n; i++)
      cin >> a[i];
    sort(a + 1, a + n + 1);  // Sort the array to allow easier greedy checks
    for (ans = (n + 1) / 2; ans; ans--) {  // Start checking from highest possible k down to 1
      int f = 1;  // Flag to indicate if current k is valid for Alice to win
      for (int i = 1; i <= ans && f; i++)
        if (a[i + ans - 1] > i)  // Check if the element at position (i + ans - 1) is greater than i
          f = 0;  // If so, Alice cannot guarantee a win with this k
      if (f)
        break;  // If we found a valid k, break and return it
    }
    cout << ans << endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/