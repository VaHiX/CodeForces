// Problem: CF 2111 F - Puzzle
// https://codeforces.com/contest/2111/problem/F

/**
 * F. Puzzle
 * 
 * Problem Description:
 * Given a ratio p/s, determine if it's possible to arrange square puzzle pieces such that:
 * - Each piece is aligned with coordinate axes
 * - No overlaps
 * - All pieces form one connected component
 * - The ratio of perimeter to area equals p/s
 * - Total number of pieces <= 50000
 * 
 * Algorithm:
 * - Simplify the ratio p/s to its lowest terms using GCD.
 * - If p is odd, multiply both p and s by 2 to make p even.
 * - For each candidate multiplier i (up to 1000), check if a valid arrangement exists:
 *   - Use a specific pattern (a x b rectangle with additional pieces)
 * - Construct the solution using:
 *   - Horizontal line of 's1' pieces
 *   - Vertical line of 's2' pieces
 *   - Fill remaining area in a grid
 * 
 * Time Complexity: O(1000 * s1 * s2) = O(10^6) in worst case, but effectively constant due to constraints.
 * Space Complexity: O(k) where k <= 50000 for storing coordinates.
 */
import java.util.*;
import java.io.*;
public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        StringTokenizer st;
        int t = Integer.parseInt(f.readLine());
        while (t-- > 0) {
            st = new StringTokenizer(f.readLine());
            long p = Integer.parseInt(st.nextToken());
            long s = Integer.parseInt(st.nextToken());
            long gcd = gcd(p, s); // Compute GCD to reduce the fraction to simplest form
            p /= gcd;
            s /= gcd;
            if (p % 2 == 1) { // If p is odd, make it even to simplify construction
                p *= 2;
                s *= 2;
            }
            long ans = -1;
            for (long i = 1; i <= 1000; i++) { // Try small multipliers up to 1000
                long a = i * p / 2;
                long b = i * s;
                if (a / 2 * ((a + 1) / 2) >= b) { // Validate if this configuration can hold enough area
                    ans = i;
                    break;
                }
            }
            if (ans == -1) {
                out.println(-1);
                continue;
            }
            long a = ans * p / 2; // Calculate dimensions for the constructed shape
            long area = ans * s; // Total area for pieces
            long s1 = a / 2; // Number of horizontal cells in base shape
            long s2 = (a + 1) / 2; // Number of vertical cells in base shape
            StringBuffer print = new StringBuffer();
            print.append(area).append("\n"); // Write total number of pieces needed
            for (int i = 0; i < s1; i++) { // First draw horizontal line from (0,0) to (0,s1-1)
                print.append(0).append(" ").append(i).append("\n");
            }
            for (int i = 1; i < s2; i++) { // Then draw vertical line from (1,0) to (s2-1,0)
                print.append(i).append(" ").append(0).append("\n");
            }
            area -= s1;
            area -= s2 - 1;
            aa: // Label for breaking nested loops
            for (long i = 1; i < s2; i++) {
                for (long j = 1; j < s1; j++) {
                    if (area == 0) break aa; // If used all pieces, stop filling
                    print.append(i).append(" ").append(j).append("\n");
                    area--;
                }
            }
            if (area != 0) { // Check if solution was complete (should not happen with valid inputs)
                out.println(-1);
                continue;
            }
            out.print(print);
        }
        f.close();
        out.close();
    }
    public static long gcd(long a, long b) {
        return b == 0 ? a : gcd(b, a % b);
    }
}


// https://github.com/VaHiX/CodeForces/