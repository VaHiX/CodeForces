// Problem: CF 508 C - Anya and Ghosts
// https://codeforces.com/contest/508/problem/C

/*
Algorithm: Greedy Assignment of Candles
Purpose: Determine the minimum number of candles needed to ensure at least 'r' candles are burning during each ghost visit.

Approach:
- For each ghost visit, we need to ensure at least 'r' candles are burning.
- We greedily assign candles to visits.
- For each visit, we check if existing candles are still burning; if not, we light new candles.
- A candle lit at second 'x' burns from second 'x+1' to 'x+t'.
- If we cannot satisfy the requirement for any visit, return -1.

Time Complexity: O(m * r) where m is number of ghosts and r is minimum required candles.
Space Complexity: O(r) for storing the times when candles were lit.

Techniques: Greedy algorithm, interval management
*/

#include <iostream>

typedef long long int ll;
#define pp pair<ll, ll>
#define dbg printf("xxxx");
#define inf 1000000000000
#define max2(a, b) ((a < b) ? b : a)
#define max3(a, b, c) max2(max2(a, b), c)
#define min2(a, b) ((a > b) ? b : a)
#define min3(a, b, c) min2(min2(a, b), c)
using namespace std;

int main() {
  ll i, j, k;
  ll m, t, r;  // m: number of ghosts, t: candle duration, r: required candles per visit
  ll d, lg;
  ll count = 0;  // total number of candles used
  cin >> m >> d >> r;  // reading input values
  ll w[m];  // array to store visit times
  for (i = 0; i < m; i++)
    cin >> w[i];
  
  // If required candles r is more than candle duration d, it's impossible
  if (r > d) {
    cout << "-1";
    return 0;
  }
  
  // Initialize candle times to ensure at least r candles are lit at first visit
  ll candle[r];
  j = 1;
  for (i = r - 1; i >= 0; i--, j++)
    candle[i] = w[0] - j;  // Place candles such that they start burning before or at the first ghost visit
  count = r;  // Initial count of candles used

  // Process each visit
  for (i = 0; i < m; i++) {
    k = 1;  // Counter for new candles needed
    for (j = r - 1; j >= 0; j--) {
      // If current candle is not burning during this visit
      if (w[i] - candle[j] > d) {
        candle[j] = w[i] - k;  // Light a new candle to cover this visit
        // Check if we can continue to light candles for the next visits or if it's impossible
        if (candle[j] + d < w[i] || (j + 1 < r && candle[j] == candle[j + 1])) {
          cout << "-1";  // Impossible case
          return 0;
        }
        count++;  // Increment count of candles used
        k++;  // Increment the number of candles needed for next assignment
      }
    }
  }
  cout << count;  // Output minimum number of candles needed
  return 0;
}


// https://github.com/VaHiX/CodeForces/