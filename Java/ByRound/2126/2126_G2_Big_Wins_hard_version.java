// Problem: CF 2126 G2 - Big Wins!  (hard version)
// https://codeforces.com/contest/2126/problem/G2

/**
 * Problem: G2. Big Wins! (hard version)
 * 
 * Algorithm/Technique: 
 * - Use a segment tree to efficiently compute range minimums
 * - Process array elements in descending order
 * - Maintain intervals representing valid subarrays where current element is the median
 * - For each element in descending order, compute the maximum med - min for valid subarrays containing it
 * 
 * Time Complexity: O(n log n) - sorting + segment tree operations
 * Space Complexity: O(n) - segment tree + additional data structures
 * 
 * Approach:
 * 1. Build a segment tree to answer range minimum queries efficiently
 * 2. Sort elements in descending order with their indices
 * 3. For each element, consider it as potential median and find the largest subarray containing it
 * 4. Use interval merging to track valid subarrays and use segment tree to compute minimums
 * 5. Track maximum med - min across all valid subarrays
 */
import java.io.*;
import java.util.*;
public class G {
    public static void main(String[] args) throws IOException {
        try (Input input = new StandardInput(); PrintWriter output = new PrintWriter(System.out)) {
            int t = input.nextInt();
            if (t == -1) {
                randomizedTesting();
                return;
            }
            while (t-->0) {
                int solution = solve(input.readIntArray());
                output.println(solution);
            }
        }
    }
    static int bruteForce(int[] a) {
        int best = 0;
        for (int i = 0; i < a.length; i++) {
            for (int j = i + 1; j <= a.length; j++) {
                int[] b = new int[j - i];
                System.arraycopy(a, i, b, 0, b.length);
                Arrays.sort(b);
                best = Math.max(best, b[b.length / 2] - b[0]);
            }
        }
        return best;
    }
    static void randomizedTesting() {
        Random r = new Random();
        for (int t = 0; t < 1000; t++) {
            int n = 10;
            int[] a = new int[n];
            for (int i = 0; i < n; i++) {
                a[i] = r.nextInt(n) + 1;
            }
            int actual = solve(a);
            int expected = bruteForce(a);
            if (expected != actual) {
                System.out.printf("input: %s, expected: %d, actual: %d\n", Arrays.toString(a), expected, actual);
                return;
            }
        }
    }
    static class Interval implements Comparable<Interval> {
        int left, right;
        public Interval(int left, int right) {
            this.left = left;
            this.right = right;
        }
        @Override
        public int compareTo(Interval o) {
            return left - o.left;
        }
        void leftJoin(Interval i) {
            int len = right - left + i.right - i.left;
            left = Math.min(left, i.left);
            right = left + len;
        }
        void rightJoin(Interval i) {
            int len = right - left + i.right - i.left;
            right = Math.max(right, i.right);
            left = right - len;
        }
    }
    static class MinSegmentTree {
        final int ABSENT_VALUE = Integer.MAX_VALUE;
        private int size;
        final private int[] a;
        MinSegmentTree(int n) {
            size = 1;
            while (size <= n) {
                size *= 2;
            }
            a = new int[2 * size];
            Arrays.fill(a, ABSENT_VALUE);
        }
        void set(int i, int value) {
            a[size + i] = value;
            for (int j = (size + i) / 2; j > 0; j /= 2) {
                a[j] = Math.min(a[2 * j], a[2 * j + 1]);
            }
        }
        int getMin(int l, int r) {
            int min = ABSENT_VALUE;
            for (l += size, r += size; l < r; l /= 2, r /= 2) {
                if (l % 2 == 1) {
                    min = Math.min(min, a[l++]);
                }
                if (r % 2 == 1) {
                    min = Math.min(min, a[--r]);
                }
            }
            return min;
        }
    }
    static class ArrayItem implements Comparable<ArrayItem> {
        int index, value;
        public ArrayItem(int index, int value) {
            this.index = index;
            this.value = value;
        }
        @Override
        public int compareTo(ArrayItem o) {
            if (value == o.value) {
                return index - o.index;
            }
            return o.value - value;
        }
    }
    private static int solve(int[] a) {
        int n = a.length;
        MinSegmentTree minSegmentTree = new MinSegmentTree(n);
        for (int i = 0; i < n; i++) {
            minSegmentTree.set(i, a[i]); // Build the segment tree with array elements
        }
        ArrayItem[] arrayItems = new ArrayItem[n];
        for (int i = 0; i < n; i++) {
            arrayItems[i] = new ArrayItem(i, a[i]); // Create items with index and value
        }
        Arrays.sort(arrayItems); // Sort in descending order by value
        
        // TreeSet to maintain intervals representing left shadows (subarrays that can extend to the left)
        TreeSet<Interval> leftShadows = new TreeSet<>(Comparator.comparingInt(i -> i.right));
        // TreeSet to maintain intervals representing right shadows (subarrays that can extend to the right)
        TreeSet<Interval> rightShadows = new TreeSet<>();
        int best = 0;
        
        // Process elements in descending order
        for (ArrayItem current : arrayItems) {
            // Create interval representing potential extension to the right
            Interval rightShadow = new Interval(current.index, current.index + 2);
            // Find overlapping intervals to merge
            Interval leftNeighbor = rightShadows.floor(rightShadow);
            if (leftNeighbor != null && leftNeighbor.right >= rightShadow.left) {
                rightShadow.leftJoin(leftNeighbor);
                rightShadows.remove(leftNeighbor);
            }
            // Continue merging with other neighbors
            while (true) {
                Interval rightNeighbor = rightShadows.ceiling(rightShadow);
                if (rightNeighbor != null && rightNeighbor.left <= rightShadow.right) {
                    rightShadow.leftJoin(rightNeighbor);
                    rightShadows.remove(rightNeighbor);
                } else {
                    break;
                }
            }
            rightShadows.add(rightShadow);
            // Compute the maximum med - min for this interval
            best = Math.max(best, current.value - minSegmentTree.getMin(rightShadow.left, Math.min(rightShadow.right, n)));
        }
        
        // Reset the interval structures for left passes
        leftShadows = new TreeSet<>(Comparator.comparingInt(i -> i.right));
        rightShadows = new TreeSet<>();
        
        // Process elements in descending order from the left perspective
        for (ArrayItem current : arrayItems) {
            // Create interval representing potential extension to the left
            Interval leftShadow = new Interval(current.index - 1, current.index + 1);
            // Find overlapping intervals to merge
            Interval rightNeighbor = leftShadows.ceiling(leftShadow);
            if (rightNeighbor != null && rightNeighbor.left <= leftShadow.right) {
                leftShadow.rightJoin(rightNeighbor);
                leftShadows.remove(rightNeighbor);
            }
            // Continue merging with other neighbors
            while (true) {
                Interval leftNeighbor = leftShadows.floor(leftShadow);
                if (leftNeighbor != null && leftNeighbor.right >= leftShadow.left) {
                    leftShadow.rightJoin(leftNeighbor);
                    leftShadows.remove(leftNeighbor);
                } else {
                    break;
                }
            }
            leftShadows.add(leftShadow);
            // Compute the maximum med - min for this interval
            best = Math.max(best, current.value - minSegmentTree.getMin(Math.max(0, leftShadow.left), leftShadow.right));
        }
        return best;
    }
    interface Input extends Closeable {
        String next() throws IOException;
        default int nextInt() throws IOException {
            return Integer.parseInt(next());
        }
        default long nextLong() throws IOException {
            return Long.parseLong(next());
        }
        default int[] readIntArray() throws IOException {
            return readIntArray(nextInt());
        }
        default int[] readIntArray(int size) throws IOException {
            int[] array = new int[size];
            for (int i = 0; i < array.length; i++) {
                array[i] = nextInt();
            }
            return array;
        }
        default long[] readLongArray() throws IOException {
            return readLongArray(nextInt());
        }
        default long[] readLongArray(int size) throws IOException {
            long[] array = new long[size];
            for (int i = 0; i < array.length; i++) {
                array[i] = nextLong();
            }
            return array;
        }
    }
    private static class StandardInput implements Input {
        private final BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        private StringTokenizer stringTokenizer;
        @Override
        public void close() throws IOException {
            reader.close();
        }
        @Override
        public String next() throws IOException {
            if (stringTokenizer == null || !stringTokenizer.hasMoreTokens()) {
                stringTokenizer = new StringTokenizer(reader.readLine());
            }
            return stringTokenizer.nextToken();
        }
    }
}


// https://github.com/VaHiX/CodeForces/