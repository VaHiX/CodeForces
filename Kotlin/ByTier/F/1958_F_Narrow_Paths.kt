// Problem: CF 1958 F - Narrow Paths
// https://codeforces.com/contest/1958/problem/F

/*
F. Narrow Paths

Purpose:
This code computes the number of ways to block exactly k cells in a 2×n matrix (from (1,1) to (2,n)) such that exactly i paths remain for Monocarp to travel.
It uses combinatorics and modular arithmetic to efficiently compute results.

Algorithms/Techniques:
- Precomputed factorials and their modular inverses
- Combinatorial mathematics with modular arithmetic
- Inclusion-exclusion or indirect counting approach

Time Complexity: O(n)
Space Complexity: O(n)

Input:
Two integers n (columns) and k (number of cells to block)

Output:
n+1 integers representing number of ways to block k cells such that i paths exist for Monocarp, for i = 0..n
*/

fun main() {
    val MOD = 1_000_000_007L
    val FAC = LongArray(400_001) // Precomputed factorials
    val INV = LongArray(400_001) // Precomputed modular inverses
    
    // Compute factorials
    FAC[0] = 1
    for (i in 1 until FAC.size) FAC[i] = FAC[i - 1] * i % MOD

    // Compute modular inverses using Fermat's little theorem
    INV[0] = 1
    INV[1] = 1
    for (i in 2 until INV.size) INV[i] = INV[MOD.toInt() % i] * (MOD - MOD / i) % MOD
    for (i in 2 until INV.size) INV[i] = INV[i - 1] * INV[i] % MOD

    // Function to compute combination C(n, k)
    fun comb(n: Int, k: Int) = FAC[n] * INV[k] % MOD * INV[n - k] % MOD

    // Read input values
    val (n, k) = readln().split(' ').map { it.toInt() }

    // Array to store answers for each number of paths
    val ans = LongArray(n + 1)

    // Fill answer array for i from 1 to n-k using formula derived from problem analysis
    for (i in 1..(n - k)) ans[i] =
        ((n - i - 1) * comb(n - i - 2, k - 2) + 2 * comb(n - i - 1, k - 1)) % MOD

    // Compute the case where exactly 0 paths remain (special handling)
    ans[0] = (comb(2 * n - 2, k) - ans.sum()) % MOD
    if (ans[0] < 0L) ans[0] += MOD // Ensure non-negative result

    println(ans.joinToString(" "))
}


// https://github.com/VaHiX/codeForces/