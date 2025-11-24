// Problem: CF 1633 C - Kill the Monster
// https://codeforces.com/contest/1633/problem/C

/*
C. Kill the Monster

Problem Description:
Monocarp is playing a computer game where his character fights monsters. Each fight consists of alternating attacks between character and monster until one's health drops to zero or below. The character can upgrade attack (w) or health (a) with at most k coins, each upgrade costing 1 coin. We need to determine if the character can win the monster fight after optimally spending coins.

Algorithms/Techniques:
- Brute force over all possible distributions of k coins between weapon and armor upgrades
- For each distribution, calculate minimum number of attacks needed for character and monster to win
- Use ceiling division to compute attack counts

Time Complexity: O(k * t) where k is max coins and t is number of test cases
Space Complexity: O(1)

*/

#include <cstdio>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll hc, dc; // character health and damage
    scanf("%lld %lld", &hc, &dc);
    ll hm, dm; // monster health and damage
    scanf("%lld %lld", &hm, &dm);
    ll k, w, a; // max coins, weapon upgrade, armor upgrade
    scanf("%lld %lld %lld", &k, &w, &a);
    
    ll win(false); // flag to track if character wins
    
    // try all possible distributions of k coins between weapon (p) and armor (k-p) upgrades
    for (ll p = 0; !win && p <= k; p++) {
      ll dct = dc + p * w; // updated character damage after p weapon upgrades
      ll hct = hc + (k - p) * a; // updated character health after (k-p) armor upgrades
      
      // Calculate minimum number of attacks needed for monster to win
      ll fa = (hm + dct - 1) / dct; // ceil(hm/dct) - monster's required attacks
      
      // Calculate minimum number of attacks needed for character to win
      ll fb = (hct + dm - 1) / dm; // ceil(hct/dm) - character's required attacks
      
      // If character needs less or equal attacks than monster, character wins
      if (fa <= fb) {
        win = true;
      }
    }
    
    puts(win ? "YES" : "NO"); // output result for current test case
  }
}


// https://github.com/VaHiX/codeForces/