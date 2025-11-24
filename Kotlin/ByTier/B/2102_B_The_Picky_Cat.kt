// Problem: CF 2102 B - The Picky Cat
// https://codeforces.com/contest/2102/problem/B

/*
 * Problem: B. The Picky Cat
 *
 * Purpose:
 *   Determine whether it's possible to make the element at index 1 become the median
 *   of the array after performing any number of operations (multiply an element by -1).
 *
 * Algorithm:
 *   - For each test case, we first compute absolute values of all elements.
 *   - Count how many elements are strictly greater than or less than the absolute value of the first element.
 *   - If the count of elements smaller than the first element's absolute value exceeds n/2, then it's impossible
 *     to make the first element the median (since we can only flip signs, so we cannot change the relative ordering
 *     in a way that satisfies this).
 *   - Otherwise, we return "YES".
 *
 * Time Complexity:
 *   O(n) per test case for processing and counting elements.
 *   Overall: O(n) over all test cases (given constraint on sum of n).
 *
 * Space Complexity:
 *   O(n) for storing the array and auxiliary arrays.
 */

import java.io.PrintWriter
import java.util.*
import kotlin.math.abs

fun PrintWriter.solve() {
    val t = readInt()
    for (i in 0 until t) {
        val n = readInt()
        val arr = IntArray(n)
        for (j in 0 until n) {
            arr[j] = readInt()
        }
        var b = IntArray(n)
        for (j in 0 until n) {
            b[j] = abs(arr[j]) // Compute absolute values
        }
        var greaterCount = 0
        var lessCount = 0
        for (j in 1 until n) {
            if (b[j] > b[0]) ++greaterCount // Count elements larger than first element's absolute value
            else ++lessCount // Count elements smaller than first element's absolute value
        }
        val answer = findAnswer(arr, b, greaterCount, lessCount)
        println(answer)
    }
}

fun findAnswer(arr: IntArray, b: IntArray, g: Int, l: Int): String {
    val n = arr.size
    if (l > n / 2) return "NO" // If too many elements are smaller than first element's absolute value, impossible
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