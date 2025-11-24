// Problem: CF 2155 D - Batteries
// https://codeforces.com/contest/2155/problem/D

/*
 * Problem: D. Batteries
 * Purpose: Find a working pair of batteries among n batteries using at most floor(n^2 / a) queries,
 *          where a is the number of working batteries (unknown). The flashlight only turns on if both
 *          selected batteries work.
 *
 * Algorithm:
 * - Uses a cyclic search strategy to efficiently narrow down working pairs.
 * - Iterates through all possible distances from 1 to n/2.
 * - For each distance, loops over all starting positions and checks the pair (start, start + distance).
 * - If the result of a query is 1 or -1 (indicating a valid working battery pair), stop and return.
 *
 * Time Complexity: O(n^2)
 * Space Complexity: O(1)
 */
import java.util.Scanner;
public class D_Batteries {
    public static void main(String[] args) {
        Scanner alpha = new Scanner(System.in);
        int tests = alpha.nextInt(); // Read number of test cases
        while (tests-- > 0) {
            int n = alpha.nextInt(); // Read number of batteries
            executeCyclicSearch(n, alpha); // Perform search for working pair
        }
        alpha.close(); // Close scanner to free resources
    }
    
    static void executeCyclicSearch(int totalAlpha, Scanner scannerAlpha) {
        int halfAlpha = totalAlpha / 2; // Calculate maximum distance to test
        int distanceAlpha = 1; // Initialize current distance
        while (distanceAlpha <= halfAlpha) { // Iterate through all distances
            for (int startAlpha = 1; startAlpha <= totalAlpha; startAlpha++) { // Loop over start positions
                int endAlpha = startAlpha + distanceAlpha; // Compute end position
                endAlpha = (endAlpha > totalAlpha) ? endAlpha - totalAlpha : endAlpha; // Wrap around if necessary
                if (performQuery(startAlpha, endAlpha, scannerAlpha)) return; // Query and check result
            }
            distanceAlpha++; // Increase distance for next iteration
        }
    }
    
    static boolean performQuery(int firstAlpha, int secondAlpha, Scanner scannerAlpha) {
        System.out.println(firstAlpha + " " + secondAlpha); // Output query
        System.out.flush(); // Flush output to ensure immediate sending
        int responseAlpha = scannerAlpha.nextInt(); // Read response from jury
        return responseAlpha == 1 || responseAlpha == -1; // Return true if found a working pair
    }
}


// https://github.com/VaHiX/CodeForces/