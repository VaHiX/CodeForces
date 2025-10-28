// Problem: CF 2150 B - Grid Counting
// https://codeforces.com/contest/2150/problem/B

/**
 * Problem: B. Grid Counting
 * 
 * Purpose: Count the number of ways to color a grid of size n×n such that:
 * - Each row k has exactly a_k black cells.
 * - For each k, there is exactly one black cell with max(x_i, y_i) = k.
 * - For each k, there is exactly one black cell with max(x_i, n + 1 - y_i) = k.
 * 
 * Algorithm:
 * - Uses combinatorics and precomputed factorials/modular inverses.
 * - Processes the array from the middle outwards (symmetric constraints).
 * - For each row i, determines how many valid positions can be chosen given constraints.
 * 
 * Time Complexity: O(n) per test case (preprocessing + processing)
 * Space Complexity: O(n) for storing factorials and inverse factorials
 */
import java.io.BufferedReader
import java.io.InputStreamReader
import java.io.PrintWriter
import java.lang.RuntimeException
import java.util.*
import kotlin.system.exitProcess

val inf = BufferedReader(InputStreamReader(System.`in`))
val ouf = PrintWriter(System.out)

fun BufferedReader.readInt() = readLine()!!.toInt()
fun BufferedReader.readInts() = readLine()!!.split(' ').map(String::toInt)
fun BufferedReader.readLong() = readLine()!!.toLong()
fun BufferedReader.readLongs() = readLine()!!.split(' ').map(String::toLong)
fun BufferedReader.readString() = readLine()!!

const val INF = Long.MAX_VALUE / 3
const val MOD = 998_244_353L

val f = LongArray(200_001)   // Factorials
val finv = LongArray(200_001) // Modular inverses of factorials

fun init() {
    f[0] = 1L
    finv[0] = 1L
    for (i in 1..200_000) {
        f[i] = f[i - 1] * i % MOD
        finv[i] = f[i].toBigInteger().modInverse(MOD.toBigInteger()).toLong()
    }
}

fun c(n: Int, k: Int) = f[n] * finv[k] % MOD * finv[n - k] % MOD  // Compute combination C(n,k)

fun solve() {
    val n = inf.readInt()
    val a = inf.readInts().toIntArray()
    
    // Check if total number of black cells equals n and suffix from middle to end is all zeros
    if (a.sum() != n || a.drop((n + 1) / 2).any { it != 0 }) {
        ouf.println(0)
        return
    }
    
    var ans = 1L
    var sp = if (n % 2 == 0) 2 else 1   // Start position for choosing next cells
    
    // Iterate from middle row down to first row to compute combinations
    for (i in (n - 1) / 2 downTo 0) {
        if (a[i] > sp) {    // Not enough room for a[i] black cells
            ans = 0L
            break
        }
        ans = (ans * c(sp, a[i])) % MOD   // Multiply by number of ways to choose positions
        sp += 2 - a[i]                    // Update available slots based on how many were used
    }
    
    ouf.println(ans)
}

fun main() {
    try {
        init()
        for (t in 1..inf.readLine()!!.toInt())
            solve()
    } catch (e: Exception) {
        e.printStackTrace()
        exitProcess(1)
    }
    ouf.close()
}


// https://github.com/VaHiX/CodeForces/