// Problem: CF 2132 D - From 1 to Infinity
// https://codeforces.com/contest/2132/problem/D

/*
 * D. From 1 to Infinity
 *
 * Problem: Given k digits of the infinite sequence formed by concatenating all positive integers (123456789101112...),
 * compute the sum of those k digits.
 *
 * Algorithm:
 * - Precompute powers of 10 up to 10^15 for digit length buckets.
 * - For each test case:
 *   - Process digit lengths from 1 to 15 in order.
 *   - For each length d, determine how many d-digit numbers are fully included.
 *   - If k allows including all numbers of current digit length, add their contribution.
 *   - Otherwise, compute partial contribution for some number(s) of that digit length.
 * - Function 'su' computes sum of digits in range [1..n] using digit DP technique with optimized bucketing.
 *
 * Time Complexity: O(log(k)) per test case — since we process each digit length from 1 to ~60 for k up to 10^15
 * Space Complexity: O(1) — fixed-size arrays and variables used
 */

import java.io.BufferedReader
import java.io.InputStreamReader

fun su(n: Long): Long {
    if (n <= 0) return 0
    var r = java.math.BigInteger.ZERO  
    var p = 1L
    while (p <= n) {
        val hi = n / (p * 10) // Higher part of the current digit group
        val cur = (n / p) % 10 // Current digit at position
        val lo = n % p // Lower part of the current digit group
        r += java.math.BigInteger.valueOf(hi * p * 45) // Sum from higher digits' combinations
        r += java.math.BigInteger.valueOf(cur * (lo + 1)) // Contribution from current digit
        r += java.math.BigInteger.valueOf((cur * (cur - 1) / 2) * p) // Arithmetic sum for current digit range
        if (p > n / 10) break
        p *= 10
    }
    return r.toLong()
}

fun main() {
    val br = BufferedReader(InputStreamReader(System.`in`))
    val tLine = br.readLine() ?: return
    var T = tLine.toInt()
    val pw = LongArray(20)
    pw[0] = 1L
    for (i in 1 until 20) pw[i] = pw[i - 1] * 10L // Precompute powers of 10 up to 10^19
    val out = StringBuilder()
    repeat(T) {
        var k = br.readLine().trim().toLong()
        var ans = 0L
        for (d in 1 until 20) { // Process digits lengths from 1 to 19
            if (k <= 0) break
            val cnt = 9L * pw[d - 1] // Number of d-digit numbers = 9 * 10^(d-1)
            val tot = cnt * d // Total number of digits contributed by all d-digit numbers
            val st = pw[d - 1] // Start of d-digit range (e.g., 1, 10, 100... etc.)
            if (k >= tot) {
                ans += su(pw[d] - 1) - su(st - 1) // Full contribution from this digit length
                k -= tot
            } else {
                val q = k / d // How many full numbers we can include in remaining k digits
                val r = (k % d).toInt() // Remainder: extra digits beyond full numbers
                if (q > 0) ans += su(st + q - 1) - su(st - 1) // Partial contribution from numbers
                if (r > 0) {
                    val num = st + q // First incomplete number to be considered
                    val s = num.toString()
                    for (i in 0 until r) ans += (s[i] - '0') // Add individual digits of the partial number
                }
                k = 0
            }
        }
        out.append(ans).append("\n")
    }
    print(out.toString())
}


// https://github.com/VaHiX/CodeForces/