// Problem: CF 670 D1 - Magic Powder - 1
// https://codeforces.com/contest/670/problem/D1

/*
Purpose: 
This code solves the problem of determining the maximum number of cookies Apollinaria can bake given limited ingredients and a fixed amount of magic powder. The strategy involves initially using all ingredients to calculate a baseline number of cookies, then optimally allocating magic powder to maximize the total cookie count.

Algorithms/Techniques:
- Greedy approach to distribute magic powder
- Binary search or iterative improvement to find the optimal number of cookies

Time Complexity: O(n * min(b[i]/a[i])) where n is number of ingredients, and b[i]/a[i] represents how many cookies we can make from ingredient i without magic powder.
Space Complexity: O(n) for storing arrays of ingredients and available quantities.

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
  ll n, count = 0;
  cin >> n >> k;
  ll a[n], b[n];
  for (i = 0; i < n; i++)
    cin >> a[i];
  for (i = 0; i < n; i++)
    cin >> b[i];
  ll Min = inf;
  // Find the minimum number of cookies possible with current ingredients (no magic powder)
  for (i = 0; i < n; i++) {
    if (b[i] / a[i] < Min)
      Min = b[i] / a[i];
  }
  count = Min;
  // Deduct ingredients needed for initial cookies
  for (i = 0; i < n; i++) {
    b[i] -= (count * a[i]);
  }
  ll need;
  // Keep trying to make more cookies with remaining magic powder
  while (k) {
    need = 0;
    // Calculate how much magic powder is needed to make one more cookie
    for (i = 0; i < n; i++) {
      if (b[i] < a[i])
        need += (a[i] - b[i]);
    }
    // If we have enough magic powder, make one more cookie
    if (k >= need) {
      count++;
      for (i = 0; i < n; i++) {
        b[i] -= a[i];
        if (b[i] < 0)
          b[i] = 0;
      }
      k -= need;
    } else
      k = 0;
  }
  cout << count;
  return 0;
}


// https://github.com/VaHiX/CodeForces/