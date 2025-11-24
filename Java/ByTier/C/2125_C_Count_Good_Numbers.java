// Problem: CF 2125 C - Count Good Numbers
// https://codeforces.com/contest/2125/problem/C

/*
 * Problem: Count Good Numbers
 * 
 * Purpose: This solution counts the number of "good" integers in a given range [l, r].
 * A number is considered good if all prime factors of it are at least two digits (i.e., >= 10).
 * 
 * Algorithm: Inclusion-Exclusion Principle
 * - We use inclusion-exclusion to count numbers that are NOT divisible by any of the primes < 10.
 * - The primes less than 10 are: 2, 3, 5, 7.
 * - Using inclusion-exclusion, we calculate how many numbers in [1, n] are divisible by at least one of these.
 * - Then subtract from total to get count of "good" numbers.
 * 
 * Time Complexity: O(1) per query — constant time due to fixed number of primes and operations.
 * Space Complexity: O(1) — only a few variables used.
 */

import java.util.*;

public class Main {
    static long countGood(long n) {
        if (n < 2) return 0; 
        long res = n;
        // Subtract counts of numbers divisible by each prime
        res -= n / 2 + n / 3 + n / 5 + n / 7;
        // Add back counts of numbers divisible by products of two primes
        res += n / 6 + n / 10 + n / 14 + n / 15 + n / 21 + n / 35;
        // Subtract counts of numbers divisible by products of three primes
        res -= n / 30 + n / 42 + n / 70 + n / 105;
        // Add back count of numbers divisible by product of all four primes (2*3*5*7 = 210)
        res += n / 210;
        return res - 1; // Subtract 1 to exclude 1 itself, which is not a good number
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        while (t-- > 0) {
            long l = sc.nextLong();
            long r = sc.nextLong();
            // Use prefix sum technique: countGood(r) - countGood(l - 1)
            System.out.println(countGood(r) - countGood(l - 1));
        }
        sc.close();
    }
}


// https://github.com/VaHiX/CodeForces/