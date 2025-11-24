// Problem: CF 2113 C - Smilo and Minecraft
// https://codeforces.com/contest/2113/problem/C

@file:OptIn(ExperimentalStdlibApi::class)
import kotlin.math.absoluteValue

// Problem: C. Smilo and Minecraft
// Purpose: Given a grid of n x m where each cell is either empty ('.'), stone ('#'), or gold ('g'),
// determine the maximum amount of gold Smilo can collect by placing dynamite in empty cells.
// When dynamite explodes at (x, y), it affects a square of side 2k+1 centered at (x,y).
// Gold inside the square is collected only if it lies on the boundary (not strictly inside).
// Strategy:
// - Use 2D prefix sum to quickly compute gold count in any rectangle.
// - For each empty cell, simulate placing dynamite and calculate total gold that would be collected.
// - This is optimized by computing overlap regions efficiently using inclusion-exclusion principle.
//
// Time Complexity: O(n * m) per test case
// Space Complexity: O(n * m) for prefix sum table and input storage

fun readInt() = readln().toInt()
fun readLong() = readln().toLong()
fun readInts() = readln().split(" ").map { it.toInt() }
fun readLongs() = readln().split(" ").map { it.toLong() }

val Int.abs get() = absoluteValue
val Long.abs get() = absoluteValue

fun yes() = println("Yes")
fun no() = println("No")

fun solve() {
    val (n, m, k) = readInts()
    val tbl = List(n) { readln() }
    val dpTbl = List(n + 1) { IntArray(m + 1) }
    
    // Build 2D prefix sum
    for (i in 0 until n) {
        for (j in 0 until m) {
            dpTbl[i + 1][j + 1] = dpTbl[i + 1][j] + dpTbl[i][j + 1] - dpTbl[i][j] + if (tbl[i][j] == 'g') 1 else 0
        }
    }
    
    val total = dpTbl[n][m] // Total gold in entire grid
    var res = 0
    
    // For each empty cell, compute the maximum gold that can be collected by placing dynamite there
    for (i in 0 until n) {
        for (j in 0 until m) {
            if (tbl[i][j] == '.') {
                // Define boundaries of explosion square around (i, j)
                val left = maxOf(0, j - k + 1)       // Left boundary of explosion
                val right = minOf(m, j + k)          // Right boundary of explosion
                val up = maxOf(0, i - k + 1)         // Top boundary of explosion
                val down = minOf(n, i + k)           // Bottom boundary of explosion
                
                // Use inclusion-exclusion principle to calculate gold inside explosion area
                // But we want gold *on* the boundary, so we subtract strictly inside region from total
                // This uses prefix sum to efficiently get counts for all four subregions
                res = maxOf(
                    res,
                    total - dpTbl[up][left] - dpTbl[down][right] + dpTbl[down][left] + dpTbl[up][right]
                )
            }
        }
    }
    
    println(res)
}

fun main() {
    var t: Int = 1
    t = readInt()
    repeat(t) { solve() }
}

// https://github.com/VaHiX/CodeForces/