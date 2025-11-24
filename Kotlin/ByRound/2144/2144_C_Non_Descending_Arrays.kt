// Problem: CF 2144 C - Non-Descending Arrays
// https://codeforces.com/contest/2144/problem/C

/**
 * C. Non-Descending Arrays
 *
 * Problem Description:
 * Given two arrays a and b of length n, we can choose any subset of indices and swap the elements
 * at those positions (i.e., swap a[i] with b[i]). A subset is considered "good" if after swapping,
 * both arrays are sorted in non-descending order.
 *
 * Task:
 * Count the number of good subsets modulo 998244353.
 *
 * Algorithm:
 * - This is a dynamic programming problem where for each index i, we track two states:
 *   dp[i][0] = number of ways to reach index i with no swap (i.e., a[i] and b[i] remain as they are)
 *   dp[i][1] = number of ways to reach index i with a swap (i.e., a[i] and b[i] swapped)
 *
 * - For each position, we check all valid transitions from the previous state:
 *   - From i-th index, if current a[i] <= next_a and current b[i] <= next_b, then transition is allowed.
 *   - If a swap occurs at i-th step, then elements are swapped accordingly for comparison.
 *
 * Time Complexity: O(n^2) per test case (nested loop over previous state and current choices)
 * Space Complexity: O(n) for DP array
 */
import java.io.BufferedReader
import java.io.InputStreamReader
import java.util.StringTokenizer

const val MOD = 998244353L

fun main() {
    val br = BufferedReader(InputStreamReader(System.`in`))
    val t = br.readLine().trim().toInt()
    val sb = StringBuilder()
    
    repeat(t) {
        val n = br.readLine().trim().toInt()
        val a = LongArray(n)
        val b = LongArray(n)
        
        // Read array 'a'
        run {
            val st = StringTokenizer(br.readLine())
            for (i in 0 until n) a[i] = st.nextToken().toLong()
        }
        
        // Read array 'b'
        run {
            val st = StringTokenizer(br.readLine())
            for (i in 0 until n) b[i] = st.nextToken().toLong()
        }
        
        // DP array: dp[i][0] = ways to reach index i without swapping, dp[i][1] = with swapping
        val dp = Array(n) { LongArray(2) }
        dp[0][0] = 1
        dp[0][1] = 1
        
        // Iteratively build the DP table
        for (i in 0 until n - 1) {
            for (cur in 0..1) { // Current state: 0 = no swap, 1 = swap
                if (dp[i][cur] == 0L) continue
                
                val curA = if (cur == 0) a[i] else b[i]
                val curB = if (cur == 0) b[i] else a[i]
                
                for (next in 0..1) { // Next state: 0 = no swap, 1 = swap
                    val nextA = if (next == 0) a[i + 1] else b[i + 1]
                    val nextB = if (next == 0) b[i + 1] else a[i + 1]
                    
                    // If valid transition (both elements maintain non-descending order)
                    if (curA <= nextA && curB <= nextB) {
                        dp[i + 1][next] = (dp[i + 1][next] + dp[i][cur]) % MOD
                    }
                }
            }
        }
        
        // Sum up both states at the last index for final result
        val ans = (dp[n - 1][0] + dp[n - 1][1]) % MOD
        sb.append(ans).append("\n")
    }
    
    print(sb.toString())
}


// https://github.com/VaHiX/codeForces/