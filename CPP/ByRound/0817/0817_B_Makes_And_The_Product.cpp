// Problem: CF 817 B - Makes And The Product
// https://codeforces.com/contest/817/problem/B

/*
 * Problem: Find the number of triples (i, j, k) such that i < j < k and a[i] * a[j] * a[k] is minimum possible.
 *
 * Algorithm:
 * - Count occurrences of each number in the array using a map.
 * - Sort the array to easily access the smallest elements.
 * - Based on the smallest three elements (a, b, c), determine how many valid triples can be formed:
 *   - If all three are different: multiply counts of each.
 *   - If first two are same but third is different: just count the third.
 *   - If first and third are same but second is different: use arithmetic progression.
 *   - If all three are same: compute combination C(n, 3) using summation.
 *
 * Time Complexity: O(n log n) due to sorting.
 * Space Complexity: O(n) for storing the array and map.
 */
#include <algorithm>
#include <iostream>
#include <map>

typedef long long int ll;
#define pp pair<ll, ll>
#define dbg printf("in\n");
#define NL printf("\n");
#define inf 1000000000000
using namespace std;

int main() {
  ll i, j, k;
  ll n;
  cin >> n;
  ll x[n]; // array to store input elements
  map<ll, ll> mp; // map to count frequency of each element
  for (i = 0; i < n; i++) {
    cin >> x[i];
    mp[x[i]]++; // increment frequency of current element
  }
  sort(x, x + n); // sort the array to get minimum elements at the start
  ll a = x[0], b = x[1], c = x[2]; // take the first three sorted elements
  if (a != b && b != c) {
    // All three elements are different, so multiply their frequencies
    cout << (mp[a] * mp[b] * mp[c]) << endl;
  } else if (a == b && b != c) {
    // First two are same, third is different
    // Only one way to choose the third (c)
    cout << (mp[c]) << endl;
  } else if (a != b && b == c) {
    // First is different, last two are same
    // Need to compute combinations of choosing 2 from mp[b] elements (C(mp[b], 2))
    k = mp[b] - 1;
    j = 0;
    while (k) {
      j += k; // sum of 1 + 2 + ... + (mp[b]-1)
      k--;
    }
    cout << j << endl;
  } else if (a == b && b == c) {
    // All three elements are same
    // Compute combinations of 3 from mp[a] elements (C(mp[a], 3))
    k = mp[a]; // total count of the repeated element
    j = 1;
    ll q = k - 2;
    while (k > 3) {
      j += (q * (q + 1)) / 2; // accumulated combination sum
      q--;
      k--;
    }
    cout << j;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/