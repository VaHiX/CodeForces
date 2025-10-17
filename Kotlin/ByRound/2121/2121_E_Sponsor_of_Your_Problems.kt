// Problem: CF 2121 E - Sponsor of Your Problems
// https://codeforces.com/contest/2121/problem/E

/*
E. Sponsor of Your Problems
Algorithms/Techniques: Digit Dynamic Programming (Digit DP)
Time Complexity: O(log(r) * 2 * 2 * 10) = O(log(r))
Space Complexity: O(log(r) * 2 * 2) = O(log(r))

The problem is to find the minimum value of f(l,x)+f(x,r) for all x in [l,r],
where f(a,b) is the number of matching digits at same positions in a and b.
We use Digit DP to enumerate valid numbers x in range [l,r] and compute the minimal cost.
*/
import java.util.*
const val INF = 1_000_000_000
lateinit var dp: Array<Array<IntArray>>
fun solve(pos: Int, l: Int, r: Int, left: String, right: String): Int {
    if (pos == left.length) return 0 // Base case: reached end of digits
    if (dp[pos][l][r] != -1) return dp[pos][l][r] // Memoization lookup
    var kk = INF
    val lDigit = left[pos] - '0' // Current digit in lower bound
    val rDigit = right[pos] - '0' // Current digit in upper bound
    val jk = if (l == 0) lDigit else 0 // Lower limit for current digit
    val lo = if (r == 0) rDigit else 9 // Upper limit for current digit
    for (d in jk..lo) {
        var cost = if (d == lDigit) 1 else 0 // Cost if digit matches lower bound
        cost += if (d == rDigit) 1 else 0 // Cost if digit matches upper bound
        val ff = if (l == 1 || d > lDigit) 1 else 0 // Whether we're still bounded on lower side
        val newR = if (r == 1 || d < rDigit) 1 else 0 // Whether we're still bounded on upper side
        cost += solve(pos + 1, ff, newR, left, right) // Recursive call to next position
        kk = minOf(kk, cost) // Take minimum over all valid digits
    }
    dp[pos][l][r] = kk // Memoize result
    return kk
}
fun main() {
    val scanner = Scanner(System.`in`)
    val t = scanner.nextInt()
    repeat(t) {
        val lVal = scanner.nextLong()
        val rVal = scanner.nextLong()
        val left = lVal.toString()
        val right = rVal.toString()
        val n = left.length
        dp = Array(n + 1) { Array(2) { IntArray(2) { -1 } } } // Initialize memoization table
        println(solve(0, 0, 0, left, right))
    }
}


// https://github.com/VaHiX/CodeForces/