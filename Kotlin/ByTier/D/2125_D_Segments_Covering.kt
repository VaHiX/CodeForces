// Problem: CF 2125 D - Segments Covering
// https://codeforces.com/contest/2125/problem/D

/*
 * Problem: D. Segments Covering
 *
 * Purpose:
 *   Calculates the probability that each cell in a linear strip of m cells is covered by exactly one segment,
 *   where each segment has an independent probability of existing.
 *
 * Algorithms/Techniques:
 *   - Probability calculation using inclusion-exclusion principle via dynamic programming
 *   - Modular exponentiation for modular inverse
 *   - Segment tree-like processing with prefix updates
 *
 * Time Complexity: O(n log n + m)
 * Space Complexity: O(n + m)
 */
import java.io.*
import java.util.StringTokenizer

const val MOD = 998244353L

fun modExp(a: Long, e: Long): Long {
    var base = a % MOD
    var exp = e
    var result = 1L
    while (exp > 0) {
        if (exp and 1L == 1L) result = (result * base) % MOD
        base = (base * base) % MOD
        exp = exp shr 1
    }
    return result
}

fun main() {
    val reader = BufferedReader(InputStreamReader(System.`in`))
    val writer = BufferedWriter(OutputStreamWriter(System.out))
    val stNM = StringTokenizer(reader.readLine())
    val n = stNM.nextToken().toInt()
    val m = stNM.nextToken().toInt()
    
    // seg[j] stores segments ending at position j with their weight for DP update
    val seg = Array(m + 1) { mutableListOf<Pair<Int, Long>>() }
    
    // F tracks the overall probability that no cell is covered by more than one segment
    var F = 1L
    
    repeat(n) {
        val st = StringTokenizer(reader.readLine())
        val l = st.nextToken().toInt()
        val r = st.nextToken().toInt()
        val p = st.nextToken().toLong()
        val q = st.nextToken().toLong()
        
        // Compute modular inverse of q
        val invQ = modExp(q, MOD - 2)
        
        // Probability that segment does NOT exist: (q - p) / q
        val oneMinus = ((q - p + MOD) % MOD * invQ) % MOD
        
        // Multiply to F the probability that segment does not exist (for exclusion principle)
        F = (F * oneMinus) % MOD
        
        // Compute d = q - p (numerator of failure probability)
        val d = (q - p + MOD) % MOD
        
        // Modular inverse of d
        val invD = modExp(d, MOD - 2)
        
        // Compute g = p / d, the probability that segment exists given it is not excluded
        val g = (p * invD) % MOD
        
        // Add segment to list ending at r
        seg[r].add(l to g)
    }
    
    // dp[j] stores the sum of probabilities that cell j is covered by exactly one segment
    val dp = LongArray(m + 1)
    dp[0] = 1L
    
    for (j in 1..m) {
        var sum = 0L
        for ((L, w) in seg[j]) {
            // For each segment ending at j with weight w, add contribution from start L-1
            sum = (sum + dp[L - 1] * w) % MOD
        }
        dp[j] = sum
    }
    
    // Final answer is F * dp[m]
    val ans = (F * dp[m]) % MOD
    writer.appendLine(ans.toString())
    writer.flush()
    writer.close()
    reader.close()
}


// https://github.com/VaHiX/CodeForces/