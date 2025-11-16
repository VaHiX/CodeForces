// Problem: CF 2167 D - Yet Another Array Problem
// https://codeforces.com/contest/2167/problem/D

import java.util.Scanner
import kotlin.math.*
fun main() {
    val sc = Scanner(System.`in`)
    val M = 200
    val s = BooleanArray(M + 1) { true }
    val p = mutableListOf<Int>()
    // Sieve of Eratosthenes to find all primes up to 200
    for (i in 2..M) {
        if (s[i]) {
            p.add(i)
            var j = i.toLong() * i
            while (j <= M) {
                s[j.toInt()] = false
                j += i
            }
        }
    }
    val t = sc.nextInt()
    repeat(t) {
        val n = sc.nextInt()
        var g = 0L
        // Compute the GCD of all elements in the array
        repeat(n) { i ->
            val x = sc.nextLong()
            g = if (i == 0) x else gcd(g, x)
        }
        var ok = false
        // Check each prime number less than or equal to 200
        for (q in p) {
            if (g % q != 0L) {
                println(q)
                ok = true
                break
            }
        }
        if (!ok) println(-1)
    }
}
fun gcd(a: Long, b: Long): Long {
    return if (b == 0L) a else gcd(b, a % b)
}

// https://github.com/VaHiX/CodeForces/