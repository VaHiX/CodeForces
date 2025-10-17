// Problem: CF 2132 D - From 1 to Infinity
// https://codeforces.com/contest/2132/problem/D

/*
 * Problem: D. From 1 to Infinity
 * Purpose: Given k digits from the concatenated sequence of positive integers (123456789101112...),
 * find the sum of all these digits.
 *
 * Approach:
 * 1. First, determine which number the k-th digit belongs to by counting how many digits are contributed
 *    by numbers with different digit lengths (1-digit, 2-digit, etc.).
 * 2. Once we know the range where the k-th digit lies, extract that specific number and calculate
 *    digit sum up to that point using mathematical tricks to avoid iterating through all digits.
 *
 * Time Complexity: O(log(k)) per test case due to logarithmic processing in digit counting and extraction.
 * Space Complexity: O(1) extra space excluding input/output buffers.
 */

import java.io.*;
import java.util.*;

public class Main {
    static long sumDigits(long n) {
        if (n <= 0) return 0;
        long res = 0, p = 1;
        while (p <= n) {
            long left = n / (p * 10);         // Count how many complete cycles of 0-9 occur before current digit
            long cur = (n / p) % 10;          // Current digit at position p
            long right = n % p;               // Remaining part after current digit

            // Add contribution from all numbers with same number of digits in left part:
            res += left * 45 * p;             // 45 = sum(0..9) used for full cycles
            
            // Compute sum of arithmetic series for current digit's range [0, cur-1]:
            res += cur * (cur - 1) / 2 * p;   // Sum of digits 0 to (cur - 1), repeated p times each
            
            // Add contribution from last partial number:
            res += cur * (right + 1);         // Number of digits from 0 to current digit in this position

            p *= 10;                          // Move to next decimal place
        }
        return res;
    }

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder sb = new StringBuilder();
        int t = Integer.parseInt(br.readLine());

        while (t-- > 0) {
            long k = Long.parseLong(br.readLine());
            long d = 1, cnt, digits;
            long start = 1;

            // Determine the number of digits in the target number
            while (true) {
                cnt = 9 * (long)Math.pow(10, d - 1);    // How many numbers with d digits exist
                digits = cnt * d;                        // Total digit count for all such numbers

                if (k > digits) {                        // Not enough digits to reach k in current block
                    k -= digits;
                    start *= 10;                         // Move to next number set (e.g., from 1-digit to 2-digit)
                    d++;
                } else break;
            }

            // Find the actual number which contains the k-th digit
            long numCount = (k - 1) / d;                 // Index of this number among numbers in `d`-digit block
            long digitIndex = (k - 1) % d;               // Position in that number's digits

            long number = start + numCount;              // Actual number containing the k-th digit
            long full = number - 1;                      // Sum of digits up to (but not including) this number
            long sum = sumDigits(full);

            // Now add the digits from the current partial number
            for (char c : Long.toString(number).toCharArray()) {
                if (digitIndex-- < 0) break;             // Stop once we've added all required digits
                sum += c - '0';
            }

            sb.append(sum).append("\n");
        }
        System.out.print(sb.toString());
    }
}


// https://github.com/VaHiX/codeForces/