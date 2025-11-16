// Problem: CF 2167 G - Mukhammadali and the Smooth Array
// https://codeforces.com/contest/2167/problem/G

import java.util.StringTokenizer

/*
 * Problem: G. Mukhammadali and the Smooth Array
 * 
 * Purpose: 
 * This code finds the minimum cost to make an array non-decreasing by changing values at specific positions.
 * It uses dynamic programming to determine the maximum total cost of a subsequence where the array remains non-decreasing.
 * The minimum cost to make it non-decreasing equals the total cost minus the maximum cost of a valid increasing subsequence.
 * 
 * Algorithm:
 * - Use dynamic programming where dp[i] represents the maximum cost to maintain a non-decreasing sequence ending at index i.
 * - For each element, check all previous elements to see if we can extend the subsequence.
 * - Finally, subtract the maximum dp value from the total cost to get the minimum change cost.
 * 
 * Time Complexity: O(n^2) per test case
 * Space Complexity: O(n) per test case
 */
fun main() {
    val t = readLine()!!.toInt()
    repeat(t) {
        val n = readLine()!!.toInt()
        val a = LongArray(n)
        val st1 = StringTokenizer(readLine()!!)
        for (i in 0 until n) {
            a[i] = st1.nextToken().toLong()
        }
        val c = LongArray(n)
        val st2 = StringTokenizer(readLine()!!)
        var total = 0L
        for (i in 0 until n) {
            c[i] = st2.nextToken().toLong()
            total += c[i]
        }
        val dp = LongArray(n)
        var maxDp = 0L
        for (i in 0 until n) {
            dp[i] = c[i] // Initialize dp[i] with the cost of changing element at i
            for (j in 0 until i) {
                if (a[j] <= a[i]) {
                    // If we can extend the non-decreasing subsequence
                    dp[i] = maxOf(dp[i], dp[j] + c[i])
                }
            }
            maxDp = maxOf(maxDp, dp[i]) // Keep track of maximum cost so far
        }
        val ans = total - maxDp // Minimum cost = total cost - maximum valid subsequence cost
        println(ans)
    }
}


// https://github.com/VaHiX/CodeForces/