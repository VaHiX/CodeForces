// Problem: CF 2148 E - Split
// https://codeforces.com/contest/2148/problem/E

/*
 * Problem: E. Split
 * Purpose: Count the number of "awesome" subarrays where elements can be distributed among k multisets such that each multiset has the same count for every value.
 *
 * Algorithms/Techniques:
 * - Frequency counting with prefix technique
 * - Two-pointer sliding window
 * - Modular arithmetic check for divisibility
 *
 * Time Complexity: O(n) per test case, since we process each element at most twice in the sliding window.
 * Space Complexity: O(n), due to auxiliary arrays like mp (frequency map), s (split counts), and cnt (current count in window).
 */

import java.util.StringTokenizer

fun main() {
    val t = readLine()!!.toInt()
    repeat(t) {
        val st = StringTokenizer(readLine()!!)
        val n = st.nextToken().toInt()
        val k = st.nextToken().toInt()
        val a = readLine()!!.split(" ").map { it.toInt() }
        val mp = IntArray(n + 1) // frequency of each element in the entire array
        val s = IntArray(n + 1) // how many copies of each element must go into each multiset (if valid)
        val cnt = IntArray(n + 1) // current count in sliding window
        for (x in a) mp[x]++ // count frequencies globally
        var bad = false
        for (i in 1..n) if (mp[i] > 0) {
            if (mp[i] % k != 0) { bad = true; break } // if not divisible by k, impossible to split evenly
            s[i] = mp[i] / k // compute how many times each value appears in each multiset
        }
        if (bad) {
            println(0)
            return@repeat
        }
        var ans = 0L
        var l = 0
        for (r in 0 until n) {
            cnt[a[r]]++ // expand window to the right, update count
            while (cnt[a[r]] > s[a[r]]) { // if count exceeds allowed limit, shrink window from left
                cnt[a[l]]--
                l++
            }
            ans += (r - l + 1) // add number of valid subarrays ending at r
        }
        println(ans)
    }
}


// https://github.com/VaHiX/codeForces/