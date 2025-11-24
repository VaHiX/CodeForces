// Problem: CF 2146 E - Yet Another MEX Problem
// https://codeforces.com/contest/2146/problem/E

/*
E. Yet Another MEX Problem

This code solves the problem of computing for each position i in an array,
the maximum weight among all subarrays ending at that position.

The key insight is to use a segment tree with range max query and range update
to efficiently maintain how many elements exceed the MEX value at any point.
Using lazy propagation, we can perform fast updates on ranges and queries.

Algorithm:
- Initialize segment tree over indices [0, n]
- For each element in array:
  - Set the element's position to 0 (because it will be considered in the MEX)
  - Add 1 to all previous indices if they are less than current element 
  - Query maximum weight from 0 to n
- The weight of a subarray is the count of indices where `a[i] > mex(a)`

Time Complexity: O(n log n) per test case
Space Complexity: O(n) for segment tree storage

*/
import java.io.*;
import java.util.StringTokenizer;
public class E {
    static void preSolve() {}
    static class Node {
        int left, right;
        int max;
        int pendingAdd;
        final Node lChild, rChild;
        Node(int left, int right) {
            this.left = left;
            this.right = right;
            if (left != right) {
                int mid = (left + right) / 2;
                lChild = new Node(left, mid);
                rChild = new Node(mid + 1, right);
            } else {
                lChild = null;
                rChild = null;
            }
        }
        int max(int left, int right) {
            if (left <= this.right && right >= this.left) {
                left = Math.max(left, this.left);
                right = Math.min(right, this.right);
                if (left == this.left && right == this.right) {
                    return pendingAdd + max; // Return current value with pending updates
                } else {
                    return pendingAdd + Math.max(lChild.max(left, right), rChild.max(left, right)); // Propagate and query
                }
            } else {
                return 0;
            }
        }
        void add(int left, int right, int value) {
            if (left <= this.right && right >= this.left) {
                left = Math.max(left, this.left);
                right = Math.min(right, this.right);
                if (left == this.left && right == this.right) {
                    pendingAdd += value; // Apply lazy propagation
                } else {
                    lChild.add(left, right, value);
                    rChild.add(left, right, value);
                    max = Math.max(lChild.max(this.left, this.right), rChild.max(this.left, this.right)); // Update node's max
                }
            }
        }
        void set(int index, int value) {
            if (index >= left && index <= right) {
                if (pendingAdd != 0) { // Resolve pending updates first
                    if (lChild != null) lChild.add(left, right, pendingAdd);
                    if (rChild != null) rChild.add(left, right, pendingAdd);
                    pendingAdd = 0;
                }
                if (left == right) {
                    max = value; // Leaf node update
                } else {
                    lChild.set(index, value);
                    rChild.set(index, value);
                    int lm = lChild.max(left, right);
                    int rm = rChild.max(left, right);
                    max = Math.max(lm, rm); // Update internal nodes
                }
            }
        }
        void check() {
            if (lChild != null) lChild.check();
            if (rChild != null) rChild.check();
            int realMax = 0;
            for (int t = left; t <= right; ++t) {
                realMax = Math.max(realMax, max(t, t));
            }
            if (realMax != max(left, right)) {
                dump();
                throw new AssertionError("realMax = " + realMax + ", interval = " + max(left, right));
            }
        }
        void dump() {
            if (lChild != null) lChild.dump();
            if (rChild != null) rChild.dump();
            System.err.println("Node(left = " + left + ", right = " + right + ", pending = " + pendingAdd + ", max = " + max + ", max interval = " + max(left, right) + ")");
        }
    }
    static void solve(Input in, PrintWriter out) {
        int n = in.nextInt();
        Node node = new Node(0, n);
        for (int i = 0; i < n; ++i) {
            int v = in.nextInt();
            node.set(v, 0);               // Set value at position v to 0
            if (v > 0) node.add(0, v - 1, 1);  // Add 1 to all positions less than v
            out.print(node.max(0, n));    // Get maximum weight in range [0, n]
            out.print(i + 1 == n ? '\n' : ' '); // Print space or newline
        }
    }
    static class Input implements Closeable {
        private final BufferedReader br;
        private StringTokenizer st;
        Input() throws IOException {
            br = new BufferedReader(new InputStreamReader(System.in));
            st = new StringTokenizer(br.readLine());
        }
        private String next() {
            while (!st.hasMoreTokens()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (IOException ex) {
                    throw new RuntimeException(ex);
                }
            }
            return st.nextToken();
        }
        private int nextInt() {
            return Integer.parseInt(next());
        }
        private int[] nextIntArray(int n) {
            int[] rv = new int[n];
            for (int i = 0; i < n; ++i) {
                rv[i] = nextInt();
            }
            return rv;
        }
        @Override
        public void close() throws IOException {
            br.close();
        }
    }
    public static void main(String[] args) throws IOException {
        preSolve();
        try (Input in = new Input(); PrintWriter out = new PrintWriter(System.out)) {
            int n = in.nextInt();
            for (int t = 0; t < n; ++t) {
                solve(in, out);
            }
        }
    }
}


// https://github.com/VaHiX/CodeForces/