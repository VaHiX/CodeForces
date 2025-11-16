// Problem: CF 2162 B - Beautiful String
// https://codeforces.com/contest/2162/problem/B

import java.util.*
/*
 * Problem: Beautiful String
 * 
 * Algorithm:
 * - Generate all possible subsequences using bitmasking (2^n possibilities)
 * - For each subsequence:
 *   - Check if it's non-decreasing
 *   - Remove the subsequence characters from original string to get x
 *   - Check if x is a palindrome
 * - Output the first valid subsequence found
 * 
 * Time Complexity: O(2^n * n), where n <= 10
 *   - 2^n subsets to check
 *   - For each subset: O(n) to check non-decreasing and O(n) to check palindrome
 * Space Complexity: O(n), for storing the subsequence and temporary strings
 */
fun main() {
    val scanner = Scanner(System.`in`)
    val t = scanner.nextInt()
    repeat(t) {
        val n = scanner.nextInt()
        val s = scanner.next()
        var found = false
        val limit = 1 shl n // Generate all 2^n subsets using bitmasks
        for (mask in 0 until limit) {
            val p = StringBuilder() // Subsequence p
            val x = StringBuilder() // Remaining string x after removing p
            val v = mutableListOf<Int>() // Indices of characters in p
            for (i in 0 until n) {
                if ((mask and (1 shl i)) != 0) {
                    // Include character i in subsequence p
                    p.append(s[i])
                    v.add(i + 1) // Store 1-based index
                } else {
                    // Include character i in remaining string x
                    x.append(s[i])
                }
            }
            var ok = true
            // Check if subsequence p is non-decreasing
            for (i in 1 until p.length) {
                if (p[i] < p[i - 1]) {
                    ok = false
                    break
                }
            }
            if (!ok) continue
            // Check if remaining string x is palindrome
            for (i in 0 until x.length / 2) {
                if (x[i] != x[x.length - 1 - i]) {
                    ok = false
                    break
                }
            }
            if (!ok) continue
            // Valid subsequence found
            println(v.size)
            if (v.isNotEmpty()) {
                println(v.joinToString(" "))
            } else {
                println()
            }
            found = true
            break
        }
        if (!found) println("-1")
    }
}


// https://github.com/VaHiX/CodeForces/