// Problem: CF 2101 A - Mex in the Grid
// https://codeforces.com/contest/2101/problem/A

/*
 * Problem: Arrange numbers from 0 to n^2 - 1 in an n x n grid such that the sum of MEX values
 *          over all possible subgrids is maximized.
 *
 * Algorithm:
 *   - This implementation fills the grid in a spiral pattern starting from the top-left,
 *     filling with decreasing values (n^2 - 1 down to 0), which helps in maximizing MEX sums
 *     by keeping smaller numbers grouped together, thus improving chances of lower MEX values
 *     for larger subgrids.
 *
 * Time Complexity: O(n^2)
 * Space Complexity: O(n^2)
 */

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt(); // Read number of test cases
        while (t-- > 0) { // Process each test case
            int n = sc.nextInt(); // Read size of grid
            int[][] grid = new int[n][n]; // Initialize grid
            int top = 0, bottom = n - 1, left = 0, right = n - 1; // Boundaries for spiral filling
            int cur = n * n - 1; // Start filling with largest value
            while (top <= bottom && left <= right) { // Spiral traversal loop
                // Fill top row from left to right
                for (int j = left; j <= right; j++) {
                    grid[top][j] = cur--; // Assign current value and decrement
                }
                top++; // Move top boundary down
                // Fill right column from top to bottom
                for (int i = top; i <= bottom; i++) {
                    grid[i][right] = cur--; // Assign current value and decrement
                }
                right--; // Move right boundary left
                if (top <= bottom) { // Check if rows remain
                    // Fill bottom row from right to left
                    for (int j = right; j >= left; j--) {
                        grid[bottom][j] = cur--; // Assign current value and decrement
                    }
                    bottom--; // Move bottom boundary up
                }
                if (left <= right) { // Check if columns remain
                    // Fill left column from bottom to top
                    for (int i = bottom; i >= top; i--) {
                        grid[i][left] = cur--; // Assign current value and decrement
                    }
                    left++; // Move left boundary right
                }
            }
            // Output the generated grid
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    System.out.print(grid[i][j]);
                    if (j < n - 1) System.out.print(" "); // Add space between elements
                }
                System.out.println(); // New line after each row
            }
            if (t > 0) System.out.println(); // Print blank line between test cases
        }
        sc.close(); // Close scanner
    }
}


// https://github.com/VaHiX/CodeForces/