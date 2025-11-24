// Problem: CF 1172 A - Nauuo and Cards
// https://codeforces.com/contest/1172/problem/A

/*
A. Nauuo and Cards
Algorithms/Techniques: Simulation, Greedy
Time Complexity: O(n)
Space Complexity: O(1)

Nauuo is a girl who loves playing cards.
One day she was playing cards but found that the cards were mixed with some empty ones.
There are n cards numbered from 1 to n, and they were mixed with another n empty cards. She piled up the 2n cards and drew n of them. The n cards in Nauuo's hands are given. The remaining n cards in the pile are also given in the order from top to bottom.
In one operation she can choose a card in her hands and play it — put it at the bottom of the pile, then draw the top card from the pile.
Nauuo wants to make the n numbered cards piled up in increasing order (the i-th card in the pile from top to bottom is the card i) as quickly as possible. Can you tell her the minimum number of operations?
*/

#include <stdio.h>
int a, b = -1, n, t = 1000000007, k = 0, p, g = 1;
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a);
    if (a && i - a > b)   // Update maximum gap between expected and actual card position
      b = i - a;
    if (a == 1)           // Record position of card '1'
      p = i;
    if (a == k + 1)       // Check for consecutive sequence starting from k+1
      k = a;
    else
      k = 0;              // Reset consecutive counter if not in sequence
    if (a && !k && a - i < t)  // Update minimum distance to next needed card
      t = a - i;
    if (a != 0)           // If there's at least one non-empty card
      g = 0;
  }
  if (k && t > n - p + 1)   // Special case: full sequence and sufficient gap
    printf("%d", p - 1);
  else if (g)               // All cards are empty
    printf("%d", n);
  else
    printf("%d", b + n + 1);  // Default result based on computed gaps
}


// https://github.com/VaHiX/codeForces/