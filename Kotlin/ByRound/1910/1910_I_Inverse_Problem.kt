// Problem: CF 1910 I - Inverse Problem
// https://codeforces.com/contest/1910/problem/I

/**
 * Problem: Count the number of strings s that produce a given string t as the lexicographically smallest result
 *          after repeatedly removing substrings of length k until length < k.
 * 
 * Algorithm:
 * - Dynamic Programming with space optimization (rolling array).
 * - For each position in the prefix of s, calculate how many ways we can fill it so that the final leftover string t is lexicographically minimal.
 * - Time Complexity: O(n * (n/k))
 * - Space Complexity: O(n/k)
 */
val MOD = 998244353

fun main() {
    val (n, k, c) = readLine()!!.split(' ').map { it.toInt() }
    val t = readLine()!!
    val cnt = n / k + 1
    val dp = Array(2) { IntArray(cnt) { 0 } } // Rolling DP array
    val pw = IntArray(cnt) { 1 } // Precompute powers for optimization
    
    dp[0][0] = 1 // Base case: one way to form empty prefix
    
    for (ii in 0 until n % k) {
        val i = ii and 1 // Current row index (0 or 1)
        val ni = i xor 1 // Next row index (flip bit)
        
        var sum = 0
        val cur = c - (t[ii].toInt() - 'a'.toInt()) - 1 // Number of letters greater than current character in t
        
        // Precompute powers of (cur + 1)
        for (j in 1 until cnt) {
            pw[j] = (pw[j - 1] * (cur + 1).toLong() % MOD).toInt()
        }
        
        var pr = 1
        for (j in 0 until cnt) {
            // Update sum with current contribution from dp[i][j]
            sum = ((sum * cur.toLong() + pr * dp[i][j].toLong()) % MOD).toInt()
            
            // Update pr for next iteration (multiply by c)
            pr = (pr * c.toLong() % MOD).toInt()
            
            // Assign value to next row
            dp[ni][j] = (sum * pw[cnt - j - 1].toLong() % MOD).toInt()
        }
    }
    
    var ans = 0
    for (i in 0 until cnt) {
        ans = (ans + dp[n % k % 2][i]) % MOD // Add up all possible ways to get to the final state
    }
    
    // Multiply by c^(n - (n % k)) due to remaining characters in the string that don't affect order of t
    for (i in 0 until n) {
        if (i % k >= n % k) {
            ans = (ans * c.toLong() % MOD).toInt()
        }
    }
    
    println(ans)
}


// https://github.com/VaHiX/codeForces/