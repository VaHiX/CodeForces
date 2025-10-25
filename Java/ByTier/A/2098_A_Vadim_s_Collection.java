// Problem: CF 2098 A - Vadim's Collection
// https://codeforces.com/contest/2098/problem/A

/**
 * Problem: A. Vadim's Collection
 * 
 * Algorithm: Greedy approach to construct the smallest beautiful number.
 * 
 * Approach:
 * 1. Count frequency of each digit (0-9) in the input string.
 * 2. For each position from left to right (0 to 9):
 *    - Find the smallest digit that is >= (10 - position - 1) and still available.
 *    - Use that digit and decrement its count.
 * 3. Output the constructed number.
 * 
 * Time Complexity: O(10 * 10) = O(1) since we have fixed input size (10 digits)
 * Space Complexity: O(1) since we use fixed size arrays of 10 elements
 * 
 * Techniques: Greedy algorithm, character counting
 */

import java.util.*;
import java.lang.*;
import java.math.BigInteger;
import java.io.*;
public class Main implements Runnable {
    public static void main(String[] args) {
        new Thread(null, new Main(), "whatever", 1 << 26).start();
    }
    private FastScanner sc;
    private PrintWriter pw;
    public void run() {
        try {
            boolean isSumitting = true;
            if (isSumitting) {
                pw = new PrintWriter(System.out);
                sc = new FastScanner(new BufferedReader(new InputStreamReader(System.in)));
            } else {
                pw = new PrintWriter(new BufferedWriter(new FileWriter("output.txt")));
                sc = new FastScanner(new BufferedReader(new FileReader("input.txt")));
            }
        } catch (Exception e) {
            throw new RuntimeException();
        }
        int t = sc.nextInt();
        while (t-- > 0) {
            solve();
        }
        pw.close();
    }
    public long mod = 1_000_000_007;
    public void solve() {
        String s = sc.nextLine();
        int n = s.length();
        int[] c = new int[10];
        for (int i = 0; i < n; i++) {
            c[s.charAt(i) - '0']++; // Count frequency of each digit
        }
        for (int i = 0; i < 10; i++) {
            int temp = 10 - i - 1; // Required minimum digit for position i
            for (int j = temp; j < 10; j++) {
                if (c[j] > 0) {
                    c[j]--; // Use one occurrence of digit j
                    pw.print(j);
                    break;
                }
            }
        }
        pw.println();
    }
    class FastScanner {
        private BufferedReader reader = null;
        private StringTokenizer tokenizer = null;
        public FastScanner(BufferedReader bf) {
            reader = bf;
            tokenizer = null;
        }
        public String next() {
            if (tokenizer == null || !tokenizer.hasMoreTokens()) {
                try {
                    tokenizer = new StringTokenizer(reader.readLine());
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
            return tokenizer.nextToken();
        }
        public String nextLine() {
            if (tokenizer == null || !tokenizer.hasMoreTokens()) {
                try {
                    return reader.readLine();
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
            return tokenizer.nextToken("\n");
        }
        public long nextLong() {
            return Long.parseLong(next());
        }
        public int nextInt() {
            return Integer.parseInt(next());
        }
        public double nextDouble() {
            return Double.parseDouble(next());
        }
        public float nextFloat() {
            return Float.parseFloat(next());
        }
        public int[] nextIntArray(int n) {
            int[] a = new int[n];
            for (int i = 0; i < n; i++) {
                a[i] = nextInt();
            }
            return a;
        }
        public String[] nextStringArray(int n) {
            String[] a = new String[n];
            for (int i = 0; i < n; i++) {
                a[i] = next();
            }
            return a;
        }
        public long[] nextLongArray(int n) {
            long[] a = new long[n];
            for (int i = 0; i < n; i++) {
                a[i] = nextLong();
            }
            return a;
        }
    }
    private static class Sorter {
        public static <T extends Comparable<? super T>> void sort(T[] arr) {
            Arrays.sort(arr);
        }
        public static <T> void sort(T[] arr, Comparator<T> c) {
            Arrays.sort(arr, c);
        }
        public static <T> void sort(T[][] arr, Comparator<T[]> c) {
            Arrays.sort(arr, c);
        }
        public static <T extends Comparable<? super T>> void sort(ArrayList<T> arr) {
            Collections.sort(arr);
        }
        public static <T> void sort(ArrayList<T> arr, Comparator<T> c) {
            Collections.sort(arr, c);
        }
        public static void normalSort(int[] arr) {
            Arrays.sort(arr);
        }
        public static void normalSort(long[] arr) {
            Arrays.sort(arr);
        }
        public static void sort(int[] arr) {
            timSort(arr);
        }
        public static void sort(int[] arr, Comparator<Integer> c) {
            timSort(arr, c);
        }
        public static void sort(int[][] arr, Comparator<Integer[]> c) {
            timSort(arr, c);
        }
        public static void sort(long[] arr) {
            timSort(arr);
        }
        public static void sort(long[] arr, Comparator<Long> c) {
            timSort(arr, c);
        }
        public static void sort(long[][] arr, Comparator<Long[]> c) {
            timSort(arr, c);
        }
        private static void timSort(int[] arr) {
            Integer[] temp = new Integer[arr.length];
            for (int i = 0; i < arr.length; i++)
                temp[i] = arr[i];
            Arrays.sort(temp);
            for (int i = 0; i < arr.length; i++)
                arr[i] = temp[i];
        }
        private static void timSort(int[] arr, Comparator<Integer> c) {
            Integer[] temp = new Integer[arr.length];
            for (int i = 0; i < arr.length; i++)
                temp[i] = arr[i];
            Arrays.sort(temp, c);
            for (int i = 0; i < arr.length; i++)
                arr[i] = temp[i];
        }
        private static void timSort(int[][] arr, Comparator<Integer[]> c) {
            Integer[][] temp = new Integer[arr.length][arr[0].length];
            for (int i = 0; i < arr.length; i++)
                for (int j = 0; j < arr[0].length; j++)
                    temp[i][j] = arr[i][j];
            Arrays.sort(temp, c);
            for (int i = 0; i < arr.length; i++)
                for (int j = 0; j < arr[0].length; j++)
                    temp[i][j] = arr[i][j];
        }
        private static void timSort(long[] arr) {
            Long[] temp = new Long[arr.length];
            for (int i = 0; i < arr.length; i++)
                temp[i] = arr[i];
            Arrays.sort(temp);
            for (int i = 0; i < arr.length; i++)
                arr[i] = temp[i];
        }
        private static void timSort(long[] arr, Comparator<Long> c) {
            Long[] temp = new Long[arr.length];
            for (int i = 0; i < arr.length; i++)
                temp[i] = arr[i];
            Arrays.sort(temp, c);
            for (int i = 0; i < arr.length; i++)
                arr[i] = temp[i];
        }
        private static void timSort(long[][] arr, Comparator<Long[]> c) {
            Long[][] temp = new Long[arr.length][arr[0].length];
            for (int i = 0; i < arr.length; i++)
                for (int j = 0; j < arr[0].length; j++)
                    temp[i][j] = arr[i][j];
            Arrays.sort(temp, c);
            for (int i = 0; i < arr.length; i++)
                for (int j = 0; j < arr[0].length; j++)
                    temp[i][j] = arr[i][j];
        }
    }
    public long fastPow(long x, long y, long mod) {
        if (y == 0)
            return 1;
        if (y == 1)
            return x % mod;
        long temp = fastPow(x, y / 2, mod);
        long ans = (temp * temp) % mod;
        return (y % 2 == 1) ? (ans * (x % mod)) % mod : ans;
    }
    public long fastPow(long x, long y) {
        if (y == 0)
            return 1;
        if (y == 1)
            return x;
        long temp = fastPow(x, y / 2);
        long ans = (temp * temp);
        return (y % 2 == 1) ? (ans * x) : ans;
    }
}


// https://github.com/VaHiX/CodeForces/