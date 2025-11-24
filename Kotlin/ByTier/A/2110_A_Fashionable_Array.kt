// Problem: CF 2110 A - Fashionable Array
// https://codeforces.com/contest/2110/problem/A

/*
 * Problem: Fashionable Array
 * 
 * Purpose:
 *   Given an array of integers, determine the minimum number of elements to remove
 *   to make the array "fashionable". An array is fashionable if the sum of its
 *   minimum and maximum elements is even.
 * 
 * Algorithm:
 *   - Sort the array.
 *   - If the difference between max and min is even, the array is already fashionable (0 operations).
 *   - Otherwise, try removing elements from either end to minimize removals such that
 *     the resulting subarray has an even sum of min and max values.
 * 
 * Time Complexity: O(n log n) per test case due to sorting.
 * Space Complexity: O(1) additional space (excluding input/output).
 * 
 * Techniques:
 *   - Two-pointer approach on sorted array.
 *   - Greedy strategy to find minimal removals.
 */

import java.io.PrintWriter
import java.math.BigInteger
import java.util.*
import kotlin.collections.ArrayList
import kotlin.math.abs
import kotlin.math.pow

lateinit var dp: Array<Array<Array<IntArray>>>
const val MOD = 1000000000 + 7

fun solve(caseNumber: Int) {
    val n = readInt()
    val arr = readInts()
    arr.sort() // Sort the array to easily access min and max values
    if ((arr.max() - arr.min()) % 2 == 0) {
        println(0) // Already fashionable if difference is even
    } else {
        var start = 0
        var end = arr.size - 1
        var ans = 0
        // Try removing from left until the subarray becomes fashionable
        while ((arr[end] - arr[start]) % 2 != 0) {
            ans++
            start++
        }
        var ans2 = 0
        start = 0
        end = arr.size - 1
        // Try removing from right until the subarray becomes fashionable
        while ((arr[end] - arr[start]) % 2 != 0) {
            ans2++
            end--
        }
        println(minOf(ans, ans2)) // Minimum of both strategies
    }
}

fun main(args: Array<String>) {
    var t = 1
    t = readInt()
    output {
        repeat(t) {
            solve(it)
        }
    }
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
@JvmField
val _writer = PrintWriter(OUTPUT, false)

inline fun output(block: PrintWriter.() -> Unit) {
    _writer.apply(block).flush()
}

fun read(): String {
    while (_tokenizer.hasMoreTokens().not()) _tokenizer = StringTokenizer(_reader.readLine() ?: return "", " ")
    return _tokenizer.nextToken()
}

private fun readInt() = readLn().toInt()
private fun readLong() = readLn().toLong()
private fun readDouble() = readLn().toDouble()
private fun readStrings() = readLn().trim().split(" ") 
private fun readInts() = readStrings().map { it.toInt() } as ArrayList<Int>
private fun readLongs() = readStrings().map { it.toLong() } as ArrayList<Long>
private fun readDoubles() = readStrings().map { it.toDouble() } as ArrayList<Double> 


// https://github.com/VaHiX/CodeForces/