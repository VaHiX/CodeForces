// Problem: CF 903 B - The Modcrab
// https://codeforces.com/contest/903/problem/B

#include <cstdio>
#include <vector>
/*
Flowerbox:
Algorithm: Greedy Strategy
Purpose: To determine the minimum number of actions (STRIKE or HEAL) required for Vova to defeat the Modcrab.
Approach:
- In each phase, decide whether to STRIKE or HEAL based on current health and attack powers.
- If Vova can defeat the monster in one strike or if his health is sufficient to survive the next attack, he strikes.
- Otherwise, he heals to restore health.
- This greedy approach ensures the minimum number of phases.

Time Complexity: O(h2 / a1), where h2 is the Modcrab's health and a1 is Vova's attack power.
Space Complexity: O(h2 / a1), for storing the sequence of actions.
*/
int main() {
  long h1, a1, c1; // Vova's health, attack, potion healing
  scanf("%ld %ld %ld", &h1, &a1, &c1);
  long h2, a2; // Modcrab's health, attack
  scanf("%ld %ld", &h2, &a2);
  std::vector<bool> act; // Vector to store actions (true = STRIKE, false = HEAL)
  while (h2 > 0) { // Continue until Modcrab is defeated
    if ((a1 >= h2) || h1 > a2) { // If Vova can win with one strike or can survive the next hit
      act.push_back(1); // Perform strike
      h2 -= a1; // Reduce Modcrab's health
    } else {
      act.push_back(0); // Heal
      h1 += c1; // Restore Vova's health
    }
    h1 -= a2; // Modcrab attacks Vova regardless
  }
  printf("%ld\n", act.size()); // Print total number of phases
  for (long p = 0; p < act.size(); p++) { // Output each action
    puts(act[p] ? "STRIKE" : "HEAL");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/