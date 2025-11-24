// Problem: CF 2108 A - Permutation Warm-Up
// https://codeforces.com/contest/2108/problem/A

/*
 * Problem: A. Permutation Warm-Up
 * Task: For a permutation p of length n, compute the number of distinct values of f(p) = sum of |p_i - i| over all permutations.
 *
 * Algorithm/Techniques:
 * - The key insight is that for any permutation, we can analyze how the absolute differences contribute to the sum.
 * - We observe that each element at position i contributes |p[i] - i| to the function value.
 * - This leads to considering all possible values that can be achieved by rearranging elements such that the total f(p) is minimized and maximized.
 * - The number of distinct values follows a mathematical pattern based on n.
 *
 * Time Complexity: O(1) per test case (constant time calculation)
 * Space Complexity: O(1) (only using a few variables)
 */

import java.io.PrintWriter
import java.util.*
import kotlin.math.abs
import kotlin.math.max
import kotlin.math.min

@JvmField val INPUT = System.`in`
@JvmField val OUTPUT = System.out
@JvmField val _reader = INPUT.bufferedReader()

fun readLine(): String? = _reader.readLine()
fun readLn() = _reader.readLine()!!
@JvmField var _tokenizer: StringTokenizer = StringTokenizer("")
fun read(): String {
    while (_tokenizer.hasMoreTokens().not()) _tokenizer = StringTokenizer(_reader.readLine() ?: return "", " ")
    return _tokenizer.nextToken()
}
fun readInt() = read().toInt()
fun readDouble() = read().toDouble()
fun readLong() = read().toLong()

fun readStrings(n: Int) = List(n) { read() }
fun readLines(n: Int) = List(n) { readLn() }
fun readInts(n: Int) = List(n) { read().toInt() }
fun readIntArray(n: Int) = IntArray(n) { read().toInt() }
fun readDoubles(n: Int) = List(n) { read().toDouble() }
fun readDoubleArray(n: Int) = DoubleArray(n) { read().toDouble() }
fun readLongs(n: Int) = List(n) { read().toLong() }
fun readLongArray(n: Int) = LongArray(n) { read().toLong() }

@JvmField val _writer = PrintWriter(OUTPUT, false)
inline fun output(block: PrintWriter.() -> Unit) { _writer.apply(block).flush() }

fun main(args: Array<String>) {
    var t = readInt()
    while (t > 0) {
        val n = readInt()
        var total = 0
        var j = n
        for (i in 1..n) {
            total += abs(j - i) // Compute cumulative difference
            j--
        }
        println(total / 2 + 1) // Result derived from mathematical observation of min/max reachable values
        t--
    }
}


// https://github.com/VaHiX/CodeForces/