// Problem: CF 2136 D - For the Champion
// https://codeforces.com/contest/2136/problem/D

/**
 * Problem: D. For the Champion
 * 
 * Purpose: This program finds the initial coordinates of a robot on an infinite 2D plane using interactive queries,
 *          where the robot must determine its starting (X, Y) position based on responses to moves and Manhattan distances
 *          from anchor points.
 *
 * Algorithm:
 * - The technique involves making specific strategic moves to obtain distance values from known anchor points.
 * - By querying the distance when moving vertically (up/down) and horizontally (left/right), we derive formulas
 *   to compute X and Y based on minima of distances.
 * - This method leverages mathematical properties of Manhattan distances to solve for coordinates using minimal queries.
 * 
 * Time Complexity: O(n) per test case, due to preprocessing anchor points and performing 10 fixed queries.
 * Space Complexity: O(n), for storing the anchor points.
 */

import java.io.IOException;
public class Main {
    static int nextInt() throws IOException {
        int sign = 1;
        int input;
        while (!Character.isDigit(input = System.in.read())) {
            sign = (input == '-' ? -1 : 1);
        }
        int val = input & 15; // Converts char to digit (input - '0')
        while (Character.isDigit(input = System.in.read())) {
            val = val * 10 + (input & 15); // Multiply by 10 and add digit
        }
        return sign * val;
    }
    static long nextLong() throws IOException {
        int input;
        while (!Character.isDigit(input = System.in.read())); // Skip non-digits
        long val = input & 15; // Converts char to digit
        while (Character.isDigit(input = System.in.read())) {
            val = val * 10 + (input & 15); // Multiply by 10 and add digit
        }
        return val;
    }
    public static void main(String[] args) throws IOException {
        int t = nextInt(); // Read number of test cases
        final int MAX_X = 1_000_000_000, MAX_Y = 1_000_000_000; // Constants for maximum coordinate values
        
        while (t-- > 0) {
            int n = nextInt(); // Number of anchor points
            long ru = 4_000_000_000L, rd = 4_000_000_000L; // Initialize large values for minimum distances
            
            // Collect anchor points and calculate ru and rd:
            // ru: min Manhattan distance when moving up from current pos to all anchors (MAX_X - x + MAX_Y - y)
            // rd: min Manhattan distance when moving down from current pos to all anchors (MAX_X - x + y + MAX_Y)
            for (int i = 0; i < n; i++) {
                long x = nextInt(), y = nextInt(); 
                ru = Math.min(ru, MAX_X - x + MAX_Y - y);
                rd = Math.min(rd, MAX_X - x + y + MAX_Y);
            }
            
            // Query to determine the 'a' value - moving left by MAX_X units (to get a minimum distance)
            for (int i = 0; i < 2; i++) {
                System.out.println("? R " + MAX_X); // Move right by MAX_X
                nextLong(); // Read response (ignore)
            }
            
            // Query to determine 'b' value - moving up by MAX_Y units (to get a minimum distance)
            System.out.println("? U " + MAX_Y); // Move up by MAX_Y
            nextLong(); // Read response (ignore)
            
            System.out.println("? U " + MAX_Y); // Second up move
            long a = nextLong(); // Store result
            
            // Query to determine 'b' value - moving down by MAX_Y units
            for (int i = 0; i < 3; i++) {
                System.out.println("? D " + MAX_Y); // Move down by MAX_Y
                nextLong(); // Read response (ignore)
            }
            
            System.out.println("? D " + MAX_Y);
            long b = nextLong(); // Store result
            
            // Compute final coordinates using derived equations:
            // X = (a + b - ru - rd) / 2 - 2 * MAX_X
            // Y = (a - b - ru + rd) / 2
            long X = (a + b - ru - rd) / 2 - 2 * MAX_X;
            long Y = (a - b - ru + rd) / 2;
            
            System.out.println("! " + X + " " + Y); // Output result
        }
    }
}


// https://github.com/VaHiX/codeForces/