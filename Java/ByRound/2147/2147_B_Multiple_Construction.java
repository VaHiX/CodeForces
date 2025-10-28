// Problem: CF 2147 B - Multiple Construction
// https://codeforces.com/contest/2147/problem/B

/**
 * Problem: B. Multiple Construction
 * 
 * Purpose: Construct an array of length 2*n such that each integer from 1 to n appears exactly twice,
 *          and the distance between the two occurrences of each integer x is divisible by x.
 * 
 * Algorithm/Techniques:
 * - For each test case, we construct the array by placing numbers in a specific pattern.
 * - Start with descending order from n to 1, then place n again, followed by ascending order from 1 to n-1.
 * - This ensures that for every number x, its two occurrences maintain a distance divisible by x.
 * 
 * Time Complexity: O(n) per test case, since we generate a sequence of 2*n elements in linear time.
 * Space Complexity: O(1) additional space, not counting the output array (which is required).
 */
import java.util.*;
public class Main {
    static List<Integer> res;
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int test = sc.nextInt();
        while (test-- > 0) {
            int n = sc.nextInt();
            // First part: print numbers from n down to 1
            for(int i=n;i>=1;i--)
            {
                System.out.print(i+" ");
            }
            // Then print n again
            System.out.print(n+" ");
            // Finally print numbers from 1 to n-1
            for(int i=1;i<n;i++)
            {
                System.out.print(i+" ");
            }
            System.out.println();
        }
    }
}


// https://github.com/VaHiX/CodeForces/