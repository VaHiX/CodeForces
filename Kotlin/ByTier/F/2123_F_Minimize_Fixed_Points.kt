// Problem: CF 2123 F - Minimize Fixed Points
// https://codeforces.com/contest/2123/problem/F

/*
F. Minimize Fixed Points

Algorithms/Techniques:
- Sieve of Eratosthenes for precomputing smallest prime factor (SPF)
- Grouping elements by their smallest prime factor to form cycles
- Greedy assignment of elements in groups to minimize fixed points

Time Complexity: O(N log N) where N is the maximum value of n (10^5).
Space Complexity: O(N) for storing SPF array and other auxiliary structures.

This code finds a "good" permutation of length n such that:
- For each position i (2 <= i <= n), gcd(p[i], i) > 1
- The number of fixed points is minimized across all good permutations.

Approach:
1. Precompute the smallest prime factor (SPF) for numbers up to N using sieve.
2. For each input n, group numbers from 1 to n based on their SPF.
3. Within each group, assign elements in a cyclic manner to avoid fixed points.
4. This ensures that no element maps to itself and gcd(p[i], i) > 1 for all i >= 2.
*/

import kotlin.math.*
fun IntArray.mp(_x : Int) : Int {
    var ans = 1
    var x = _x
    while (x > 1) {
        ans = max(ans, this[x]) // Track the maximum prime factor encountered
        x /= this[x] // Move to next factor by dividing with SPF
    }
    return ans
}
fun main() {
    val N = 100001
    val lp = IntArray(N) // Array storing smallest prime factor for each number
    val p = mutableListOf<Int>() // List of primes found so far
    for (i in 2..N - 1) {
        if (lp[i] == 0) { // i is a prime
            lp[i] = i
            p.add(i)
        }
        // Mark multiples of current prime with this prime as their smallest factor
        p.takeWhile {it <= lp[i] && it * i < N}.forEach {lp[it * i] = it}
    }
    repeat(readln().toInt()) {
        val n = readln().toInt()
        val a = IntArray(n) {it + 1}.groupBy {lp.mp(it)} // Group numbers by their max prime factor
        val ans = IntArray(n)
        for ((_, v) in a) {
            // For each group, assign elements cyclically to minimize fixed points
            for (i in v.indices) {
                ans[v[i] - 1] = v[(i + 1) % v.size]
            }
        }
        println(ans.joinToString(" "))
    }
}


// https://github.com/VaHiX/CodeForces/