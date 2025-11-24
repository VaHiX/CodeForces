// Problem: CF 828 A - Restaurant Tables
// https://codeforces.com/contest/828/problem/A

/*
Algorithm: Greedy Simulation
Time Complexity: O(n) where n is the number of groups
Space Complexity: O(1) as we use only a fixed size array and a few variables

The algorithm simulates the seating process:
- For groups of 1 person:
  * First try to seat at an empty 1-seater table
  * If none available, try to seat at an empty 2-seater table (occupying one seat)
  * If none available, try to seat at a 2-seater table that has one person (freeing up seat)
  * If none available, deny service
- For groups of 2 people:
  * First try to seat at an empty 2-seater table
  * If none available, deny service

The array f[3] keeps track of:
f[0] = number of empty 1-seater tables
f[1] = number of empty 2-seater tables  
f[2] = number of 2-seater tables with 1 person (available seat)
*/

#include <iostream>

typedef long long int ll;
#define pp pair<ll, ll>
#define dbg printf("in\n");
#define NL printf("\n");
#define inf 1000000000000
using namespace std;

int main() {
  ll i, j, k;
  ll n, m;
  ll a, b;
  ll f[3]; // f[0] = empty 1-seater, f[1] = empty 2-seater, f[2] = 2-seater with 1 person
  cin >> n >> a >> b;
  ll g[n];
  f[0] = a;  // initialize empty 1-seater tables
  f[1] = b;  // initialize empty 2-seater tables
  f[2] = 0;  // no 2-seaters with 1 person initially
  ll count = 0; // count of denied people
  
  for (i = 0; i < n; i++) {
    cin >> k; // read group size
    if (k == 2) {
      // group of 2 people
      if (f[1] > 0) {
        // there is an empty 2-seater table
        f[1]--; // occupy it
      } else {
        // no empty 2-seater, deny service to 2 people
        count += 2;
      }
    } else {
      // group of 1 person
      if (f[0] > 0) {
        // there is an empty 1-seater table
        f[0]--; // occupy it
      } else if (f[1] > 0) {
        // there is an empty 2-seater table
        f[1]--; // occupy it
        f[2]++; // but now it has one person, so we're increasing the 2-seater with 1 person
      } else if (f[2] > 0) {
        // there is a 2-seater with 1 person
        f[2]--; // occupy the remaining seat
      } else {
        // no table available at all
        count++; // deny service to 1 person
      }
    }
  }
  cout << count;
  return 0;
}


// https://github.com/VaHiX/CodeForces/