// Problem: CF 2129 B - Stay or Mirror
// https://codeforces.com/contest/2129/problem/B

/*
B. Stay or Mirror
 time limit per test2 seconds
 memory limit per test256 megabytes

Purpose:
This code solves the problem of minimizing the number of inversions in an array where each element can either be p[i] or 2*n - p[i].
It uses a Binary Indexed Tree (BIT) to efficiently compute prefix sums and inversion counts.

Algorithms/Techniques:
- Binary Indexed Tree (Fenwick Tree) for efficient prefix sum queries and updates
- Greedy decision-making for choosing between p[i] and 2*n - p[i]

Time Complexity: O(n log n) per test case
Space Complexity: O(n)

*/

import java.util.*
class BIT(private var n: Int) {
    private var f = LongArray(n + 1)
    fun init(size: Int) {
        n = size
        f = LongArray(n + 1)
    }
    fun update(i_: Int) {
        var i = i_
        while (i <= n) { // Update all relevant nodes in BIT
            f[i]++
            i += i and -i
        }
    }
    fun query(i_: Int): Long {
        var i = i_
        var sum = 0L
        while (i > 0) { // Query prefix sum up to index i
            sum += f[i]
            i -= i and -i
        }
        return sum
    }
    fun reset() {
        f.fill(0L) // Reset BIT to initial state
    }
}
fun main() {
    val reader = System.`in`.bufferedReader()
    val t = reader.readLine().toInt()
    repeat(t) {
        val n = reader.readLine().toInt()
        val p = listOf(0L) + reader.readLine().split(" ").map { it.toLong() } // 1-indexed
        val invr = LongArray(n + 1)
        val gl = LongArray(n + 1)
        val bit = BIT(n)
        bit.init(n)
        var invp = 0L
        for (i in n downTo 1) {
            invr[i] = bit.query(p[i].toInt() - 1) // Count elements smaller than p[i] already processed
            invp += invr[i]
            bit.update(p[i].toInt()) // Add current element to BIT
        }
        bit.reset()
        for (i in 1..n) {
            gl[i] = (i - 1 - bit.query(p[i].toInt())).toLong() // Count elements larger than p[i] that are ahead
            bit.update(p[i].toInt())
        }
        var sumNeg = 0L
        for (i in 1..n) {
            val D = (n - i) - invr[i] - gl[i] // Determine optimal choice's impact on inversion count
            if (D < 0) sumNeg += D // If negative, we should consider choosing 2*n - p[i] instead of p[i]
        }
        val ans = invp + sumNeg
        println(ans)
    }
}


// https://github.com/VaHiX/CodeForces/