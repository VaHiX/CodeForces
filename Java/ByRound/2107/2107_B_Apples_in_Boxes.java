// Problem: CF 2107 B - Apples in Boxes
// https://codeforces.com/contest/2107/problem/B

/**
 * Problem: Apples in Boxes
 * 
 * Game Description:
 * Tom and Jerry play a turn-based game with n boxes of apples. On each turn,
 * a player must pick 1 apple from any non-empty box. If after the move, the
 * difference between max and min number of apples in boxes exceeds k, the
 * current player loses. The player who cannot make a move also loses.
 * 
 * Algorithm:
 * - For each test case, we simulate one possible move by Tom:
 *   - We decrease the box with maximum apples by 1.
 *   - Then check if the difference between max and min exceeds k or
 *     if the total number of apples is even.
 *   - Based on these conditions, determine the winner.
 * 
 * Time Complexity: O(n log n) per test case due to sorting
 * Space Complexity: O(n) for storing the array of apples
 */
import java.util.*;
public class ApplesInBoxes {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        while (t-- > 0) {
            int n = sc.nextInt();
            int k = sc.nextInt();
            int[] a = new int[n];
            long sum = 0;
            for (int i = 0; i < n; i++) {
                a[i] = sc.nextInt(); // Read apples in each box
                sum += a[i]; // Calculate total apples
            }
            Arrays.sort(a); // Sort to easily access max and min
            a[n - 1]--; // Tom makes his move: take one apple from the box with most apples
            Arrays.sort(a); // Re-sort after Tom's move
            if ((a[n - 1] - a[0]) > k || sum % 2 == 0) { 
                // If max-min exceeds k, or total apples is even, Jerry wins
                System.out.println("Jerry");
            } else {
                // Otherwise, Tom wins (as per game rules and strategy)
                System.out.println("Tom");
            }
        }
        sc.close();
    }
}


// https://github.com/VaHiX/CodeForces/