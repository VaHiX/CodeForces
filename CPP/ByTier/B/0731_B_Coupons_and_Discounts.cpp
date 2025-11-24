// Problem: CF 731 B - Coupons and Discounts
// https://codeforces.com/contest/731/problem/B

/*
Algorithm: Greedy approach with carry tracking
Techniques: 
- Tracking available "carry" of pizza from previous day to use for current day
- Using coupon (2 pizzas in 2 consecutive days) and discount (2 pizzas in 1 day)

Time Complexity: O(n) - single pass through the array
Space Complexity: O(1) - only using a few variables for tracking

The idea is:
- On each day, we need 'a[i]' pizzas
- We can use coupons (buy 1 pizza on day i and 1 on day i+1) or discounts (buy 2 pizzas on day i)
- We track how many extra pizzas we have from previous day (carry)
- If current day needs odd number of pizzas, and we have carry from previous day, we can use it.
- If we need odd number of pizzas and no carry, we must carry 1 pizza to next day.
- If we need even number of pizzas, we can use up our carry (if any) but can't carry over.
- At the end, no carry should remain.
*/
#include <iostream>

typedef long long int ll;
#define pp pair<ll, ll>
#define dbg printf("in\n");
#define NL printf("\n");
#define inf 1000000000000
#define max2(a, b) ((a < b) ? b : a)
#define max3(a, b, c) max2(max2(a, b), c)
#define min2(a, b) ((a > b) ? b : a)
#define min3(a, b, c) min2(min2(a, b), c)
using namespace std;
int main() {
  ll i, j, k;
  ll x, n;
  cin >> n;
  ll a[n];
  for (i = 0; i < n; i++)
    cin >> a[i];
  ll carry = 0;
  bool f = true;
  for (i = 0; i < n; i++) {
    if (a[i] % 2) { // if current day needs odd number of pizzas
      if (carry) // if we have carry from previous day
        carry = 0; // use the carry (consume 1 pizza), now no carry left
      else
        carry = 1; // no carry, so we must carry 1 pizza to next day
    } else { // if current day needs even number of pizzas
      if (carry && a[i] == 0) { // if we have carry but no teams today (a[i] = 0)
        f = false; // this is invalid - cannot use coupon without buying pizza
        break;
      }
    }
  }
  if (carry > 0) // if we still have carry at the end, it means we couldn't use it
    f = false;
  if (f)
    cout << "YES";
  else
    cout << "NO";
  return 0;
}


// https://github.com/VaHiX/CodeForces/