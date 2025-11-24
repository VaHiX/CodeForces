// Problem: CF 2149 A - Be Positive
// https://codeforces.com/contest/2149/problem/A

/**
 * Problem: Be Positive
 * 
 * Purpose: 
 * Given an array of integers where each element is -1, 0, or 1,
 * the goal is to make the product of all elements strictly positive
 * with the minimum number of operations. Each operation allows increasing
 * an element by 1.
 * 
 * Algorithm:
 * - Count zeros and -1s in the array.
 * - If there are an odd number of -1s, we must change at least one -1 to 1,
 *   which requires 2 operations per such -1 to make it positive (from -1 to 1).
 * - For each zero, we need one operation to turn it into 1.
 * 
 * Time Complexity: O(n) where n is the length of the array.
 * Space Complexity: O(1), constant space used.
 */

import java.util.Scanner;

public class BePositive {
    
    public static void solve(Scanner sc) {
        int n = sc.nextInt(); // Read the size of array
        int count = 0; // Count of operations needed
        int minuscount = 0; // Count of -1s in the array
        
        for (int i = 0; i < n; i++) {
            int s = sc.nextInt(); // Read current element
            if (s == 0) count++; // If it's zero, we need one operation to make it 1
            else if (s == -1) minuscount++; // Count how many -1s exist
        }
        
        // If there are odd number of -1s, we must convert at least one of them
        // to make the product positive. Converting -1 to 1 takes 2 operations (0 -> 1 -> 2, etc., but effectively we need 2 steps to get from -1 to 1)
        if (minuscount % 2 != 0) count = count + 2;
        
        System.out.println(count); // Print minimum operations needed
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt(); // Read number of test cases
        
        while (t-- > 0) {
            solve(sc); // Process each test case
        }
        
        sc.close();
    }
}


// https://github.com/VaHiX/CodeForces/