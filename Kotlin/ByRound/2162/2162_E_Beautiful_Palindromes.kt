// Problem: CF 2162 E - Beautiful Palindromes
// https://codeforces.com/contest/2162/problem/E

/*
 * Problem: Beautiful Palindromes
 * 
 * Algorithm:
 * - Use hashing to check palindromes efficiently.
 * - Precompute forward and backward hashes for the original array.
 * - Identify palindromic subarrays by comparing forward and backward hashes.
 * - Minimize palindromic subarrays by appending values that break existing palindromes.
 * 
 * Time Complexity: O(n) per test case, where n is the length of the array.
 * Space Complexity: O(n) for storing the array and hash values.
 * 
 * Techniques:
 * - Rolling hash with multiple bases for collision resistance.
 * - Efficient palindrome detection using hashes.
 * - Greedy strategy to minimize palindromic subarrays.
 */

import java.util.*
import kotlin.math.*
fun main() {
    val reader = System.`in`.bufferedReader()
    val out = StringBuilder()
    val t = reader.readLine().toInt()
    val M = 1000000007L
    val Q = 1000000009L
    val B = 131L
    val C = 137L
    repeat(t) {
        val (n, k) = reader.readLine().split(" ").map { it.toInt() }
        val a = LongArray(n + 1)
        val tokens = reader.readLine().split(" ").map { it.toLong() }
        for (i in 1..n) a[i] = tokens[i - 1]
        val x = LongArray(n + 1) { 1L } // Powers of base B for hash
        val y = LongArray(n + 1) // Forward hash
        val u = LongArray(n + 1) { 1L } // Powers of base C for hash
        val v = LongArray(n + 1) // Forward hash with base C
        for (i in 1..n) {
            x[i] = x[i - 1] * B % M
            y[i] = (y[i - 1] * B + a[i]) % M
            u[i] = u[i - 1] * C % Q
            v[i] = (v[i - 1] * C + a[i]) % Q
        }
        fun g(l: Int, r: Int): Pair<Long, Long> {
            // Get hash of subarray from l to r
            val A = (y[r] - y[l - 1] * x[r - l + 1] % M + M) % M
            val Bv = (v[r] - v[l - 1] * u[r - l + 1] % Q + Q) % Q
            return Pair(A, Bv)
        }
        val b = LongArray(n + 1)
        // Reverse array for backward hash computation
        for (i in 1..n) b[i] = a[n - i + 1]
        val w = LongArray(n + 1) // Backward hash
        val z = LongArray(n + 1) // Backward hash with base C
        for (i in 1..n) {
            w[i] = (w[i - 1] * B + b[i]) % M
            z[i] = (z[i - 1] * C + b[i]) % Q
        }
        val c = mutableListOf<Int>() // Store palindromic subarray lengths
        for (r in 1..n) {
            // Compare hash from original and reverse
            val h = g(n - r + 1, n)
            val r1 = w[r]
            val r2 = z[r]
            if (h.first == r1 && h.second == r2) c.add(r)
        }
        val s = mutableListOf<Long>() // Result list of chosen integers
        var cur = n
        val f = mutableSetOf<Long>() // Set of elements that are part of palindromic subarrays
        f.add(a[cur])
        for (r in c) {
            if (r <= cur - 1) {
                val p = cur - r
                f.add(a[p])
            }
        }
        var ch = 1L // Current candidate to append
        while (ch <= n && f.contains(ch)) ch++ // Find first available integer not in f
        s.add(ch)
        val newA = a.toMutableList()
        newA.add(ch)
        cur++
        if (k > 1) {
            // Greedily append values to minimize palindromes
            var p1 = a[n]
            var p2 = ch
            for (i in 1 until k) {
                var b1 = p1
                var b2 = p2
                ch = 1
                // Find next suitable value to append
                while ((ch == b1 || ch == b2) && ch <= n) ch++
                s.add(ch)
                p1 = p2
                p2 = ch
            }
        }
        out.append(s.joinToString(" ")).append('\n')
    }
    print(out)
}


// https://github.com/VaHiX/CodeForces/