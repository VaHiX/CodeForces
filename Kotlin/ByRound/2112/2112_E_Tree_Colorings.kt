// Problem: CF 2112 E - Tree Colorings
// https://codeforces.com/contest/2112/problem/E

/*
 * Problem: E. Tree Colorings
 * Purpose: Find the minimum number of vertices in a tree with exactly m beautiful colorings.
 *
 * Algorithms:
 * - Preprocessing primes using Sieve of Eratosthenes (SPF array)
 * - Recursive generation of divisors of a number
 * - Dynamic Programming to compute minimal vertex count for each number of colorings
 * 
 * Time Complexity: O(maxM * log(log(maxM)) + maxM * sqrt(maxM))
 * Space Complexity: O(maxM)
 */
import java.io.BufferedReader
import java.io.InputStreamReader
import java.io.PrintWriter
import kotlin.math.min

private const val INF = 1_000_000_000

fun main() {
    val br = BufferedReader(InputStreamReader(System.`in`))
    val out = PrintWriter(System.out)
    val t = br.readLine().toInt()
    val query = IntArray(t)
    var maxM = 0
    repeat(t) { i ->
        val v = br.readLine().trim().toInt()
        query[i] = v
        if (v > maxM) maxM = v
    }
    
    // Sieve of Eratosthenes to find smallest prime factor (SPF)
    val spf = IntArray(maxM + 1)
    for (i in 2..maxM) if (spf[i] == 0) {
        spf[i] = i
        if (i.toLong() * i <= maxM) {
            var j = i * i
            while (j <= maxM) {
                if (spf[j] == 0) spf[j] = i
                j += i
            }
        }
    }
    
    val tmp = IntArray(32)          // Temporary array for generating divisors
    
    // Function to process all divisors of n and apply action to each
    fun processDivisors(n: Int, action: (Int) -> Unit) {
        var x = n
        var len = 0
        val primes = IntArray(16); val exp = IntArray(16)
        while (x > 1) {
            val p = spf[x]
            var c = 0
            var y = x
            while (y % p == 0) { y /= p; c++ }
            primes[len] = p; exp[len] = c; len++
            x = y
        }
        fun dfs(idx: Int, cur: Int) {
            if (idx == len) {
                if (cur >= 3) action(cur)
                return
            }
            var prod = 1
            repeat(exp[idx] + 1) {
                dfs(idx + 1, cur * prod)
                prod *= primes[idx]
            }
        }
        dfs(0, 1)
    }
    
    // dp[m] stores the minimum number of vertices needed for m beautiful colorings
    val dp = IntArray(maxM + 1) { INF }
    val minSize = IntArray(maxM + 3) { INF }   // minSize[i]: minimum vertices with i colorings
    
    dp[1] = 0   // Base case: 1 coloring needs 0 additional vertices beyond root
    for (m in 3..maxM) {
        minSize[m] = 1 + dp[m - 2]             // Default way to build up from smaller values
        
        var best = minSize[m]
        processDivisors(m) { d ->
            val q = m / d
            if (dp[q] < INF) best = min(best, dp[q] + minSize[d])
        }
        dp[m] = best   // Update DP with minimum possible value
    }
    
    for (m in query) {
        when {
            m == 1      -> out.println(1)       // Special case for exactly 1 coloring
            dp[m] >= INF -> out.println(-1)     // No valid tree can be formed
            else         -> out.println(1 + dp[m]) // Root plus computed vertices
        }
    }
    out.flush()
}


// https://github.com/VaHiX/CodeForces/