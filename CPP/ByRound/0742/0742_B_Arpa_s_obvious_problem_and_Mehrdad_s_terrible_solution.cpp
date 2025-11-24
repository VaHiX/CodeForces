// Problem: CF 742 B - Arpa’s obvious problem and Mehrdad’s terrible solution
// https://codeforces.com/contest/742/problem/B

/*
 * Problem: Count pairs (i, j) such that a[i] XOR a[j] = x
 * 
 * Algorithm:
 * - Use a map to store frequency of each element in the array
 * - For each unique element, calculate how many pairs can be formed:
 *   - If x ^ element == element, then we need to choose 2 from frequency (C(n,2))
 *   - Otherwise, multiply frequencies of element and (element ^ x)
 * - Since each pair is counted twice, divide final result by 2
 * 
 * Time Complexity: O(n * log n) due to map operations
 * Space Complexity: O(n) for storing elements in the map
 */
#include <iostream>
#include <map>
#include <utility>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n");
#define nl printf("\n");
#define N 1001
#define mod 1000000007
using namespace std;

int main() {
  ll i, j, k;
  ll n, m, x;
  cin >> n >> x;
  map<ll, ll> mp; // Map to store frequency of each element
  for (i = 0; i < n; i++) {
    cin >> m;
    mp[m]++; // Increment frequency of element
  }
  ll cnt = 0, y;
  map<ll, ll>::iterator p = mp.begin();
  while (p != mp.end()) {
    m = x ^ p->first; // Find the value that when XORed with x gives current element
    if (m == p->first)
      y = (p->second - 1) * p->second; // Special case: same element, choose 2 from frequency
    else
      y = p->second * mp[m]; // Multiply frequencies of element and its XOR partner
    cnt += y;
    p++;
  }
  cout << cnt / 2 << endl; // Divide by 2 since each pair counted twice
  return 0;
}


// https://github.com/VaHiX/CodeForces/