// Problem: CF 2138 F - Ode to the Bridge Builder
// https://codeforces.com/contest/2138/problem/F

/*
 * F. Ode to the Bridge Builder
 * 
 * PURPOSE:
 *   This code constructs a point (p, q) on a 2D plane using a series of operations,
 *   where each operation adds a new point and forms a triangle with two existing points.
 *   Each triangle must satisfy side length constraints: 0.5 <= side <= 1.
 *   
 * ALGORITHM:
 *   - Start with two points at (0, 0) and (1, 0).
 *   - Compute the angle to the target point and use that to direct construction toward it.
 *   - Build segments incrementally toward the destination, adjusting for deviation.
 *   - Special handling is applied when the initial angle is too small or large.
 *   
 * TIME COMPLEXITY:
 *   O(m) where m = ceil(2 * sqrt(p^2 + q^2)), due to a linear construction path.
 *   
 * SPACE COMPLEXITY:
 *   O(m) for storing intermediate points and operations.
 */

import java.io.*;
import java.util.*;

public class Main {
    static final int N = 100000;
    static final double PI = Math.acos(-1);
    static double[] xx = new double[N];
    static double[] yy = new double[N];
    static int[] uu = new int[N];
    static int[] vv = new int[N];
    static int n;

    // Adds a point to the array and increments counter
    static int add(double x, double y, int u, int v) {
        xx[n] = x;
        yy[n] = y;
        uu[n] = u;
        vv[n] = v;
        return n++;
    }

    public static void main(String[] args) throws IOException {
        FastScanner fs = new FastScanner(System.in);
        PrintWriter out = new PrintWriter(System.out);
        int t = fs.nextInt();
        while (t-- > 0) {
            int x = fs.nextInt();
            int y = fs.nextInt();
            fs.nextInt(); // m is ignored, computed internally

            double d = Math.hypot(x, y); // Distance to target point
            double ang = Math.atan2(y, x); // Angle to target point
            double dx = Math.cos(ang);
            double dy = Math.sin(ang); // Unit vector towards target

            n = 0;
            int i = add(0, 0, -1, -1); // Add first point (0,0)
            int j = add(1, 0, -1, -1); // Add second point (1,0)
            int special = 0;

            // Adjust initial points if angle is too small or large
            if (ang < PI / 6) {
                j = add(Math.cos(ang + PI / 6), Math.sin(ang + PI / 6), 0, 1);
                special = 1;
            } else if (ang > PI / 3) {
                j = add(Math.cos(ang - PI / 6), Math.sin(ang - PI / 6), 0, 1);
                special = 1;
            }

            // Iteratively move towards the target using small steps
            while (d > 2) {
                i = add(xx[i] + dx, yy[i] + dy, i, j); // Add point in direction of target
                j = add(xx[j] + dx, yy[j] + dy, i, j);
                d--;
            }

            // Final adjustment near the destination
            if (special == 1 && d <= 1.5) {
                i = add(xx[i] + dx * d / 2, yy[i] + dy * d / 2, i, j);
                i = add(xx[i] + dx * d / 2, yy[i] + dy * d / 2, i, j);
            } else {
                i = add(xx[i] + dx * d / 2, yy[i] + dy * d / 2, i, j);
                j = add(xx[j] + dx * d / 2, yy[j] + dy * d / 2, i, j);
                i = add(xx[i] + dx * d / 2, yy[i] + dy * d / 2, i, j);
            }

            out.println(n - 2); // Output number of operations
            for (i = 2; i < n; i++) {
                out.printf("%d %d %.12f %.12f%n", uu[i] + 1, vv[i] + 1, xx[i], yy[i]); // Print each operation
            }
        }
        out.flush();
    }

    static class FastScanner {
        private final InputStream in;
        private final byte[] buffer = new byte[1 << 16];
        private int ptr = 0, len = 0;
        
        FastScanner(InputStream in) {
            this.in = in;
        }
        
        private int readByte() throws IOException {
            if (ptr >= len) {
                len = in.read(buffer);
                ptr = 0;
                if (len <= 0) return -1;
            }
            return buffer[ptr++];
        }
        
        int nextInt() throws IOException {
            int c, sign = 1, val = 0;
            do {
                c = readByte();
            } while (c <= ' ');
            if (c == '-') {
                sign = -1;
                c = readByte();
            }
            while (c > ' ') {
                val = val * 10 + (c - '0');
                c = readByte();
            }
            return val * sign;
        }
    }
}


// https://github.com/VaHiX/codeForces/