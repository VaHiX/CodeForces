// Problem: CF 462 B - Appleman and Card Game
// https://codeforces.com/contest/462/problem/B

/*
Algorithm: Greedy approach
- Count frequency of each character in the string
- Sort frequencies in descending order
- Greedily select the highest frequencies to maximize the sum of squares
- For each selected group of cards, add the square of its count to the result
Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing character frequencies and the vector of counts
*/
#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

typedef long long int ll;
#define pp pair<char, ll>
#define dbg printf("in");
#define NL printf("\n");
#define S 210000
#define inf 1000000000000
using namespace std;
int main() {
  ll i, j, k;
  ll n;
  string s;
  map<char, ll> cs; // map to store frequency of each character
  cin >> n >> k;
  cin >> s;
  for (i = 0; i < s.length(); i++)
    cs[s[i]]++; // count frequency of each character
  vector<ll> v; // vector to store frequencies
  map<char, ll>::iterator p = cs.begin();
  while (p != cs.end()) {
    v.push_back(p->second); // push frequency into vector
    p++;
  }
  ll count = 0;
  sort(v.begin(), v.end(), greater<ll>()); // sort frequencies in descending order
  i = 0;
  while (k > 0 && i < v.size()) {
    if (v[i] > k) {
      count += (k * k); // if remaining k is less than current frequency, use all k
      break;
    } else {
      k -= v[i]; // reduce k by current frequency
      count += (v[i] * v[i]); // add square of frequency to result
    }
    i++;
  }
  cout << count;
  return 0;
}


// https://github.com/VaHiX/CodeForces/