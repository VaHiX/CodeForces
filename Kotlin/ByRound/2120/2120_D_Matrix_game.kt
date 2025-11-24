// Problem: CF 2120 D - Matrix game
// https://codeforces.com/contest/2120/problem/D

/*
 * Problem: D. Matrix game
 * Purpose: Find the lexicographically smallest (n, m) such that any n×m matrix with elements in [1,k] 
 *          has a submatrix of size a×b with all equal elements.
 * 
 * Algorithms/Techniques:
 * - Binary search on the answer for minimal (n,m)
 * - Combinatorial math for counting valid configurations
 * - Fermat's little theorem for modular inverse
 * - Preprocessing factorials and their inverses
 * 
 * Time Complexity: O(max(a, b, k) * log(max(a, b, k))) per test case
 * Space Complexity: O(max(a, b, k)) per test case
 */

const val MOD = 1_000_000_007L

// Modular exponentiation using binary exponentiation
fun Solve(x0: Long, vv: Long): Long {
    var x = x0 % MOD
    var mo = 1L
    var v = vv
    while (v > 0) {
        if (v and 1L == 1L) mo = (mo * x) % MOD
        x = (x * x) % MOD
        v = v shr 1
    }
    return mo
}

fun main() {
    val t = readLine()!!.toInt()
    val cnt = ArrayList<Triple<Long, Long, Long>>(t)
    var mx = 0L
    repeat(t) {
        val (a, b, k) = readLine()!!.split(" ").map { it.toLong() }
        cnt.add(Triple(a, b, k))
        if (a > mx) mx = a
    }
    
    // Precompute factorials and inverse factorials
    val mp = LongArray(mx.toInt() + 1)
    val mp1 = LongArray(mx.toInt() + 1)
    mp[0] = 1L
    for (i in 1..mx.toInt()) {
        mp[i] = (mp[i - 1] * i) % MOD
    }
    mp1[mx.toInt()] = Solve(mp[mx.toInt()], MOD - 2) // Inverse of factorial using Fermat's little theorem
    for (i in mx.toInt() downTo 1) {
        mp1[i - 1] = (mp1[i] * i) % MOD
    }
    
    for ((a, b, k) in cnt) {
        if (a == 1L) {
            // Special case: a = 1 implies any 1×m matrix has a 1×b submatrix
            val n = 1L
            val m = if (b == 1L) 1L else ((k % MOD) * ((b - 1) % MOD) % MOD + 1) % MOD
            println("$n $m")
        } else {
            // General case: Compute minimal dimensions for a×b submatrix to always exist
            var n1 = ((a - 1) % MOD * k % MOD + 1) % MOD
            var vecB = 1L
            for (i in 0 until a) {
                var t = (n1 - i + MOD) % MOD // Compute terms needed for combination formula
                vecB = (vecB * t) % MOD
            }
            val vecC = (vecB * mp1[a.toInt()]) % MOD // Final combination value
            val t = ((b - 1) % MOD * k % MOD) % MOD
            val m = (t * vecC % MOD + 1) % MOD
            println("$n1 $m")
        }
    }
}


// https://github.com/VaHiX/CodeForces/