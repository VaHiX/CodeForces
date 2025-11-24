// Problem: CF 2104 A - Three Decks
// https://codeforces.com/contest/2104/problem/A

/*
Problem: Three Decks

Algorithm/Techniques: Mathematical analysis and simulation
Time Complexity: O(1) per test case
Space Complexity: O(1)

The problem involves determining if we can redistribute cards from the third deck to the first two decks such that all three decks end up with equal numbers of cards.

Approach:
1. For the final state to have equal number of cards in each deck, the total number of cards must be divisible by 3.
2. Let the target number of cards per deck be sum/3.
3. We need to check if the given decks can be made equal by moving some cards from the third deck to first and second.
4. The key insight is that the cards in the first two decks are already "fixed" relative to each other (i.e., we can only move them around within their limits).
5. So, we simulate: 
   - First check if total sum of cards can be equally distributed among 3 decks (sum % 3 == 0)
   - Then, calculate how many cards should be moved to first and second deck such that final count becomes sum/3
   - Also make sure that the number of cards taken from third deck is valid and does not exceed it.

Key checks in code:
- sum must be divisible by 3
- The maximum possible new card count for first or second deck should not exceed what's available after distributing cards (b <= sum / 3)
*/

import java.util.*;
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        while (t-- > 0) {
            int a = sc.nextInt(); // Cards in first deck
            int b = sc.nextInt(); // Cards in second deck
            int c = sc.nextInt(); // Cards in third deck
            long sum = a + b + c; // Total number of cards
            // Check if sum is divisible by 3 and if second deck can accommodate final amount
            System.out.println(sum % 3 == 0 && b <= sum / 3 ? "YES" : "NO");
        }
    }
}


// https://github.com/VaHiX/CodeForces/