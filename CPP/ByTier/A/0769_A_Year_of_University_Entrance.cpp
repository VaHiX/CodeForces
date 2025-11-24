// Problem: CF 769 A - Year of University Entrance
// https://codeforces.com/contest/769/problem/A

/*
Code Purpose:
This program determines the year of university entrance for student Igor,
based on the groups he joined. The groups correspond to years of entrance,
and Igor joins groups for years within a range of x years from his own entrance year.
The solution leverages the fact that the entrance year must be the median of the sorted group years,
as the group selection is symmetric around the student's entry year.

Algorithms/Techniques:
- Sorting the array of group years.
- Finding the median of the sorted array.
- Time Complexity: O(n log n) due to sorting.
- Space Complexity: O(1) if we ignore input storage, otherwise O(n) for storing the array.

*/
#include <algorithm>
#include <iostream>

typedef long long int ll;
#define pp pair<ll, ll>
#define dbg printf("xxxx");
#define pi 3.1416
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
  sort(a, a + n); // Sort the array of group years
  cout << a[n / 2]; // The median year is Igor's year of entrance
  return 0;
}


// https://github.com/VaHiX/CodeForces/