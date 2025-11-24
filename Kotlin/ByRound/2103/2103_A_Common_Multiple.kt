// Problem: CF 2103 A - Common Multiple
// https://codeforces.com/contest/2103/problem/A

/**
 * Problem: Maximum Size of Beautiful Subsequence
 *
 * A subsequence is beautiful if there exists an array y of distinct elements such that
 * all products x[i] * y[i] are equal.
 *
 * Key Insight:
 * - For a subsequence to be beautiful, the product x[i] * y[i] must be the same for all i.
 * - If we fix this product P, then for each element x[i], we need y[i] = P / x[i].
 * - To ensure distinct elements in y, we must avoid having multiple x[i] values such that
 *   P / x[i] is the same. This means x[i] and x[j] can't be such that their reciprocals lead to same y[i].
 *
 * Algorithm:
 * 1. For each test case:
 *    - Count how many zeros are in the array.
 *    - Count distinct non-zero elements.
 *    - The result is max(zero_count, distinct_non_zero_count), because:
 *      - If we take all zeros, we can assign any distinct y values (since 0 * anything = 0).
 *      - If we take more than zero_count elements, we must avoid duplicate quotients P/x[i].
 *      - So the answer is the maximum of:
 *        a) Number of zeros (we can include all)
 *        b) Number of distinct non-zero values (since they give us unique y values if product is chosen properly)
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for storing array and set operations
 */
import java.io.PrintWriter
import java.util.*
import kotlin.math.max

fun PrintWriter.solve() {
    val t = readInt()
    for (i in 1..t) {
        val n = readInt()
        val arr = LongArray(n)
        for (j in 0 until n) {
            arr[j] = readLong()
        }
        val zeroCount = arr.toList().count { it == 0L } // Count all zeros
        val distinctNonZeroCount = arr.toSet().count { it != 0L } // Count distinct non-zero elements
        println(max(zeroCount, distinctNonZeroCount)) // Return maximum of the two
    }
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