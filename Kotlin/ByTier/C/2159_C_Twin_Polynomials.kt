// Problem: CF 2159 C - Twin Polynomials
// https://codeforces.com/contest/2159/problem/C

/**
 * Problem: Twin Polynomials
 * 
 * Purpose:
 *   This solution counts the number of "cool" polynomials of degree n that can be formed,
 *   where a polynomial is "cool" if it equals its twin polynomial.
 *   
 * Approach:
 *   1. Precompute dynamic programming arrays for valid configurations.
 *   2. Process the input polynomial coefficients, identifying constraints and dependencies.
 *   3. Calculate the number of valid assignments for undetermined coefficients using DP.
 * 
 * Algorithms/Techniques:
 *   - Dynamic Programming with memoization
 *   - Constraint propagation on polynomial coefficients
 *   - Modular arithmetic for large numbers
 * 
 * Time Complexity: O(n)
 *   - Preprocessing takes O(n) time.
 *   - Each test case is processed in O(n) time.
 * 
 * Space Complexity: O(n)
 *   - Two arrays of size n+1 are used for DP computations.
 */

const val MOD = 1_000_000_007L
const val LIMIT = 400_001

fun main() {
    // Precompute dp array for general cases
    val dp = LongArray(LIMIT + 1)
    dp[0] = 1L
    for (x in 1..LIMIT) {
        dp[x] += dp[x - 1]
        if (x >= 2) {
            dp[x] += (x - 1).toLong() * dp[x - 2]
        }
        dp[x] %= MOD
    }
    
    // Precompute dpZero array for special cases related to zero coefficients
    val dpZero = LongArray(LIMIT + 1)
    dpZero[0] = 1L
    for (x in 1..LIMIT) {
        dpZero[x] += 2L * dpZero[x - 1]
        if (x >= 2) {
            dpZero[x] += (x - 1).toLong() * dpZero[x - 2]
        }
        dpZero[x] %= MOD
    }
    
    repeat(readln().toInt()) {
        val n = readln().toInt()
        val f = readln().split(" ").map(String::toInt).toIntArray()
        
        // Propagate known constraints between coefficients
        for (k in 1..n) {
            if (f[k] in 1..n && f[f[k]] == -1) {
                f[f[k]] = k
            }
        }
        
        // Check for invalid configurations
        if ((1..n).any { f[it] > n || (f[it] != -1 && f[it] != 0 && f[f[it]] != it) }) {
            println(0)
        } else {
            // Count number of undetermined coefficients
            val amtFree = (1..n).count { f[it] == -1 }
            
            // Initialize result based on free variables
            var answer = dpZero[amtFree]
            
            // Adjust if the last coefficient is undetermined
            if (f[n] == -1) {
                answer -= dpZero[amtFree - 1]
                answer += MOD
            }
            answer %= MOD
            println(answer)
        }
    }
}


// https://github.com/VaHiX/CodeForces/