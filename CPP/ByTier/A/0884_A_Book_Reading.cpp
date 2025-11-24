// Problem: CF 884 A - Book Reading
// https://codeforces.com/contest/884/problem/A

/*
Purpose: This code determines the minimum day number on which Luba finishes reading a book.
         It simulates the process of reading over consecutive days, subtracting the available 
         reading time (86400 - work time) from the total time required to read the book.

Algorithms/Techniques: Simulation, Greedy approach

Time Complexity: O(n) where n is the number of days
Space Complexity: O(1) - only using a few variables regardless of input size

*/
#include <iostream>

typedef long long int ll;
#define dbg printf("in\n");
#define nl printf("\n");
#define inf 1000000
using namespace std;
int main() {
  int i, j, k;
  int n, t, m;
  cin >> n >> t;
  int cnt = 0;
  while (n--) {
    cin >> m;
    k = 86400 - m; // Calculate available reading time for the day
    t -= k;        // Subtract the reading time from total required time
    cnt++;         // Increment day counter
    if (t <= 0)    // If all reading time is covered, break
      break;
  }
  cout << cnt;
  return 0;
}


// https://github.com/VaHiX/CodeForces/