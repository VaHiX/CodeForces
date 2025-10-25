// Problem: CF 2148 C - Pacer
// https://codeforces.com/contest/2148/problem/C

// *********************************************************************
// * Problem: C. Pacer                                                *
// * Algorithm: Greedy with Interval Optimization                     *
// * Time Complexity: O(n) per test case                              *
// * Space Complexity: O(1)                                           *
// *                                                                    *
// * Description:                                                     *
// * Farmer John must follow a sequence of requirements for the       *
// * FitnessGram Pacer Test, where he can either run or stay at       *
// * each minute. Each run from one side to the other costs one      *
// * minute and earns one point. The goal is to maximize points while *
// * satisfying all timing constraints.                                *
// *                                                                  *
// * Strategy:                                                        *
// * For each interval between two consecutive requirements, we compute*
// * how many runs (i.e., points) can be achieved optimally. We use   *
// * parity checks to decide if there's a need to reduce the number   *
// * of potential runs due to constraints at the boundary.             *
// *********************************************************************

import java.io.BufferedInputStream
import kotlin.math.*
private class FastScanner {
    private val input = BufferedInputStream(System.`in`)
    private val buffer = ByteArray(1 shl 16)
    private var len = 0
    private var ptr = 0
    private fun read(): Int {
        if (ptr >= len) {
            len = input.read(buffer)
            ptr = 0
            if (len <= 0) return -1
        }
        return buffer[ptr++].toInt()
    }
    fun nextInt(): Int {
        var c = read()
        while (c <= 32 && c >= 0) c = read()
        var sign = 1
        if (c == '-'.code) { sign = -1; c = read() }
        var res = 0
        while (c > 32) {
            res = res * 10 + (c - '0'.code)
            c = read()
        }
        return res * sign
    }
}
fun main() {
    val fs = FastScanner()
    val t = fs.nextInt()
    val sb = StringBuilder()
    repeat(t) {
        val n = fs.nextInt()
        val m = fs.nextInt()
        var prevA = 0
        var prevB = 0
        var ans = 0L
        for (i in 0 until n) {
            val ai = fs.nextInt()  // Time of next requirement
            val bi = fs.nextInt()  // Required side at time ai
            val len = ai - prevA   // Duration of interval
            val parity = prevB xor bi  // Parity check between sides
            // If the parity matches, we can run the full interval,
            // otherwise, reduce by one to meet constraint.
            val add = if (len % 2 == parity) len else len - 1
            ans += add.toLong()
            prevA = ai
            prevB = bi
        }
        // Add points for the final stretch from last requirement to time m
        ans += (m - prevA).toLong()
        sb.append(ans).append('\n')
    }
    print(sb.toString())
}


// https://github.com/VaHiX/codeForces/