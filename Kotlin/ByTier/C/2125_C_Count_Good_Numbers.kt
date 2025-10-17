// Problem: CF 2125 C - Count Good Numbers
// https://codeforces.com/contest/2125/problem/C

/**
 * Problem: C. Count Good Numbers
 *
 * Purpose:
 *   This program counts the number of "good" integers in a given range [l, r].
 *   A good integer is defined as one whose prime factors all consist of at least two digits.
 *   The algorithm uses inclusion-exclusion principle to efficiently count such numbers.
 *
 * Approach:
 *   - Predefined list of small primes (2, 3, 5, 7) which are less than 10.
 *   - For each query [l, r], we calculate how many numbers in that range have all prime factors >= 10.
 *   - This is achieved by applying inclusion-exclusion over all subsets of {2, 3, 5, 7}.
 *   - For each subset (mask), compute LCM and use the formula to count multiples in the interval.
 *   - Add/subtract based on parity of number of primes in the subset.
 *
 * Time Complexity:
 *   O(2^k * t), where k=4 (size of primes list) and t is number of test cases.
 *   So effectively O(t), since 2^4 = 16 is constant.
 *
 * Space Complexity:
 *   O(1), as no extra space is used apart from variables.
 */

import java.util.*

fun main() {
    val reader = Scanner(System.`in`)
    val t = reader.nextInt()
    val primes = listOf(2L, 3L, 5L, 7L) // Primes less than 10
    repeat(t) {
        val l = reader.nextLong()
        val r = reader.nextLong()
        val total = r - l + 1
        var bad = 0L // Count of numbers violating the "good" condition (i.e., with small prime factors)
        for (mask in 1 until (1 shl primes.size)) { // Generate all non-empty subsets of primes
            var lcm = 1L
            var bits = 0
            for (i in primes.indices) {
                if ((mask shr i) and 1 == 1) { // Check if i-th prime is included in current subset
                    bits++
                    lcm *= primes[i]
                }
            }
            val count = r / lcm - (l - 1) / lcm // Count of multiples of LCM in [l, r]
            if (bits % 2 == 1) {
                bad += count // Odd number of primes → add to bad count (inclusion)
            } else {
                bad -= count // Even number of primes → subtract from bad count (exclusion)
            }
        }
        println(total - bad) // Total - Bad gives count of "good" numbers
    }
}


// https://github.com/VaHiX/CodeForces/