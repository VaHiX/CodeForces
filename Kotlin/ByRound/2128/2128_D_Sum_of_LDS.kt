// Problem: CF 2128 D - Sum of LDS
// https://codeforces.com/contest/2128/problem/D

/*
 * Problem: D. Sum of LDS
 * Algorithm: Dynamic Programming with prefix sums
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) per test case
 * 
 * Given a permutation satisfying max(p_i, p_{i+1}) > p_{i+2}, we compute the sum
 * of lengths of longest decreasing subsequences (LDS) over all subarrays.
 * 
 * The key insight is that for any position i, we can compute the contribution
 * of subarrays ending at i to the total sum using dynamic programming.
 * 
 * We use a DP array 'sum' where sum[i] represents the sum of LDS lengths for all
 * subarrays ending at index i.
*/

fun main() {
    val t = readln().toInt()
    val ans = mutableListOf<Long>()
    repeat(t) {
        val n = readln().toInt()
        val a = readln().split(" ").map { it.toInt() }
        val sum = LongArray(n)
        sum[0] = 1
        sum[1] = 2
        if (a[0] > a[1]) sum[1]++ // If first two elements form a decreasing pair, increment count
        
        for (i in 2..<n) {
            // For each i, depending on whether current element is less than previous,
            // we either add i+1 to the previous sum or use the value from two positions back
            sum[i] = if (a[i] < a[i - 1]) {
                sum[i - 1] + i + 1
            } else {
                sum[i - 2] + i + 1
            }
        }
        
        ans += sum.sum() // Add total contribution of all subarrays for this test case
    }
    println(ans.joinToString("\n"))
}


// https://github.com/VaHiX/CodeForces/