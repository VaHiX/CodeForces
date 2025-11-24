// Problem: CF 2152 D - Division Versus Addition
// https://codeforces.com/contest/2152/problem/D

/**
 * Problem: D. Division Versus Addition
 *
 * Purpose:
 *   - Computes the "value" of subarrays, which represents the number of moves Poby makes
 *     in an optimal two-player game where Poby reduces elements (by floor division by 2)
 *     and Rekkles increases them (by adding 1), until all elements become 1.
 *
 * Algorithm:
 *   - For each element in the array, compute how many divisions by 2 are needed to reach 1.
 *     This is done via a helper function `ceilLog(x)` that counts the number of times
 *     we can divide x by 2 (rounded up) before reaching 1.
 *   - Precompute prefix sums of these values (`sums`) and count "opportunities" where
 *     an element can be reduced by one more step due to a transition in `ceilLog`.
 *   - For each query [l, r], calculate total operations minus adjustments for "opportunities".
 *
 * Time Complexity:
 *   - O(n + q) per test case, where n is the size of input array and q number of queries.
 *     Preprocessing: O(n), Queries: O(q)
 *
 * Space Complexity:
 *   - O(n) for auxiliary arrays (`sums`, `opportunities`)
 */

fun main() {
    val out = StringBuilder()
    repeat(readln().toInt()) {
        val (n, q) = readln().split(" ").map(String::toInt)
        val xs = listOf(0) + readln().split(" ").map(String::toInt) // 1-based indexing
        val sums = IntArray(n + 1)     // Prefix sum of ceilLog values for each element
        val opportunities = IntArray(n + 1) // Count transitions where ceilLog increases

        // Precompute the prefix sums and opportunities
        for (j in 1..n) {
            sums[j] = sums[j - 1] + ceilLog(xs[j])   // Accumulate number of operations needed
            opportunities[j] = opportunities[j - 1]
            if (ceilLog(xs[j]) > ceilLog(xs[j] - 1) && xs[j] != 2) {
                // If moving from x to x-1 reduces the log but x is not 2, then this is an opportunity
                opportunities[j]++
            }
        }

        repeat(q) {
            val (l, r) = readln().split(" ").map(String::toInt)
            var answer = sums[r] - sums[l - 1]          // Total operations in subarray [l,r]
            val numOpportunities = opportunities[r] - opportunities[l - 1] // Count of transitions
            answer -= (numOpportunities + 1) / 2        // Adjust for optimal play balance
            out.appendLine(answer)
        }
    }
    print(out)
}

/**
 * Calculates the number of steps needed to reduce x to 1 using floor division by 2.
 * This simulates the number of operations Poby will make on a single element.
 */
fun ceilLog(x: Int): Int {
    var x = x
    var result = 0
    while (x > 1) {
        x = (x + 1) / 2   // Simulate floor division by 2 with rounding up
        result++
    }
    return result
}


// https://github.com/VaHiX/CodeForces/