// Problem: CF 2130 A - Submission is All You Need
// https://codeforces.com/contest/2130/problem/A

/*
 * Problem: Maximum Score from Multiset Operations
 * 
 * Algorithms/Techniques:
 * - Greedy approach with selection of subsets to maximize score
 * - For each element, we can either:
 *   1. Add its value to the score (sum operation) if it's not zero,
 *   2. Or add 1 to the score (mex operation) if it's zero.
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1)
 * 
 * The key insight is that:
 * - If an element is 0, we can use it to get a mex of 1, so adding one to score.
 * - If an element is non-zero, we can sum it and add its value.
 * We process all elements and accumulate the best possible gain per element.
 */
import java.util.Scanner;
public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int t = in.nextInt();
        while (t-- > 0) {
            int n = in.nextInt();
            int tmp, ans = 0;
            for (int i = 0; i < n; i++) {
                tmp = in.nextInt(); // Read current element
                ans += tmp + (tmp == 0 ? 1 : 0); // Add value and if zero add 1 for mex benefit
            }
            System.out.println(ans);
        }
    }
}


// https://github.com/VaHiX/codeForces/