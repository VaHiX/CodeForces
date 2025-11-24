// Problem: CF 1612 C - Chat Ban
// https://codeforces.com/contest/1612/problem/C

/*
C. Chat Ban
Purpose: Given an emote triangle of size k (2k-1 messages), determine how many messages will be sent before the total emotes sent reaches x.
Algorithm: Binary search on the number of messages to find the minimum message count where cumulative emotes >= x.
Time Complexity: O(t * log(2k)) where t is number of test cases and k <= 10^9.
Space Complexity: O(1) - only using a few variables.

The emote triangle has:
- First k messages: 1, 2, ..., k emotes
- Next k-1 messages: k-1, k-2, ..., 1 emotes

We use binary search to find the least message index such that sum of emotes up to that message >= x.
*/

#include <cstdio>
typedef long long ll;

// Function to check if total emotes up to 'lines' messages is less than x
bool check(ll lines, ll k, ll x) {
  ll total;
  if (lines <= k) {
    // Sum of first 'lines' natural numbers: lines*(lines+1)/2
    total = lines * (lines + 1) / 2;
  } else {
    // First k terms: 1 + 2 + ... + k = k*k/2
    // Then decreasing from k to (k - (lines-k)) -> arithmetic sequence
    // Total = k*k - sum of (2k-1-lines) to (k-1) which is (2*k-1-lines)*(2*k-lines)/2
    total = k * k - (2 * k - 1 - lines) * (2 * k - lines) / 2;
  }
  return total < x; // if total is less than x, we haven't reached x yet
}

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll k, x;
    scanf("%lld %lld", &k, &x);
    ll left(0), right(2 * k - 1), w(2 * k - 1); // Binary search bounds
    while (left <= right) {
      ll mid = (left + right) / 2; // Midpoint of binary search
      if (check(mid, k, x)) {
        left = mid + 1;  // Need more messages to reach x emotes
      } else {
        w = mid;         // Found a valid answer, try for smaller
        right = mid - 1;
      }
    }
    printf("%lld\n", w); // Print the minimum message count
  }
}


// https://github.com/VaHiX/codeForces/