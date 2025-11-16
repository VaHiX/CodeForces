// Problem: CF 1077 C - Good Array
// https://codeforces.com/contest/1077/problem/C

/*
Algorithm/Technique: 
- The problem is to find "nice" indices, i.e., indices such that removing the element at that index results in an array where one element equals the sum of all others.
- Key insight: if we remove an element at index i, the remaining sum is (total_sum - a[i]), and we want to check if any remaining element equals (total_sum - a[i]).
- For the remaining array to be "good", we need an element equal to (total_sum - a[i]), and since we remove one element, the new sum must be even and one of the elements should be sum/2.
- Since the sum of the array after deletion is (total_sum - a[i]), we can test whether that sum can be split into two equal parts.
- Specifically, for an element to be the sum of others, if the sum is S and we remove a[i], the sum becomes S - a[i]. For this to be valid, S - a[i] should be even, and for an element to be equal to (S - a[i]), it should equal (S - a[i]) / 2.
- To simplify, we can sort the array, and for each element, we test if (total_sum - element) can be split into two equal parts, which means total_sum - element should be even, and there should be existing element equal to (total_sum - element)/2.
- The implementation uses sorting to allow efficient identification of elements. We only check for the largest element (after removing smaller ones) as it gives a direct comparison.

Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing indices
*/

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

typedef long long ll;
int main() {
  ll n;
  scanf("%lld", &n);
  std::vector<std::pair<ll, ll>> a(n);  // pair of {value, original index}
  ll sum(0);
  for (ll p = 0; p < n; p++) {
    scanf("%lld", &a[p].first);
    a[p].second = p;
    sum += a[p].first;
  }
  sort(a.begin(), a.end());  // sort by value
  std::vector<ll> ids;
  for (ll p = 0; p < n; p++) {
    // Case 1: Not the last element, check if sum - current equals 2 * max element
    if ((p + 1 < n) && (sum - a[p].first == 2 * a[n - 1].first)) {
      ids.push_back(1 + a[p].second);
    } else if ((p == n - 1) && (sum - a[n - 1].first == 2 * a[n - 2].first)) {
      // Case 2: This is the last element, compare with second to last max
      ids.push_back(1 + a[p].second);
    }
  }
  printf("%ld\n", ids.size());
  for (ll p = 0; p < ids.size(); p++) {
    printf("%lld ", ids[p]);
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/CodeForces/