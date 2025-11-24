// Problem: CF 2145 F - Long Journey
// https://codeforces.com/contest/2145/problem/F

/*
 * Problem: F. Long Journey
 * Purpose: Simulate a chip moving through cells with traps activating based on modular arithmetic cycles.
 *          Determine minimum turns to reach cell m or return -1 if impossible.
 *
 * Algorithm:
 *   - Use cycle detection with HashMap to identify repeating states (position + phase).
 *   - For each turn, determine which trap rules apply and whether the chip can move.
 *   - Apply optimizations for long paths using cycle length and gain to reduce time.
 *   - Time complexity: O(n * L) where L is the least common multiple of a[i], worst case ~ 10^7
 *   - Space complexity: O(L) for storing seen states.
 */
import java.io.*;
import java.util.*;
public class Main {
    static long gcd(long a, long b) {
        while (b != 0) {
            long t = a % b;
            a = b;
            b = t;
        }
        return a;
    }
    static long lcm(long a, long b) {
        return a / gcd(a, b) * b;
    }
    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner(System.in);
        int T = fs.nextInt();
        StringBuilder out = new StringBuilder();
        while (T-- > 0) {
            int n = fs.nextInt();
            long m = fs.nextLong();
            long[] a = new long[n];
            long[] b = new long[n];
            for (int i = 0; i < n; i++) a[i] = fs.nextLong();
            for (int i = 0; i < n; i++) b[i] = fs.nextLong();
            out.append(solve(n, m, a, b)).append('\n');
        }
        System.out.print(out.toString());
    }
    static long solve(int n, long m, long[] a, long[] b) {
        if (m == 0) return 0;
        long L = 1;
        for (int i = 0; i < n; i++) L = lcm(L, a[i]); // Calculate cycle length
        long pos = 0L;
        long turn = 1L; 
        HashMap<Long, long[]> seen = new HashMap<>();
        while (true) {
            int phase = (int) ((turn - 1) % n);      // Determine which trap rule applies
            long residue = pos % L;
            long key = (residue << 4) | phase;       // Encode state to detect cycles
            if (seen.containsKey(key)) {
                long[] prev = seen.get(key);
                long prevTurn = prev[0];
                long prevPos = prev[1];
                long cycleTurns = turn - prevTurn;
                long cycleGain = pos - prevPos;
                if (cycleGain <= 0) return -1;       // No progress, impossible
                long remaining = m - pos;
                long fullCycles = remaining / cycleGain;
                if (fullCycles > 0) {
                    long apply = Math.max(0L, fullCycles - 1L);
                    pos += apply * cycleGain;
                    turn += apply * cycleTurns;
                }
            } else {
                seen.put(key, new long[]{turn, pos}); // Record state
            }
            phase = (int) ((turn - 1) % n);
            boolean canMove = ((pos + 1) % a[phase]) != b[phase]; // Check if move is valid
            boolean canStay = (pos % a[phase]) != b[phase];        // Check if staying is valid
            if (!canMove && !canStay) return -1;                   // Dead end
            if (canMove) pos += 1L;
            if (pos == m) return turn; 
            turn++;
        }
    }
    static class FastScanner {
        private final byte[] buffer = new byte[1 << 16];
        private int ptr = 0, len = 0;
        private final InputStream in;
        FastScanner(InputStream in) { this.in = in; }
        int readByte() throws IOException {
            if (ptr >= len) {
                len = in.read(buffer);
                ptr = 0;
                if (len <= 0) return -1;
            }
            return buffer[ptr++];
        }
        long nextLong() throws IOException {
            int c;
            while ((c = readByte()) <= 32 && c != -1) ;
            boolean neg = c == '-';
            if (neg) c = readByte();
            long val = 0;
            while (c > 32) {
                val = val * 10 + (c - '0');
                c = readByte();
            }
            return neg ? -val : val;
        }
        int nextInt() throws IOException { return (int) nextLong(); }
    }
}


// https://github.com/VaHiX/CodeForces/