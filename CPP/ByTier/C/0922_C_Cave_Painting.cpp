// Problem: CF 922 C - Cave Painting
// https://codeforces.com/contest/922/problem/C

/*
Purpose: 
  This program determines whether the remainders of a number n when divided by all integers from 1 to k are distinct.
  
Algorithm:
  - For each integer i from 1 to k, compute the remainder n % i.
  - Store each remainder in a set to check for duplicates.
  - If a duplicate remainder is found, output "No"; otherwise, output "Yes".
  
Time Complexity: O(k * log k)
  - The loop runs k times, and each set operation (insertion and count) takes O(log k) time.
Space Complexity: O(k)
  - The set stores at most k remainders.

Techniques:
  - Use of std::set for efficient duplicate detection.
  - Early termination when a duplicate is found.
*/

#include <cstdio>
#include <set>
typedef long long ll;
int main() {
  ll n, k;
  scanf("%lld %lld", &n, &k);
  std::set<ll> s;
  bool possible(true);
  for (long p = 1; p <= k; p++) {
    if (s.count(n % p)) {  // Check if the remainder is already seen
      possible = false;
      break;
    }
    s.insert(n % p);  // Insert the new remainder into the set
  }
  puts(possible ? "Yes" : "No");
  return 0;
}


// https://github.com/VaHiX/CodeForces/