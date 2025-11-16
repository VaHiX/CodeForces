// Problem: CF 2125 E - Sets of Complementary Sums
// https://codeforces.com/contest/2125/problem/E

/*
E. Sets of Complementary Sums

Algorithm: Dynamic Programming with Prefix Sums

Approach:
The problem asks for counting the number of distinct sets of complementary sums where:
- Each set contains exactly `n` elements,
- Each element is in range [1, x],
- The set Q = {s - a_i | 1 ≤ i ≤ m} is formed from an array 'a' with sum s.

Key insight:
For any valid set Q of size n and max element x:
1. We can derive constraints on the minimal sum S that can be achieved.
2. A complementary set corresponds to a partitioning, leading to a dynamic programming solution for counting valid combinations.

DP State: 
- dp[j] = number of ways to form subset sums up to j using elements from [0..n-1]
- Two prefix arrays are maintained for efficient computation of sum contributions:
    - S1[i] = sum of dp[0..i]
    - S2[i] = sum of i * dp[i] for i in 0..i

Time Complexity: O(n * K) where K is bounded by approximately x
Space Complexity: O(K) where K is bounded by approximately x

*/

import kotlin.math.*
const val MOD = 998244353L

fun solve() {
    val (nStr, xStr) = readln().split(" ")
    val n = nStr.toLong()
    val x = xStr.toLong()
    
    if (n > x) {
        println(0)
        return
    }
    if (n == 1L) {
        println(x % MOD)
        return
    }
    if (n == 2L) {
        // For n=2, we count pairs of distinct elements (a,b) such that both are in [1,x]
        // Total combinations = x * (x - 1), divided by 2 for unordered pairs
        val combinations = (x % MOD) * ((x - 1) % MOD) % MOD
        val inv2 = (MOD + 1) / 2 // Multiplicative inverse of 2 mod MOD
        println((combinations * inv2) % MOD)
        return
    }

    // Compute K based on constraints derived from the problem's structure.
    val K = x - n + 1 - n * (n - 1) / 2
    if (K < 0) {
        println(0)
        return
    }

    // dp[i] stores number of ways to create a subset of size i with sum j, using elements from [0..n-1]
    val dp = LongArray(K.toInt() + 1)
    dp[0] = 1L

    // Dynamic programming step: fill dp array using inclusion of new values
    for (i in 1 until n) {
        for (j in i..K) {
            dp[j.toInt()] = (dp[j.toInt()] + dp[(j - i).toInt()]) % MOD
        }
    }

    // Prefix sums for optimization:
    val S1 = LongArray(K.toInt() + 1)
    S1[0] = dp[0]
    for (s in 1..K.toInt()) {
        S1[s] = (S1[s - 1] + dp[s]) % MOD
    }

    val S2 = LongArray(K.toInt() + 1)
    S2[0] = 0L
    for (s in 1..K.toInt()) {
        val term = (s.toLong() % MOD) * dp[s] % MOD
        S2[s] = (S2[s - 1] + term) % MOD
    }

    // Final answer calculation using inclusion-exclusion principle or similar
    val KMod = (K + 1) % MOD
    val term1 = KMod * S1[K.toInt()] % MOD
    val term2 = S2[K.toInt()]
    val ans = (term1 - term2 + MOD) % MOD
    println(ans)
}

fun main() {
    val t = readln().toInt()
    repeat(t) {
        solve()
    }
}


// https://github.com/VaHiX/CodeForces/