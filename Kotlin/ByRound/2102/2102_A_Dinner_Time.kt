// Problem: CF 2102 A - Dinner Time
// https://codeforces.com/contest/2102/problem/A

/*
 * Problem: Dinner Time
 * 
 * Given four integers n, m, p, and q, determine whether there exists an integer array a[1], a[2], ..., a[n]
 * such that:
 * 1. The sum of all elements is equal to m.
 * 2. The sum of every p consecutive elements is equal to q.
 *
 * Algorithm:
 * - Use mathematical analysis to validate the constraints:
 *   - If n == 1, array must contain just one element, so m must equal q.
 *   - If n == p, then all segments are the full array, so m must equal q.
 *   - If n is divisible by p, we have n/p overlapping segments. The total sum of all segments
 *     equals (n/p) * q. The sum of elements in the array appears multiple times depending on overlaps.
 *     We derive a condition based on how many times each element contributes to segment sums.
 *
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 */

import java.io.PrintWriter
import java.util.*
import kotlin.math.abs

fun PrintWriter.solve() {
    val t = readInt()
    for (i in 0 until t) {
        val n = readLong()
        val m = readLong()
        val p = readLong()
        val q = readLong()
        val answer = findAnswer(n, m, p, q)
        println(answer)
    }
}

fun findAnswer(n: Long, m: Long, p: Long, q: Long): String {
    // If n == 1, the only element must equal m and also q for a valid solution
    if (n == 1L && m != q) return "NO"
    if (n == 1L) return "YES"

    // If n == p, all elements form one segment; thus, m must equal q
    if (n == p && m != q) return "NO"
    if (n == p) return "YES"

    // If n is divisible by p and m is not divisible by q, impossible to distribute
    if (n % p == 0L && m % q != 0L) return "NO"

    val k = n / p
    // Check if segments can sum to q when considering total count of segments
    if (n % p == 0L && m / q != k) return "NO"
    
    return "YES"
}

fun main() {
    _writer.solve(); _writer.flush()
}

@JvmField
val INPUT = System.`in`
@JvmField
val OUTPUT = System.out
@JvmField
val _reader = INPUT.bufferedReader()

fun readLine(): String? = _reader.readLine()
fun readLn() = _reader.readLine()!!
@JvmField
var _tokenizer: StringTokenizer = StringTokenizer("")
fun read(): String {
    while (_tokenizer.hasMoreTokens().not()) _tokenizer = StringTokenizer(
        _reader.readLine() ?: return "", " ")
    return _tokenizer.nextToken()
}

fun readInt() = read().toInt()
fun readDouble() = read().toDouble()
fun readLong() = read().toLong()

fun readStrings(n: Int) = Array(n) { read() }
fun readLines(n: Int) = Array(n) { readLn() }
fun readIntArray(n: Int) = IntArray(n) { read().toInt() }
fun readDoubleArray(n: Int) = DoubleArray(n) { read().toDouble() }
fun readLongArray(n: Int) = LongArray(n) { read().toLong() }

@JvmField
val _writer = PrintWriter(OUTPUT, false)

fun bigMod(B: Long, P: Long, M: Long): Long {
    var (r, p, b) = listOf(1, P, B)
    while (p > 0) {
        if (p % 2L == 1L) r = (r * b) % M
        p /= 2
        b = (b * b) % M
    }
    return r
}


// https://github.com/VaHiX/CodeForces/