// Problem: CF 2144 A - Cut the Array
// https://codeforces.com/contest/2144/problem/A

/*
 * Problem: A. Cut the Array
 * Purpose: Given an array of non-negative integers, find two indices l and r such that 
 *          the array can be split into three parts where either all three remainders modulo 3 are equal,
 *          or all three remainders modulo 3 are different.
 * 
 * Algorithms/Techniques:
 * - Prefix Sum: To efficiently compute segment sums
 * - Brute Force: Check all valid pairs (l, r) for the condition
 * 
 * Time Complexity: O(n^2) per test case, where n is the array length.
 * Space Complexity: O(n) for storing prefix sums.
 */

import java.io.BufferedReader
import java.io.InputStreamReader
import java.util.StringTokenizer

fun main() {
    val reader = BufferedReader(InputStreamReader(System.`in`))
    val t = reader.readLine().toInt()
    repeat(t) {
        val n = reader.readLine().toInt()
        val st = StringTokenizer(reader.readLine())
        val arr = IntArray(n) { st.nextToken().toInt() }
        val prefix = LongArray(n + 1)
        for (i in 0 until n) {
            prefix[i + 1] = prefix[i] + arr[i]
        }
        var found = false
        var ansL = 0
        var ansR = 0
        loop@ for (l in 1 until n) { // l starts from 1 because we need at least one element in prefix
            for (r in l + 1 until n) { // r must be greater than l to form valid middle part
                val s1 = ((prefix[l] - prefix[0]) % 3 + 3) % 3 // remainder of prefix sum modulo 3
                val s2 = ((prefix[r] - prefix[l]) % 3 + 3) % 3 // remainder of middle part sum modulo 3
                val s3 = ((prefix[n] - prefix[r]) % 3 + 3) % 3 // remainder of suffix sum modulo 3
                val allEqual = (s1 == s2 && s2 == s3)
                val allDifferent = (s1 != s2 && s2 != s3 && s1 != s3)
                if (allEqual || allDifferent) {
                    ansL = l
                    ansR = r
                    found = true
                    break@loop
                }
            }
        }
        if (found) {
            println("$ansL $ansR")
        } else {
            println("0 0")
        }
    }
}


// https://github.com/VaHiX/codeForces/