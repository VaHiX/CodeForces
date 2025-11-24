// Problem: CF 2104 D - Array and GCD
// https://codeforces.com/contest/2104/problem/D

/*
 * Problem: D. Array and GCD
 * 
 * Purpose: Given an array of integers, determine the minimum number of elements to remove 
 *          so that the remaining array can be transformed into an "ideal" array using 
 *          specific operations. An ideal array has all elements >= 2, and GCD of every 
 *          pair of distinct elements equals 1.
 *
 * Algorithms:
 * - Sieve of Eratosthenes to precompute primes up to a limit
 * - Prefix sums for efficient range sum queries
 * - Binary search on the answer to find minimum elements to keep
 * 
 * Time Complexity: O(max_n * log(log(max_n)) + sum(n) * log(n))
 * Space Complexity: O(max_n)
 */

import kotlin.math.*

fun main() {
    val t = readLine()!!.toInt()
    val n = IntArray(t)
    val vecA = Array(t) { mutableListOf<Long>() }
    var maxn = 0
    for (i in 0 until t) {
        n[i] = readLine()!!.toInt()
        maxn = max(maxn, n[i])
        vecA[i] = readLine()!!.split(" ").map { it.toLong() }.toMutableList()
    }
    var m: Int
    if (maxn < 6) {
        m = 15
    } else {
        val nVal = maxn.toDouble()
        val logN = ln(nVal)
        val ans = nVal * (logN + ln(logN))
        m = (ans + 10).toInt() // Estimate of number of primes up to maxn
    }
    val cps = BooleanArray(m + 1) { false } // Composites array for sieve
    val pri = ArrayList<Int>(maxn)
    for (i in 2..m) {
        if (!cps[i]) {
            pri.add(i)
            if (i.toLong() * i <= m) {
                for (j in i * i..m step i) {
                    cps[j] = true
                }
            }
        }
    }
    val p = LongArray(maxn + 1) { 0 } // Prefix sum of primes
    for (i in 1..maxn) {
        p[i] = p[i - 1] + pri[i - 1]
    }
    for (tc in 0 until t) {
        val nVal = n[tc]
        val a = vecA[tc]
        a.sortDescending()
        val pref = LongArray(nVal + 1) { 0 } // Prefix sum of array elements
        for (i in 1..nVal) {
            pref[i] = pref[i - 1] + a[i - 1]
        }
        var lo = 1
        var hi = nVal
        var mid = 1
        while (lo <= hi) {
            val midVal = (lo + hi) / 2
            if (pref[midVal] >= p[midVal]) { // Condition to check if we can keep mid elements
                mid = midVal
                lo = midVal + 1
            } else {
                hi = midVal - 1
            }
        }
        println(nVal - mid) // Number of elements to remove
    }
}


// https://github.com/VaHiX/CodeForces/