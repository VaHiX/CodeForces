// Problem: CF 478 B - Random Teams
// https://codeforces.com/contest/478/problem/B

/*
 * Problem: B. Random Teams
 *
 * Purpose: Given n participants and m teams, compute the minimum and maximum
 *          number of pairs of friends that could be formed when each pair of
 *          participants from the same team become friends.
 *
 * Algorithm:
 *   - To find minimum pairs:
 *     Distribute participants as evenly as possible among teams. This minimizes
 *     the total number of pairs. For each team with k participants, the number
 *     of pairs is k*(k-1)/2. The distribution is such that some teams have
 *     floor(n/m) participants and others have floor(n/m)+1 participants.
 *     This results in a formula based on how many teams get one extra participant.
 *
 *   - To find maximum pairs:
 *     Maximize the number of pairs by concentrating as many participants as
 *     possible in one team. This means one team gets (n - m + 1) people and the rest
 *     get 1 person each. The number of pairs in a team of size k is k*(k-1)/2.
 *     So maximum pairs = (n - m + 1) * (n - m) / 2.
 *
 * Time Complexity: O(1) - Constant time arithmetic operations.
 * Space Complexity: O(1) - Only a few variables used.
 */

#include <cstdio>
int main() {
  long long n, m;
  scanf("%lld %lld\n", &n, &m);
  // Calculate minimum number of pairs
  // Distribute n people into m teams as evenly as possible
  // Some teams get (n/m) people, others get (n/m + 1) people
  long long minPairs = ((n % m) * (n / m + 1) * (n / m) / 2) +
                       ((m - n % m) * (n / m) * (-1 + n / m) / 2);
  // Calculate maximum number of pairs
  // Put as many people as possible in one team (n - m + 1)
  // The rest are distributed one each in remaining teams
  long long maxPairs = (n - m + 1) * (n - m) / 2;
  printf("%lld %lld\n", minPairs, maxPairs);
  return 0;
}


// https://github.com/VaHiX/CodeForces/