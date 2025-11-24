// Problem: CF 2130 B - Pathless
// https://codeforces.com/contest/2130/problem/B

/*
 * Problem: B. Pathless
 * Purpose: Determine if an array of 0s, 1s, and 2s can be rearranged such that
 *          Alice cannot find a path from index 1 to n with sum exactly s.
 *
 * Algorithm:
 *   - Count occurrences of 0s, 1s, and 2s in the input array.
 *   - Let total sum = sum of all elements in original array.
 *   - If s is less than 0 or s equals 1, then we want to rearrange in a way that
 *     makes it impossible to achieve exactly s using valid moves (i.e., adjacent).
 *     This is possible only under special conditions:
 *       - If s < total_sum or (s == total_sum + 1), then Alice could make a path,
 *         but if s is too small or just 1 more than min possible sum, it's feasible.
 *       - However, since movement is constrained to adjacent indices, and we are 
 *         given at least one 0, 1, and 2, this means we can always form a valid path
 *         unless s < sum of all values in array or s > max possible sum (n*2).
 *       - If total_sum is less than s, return -1.
 *       - If s = total_sum + 1, then it's impossible unless some specific condition.
 *     We are only checking for special case where the remaining difference u = s - sum,
 *     is either negative or equal to one - i.e., we can never reach that exact sum.
 *   - We reconstruct array such that all 0s come first, followed by 2s, then 1s.
 *     This creates a sequence that makes reaching the target sum impossible for Alice.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */

import java.util.*

fun main() {
    val r = Scanner(System.`in`)
    val q = r.nextInt()
    repeat(q) {
        val i = r.nextInt()  // Length of the array
        val j = r.nextInt()  // Target sum s
        val k = ArrayList<Int>(i)
        var l = 0         // Total sum of elements
        var m = 0         // Count of 0s
        var o = 0         // Count of 1s
        var p = 0         // Count of 2s
        for (x in 0 until i) {
            val y = r.nextInt()
            k.add(y)
            l += y
            when (y) {
                0 -> m++
                1 -> o++
                2 -> p++
            }
        }
        val u = j - l  // Difference between desired sum and actual sum
        if (u < 0 || u == 1) {  // If difference is negative or exactly 1, impossible to achieve unless we have special arrangement
            val v = StringBuilder()
            var w = true         // Flag to control appending space before numbers
            for (x in 0 until m) {   // Add all zeros first
                if (!w) v.append(" ")
                v.append("0")
                w = false
            }
            for (x in 0 until p) {   // Then add 2s
                if (!w) v.append(" ")
                v.append("2")
                w = false
            }
            for (x in 0 until o) {   // Finally add 1s
                if (!w) v.append(" ")
                v.append("1")
                w = false
            }
            println(v.toString())
        } else {
            println(-1)
        }
    }
    r.close()
}


// https://github.com/VaHiX/codeForces/