// Problem: CF 2114 C - Need More Arrays
// https://codeforces.com/contest/2114/problem/C

/*
C. Need More Arrays
Algorithm: Greedy approach to maximize number of arrays formed by the given rules.
Time Complexity: O(n) per test case, where n is the size of the array.
Space Complexity: O(1) excluding input storage.

The problem requires us to remove elements from a sorted array to maximize
the number of new arrays created according to specific rules:
- Start with first element in new array
- For each next element:
  * If current_element > previous_element + 1, start a new array
  * Otherwise, add it to the existing array

Approach:
We iterate through the array and greedily decide when to start a new array.
If the current element is more than 1 greater than the last added element,
we must begin a new array. This greedy selection yields optimal number of arrays.

*/

import java.io.PrintWriter
import java.util.*
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

fun sqrt(x: Int): Int {
    var i = 0
    while(i*i <= x) {
        if((i*i) == x) {
            return i
        }
        i++
    }
    return -1
}

fun main(args: Array<String>) {
    var t = readInt()
    while (t > 0) {
        val n = readInt()
        val numbers = readLine()!!.split(" ").map { it.toInt() }
        var i = 1
        var ant = numbers[0] // Track last element added to current array
        var ans = 1 // Count of arrays, initialized with at least one (the first)
        while(i < n) {
            // If this element is more than 1 greater than previous element,
            // we start a new array; otherwise, keep adding to existing array
            if(numbers[i] > (ant + 1)) {
                ant = numbers[i]
                ans++
            }
            i++
        }
        println(ans)
        t--
    }
}


// https://github.com/VaHiX/CodeForces/