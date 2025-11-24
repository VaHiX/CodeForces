// Problem: CF 2104 B - Move to the End
// https://codeforces.com/contest/2104/problem/B

/*
B. Move to the End
Algorithms/Techniques: Prefix/Suffix arrays, Greedy approach

Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

For each k, we want to maximize the sum of the last k elements after moving one element to the end of the array.
We precompute suffix sums and prefix maxima to efficiently calculate the best possible sum for each k.
*/

import java.io.PrintWriter
import java.util.*
import kotlin.math.max

fun PrintWriter.solve() {
    val t = readInt()
    for (i in 0 until t) {
        val n = readInt()
        val arr = IntArray(n)
        for (j in 0 until n) {
            arr[j] = readInt()
        }
        // Compute suffix sum array where suffixSum[i] is sum of elements from index i to n-1
        val suffixSum = LongArray(n + 1)
        for (j in n - 1 downTo 0) {
            if (j == n - 1) {
                suffixSum[j] = arr[n - 1].toLong()
                continue
            }
            suffixSum[j] = suffixSum[j + 1] + arr[j]
        }
        // answer[i] will store the maximum sum of last (n-1-i) elements for k = n-1-i+1
        val answer = LongArray(n)
        for (j in 0 until n) {
            answer[j] = suffixSum[n - 1 - j] // This is sum of last (n-1-j) elements without any move
        }
        // Compute prefix maximum array where prefixMax[i] is max element from index 0 to i
        val prefixMax = IntArray(n)
        for (j in 0 until n) {
            if (j == 0) {
                prefixMax[0] = arr[0]
                continue
            }
            prefixMax[j] = max(prefixMax[j - 1], arr[j])
        }
        // For each k, determine the maximum sum we can get by moving one element to end:
        // Either: suffixSum[n-1-j] (sum of last k elements without move) OR
        //         suffixSum[n-1-j] - arr[n-1-j] + prefixMax[n-1-j] (sum after moving the best element)
        for (j in 0 until n) {
            answer[j] = max(suffixSum[n - 1 - j], suffixSum[n - 1 - j] - arr[n - 1 - j] + prefixMax[n - 1 - j])
        }
        println(answer.joinToString(" "))
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