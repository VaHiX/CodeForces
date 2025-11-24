// Problem: CF 2148 G - Farmer John's Last Wish
// https://codeforces.com/contest/2148/problem/G

/*
 * Farmer John's Last Wish - Problem G
 *
 * Purpose:
 *   Given an array of integers, compute for each prefix the maximum value of f(a) over all possible reorderings,
 *   where f(a) is defined as the largest index k < n such that gcd(a_1, ..., a_k) > gcd(a_1, ..., a_{k+1}).
 *
 * Algorithm:
 *   - Precompute smallest prime factors for numbers up to max value in input using sieve.
 *   - For each prefix:
 *     - Maintain counts of prime factor occurrences in current window.
 *     - Track maximum frequency of a non-removed prime divisor (i.e. those not yet in gcd).
 *     - Compute result as maximum of all such counts.
 *
 * Time Complexity: O(n * sqrt(max_val) + n * log(n))
 * Space Complexity: O(max_val + n)
 */

import java.util.*
import kotlin.math.max
typealias ll = Long
var f = LongArray(0)

// Build sieve to compute smallest prime factor for numbers up to m
fun build(m: Int) {
    f = LongArray(m + 1) { 0L }
    for (i in 2..m) {
        if (f[i] == 0L) {
            f[i] = i.toLong()
            if (1L * i * i <= m) {
                var j = i * i
                while (j <= m) {
                    if (f[j] == 0L) f[j] = i.toLong() // Mark smallest prime factor
                    j += i
                }
            }
        }
    }
    for (i in 2..m) if (f[i] == 0L) f[i] = i.toLong() // Handle case where i is prime
}

// Factorize number into list of (prime, exponent) pairs
fun fact(x: Long): List<Pair<Long, Long>> {
    var num = x
    val v = mutableListOf<Pair<Long, Long>>()
    while (num > 1) {
        val p = f[num.toInt()]
        var c = 0L
        while (num % p == 0L) {
            num /= p
            c++
        }
        v.add(Pair(p, c))
    }
    return v
}

// Standard Euclidean GCD implementation
fun gcd(a: Long, b: Long): Long {
    var x = a
    var y = b
    while (y != 0L) {
        val tmp = y
        y = x % y
        x = tmp
    }
    return x
}

fun main() {
    val reader = System.`in`.bufferedReader()
    val t = reader.readLine().toInt()
    val adj = Array(t) { mutableListOf<Long>() }
    var maxx = 1L
    repeat(t) { i ->
        val n = reader.readLine().toInt()
        val nums = reader.readLine().split(" ").map { it.toLong() }
        adj[i].addAll(nums)
        maxx = max(maxx, nums.fold(1L) { acc, v -> max(acc, v) })
    }
    build(maxx.toInt())
    for (x in 0 until t) {
        val a = adj[x]
        val n = a.size
        val mp = mutableMapOf<Long, MutableList<Long>>() // Maps prime to list of counts for each power
        val cnt = mutableMapOf<Long, Long>() // Count of how many times a prime appears
        val pq = PriorityQueue<Pair<Long, Long>>(compareByDescending { it.first }) // Max heap for frequent primes
        val ans = MutableList(n) { 0L }
        var g = 0L // Running GCD so far
        var inf = -1L // Indicates if gcd has changed
        var pf = listOf<Pair<Long, Long>>() // Prime factorization of current GCD
        val st = mutableSetOf<Long>() // Set of primes that appear in current GCD

        for (i in 0 until n) {
            val num = a[i]
            val poww = fact(num) // Factorize the current number
            for ((y, e) in poww) {
                mp.putIfAbsent(y, mutableListOf(0L, 0L)) // Ensure enough space for powers
                if (mp[y]!!.size < e + 2) {
                    while (mp[y]!!.size < e + 2) mp[y]!!.add(0L)
                }
                for (r in 1..e) mp[y]!![r.toInt()]++ // Increment counts for this power of prime
                cnt[y] = (cnt[y] ?: 0) + 1 // Update total occurrences
                pq.add(Pair(cnt[y]!!, y))
            }
            g = if (i == 0) num else gcd(g, num) // Update running GCD, if needed
            if (g != inf) {
                st.clear() // Recompute set of primes in GCD
                pf = fact(g)
                pf.forEach { st.add(it.first) }
                inf = g
            }
            var sumt = 0L // Max power of a prime that is not in current gcd
            for ((pp, e) in pf) {
                val idx = e + 1
                if (mp.containsKey(pp) && mp[pp]!!.size > idx) {
                    sumt = max(sumt, mp[pp]!![idx.toInt()])
                }
            }
            var bn = 0L // Maximum count of a prime not in GCD yet
            val b = mutableListOf<Pair<Long, Long>>()
            while (pq.isNotEmpty()) {
                val tp = pq.peek()
                val v = tp.first
                val pp = tp.second
                if (cnt[pp] != v) {
                    pq.poll()
                    continue
                }
                if (st.contains(pp)) { // Prime already part of gcd, cannot use it in this calculation
                    b.add(tp)
                    pq.poll()
                    continue
                }
                bn = v
                break
            }
            b.forEach { pq.add(it) } // Re-add primes that were not used yet
            ans[i] = max(sumt, bn) // Final answer for current prefix
        }
        println(ans.joinToString(" "))
    }
}


// https://github.com/VaHiX/CodeForces/