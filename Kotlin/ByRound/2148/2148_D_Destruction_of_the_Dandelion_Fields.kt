// Problem: CF 2148 D - Destruction of the Dandelion Fields
// https://codeforces.com/contest/2148/problem/D

/*
 * Problem: D. Destruction of the Dandelion Fields
 * 
 * Purpose:
 *   Farmer John wants to maximize the number of dandelions he cuts by visiting n fields in an optimal order.
 *   The lawnmower toggles its state when entering a field with an odd number of dandelions,
 *   and cuts all dandelions only if it's ON at that time.
 *
 * Algorithm:
 *   - Separate even and odd numbers.
 *   - If no odd numbers exist, return 0 (lawnmower never turns on).
 *   - If odd numbers are present:
 *     - Sort odds in descending order.
 *     - Take the first (odds.size + 1) / 2 elements to maximize the number of dandelions cut when lawnmower is ON.
 *     - Add all evens to sumE.
 *     - Return sumE + sum of selected odd numbers.
 *
 * Time Complexity: O(n log n) due to sorting
 * Space Complexity: O(n) for storing odds list
 */

import java.io.BufferedInputStream
import kotlin.math.*
private val input = BufferedInputStream(System.`in`)
private fun nextLong(): Long {
    var c = input.read()
    while (c <= 32 && c >= 0) c = input.read()
    var sign = 1
    if (c == '-'.code) { sign = -1; c = input.read() }
    var num = 0L
    while (c > 32) {
        num = num * 10 + (c - '0'.code)
        c = input.read()
    }
    return num * sign
}
fun main() {
    val t = nextLong().toInt()
    val out = StringBuilder()
    repeat(t) {
        val n = nextLong().toInt()
        val odds = ArrayList<Long>()
        var sumE = 0L // Sum of all even numbers (cut regardless of lawnmower state)
        repeat(n) {
            val a = nextLong()
            if (a % 2L == 0L) sumE += a else odds.add(a)
        }
        if (odds.isEmpty()) {
            out.append("0\n")
        } else {
            odds.sortDescending() // Sort in descending order to get maximum dandelions when ON
            val take = (odds.size + 1) / 2 // Take ceiling of half the odds to maximize sum
            var sumOddSelected = 0L // Sum of selected odd numbers that will be cut when lawnmower is ON
            for (i in 0 until take) sumOddSelected += odds[i]
            out.append((sumE + sumOddSelected).toString()).append('\n')
        }
    }
    print(out.toString())
}


// https://github.com/VaHiX/codeForces/