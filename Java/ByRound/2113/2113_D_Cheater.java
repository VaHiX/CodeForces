// Problem: CF 2113 D - Cheater
// https://codeforces.com/contest/2113/problem/D

/*
 * Problem: D. Cheater
 * 
 * Purpose: Maximize the number of points a player can achieve in a card game where:
 *          - Player and dealer each have n cards.
 *          - In each round, both play one card from top of their hand.
 *          - Higher value wins the round; loser's card is placed on top of their hand.
 *          - Player can swap at most two cards in hand to maximize points.
 * 
 * Algorithm:
 * 1. Binary search on the answer (number of rounds won).
 * 2. For each candidate number of wins, check if it's possible using a greedy approach:
 *    - Precompute prefix minimums (for identifying the smallest card seen so far)
 *    - Precompute suffix maximums (for knowing best future cards)
 *    - Simulate the gameplay considering optimal use of the swap.
 * 
 * Time Complexity: O(n log n)
 * Space Complexity: O(n)
 */

import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int test = sc.nextInt();
        while (test-- > 0) {
            int n = sc.nextInt();
            int a[] = new int[n];
            int b[] = new int[n];
            for(int i=0;i<n;i++) {
                a[i] = sc.nextInt(); // Player's cards
            }
            for(int i=0;i<n;i++) {
                b[i] = sc.nextInt(); // Dealer's cards
            }

            // Preprocessing suffix maximums: suf[i] = max(a[i], a[i+1], ..., a[n-1])
            int suf[] = new int[n];
            suf[n-1] = a[n-1];
            for(int i=n-2;i>=0;i--) {
                suf[i] = Math.max(suf[i+1],a[i]);
            }

            // Preprocessing prefix minimum indices: pre[i] = index of min element in a[0..i]
            int pre[] = new int[n];
            pre[0] = 0; // Minimum so far is at index 0 for first element
            for(int i=1;i<n;i++) {
                if(a[i] < a[pre[i-1]]) {
                    pre[i] = i;
                } else {
                    pre[i] = pre[i-1];
                }
            }

            // Binary search on the answer
            int low = 0; 
            int high = n-1;
            while(low <= high) {
                int mid = (low + high) / 2;
                boolean res = f(a,b,pre,suf,n,mid);
                if(res) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
            System.out.println(low);
        }
    }

    // Helper function for checking if 'ind' rounds can be won
    public static boolean f(int a[], int b[], int pre[], int suf[], int n, int ind) {
        int max = ind + 1 < n ? suf[ind + 1] : 0; // Maximum card in remaining part after ind
        int minInd = pre[ind]; // Index of minimum element in prefix up to 'ind'
        max = Math.max(a[minInd], max); // Update max with min index's value
        
        int i = 0; 
        int j = 0; 
        int cnt = 0;
        while(i <= ind && j < n && cnt < n) {
            cnt++;
            int val = i == minInd ? max : a[i]; // Use maximum instead of the lowest card
            if(val > b[j]) {
                i++; // Player wins round
            } else {
                j++; // Dealer wins round
            }
        }
        return i > ind; // Return true if all cards in prefix are used or all rounds won
    }
}


// https://github.com/VaHiX/CodeForces/