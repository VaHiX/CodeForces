// Problem: CF 2103 B - Binary Typewriter
// https://codeforces.com/contest/2103/problem/B

/*
 * B. Binary Typewriter
 *
 * Problem Description:
 * Given a binary string s of length n, you have a typewriter with buttons '0' and '1'.
 * Initially, your finger is on button '0'. You can:
 * 1. Press the button (costs 1)
 * 2. Move finger to the other button (costs 1)
 *
 * You are allowed to reverse at most one substring of s before typing.
 * Objective: Find minimum cost to type the final string using optimal reversal.
 *
 * Approach:
 * - Preprocess and compute minimal operations needed based on transitions in string
 * - Use dynamic programming or prefix/suffix analysis to evaluate impact of reversing substrings
 * - Consider all valid cases where a reversal might improve cost
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for auxiliary arrays
 */

import kotlin.math.min
import kotlin.math.max

fun solve() {
    val n = readln().toLong()
    val s = readln()
    var dif = 0L
    // Count number of transitions in the string
    for (i in 1 until n.toInt()) {
        if (s[i] != s[i - 1]) dif++
    }
    // Compute A: base cost assuming no reversals
    val A = (if (s[0] == '1') 1L else 0L) + dif
    // minl and maxr store minimum and maximum indices for each pair of consecutive characters
    val minl = LongArray(4) { n + 1 }
    val maxr = LongArray(4) { 0 }
    for (i in 1 until n.toInt()) {
        val x = (s[i - 1] - '0').toInt()
        val y = (s[i] - '0').toInt()
        val idx = x * 2 + y // Maps pairs (0,0), (0,1), (1,0), (1,1) to indices
        minl[idx] = min(minl[idx], (i + 1).toLong())
        maxr[idx] = i.toLong()
    }
    val y0 = (s[0] - '0').toInt() // First character value
    val un = (s[n.toInt() - 1] - '0').toInt() // Last character value
    val d = { a: Int, b: Int -> if (a != b) 1L else 0L } // Cost of switching between values
    var best = 0L // Best gain from reversal
    
    // Evaluate all combinations of transitions to find best improvement
    for (x in 0..1) {
        for (y in 0..1) {
            val idx1 = x * 2 + y
            val l = minl[idx1]
            if (l > n) continue
            for (u in 0..1) {
                for (v in 0..1) {
                    val idx2 = u * 2 + v
                    val r = maxr[idx2]
                    if (r < 1 || l > r) continue
                    // Calculate gain from transition x->y and u->v
                    val g = d(x, y) - d(x, u) + d(u, v) - d(y, v)
                    if (g > best) best = g
                }
            }
        }
    }

    // Additional evaluation for edge cases
    for (u in 0..1) {
        for (v in 0..1) {
            val idx = u * 2 + v
            val r = maxr[idx]
            if (r < 1) continue
            val g = d(u, v) - d(y0, v) + (if (y0 == 1) 1L else 0L) - (if (u == 1) 1L else 0L)
            if (g > best) best = g
        }
    }

    // Another case where we change the last character's contribution
    for (x in 0..1) {
        for (y in 0..1) {
            val idx = x * 2 + y
            val l = minl[idx]
            if (l > n) continue
            val g = d(x, y) - d(x, un)
            if (g > best) best = g
        }
    }

    // Evaluate one more edge case: cost difference between first and last character
    run {
        val g = (if (y0 == 1) 1L else 0L) - (if (un == 1) 1L else 0L)
        if (g > best) best = g
    }

    // Final answer: total length plus base cost minus best gain from reversal
    val ans = n + A - best
    println(ans)
}

fun main() {
    val tests = readln().toInt()
    repeat(tests) {
        solve()
    }
}


// https://github.com/VaHiX/CodeForces/