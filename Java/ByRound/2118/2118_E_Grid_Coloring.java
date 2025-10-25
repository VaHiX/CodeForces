// Problem: CF 2118 E - Grid Coloring
// https://codeforces.com/contest/2118/problem/E

/*
E. Grid Coloring
Algorithm: The solution uses a greedy approach by sorting all grid points based on their chessboard distance from the center of the grid, with tie-breaking by Manhattan distance. This ensures that we color cells in an order that minimizes the penalties incurred by previously colored cells.
Time Complexity: O(n * m * log(n * m)), due to sorting the points.
Space Complexity: O(n * m), for storing all the points.

The problem involves coloring a grid such that no cell receives more than 3 penalties during the process. The key insight is to sort the points based on their distance from the center of the grid using the chessboard distance as the primary criterion, and Manhattan distance to break ties.
*/
import java.io.*;
import java.util.*;
public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int T = Integer.parseInt(br.readLine());
        while (T-- > 0) {
            String[] dims = br.readLine().split(" ");
            int n = Integer.parseInt(dims[0]);
            int m = Integer.parseInt(dims[1]);
            int cx = n / 2;  // Center x-coordinate
            int cy = m / 2;  // Center y-coordinate
            List<int[]> points = new ArrayList<>();
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    int dx = Math.abs(i - cx);   // Horizontal distance to center
                    int dy = Math.abs(j - cy);   // Vertical distance to center
                    int c = Math.max(dx, dy);    // Chessboard distance
                    int mDist = dx + dy;         // Manhattan distance
                    int x = i + 1;               // 1-based row index
                    int y = j + 1;               // 1-based column index
                    points.add(new int[]{c, mDist, x, y}); // Store as [chessboard_dist, manhattan_dist, x, y]
                }
            }
            Collections.sort(points, (a, b) -> {
                if (a[0] != b[0]) {             // If chessboard distances differ
                    return Integer.compare(a[0], b[0]); // Sort by chessboard distance ascending
                } else {
                    return Integer.compare(a[1], b[1]); // Otherwise sort by Manhattan distance ascending
                }
            });
            for (int[] point : points) {
                System.out.println(point[2] + " " + point[3]); // Print 1-based coordinates
            }
        }
    }
}


// https://github.com/VaHiX/CodeForces/