// Problem: CF 2011 F - Good Subarray
// https://codeforces.com/contest/2011/problem/F

/*
F. Good Subarray
Algorithm: 
- For each position, we track the last occurrence of values that are within 1 of the current value (x-1, x, x+1).
- This helps us determine if a contiguous subarray can form a "good" sequence.
- Using a stack-based approach from right to left, we compute how many valid subarrays end at each index.
- Time Complexity: O(n) amortized per test case due to stack operations.
- Space Complexity: O(n) for auxiliary arrays and stack.

Techniques:
- Sliding window with stack
- Preprocessing last seen indices for values within range [-1, +1]
*/

import java.io.BufferedOutputStream
import java.io.IOException
import java.io.InputStream
import java.io.PrintWriter
import kotlin.math.*
const val singleTest: Boolean = false
fun solve() {
    val n = ni()
    val arr = nextIntArray(n)
    val lastPos = IntArray(n) // Stores the latest position where a value in range [arr[i]-1, arr[i]+1] was seen.
    val seen = Array(n + 3) { -1 } // seen[x] stores the last index where value x was encountered.
    for (i in 0 until n) {
        val l = maxOf(seen[arr[i]], seen[arr[i] + 1], seen[arr[i] - 1]) // Find last position of any value in [arr[i]-1, arr[i]+1]
        lastPos[i] = l
        seen[arr[i]] = i // Update the last seen index of current value.
    }
    val stack = ArrayDeque<Int>() // Stack to maintain indices for efficient range calculation.
    var res = 0L // Result counter.
    for (i in n - 1 downTo 0) {
        while (stack.isNotEmpty() && lastPos[stack.first()] >= i) stack.removeFirst() // Remove outdated elements
        val r = if (stack.isEmpty()) n else stack.first() // Right boundary of valid range starting at index i
        res += (r - i) // Add number of valid subarrays ending at i
        stack.addFirst(i) // Push current index to stack for future calculations
    }
    print(res)
}
fun main() {
    val numOfTests = if (singleTest) 1 else ni()
    for (test in 1..numOfTests) solve()
    out.flush()
}
class FastScanner(private val stream: InputStream) {
    private val buf = ByteArray(1024)
    private var curChar = 0
    private var numChars = 0
    private fun read(): Int {
    if (numChars == -1) throw Exception("Input miss match!")
    if (curChar >= numChars) {
        curChar = 0
        try {
        numChars = stream.read(buf)
            } catch (e: IOException) {
        throw Exception("Input miss match!")
            }
        if (numChars <= 0) return -1
    }
    return buf[curChar++].toInt()
        }
    fun nextInt(): Int = nextLong().toInt()
    fun nextLong(): Long {
    var c = read()
    while (isWhitespace(c)) c = read()
    var negative = false
    if (c == '-'.code) {
        negative = true
        c = read()
    }
    var res: Long = 0
    do {
        if (c < '0'.code || c > '9'.code) throw Exception("Input miss match!")
        res = res * 10 + (c - '0'.code)
        c = read()
    } while (!isWhitespace(c))
    return if (negative) -res else res
        }
    fun nextDouble(): Double = next().toDouble()
    fun nextChar(): Char {
    var c = read()
    while (isWhitespace(c)) c = read()
    return c.toChar()
        }
    fun next(): String {
    var c = read()
    while (isWhitespace(c)) c = read()
    val res = StringBuilder()
    do {
        res.appendCodePoint(c)
        c = read()
    } while (!isWhitespace(c))
    return res.toString()
        }
    private fun isWhitespace(c: Int): Boolean =
        c == ' '.code || c == '\n'.code || c == '\r'.code || c == '\t'.code || c == -1
}
val scanner = FastScanner(System.`in`)
var out = PrintWriter(BufferedOutputStream(System.`out`))
fun ni() = scanner.nextInt()
fun nl() = scanner.nextLong()
fun nd() = scanner.nextDouble()
fun nc() = scanner.nextChar()
fun ns() = scanner.next()
fun nextIntArray(n: Int) = Array(n) { ni() }
fun nextLongArray(n: Int) = Array(n) { nl() }
fun nextDoubleArray(n: Int) = Array(n) { nd() }
fun nextCharArray(n: Int) = Array(n) { scanner.nextChar() }
fun nextIntGrid(n: Int, m: Int) = Array(n) { nextIntArray(m) }
fun nextLongGrid(n: Int, m: Int) = Array(n) { nextLongArray(m) }
fun nextDoubleGrid(n: Int, m: Int) = Array(n) { nextDoubleArray(m) }
fun nextCharGrid(n: Int, m: Int) = Array(n) { nextCharArray(m) }
fun print(array: Array<Int>) = out.println(array.joinToString(" "))
fun print(array: Array<Long>) = out.println(array.joinToString(" "))
fun print(array: Array<Double>) = out.println(array.joinToString(" "))
fun print(array: IntArray) = out.println(array.joinToString(" "))
fun print(array: LongArray) = out.println(array.joinToString(" "))
fun print(array: DoubleArray) = out.println(array.joinToString(" "))
fun print(list: List<Any>) = out.println(list.joinToString(" "))
fun print(obj: Any) = out.println(obj.toString())


// https://github.com/VaHiX/codeForces/