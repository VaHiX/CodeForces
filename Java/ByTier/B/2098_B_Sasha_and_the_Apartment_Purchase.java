// Problem: CF 2098 B - Sasha and the Apartment Purchase
// https://codeforces.com/contest/2098/problem/B

/*
 * Problem: Sasha and the Apartment Purchase
 * 
 * Algorithm/Technique:
 * - Sort the array of bar positions.
 * - For each possible house number, compute the minimum possible sum of distances to bars
 *   by considering at most k bars can be closed.
 * - The optimal strategy is to find a window of bars such that removing at most k bars
 *   from the sorted array minimizes the total distance to the center of that window.
 * - Use sliding window technique to evaluate all valid windows efficiently.
 *
 * Time Complexity: O(n log n) per test case due to sorting, where n is the number of bars
 * Space Complexity: O(n) for storing the array and additional structures
 */

import java.io.*;
import java.math.BigInteger;
import java.util.*;
public class EasyProblem {
    static class FastReader {
        BufferedReader br;
        StringTokenizer st;
        public FastReader() {
            br = new BufferedReader(new InputStreamReader(System.in));
        }
        String next() {
            while (st == null || !st.hasMoreElements()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }
        int nextInt() {
            return Integer.parseInt(next());
        }
        long nextLong() {
            return Long.parseLong(next());
        }
        double nextDouble() {
            return Double.parseDouble(next());
        }
        String nextLine() {
            String str = "";
            try {
                str = br.readLine();
            } catch (IOException e) {
                e.printStackTrace();
            }
            return str;
        }
    }
    static int gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
    }
    static long lcm(long a, long b) {
        return (a * b) / gcd((int) a, (int) b);
    }
    static boolean isPrime(long n) {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }
    static void sieveOfEratosthenes(int N, boolean[] isPrime) {
        Arrays.fill(isPrime, true);
        isPrime[0] = isPrime[1] = false;
        for (int p = 2; p * p <= N; p++) {
            if (isPrime[p]) {
                for (int i = p * p; i <= N; i += p) {
                    isPrime[i] = false;
                }
            }
        }
    }
    static void sort(int[] arr) {
        Arrays.sort(arr);
    }
    public static void main(String[] args) {
        FastReader in = new FastReader();
        PrintWriter out = new PrintWriter(System.out);
        int t = in.nextInt();
        while (t-- > 0) {
            solve(out, in);
        }
        out.flush();
        out.close();
    }
    static void solve(PrintWriter out, FastReader sc) {
     int n=sc.nextInt();
     long k=sc.nextLong();
     long []arr=new long [n];
     for(int i=0;i<n;i++){
        arr[i]=sc.nextLong();
     }
     long ans=0;
     Arrays.sort(arr); // Sort the bar positions
     ArrayList<Long>list=new ArrayList<>();
    for(int i=0;i<n;i++){
       if(Math.abs((n-i-1)-i)<=k+1)list.add(arr[i]); // Add bars in a valid window
    }
    ans= list.getLast()-list.getFirst(); // Calculate range of the valid window
    out.println(ans+1); // Output number of houses in that range
    }
}


// https://github.com/VaHiX/CodeForces/