// Problem: CF 884 B - Japanese Crosswords Strike Back
// https://codeforces.com/contest/884/problem/B

/*
Purpose: Determine if there exists exactly one binary string of given length x 
         that matches the provided encoding (array of segment lengths of 1's).

Algorithms/Techniques: 
- Greedy approach to validate if the sum of segment lengths plus gaps between segments 
  equals the total length.

Time Complexity: O(n), where n is the number of segments.
Space Complexity: O(1), only using a constant amount of extra space.

*/
#include <iostream>

typedef long long int ll;
#define dbg printf("in\n");
#define nl printf("\n");
#define inf 1000000
using namespace std;
int main() {
  int i, j, k;
  int n, t, m, x;
  cin >> n >> x;
  int cnt = n - 1;  // Initialize with n-1 for gaps between segments
  for (i = 0; i < n; i++) {
    cin >> m;
    cnt += m;  // Add the length of each segment to the total count
  }
  if (cnt == x)  // If total segments and gaps match the required length
    cout << "YES";
  else
    cout << "NO";
  return 0;
}


// https://github.com/VaHiX/CodeForces/