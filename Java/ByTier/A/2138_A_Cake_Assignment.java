// Problem: CF 2138 A - Cake Assignment
// https://codeforces.com/contest/2138/problem/A

/**
 * Problem: Cake Assignment
 *
 * Description:
 * Chocola and Vanilla initially have 2^k cakes each, making a total of 2^(k+1) cakes.
 * They want to redistribute the cakes such that Chocola ends up with exactly x cakes,
 * and Vanilla gets (2^(k+1) - x) cakes. 
 *
 * Available operations:
 * Operation 1: Chocola gives half her cakes to Vanilla (only if Chocola has even number of cakes).
 * Operation 2: Vanilla gives half her cakes to Chocola (only if Vanilla has even number of cakes).
 *
 * Goal: Find minimum number of operations to reach target (x), and output a valid sequence of operations.
 *
 * Algorithm:
 * The process is essentially based on reversing the distribution steps using binary representation logic.
 * We simulate backward from the desired state towards the starting point by performing reverse operations.
 * Using greedy approach we decide at each step which person gives half their cakes to the other,
 * ensuring they move closer to the required allocation for Chocola.
 *
 * Time Complexity: O(k) per test case, since k <= 60 and number of steps is bounded by 120.
 * Space Complexity: O(1), only constant extra space used apart from output array.
 */
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.*;
public final class Main {
    private final static class Printer {
        final PrintWriter pr;
        final StringBuilder sb;
        public Printer() {
            pr = new PrintWriter(new OutputStreamWriter(System.out));
            sb = new StringBuilder();
        }
        public void add(Object o) {
            sb.append(o);
        }
        public void addln(Object o) {
            sb.append(o).append("\n");
        }
        public void addln() {
            sb.append("\n");
        }
        public void print() {
            pr.write(sb.toString());
            sb.setLength(0);
        }
        public void close() {
            sb.setLength(0);
            pr.close();
        }
    }
    private final static class Reader {
        final BufferedReader br;
        StringTokenizer st;
        public Reader() {
            br = new BufferedReader(new InputStreamReader(System.in));
        }
        public String next() {
            while (st == null || !st.hasMoreElements()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (Exception  e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }
        public int nextInt() {
            return Integer.parseInt(next());
        }
        public long nextLong() {
            return Long.parseLong(next());
        }
        public double nextDouble() {
            return Double.parseDouble(next());
        }
        public float nextFloat() {
            return Float.parseFloat(next());
        }
        public String nextLine() {
            String str = "";
            try {
                str = br.readLine();
            } catch (Exception e)  {
                e.printStackTrace();
            }
            return str;
        }
    }
    private final Printer p;
    private final Reader r;
    public Main() {
        this.p = new Printer();
        this.r = new Reader();
    }
    public static void main(String[] args) {
        new Main().perform();
    }
    void perform() {
        int tc = r.nextInt(); // read number of test cases
        nextTC:
        while(tc-- > 0) {
            final long k = r.nextLong(); // value of k as given by input
            long x = r.nextLong(); // number of cakes Chocola should end with
            long choco = 1L << k; // initial amount of cakes each person has
            long vani = 1L << k;
            final long total = 1L << (k + 1); // total number of cakes
            final long initial = 1L << k; // initial quantity per person
            if(x == 0 || x == total) { // edge cases where invalid distribution is impossible or already satisfied
                p.addln(-1); // -1 indicates no valid operation needed (but here it's a dummy case for problem constraint)
                continue nextTC;
            }
            // Start with current positions
            choco = x;  // assign actual values to choco & vani, now in the final state
            vani = total - choco; // compute what vani currently has
            final int[] ans = new int[1 << 8]; // answer array for storing sequence of operations
            int filled = 0; // pointer to track current position in ans array
            
            /* 
             * simulate process back from target distribution to initial state.
             * at each step decide whether choco or vani should give half their cakes.
             * this reverse thinking gives us minimum steps and order.
            */
            while(choco != initial) { // while we haven't reached the original (equal) distribution
                if(choco > vani) { // if Chocola has more than Vanilla
                    ans[filled++] = 2; // operation: Vanilla gives half to Chocola (reverse of operation 1)
                    choco -= vani; // subtract what was given away from Chocola's count
                    vani <<= 1L; // multiply vani's count as it increases after giving
                } else { // if Vanilla has more than Chocola
                    ans[filled++] = 1; // operation: Chocola gives half to Vanilla (reverse of operation 2)
                    vani -= choco; // subtract what was given away from Vanilla's count
                    choco <<= 1L; // multiply choco's count as it increases after giving
                }
            }
            
            p.addln(filled); // output number of operations required
            for (int i = filled - 1; i > -1; --i) { // print in reverse order to get real sequence
                p.add(ans[i] + " "); // add each operation to output string buffer
            }
            p.addln(); // newline after printing operations
        }
        p.print(); // flush and print final output
        p.close(); // close resources
    }
}


// https://github.com/VaHiX/codeForces/