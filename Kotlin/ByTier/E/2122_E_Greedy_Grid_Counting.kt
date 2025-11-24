// Problem: CF 2122 E - Greedy Grid Counting
// https://codeforces.com/contest/2122/problem/E

/*
E. Greedy Grid Counting

Algorithms/Techniques: Dynamic Programming with State Compression, Difference Constraints, Modular Arithmetic

Time Complexity: O(n * k^2)
Space Complexity: O(n * k)

A path in a grid is called greedy if it starts at the top-left cell and moves only to the right or downward,
always moving to its neighbor with the greater value (or either if the values are equal).
Given a partially filled 2×n grid of integers between 1 and k, count the number of ways to fill the empty cells
such that in every subgrid, there exists a greedy path that achieves the maximum value out of all down/right paths.
*/

import kotlin.math.abs
import kotlin.math.min
const val MOD = 998244353L

fun main() {
    repeat(readLine()!!.toInt()) {
        val (n, k) = readLine()!!.split(" ").map(String::toInt)
        val kL = k.toLong()
        val initial = Array(2) { readLine()!!.split(" ").map(String::toInt) }
        val dp = Array(n) { LongArray(k + 1) }
        // Initialize the last column: if it's unfilled, set to k; otherwise 1 way (as it's fixed)
        dp[n - 1][0] = if (initial[1][n - 1] == -1) kL else 1L
        
        // Iterate from right to left
        for (j in n - 1 downTo 1) {
            val top = initial[0][j]
            val bottom = initial[1][j - 1]
            
            // Precompute the number of valid transitions based on top and bottom values
            val ways = LongArray((2 * k) + 1) { it ->
                val d = it - k // difference from previous column's value
                if (top == -1) {
                    if (bottom == -1) {
                        k - abs(d) // all differences valid within range
                    } else {
                        if (bottom - d in 1..k) 1 else 0 // check if valid assignment 
                    }
                } else {
                    if (bottom == -1) {
                        if (top + d in 1..k) 1 else 0 // check if valid assignment
                    } else {
                        if (bottom - top == d) 1 else 0 // exact difference required
                    }
                }.toLong()
            }
            
            // Update dp based on previous state and the number of ways to transition
            for (prevD in 0..k) {
                val prev = dp[j][prevD] % MOD
                for (d in -(k - 1)..k - 1) {
                    val here = ways[d + k] * prev // compute total combinations
                    
                    if (d > 0) {
                        // If we move up, ensure we're not exceeding a limit; reset to 0
                        if (d >= prevD) {
                            dp[j - 1][0] += here
                        }
                    } else {
                        // Compute the new difference state
                        val nextD = min(k, prevD - d)
                        dp[j - 1][nextD] += here
                    }
                }
            }
        }
        
        // Final result includes contribution from first column
        var answer = dp[0].map { it % MOD }.sum() * (if (initial[0][0] == -1) kL else 1L)
        answer %= MOD
        println(answer)
    }
}


// https://github.com/VaHiX/CodeForces/