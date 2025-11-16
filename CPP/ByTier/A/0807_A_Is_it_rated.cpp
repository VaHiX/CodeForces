// Problem: CF 807 A - Is it rated?
// https://codeforces.com/contest/807/problem/A

/*
Purpose: Determine if a Codeforces round is rated, unrated, or impossible to determine based on rating changes and standings.
Algorithm: 
- Iterate through all participants and check for rating changes.
- If any participant's rating changed, the round is definitely rated.
- If no ratings changed, check if the standings are in non-increasing order of ratings.
  - If not, the round is unrated (because if it were rated, there would have been a rating change).
  - If yes, we can't determine if it's rated or not.

Time Complexity: O(n), where n is the number of participants.
Space Complexity: O(1), only using a few variables.

*/
#include <cstdio>
int main() {
  int n;
  scanf("%d", &n);
  int prev(-1); // Store previous rating to check ordering
  bool unrated(false); // Flag to indicate if round is unrated
  while (n--) {
    int a, b;
    scanf("%d %d", &a, &b);
    if (a != b) {
      // If any rating changed, round is definitely rated
      puts("rated");
      return 0;
    }
    if ((prev >= 0) && (a > prev)) {
      // If current rating is greater than previous, standings are not in non-increasing order
      unrated = true;
    }
    prev = a; // Update previous rating
  }
  // If no rating changed and standings are non-increasing, it's maybe rated
  puts(unrated ? "unrated" : "maybe");
  return 0;
}


// https://github.com/VaHiX/CodeForces/