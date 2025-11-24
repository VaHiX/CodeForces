// Problem: CF 2113 A - Shashliks
// https://codeforces.com/contest/2113/problem/A

@file:OptIn(ExperimentalStdlibApi::class)
import kotlin.math.absoluteValue

// Purpose: This code solves the problem of maximizing the number of shashlik portions cooked
//          given initial grill temperature and cooking requirements for two types of shashlik.
//          It uses a greedy approach to determine optimal cooking order based on which type
//          gives more value in terms of total cooked portions per unit temperature drop.
//
// Algorithms/Techniques:
//   - Greedy algorithm with case analysis
//   - Optimization by trying both cooking orders
//
// Time Complexity: O(1) per test case (constant time operations)
// Space Complexity: O(1) (only using fixed number of variables)

fun readInt() = readln().toInt()
fun readLong() = readln().toLong()
fun readInts() = readln().split(" ").map { it.toInt() }
fun readLongs() = readln().split(" ").map { it.toLong() }

val Int.abs get() = absoluteValue
val Long.abs get() = absoluteValue

fun solve() {
    var (k, a, b, x, y) = readLongs()
    
    if (x < y) {
        // Try cooking as many portions of type 2 as possible first (since it has smaller drop)
        val p = if (k >= a) (k - a) / x + 1 else 0 // number of type 1 portions we could cook
        k -= p * x // reduce temperature accordingly
        println(p + (if (k >= b) (k - b) / y + 1 else 0)) // add remaining type 2 portions
    } else {
        // Try cooking as many portions of type 1 as possible first
        val p = if (k >= b) (k - b) / y + 1 else 0 // number of type 2 portions we could cook
        k -= p * y // reduce temperature accordingly
        println(p + (if (k >= a) (k - a) / x + 1 else 0)) // add remaining type 1 portions
    }
}

fun main() {
    var t: Int = 1
    t = readInt()
    repeat(t) { solve() }
}

// https://github.com/VaHiX/CodeForces/