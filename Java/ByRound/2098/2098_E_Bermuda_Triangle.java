// Problem: CF 2098 E - Bermuda Triangle
// https://codeforces.com/contest/2098/problem/E

/**
 * Problem: Bermuda Triangle
 * 
 * Algorithm:
 * The problem is about simulating the path of an airplane inside a triangular region
 * and determining if it can escape by hitting a vertex, and counting the number
 * of boundary hits before escaping.
 * 
 * We use mathematical techniques to solve this, including:
 * - Linear Diophantine equations to find intersection points
 * - Extended Euclidean algorithm for solving equations
 * - Vector reflection math
 * 
 * Time Complexity: O(log(min(n, vx, vy))) per test case due to GCD computations
 * Space Complexity: O(1) - only a constant amount of extra space used
 */
import java.util.*;

public class Main {
    static class G {
        long a, b, c;
        G(long a, long b, long c) {
            this.a = a;
            this.b = b;
            this.c = c;
        }
    }
    static class I {
        long a, b, c, d, e;
        I(long a, long b, long c, long d, long e) {
            this.a = a;
            this.b = b;
            this.c = c;
            this.d = d;
            this.e = e;
        }
    }
    static class C {
        long a, b;
        C(long a, long b) {
            this.a = a;
            this.b = b;
        }
    }
    
    /**
     * Extended Euclidean algorithm to solve ax + by = gcd(a,b)
     */
    static G A(long a, long b) {
        if (b == 0) {
            return new G(a, 1, 0);
        }
        G c = A(b, a % b);
        long d = c.c;
        long e = c.b - (a / b) * c.c;
        return new G(c.a, d, e);
    }
    
    /**
     * Ceiling division: ceil(a/b)
     */
    static long B(long a, long b) {
        if (a >= 0) {
            return (a + b - 1) / b;
        } else {
            return a / b;
        }
    }
    
    /**
     * Reads input data for one test case
     */
    static I C(Scanner a) {
        long b = a.nextLong();
        long c = a.nextLong();
        long d = a.nextLong();
        long e = a.nextLong();
        long f = a.nextLong();
        return new I(b, c, d, e, f);
    }
    
    /**
     * Checks if 'b' divides 'a'
     */
    static boolean D(long a, long b) {
        return b % a == 0;
    }
    
    /**
     * Solves linear Diophantine equation ax + by = c
     */
    static C E(long a, long b, long c) {
        G d = A(c, b);
        if (a % d.a != 0) {
            return null;
        }
        long e = a / d.a;
        long f = d.b * e;
        long g = -d.c * e;
        return new C(f, g);
    }
    
    /**
     * Calculates intersection point of two lines
     */
    static C F(long a, long b, long c, long d, long e) {
        long f = c / e;
        long g = d / e;
        long h = Math.max(B(1 - a, f), B(1 - b, g));
        long i = a + f * h;
        long j = b + g * h;
        return new C(i, j);
    }
    
    /**
     * Calculates number of reflections needed to escape
     */
    static long G(long a, long b, long c, long d) {
        if (a <= 0 || b <= 0) {
            return -1;
        }
        if (a == b) {
            if (a == 1 || c == d) {
                return 1;
            } else {
                return 3 * a - 2;
            }
        } else {
            long e = Math.max(a, b);
            long f = ((e - Math.min(a, b)) & 1) == 0 ? e : e - 1;
            return a + b - 2 + f;
        }
    }
    
    /**
     * Main logic to determine escape count
     */
    static long H(I a) {
        // This line calculates intersection of the line trajectory with one side
        long b = a.e * a.b - a.d * a.c;
        if (!D(a.a, b)) {
            return -1;
        }
        long c = b / a.a;
        C d = E(c, a.d, a.e);
        if (d == null) {
            return -1;
        }
        G e = A(a.e, a.d);
        C f = F(d.a, d.b, a.d, a.e, e.a);
        return G(f.a, f.b, a.d, a.e);
    }
    
    public static void main(String[] args) {
        Scanner a = new Scanner(System.in);
        int b = a.nextInt();
        int c = 0;
        while (c < b) {
            I d = C(a);
            long e = H(d);
            System.out.println(e);
            c++;
        }
        a.close();
    }
}


// https://github.com/VaHiX/CodeForces/