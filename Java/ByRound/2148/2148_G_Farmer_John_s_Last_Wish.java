// Problem: CF 2148 G - Farmer John's Last Wish
// https://codeforces.com/contest/2148/problem/G

/*
G. Farmer John's Last Wish
Purpose: Given an array, compute for each prefix the maximum value of f(a) over all possible reorderings,
         where f(a) is defined as the largest index k such that gcd of first k elements is greater than gcd of first k+1 elements.
         This problem requires tracking divisor counts and maintaining maximums efficiently.

Algorithms/Techniques:
- GCD calculation using Euclidean algorithm
- Divisor counting with prefix updates
- Efficiently updating and querying divisor counts for all divisors of current element

Time Complexity: O(n * sqrt(max_value)) per test case, where max_value <= n.
Space Complexity: O(n) for the divisor count array.

*/
import java.io.*;
import java.util.*;
public class G_Farmer_John_s_Last_Wish {
    static long gcd(long a, long b) {
        while (b != 0) {
            long tmp = a % b;
            a = b;
            b = tmp;
        }
        return a;
    }

    // Increment the count of divisor 'x' and update best if needed
    static long updateDivisorCount(long x, long currentGcd, long[] divisorCount) {
        divisorCount[(int) x]++;
        if (x <= currentGcd) return 0; // Skip if current element's divisor is less than or equal to gcd so far
        return divisorCount[(int) x];
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.parseInt(br.readLine().trim());
        while (t-- > 0) {
            int n = Integer.parseInt(br.readLine().trim());
            long[] arr = new long[n];
            StringTokenizer st = new StringTokenizer(br.readLine());
            for (int i = 0; i < n; i++) {
                arr[i] = Long.parseLong(st.nextToken());
            }
            long[] divisorCount = new long[n + 1]; // Count occurrences of each possible divisor
            long gcdSoFar = 0, best = 0;
            StringBuilder output = new StringBuilder();
            for (int i = 0; i < n; i++) {
                long prevGcd = gcdSoFar; // Save previous GCD before updating it
                gcdSoFar = gcd(gcdSoFar, arr[i]); // Update the running GCD with current element

                // For all divisors of current element, update their counts and best result
                for (long d = 1; d * d <= arr[i]; d++) {
                    if (arr[i] % d == 0) {
                        best = Math.max(best, updateDivisorCount(d, gcdSoFar, divisorCount));
                        if (d != arr[i] / d) {
                            best = Math.max(best, updateDivisorCount(arr[i] / d, gcdSoFar, divisorCount));
                        }
                    }
                }

                // Check for previous GCD values that were reduced due to new element
                for (long d = prevGcd; d > gcdSoFar; d--) {
                    best = Math.max(best, divisorCount[(int) d]);
                }
                output.append(best).append(" ");
            }
            System.out.println(output.toString().trim());
        }
    }
}


// https://github.com/VaHiX/CodeForces/