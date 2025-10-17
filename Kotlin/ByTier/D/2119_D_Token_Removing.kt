// Problem: CF 2119 D - Token Removing
// https://codeforces.com/contest/2119/problem/D

/*
 * Problem: D. Token Removing
 * 
 * Purpose: Calculate the sum of weights over all (n+1)! valid sequences of length n,
 * where each sequence a is valid if 0 <= a[i] <= i, and f(a) represents number of ways
 * to remove tokens based on sequence a.
 *
 * Algorithms/Techniques:
 * - Dynamic Programming with optimized state transitions.
 * - The DP tracks how many ways there are to place tokens such that we end up with k tokens
 *   remaining at the end of operations. We process elements from n down to 1.
 *
 * Time Complexity: O(n^2)
 * Space Complexity: O(n)
 */

fun main() {
    val t = readLine()!!.toInt()
    repeat(t) {
        val (n, m) = readLine()!!.split(" ").map { it.toInt() }
        println(solveCase(n, m))
    }
}

fun solveCase(n: Int, mod: Int): Int {
    val dp = MutableList(n + 1) { 0 }
    dp[0] = 1 % mod
    var maxK = 0
    for (p in n downTo 1) {
        maxK = updateDP(dp, p, n, maxK, mod)
    }
    return sumDP(dp, mod)
}

fun updateDP(dp: MutableList<Int>, p: Int, n: Int, maxK: Int, mod: Int): Int {
    var currentMaxK = maxK
    for (k in maxK downTo 0) {
        if (dp[k] == 0) continue // Skip unused states
        val free = n - p + 1 - k // Number of available positions to place new token
        if (free <= 0) break // Stop when no more space is available
        val add = ((dp[k].toLong() * free) % mod * p) % mod // Multiply by factor and accumulate
        dp[k + 1] = (dp[k + 1] + add.toInt()) % mod // Update next state
    }
    if (dp[maxK + 1] != 0) currentMaxK++ // Increase maxK if new non-zero state appeared
    return currentMaxK
}

fun sumDP(dp: List<Int>, mod: Int): Int {
    var res = 0
    for (valDP in dp) {
        res = (res + valDP) % mod
    }
    return res
}


// https://github.com/VaHiX/CodeForces/