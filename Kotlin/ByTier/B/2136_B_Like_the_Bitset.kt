// Problem: CF 2136 B - Like the Bitset
// https://codeforces.com/contest/2136/problem/B

/**
 * Problem: B. Like the Bitset
 * 
 * Purpose:
 *   Given a binary string s of length n and an integer k, construct a permutation p of length n such that for each position i where s[i] == '1', 
 *   every interval [l,r] with length at least k covering position i must have its maximum element in the interval not equal to p[i].
 *   
 *   This ensures that no element at a '1' position can be the maximum in any valid interval of length >= k.
 *
 * Algorithm:
 *   1. First, we check if the longest consecutive run of '1's is greater than or equal to k. If so, it's impossible to construct a valid permutation (return "NO").
 *   2. Otherwise, we try to assign values to the permutation such that elements with s[i] == 0 are given higher values, and those with s[i] == 1 are given lower values.
 *      - We separate indices of '0's and '1's into two arrays.
 *      - Assign the largest available numbers to all '0' positions first (to prevent them from being max in intervals).
 *      - Then assign remaining numbers to '1' positions in reverse order (to keep low values for '1's, but this will still avoid conflict with interval constraints).
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n)
 */
import java.io.BufferedInputStream
import java.lang.StringBuilder

private class FastScanner {
    private val input = BufferedInputStream(System.`in`)
    private val buffer = ByteArray(1 shl 16)
    private var len = 0
    private var ptr = 0
    private fun readByte(): Int {
        if (ptr >= len) {
            len = input.read(buffer)
            ptr = 0
            if (len <= 0) return -1
        }
        return buffer[ptr++].toInt()
    }
    fun next(): String {
        val sb = StringBuilder()
        var c = readByte()
        while (c <= 32 && c >= 0) c = readByte()
        while (c > 32) {
            sb.append(c.toChar())
            c = readByte()
        }
        return sb.toString()
    }
    fun nextInt(): Int = next().toInt()
}

private fun longestOnesRun(s: String): Int {
    var best = 0
    var run = 0
    for (ch in s) {
        if (ch == '1') {
            run++
            if (run > best) best = run
        } else {
            run = 0
        }
    }
    return best
}

fun main() {
    val fs = FastScanner()
    val t = fs.nextInt()
    val out = StringBuilder()
    repeat(t) {
        val n = fs.nextInt()
        val k = fs.nextInt()
        val s = fs.next()
        
        // Early check: if longest run of '1's is >= k, impossible to build valid permutation
        if (longestOnesRun(s) >= k) {
            out.append("NO\n")
            return@repeat
        }
        out.append("YES\n")
        
        // Arrays to store indices of zeros and ones
        val zeroIdx = IntArray(n)
        val oneIdx = IntArray(n)
        var zc = 0 // count of zeros
        var oc = 0 // count of ones
        
        // Populate index arrays with positions of '0' and '1'
        for (i in 0 until n) {
            if (s[i] == '0') zeroIdx[zc++] = i else oneIdx[oc++] = i
        }
        
        // Initialize permutation array
        val perm = IntArray(n)
        var cur = n // current highest value to assign

        // Assign values to zeros first (largest numbers to avoid conflicts)
        for (j in 0 until zc) {
            perm[zeroIdx[j]] = cur
            cur--
        }

        // Assign remaining values to ones (smaller numbers to minimize conflict risk)
        for (j in 0 until oc) {
            perm[oneIdx[j]] = cur
            cur--
        }

        // Output permutation
        for (i in 0 until n) {
            if (i > 0) out.append(' ')
            out.append(perm[i])
        }
        out.append('\n')
    }
    print(out.toString())
}


// https://github.com/VaHiX/CodeForces/