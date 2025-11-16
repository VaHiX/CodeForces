// Problem: CF 2167 C - Isamatdin and His Magic Wand!
// https://codeforces.com/contest/2167/problem/C

import java.util.Scanner

fun main() {
    val sc = Scanner(System.`in`)
    val t = sc.nextInt()
    repeat(t) {
        val n = sc.nextInt()
        val a = LongArray(n) { sc.nextLong() }
        var ev = 0
        var od = 0
        for (x in a) {
            if (x % 2L == 0L) ev++ else od++  // Count even and odd numbers
        }
        // If both even and odd numbers exist, we can sort to get lexicographically smallest
        // Otherwise, no swaps are possible, so original order is the best we can do
        val result = if (ev > 0 && od > 0) a.sorted() else a.toList()
        println(result.joinToString(" "))
    }
}

// https://github.com/VaHiX/CodeForces/