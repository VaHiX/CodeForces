// Problem: CF 2153 D - Not Alone
// https://codeforces.com/contest/2153/problem/D

/*
Problem: D. Not Alone
Purpose: Given a circular array of integers, find minimum operations to make it "nice" (every element has at least one adjacent equal element).
Algorithm: Dynamic Programming + Sliding Window Optimization
Time Complexity: O(n)
Space Complexity: O(n)

Approach:
- For every position in the array, we can either set it to a value that makes it equal to its neighbors or not.
- Since the array is circular, each element is adjacent to two others.
- We use DP to compute optimal cost for segments of 2 or 3 elements, considering rotations.
- Since array is circular and length >= 3, we try starting from indices 0, 1, 2 to cover all possible configurations.
*/
import kotlin.math.abs
import java.io.InputStream
import java.io.Writer
import java.io.OutputStreamWriter
import java.io.BufferedWriter
import java.io.OutputStream
import java.io.PrintWriter
import java.io.Closeable
open class FastReader(private val input: InputStream, bufCap: Int = 8192) {
    companion object { private const val NC = 0.toChar() }
    private val buf = ByteArray(bufCap)
    private var bId = 0
    private var size = 0
    private var c = NC
    private val char: Char
        get() {
            while (bId == size) { size = input.read(buf); if (size == -1) return NC; bId = 0 }
            return buf[bId++].toInt().toChar()
        }
    private fun isWhitespace(c: Char) = c.toInt() !in 33..126
    private fun skip(): Char { var b: Char; while (char.also { b = it } != NC && isWhitespace(b)); return b }
    fun ns() = buildString {
        while (true) { c = char; if (!isWhitespace(c)) break }; append(c);
        while (true) { c = char; if (isWhitespace(c)) break; append(c) }
    }
    fun ns(n: Int): CharArray {
        val buf = CharArray(n); var (b, p) = skip() to 0
        while (p < n && !isWhitespace(b)) { buf[p++] = b;b = char }
        return if (n == p) buf else buf.copyOf(p)
    }
    fun ni(): Int {
        var neg = false; if (c == NC) c = char
        while (c < '0' || c > '9') { if (c == '-') neg = true;c = char }
        var res = 0; while (c in '0'..'9') { res = (res shl 3) + (res shl 1) + (c - '0'); c = char }
        return if (neg) -res else res
    }
    fun nl(): Long {
        var neg = false; if (c == NC) c = char
        while (c < '0' || c > '9') { if (c == '-') neg = true; c = char }
        var res = 0L; while (c in '0'..'9') { res = (res shl 3) + (res shl 1) + (c - '0'); c = char }
        return if (neg) -res else res
    }
    fun na(n: Int) = IntArray(n) { ni() }; fun nal(n: Int) = LongArray(n) { nl() }; fun nad(n: Int) = DoubleArray(n) { nd() }
    fun nm(n: Int, m: Int) = Array(n) { ns(m) }; fun nmi(n: Int, m: Int) = Array(n) { na(m) }
    fun nd() = ns().toDouble(); fun nc() = skip()
}
open class FastWriter : Closeable {
    private val writer: PrintWriter
    constructor(output: OutputStream, bufCap: Int = 8192) {
        this.writer = PrintWriter(BufferedWriter(OutputStreamWriter(output), bufCap))
    }
    constructor(writer: Writer, bufCap: Int = 8192) {
        this.writer = PrintWriter(BufferedWriter(writer, bufCap))
    }
    override fun close() { writer.flush(); try { writer.close() } catch (e: Exception) { e.printStackTrace() } }
    fun print(b: Boolean) = writer.print(b); fun print(c: Char) = writer.print(c); fun print(i: Int) = writer.print(i)
    fun print(l: Long) = writer.print(l); fun print(f: Float) = writer.print(f); fun print(d: Double) = writer.print(d)
    fun print(s: CharArray) = writer.print(s); fun print(s: String?) = writer.print(s);
    fun print(obj: Any?) = writer.print(obj)
    fun println() = writer.println(); fun println(x: Boolean) = writer.println(x); fun println(x: Char) = writer.println(x)
    fun println(x: Int) = writer.println(x); fun println(x: Long) = writer.println(x); fun println(x: Float) = writer.println(x)
    fun println(x: Double) = writer.println(x); fun println(x: CharArray) = writer.println(x); fun println(x: String) = writer.println(x)
    fun println(x: Any) = writer.println(x)
    fun printf(format: String, vararg args: Any?) = writer.format(format, *args)
    fun flush() = writer.flush()
}
typealias int = Int
typealias long = Long
inline fun lao(vararg nums: Long) = longArrayOf(*nums)
inline fun lar(size: Int, init: (Int) -> Long = { 0L }) = LongArray(size) { init(it) }
private val bufCap = 65536
private val rd = FastReader(System.`in`, bufCap)
private val wt = FastWriter(System.out, bufCap)
private fun solve() {
    val cases = rd.ni()
    fun cost(a: long, b: long) = abs(a - b)
    fun cost(a: long, b: long, c: long): long {
        val mid = lao(a, b, c).sorted()[1]
        return abs(mid - a) + abs(mid - b) + abs(mid - c)
    }
    repeat(cases) {
        val n = rd.ni()
        val nums = rd.nal(n)
        fun dp(st: int): long {
            fun v(i: int) = nums[(i + n + st) % n]
            val dp = lar(n + 1) { 0x3f3f3f3f3f3f3f3fL } // Large value for infinity
            dp[0] = 0
            for (index in 2 .. n) {
                dp[index] = dp[index - 2] + cost(v(index - 1), v(index - 2)) // Cost of assigning values to two consecutive positions 
                if (index >= 3) {
                    dp[index] = minOf(dp[index], dp[index - 3] + cost(v(index - 1), v(index - 2), v(index - 3))) // Cost of three consecutive positions
                }
            }
            return dp[n]
        }
        val ans = (0 until 3).minOf { dp(it) } // Try starting from 0-th, 1st, or 2nd index to cover full circle
        wt.println(ans)
    }
}
fun main(args: Array<String>) {
    solve()
    wt.flush()
}


// https://github.com/VaHiX/CodeForces/