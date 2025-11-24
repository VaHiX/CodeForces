// Problem: CF 2109 C1 - Hacking Numbers (Easy Version)
// https://codeforces.com/contest/2109/problem/C1

/*
 * Problem: C1. Hacking Numbers (Easy Version)
 * Purpose: This code solves an interactive problem where we need to make an unknown integer x equal to a given target n,
 * using at most 7 commands. It uses digit sum, addition and multiplication operations strategically.
 *
 * Algorithms/Techniques:
 * - Digit Sum Operation: Used to reduce large numbers into smaller ones.
 * - Addition/Subtraction: To adjust values towards the target.
 * - Multiplication: To scale up or down efficiently.
 * 
 * Time Complexity: O(1) per test case, since we are using a fixed number of operations (at most 7).
 * Space Complexity: O(1), as we use a constant amount of space regardless of input size.
 */
import java.util.Scanner;
public class Numbers {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        int t = s.nextInt();
        while (0<t--) { // Loop through each test case
            int n = s.nextInt(); // Read the target number
            for (int i = 0; i<2; i++) { // Perform two digit sum operations to reduce the value
                query(s, "digit");
            }
            query(s, "add -8"); // Adjust the value by subtracting 8
            query(s, "add -4"); // Continue adjusting
            query(s, "add -2"); // Continue adjusting
            query(s, "add -1"); // Continue adjusting
            query(s, "add " + (n-1)); // Add the remaining difference to reach target
            if (query(s, "!") == -1) { // Check if we have reached the target
                t=0; // Exit loop if correct
            }
        }
    }
    public static int query(Scanner s, String str) {
        System.out.println(str); // Send command to jury
        System.out.flush(); // Ensure output is sent immediately
        return s.nextInt(); // Read response from jury
    }
}


// https://github.com/VaHiX/CodeForces/