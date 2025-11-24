// Problem: CF 1951 B - Battle Cows
// https://codeforces.com/contest/1951/problem/B

/*
B. Battle Cows
Algorithm: Simulation with optimization
Time Complexity: O(n) per test case
Space Complexity: O(n) for the vector storing ratings

The problem simulates a tournament where cows compete in a bracket-style match,
where the higher-rated cow wins each match. You may swap your cow (at index k)
with another cow only once to maximize the number of matches your cow wins.

Approach:
- Simulate the tournament as given.
- Identify how many matches your cow can win in its current position.
- Try swapping with other cows and compute if that increases wins.
- The logic uses a greedy method to determine max wins possible after one swap.
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    long b = a[--k]; // Get the rating of the cow at position k
    long first(n), second(n); // first: first position > b, second: second position > b
    for (long p = 0; p < n; p++) {
      if (a[p] > b && first == n) { // First cow with rating > b
        first = p;
      } else if (a[p] > b) { // Second cow with rating > b
        second = p;
        break;
      }
    }
    long resA = first - 1; // Wins without swapping: number of positions before first higher rated
    long resB = (second < k ? second : k) - first - (first == 0); // Potential wins after swap
    printf("%ld\n", resA > resB ? resA : resB);
  }
}


// https://github.com/VaHiX/codeForces/