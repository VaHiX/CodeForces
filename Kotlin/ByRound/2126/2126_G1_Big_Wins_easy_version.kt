// Problem: CF 2126 G1 - Big Wins! (easy version)
// https://codeforces.com/contest/2126/problem/G1

/*
 * Problem: G1. Big Wins! (easy version)
 * Algorithm: Binary search + Sliding window with prefix sum optimization
 *
 * Purpose:
 *   Given an array of integers, find the maximum value of (median - minimum) over all possible subarrays.
 *   The approach uses binary search on the answer and a sliding window technique to check if a valid segment exists.
 *
 * Time Complexity:
 *   For each test case, O(n * log(max(a)) * log(max(a))) where n is array size and max(a) <= min(n, 100)
 *   Space Complexity:
 *   O(max(a)) for frequency array; the rest is O(1) extra space.
 */

import kotlin.math.min
import kotlin.math.max

fun readInput(): Pair<Int, List<Int>> {
    val n = readLine()!!.toInt()
    val a = readLine()!!.split(" ").map { it.toInt() }
    return Pair(n, a)
}

/**
 * Checks whether there exists a valid segment where:
 * - All elements >= x
 * - There's some element = x (to allow for median choice)
 * - The prefix sum condition ensures that the subarray can have med - min >= (bestY - x) 
 */
fun canSegmentExist(a: List<Int>, x: Int, mid: Int): Boolean {
    var s = 0
    var minPref = 0
    var lastZeroMp = Int.MAX_VALUE
    var inSeg = false
    var hasZero = false
    for (v in a) {
        if (v < x) {
            inSeg = false
        } else {
            if (!inSeg) {
                inSeg = true
                s = 0
                minPref = 0
                lastZeroMp = Int.MAX_VALUE
                hasZero = false
            }
            if (v == x) {
                hasZero = true
                lastZeroMp = min(lastZeroMp, minPref)
            }
            s += if (v >= mid) 1 else -1
            minPref = min(minPref, s)
            if (hasZero && s - lastZeroMp >= 0) {
                return true
            }
        }
    }
    return false
}

fun solve() {
    val (n, a) = readInput()
    val mx = if (a.isEmpty()) 0 else a.max() ?: 0
    val freq = IntArray(mx + 1)
    for (v in a) freq[v]++
    var ans = 0L
    val C = mx
    for (x in 1..C) {
        if (freq[x] == 0) continue
        var lo = x + 1
        var hi = C
        var bestY = x
        while (lo <= hi) {
            val mid = (lo + hi) shr 1
            if (canSegmentExist(a, x, mid)) {
                bestY = mid
                lo = mid + 1
            } else {
                hi = mid - 1
            }
        }
        ans = max(ans, (bestY - x).toLong())
    }
    println(ans)
}

fun main() {
    val T = readLine()!!.toInt()
    repeat(T) {
        solve()
    }
}


// https://github.com/VaHiX/CodeForces/