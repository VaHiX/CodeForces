// Problem: CF 758 A - Holiday Of Equality
// https://codeforces.com/contest/758/problem/A

/*
Purpose: This program solves the "Holiday Of Equality" problem where the goal is to make the welfare of all citizens equal by giving out the minimum number of burles. The approach is to find the maximum welfare value and then calculate how much needs to be added to each citizen to reach that maximum.

Algorithms/Techniques: Sorting, Greedy Approach

Time Complexity: O(n log n) due to sorting
Space Complexity: O(1) excluding input storage

*/
#include <bits/std_abs.h>
#include <algorithm>
#include <functional>
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
  ll n;
  cin >> n;
  ll a[n];
  for (i = 0; i < n; i++)
    cin >> a[i];
  sort(a, a + n, greater<ll>()); // Sort in descending order to get maximum at index 0
  ll m = a[0]; // Maximum welfare value
  ll count2 = 0;
  for (i = 0; i < n; i++) {
    count2 += abs(m - a[i]); // Add the difference to total cost
  }
  cout << count2;
  return 0;
}


// https://github.com/VaHiX/CodeForces/