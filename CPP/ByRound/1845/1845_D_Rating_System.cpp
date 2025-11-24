// Problem: CF 1845 D - Rating System
// https://codeforces.com/contest/1845/problem/D

/*
Algorithm: Rating System
Purpose: To determine the optimal value of k such that the final rating after all matches is maximized,
         considering that the rating cannot fall below k once it reaches that level.

Approach:
- Simulate the match sequence and track the cumulative sum of rating changes.
- Track the minimum prefix sum encountered so far (which represents the lowest rating reached).
- For each step, calculate how much we can "shift" the starting point (by subtracting the minimum prefix),
  to find the optimal k that ensures the rating never drops below it and still maximizes the final score.

Time Complexity: O(n) where n is the number of matches.
Space Complexity: O(n) due to input vector storage.

Techniques:
- Prefix sum calculation
- Greedy update of k based on prefix minima

*/

#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

void ratingSystem(); // Function declaration

int main() {
  int t;
  scanf("%d", &t);
  for (int tc = 1; tc <= t; tc++) {
    ratingSystem(); // Process each test case
  }
}

void ratingSystem() {
  int n;
  scanf("%d", &n);
  vector<int> a(n); // Read the rating changes
  for (int &ai : a) {
    scanf("%d", &ai);
  }

  long long del = 0, k = 0; // del tracks the shift, k stores the optimal value
  long long sum = 0, mx = 0; // sum tracks prefix sum, mx tracks max prefix sum

  for (int ai : a) {
    sum += ai; // Update cumulative sum
    mx = max(mx, sum); // Track maximum prefix sum

    // If shifting the current prefix by mx gives us a better del value, update k
    if (sum - mx < del) {
      del = sum - mx;
      k = mx;
    }
  }

  printf("%lld\n", k); // Output the optimal value of k
}


// https://github.com/VaHiX/CodeForces/