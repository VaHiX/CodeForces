// Problem: CF 819 A - Mister B and Boring Game
// https://codeforces.com/contest/819/problem/A

#include <algorithm>
#include <iostream>

using namespace std;
int a, b, l, r;
int main() {
  cin >> a >> b >> l >> r;
  int cl = --l / (a + b);  // Calculate which full round l is in
  int pl = l % (a + b);    // Position within the round for l
  int cr = --r / (a + b);  // Calculate which full round r is in
  int pr = r % (a + b);    // Position within the round for r
  
  if (cl == cr) {  // If l and r are in the same round
    cout << min(r - l + 1, max(a - pl, 1));  // Return minimum of segment size and number of distinct letters
    return 0;
  }
  
  if (a <= b) {  // If Mister B's move is less than or equal to opponent's move
    if (cl < cr - 1) {  // If there are multiple full rounds between l and r
      cout << a + 1 << "\n";  // Minimum distinct letters in such case
    } else {  // If there is only one round between l and r
      int x = max(1, a - pl);  // Number of distinct letters at start of segment
      int y = min(a, pr + 1);  // Number of distinct letters at end of segment
      cout << min(a, x + y) + (y == a);  // Total distinct letters
    }
    return 0;
  }
  
  int d = a - b;  // Difference in letters appended per move
  if (cl == cr - 1) {  // If l and r are in consecutive rounds
    cout << max(1, min(d, a - pl)) + min(a, pr + 1);  // Compute distinct letters
    return 0;
  }
  
  if (cl == cr - 2) {  // If l and r are in rounds with one round in between
    cout << a + max(1, d + min(0, pr - a + 1 + max(0, a - pl)));  // Complex calculation for distinct letters
    return 0;
  }
  
  cout << a + d << "\n";  // Default case for large gaps in rounds
}


// https://github.com/VaHiX/CodeForces/