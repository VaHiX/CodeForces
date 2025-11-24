// Problem: CF 2153 C - Symmetrical Polygons
// https://codeforces.com/contest/2153/problem/C

/**
 * Problem: C. Symmetrical Polygons
 * 
 * Purpose: Find the maximum possible perimeter of a non-degenerate, symmetrical and strictly convex polygon
 * that can be formed from a subset of given sticks.
 * 
 * Algorithm:
 * 1. Sort the stick lengths.
 * 2. Group sticks by their lengths and keep track of odd-count groups.
 * 3. For each odd-length group, check if we can form a valid symmetrical polygon by combining it with
 *    another group. The key is to ensure that the total number of sticks is at least 3, and the polygon
 *    satisfies the conditions of being strictly convex and non-degenerate.
 * 
 * Time Complexity: O(n log n) due to sorting and linear scanning through groupings
 * Space Complexity: O(n) for storing the sorted array and grouping information
 */
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
inline fun findFirst(n: Int, judge: (Int) -> Boolean): Int {
    var l = 0
    var r = n
    while (l < r) {
        val mid = l + (r - l) / 2
        if (judge(mid)) r = mid
        else l = mid + 1
    }
    return l
}
inline fun findFirst(l: Int, r: Int, judge: (Int) -> Boolean) = findFirst(r - l) { judge(it + l) } + l
typealias long = Long
private val bufCap = 65536
private val rd = FastReader(System.`in`, bufCap)
private val wt = FastWriter(System.out, bufCap)
private fun solve() {
    val cases = rd.ni()
    repeat(cases) {
        val n = rd.ni()
        val lens = rd.nal(n).sorted().toLongArray()
        var rest = 0L
        var restCnt = 0
        val odds = buildList {
            add(0L); add(0L) // Two dummy elements to avoid index issues
            var i = 0
            while (i < n) {
                var j = i + 1
                while (j < n && lens[j] == lens[i]) {
                    j++
                }
                val cnt = j - i
                rest += if ((cnt and 1) == 1) {
                    add(lens[i])
                    restCnt += cnt - 1
                    (cnt - 1) * lens[i]
                } else {
                    restCnt += cnt
                    cnt * lens[i]
                }
                i = j
            }
        }.toLongArray()
        if (rest == 0L) {
            wt.println(0L)
            return@repeat
        }
        fun cnt(len: long) = if (len > 0) 1 else 0
        var ans = 0L
        for (i in odds.indices) {
            val last = findFirst(i, odds.size) {
                odds[it] >= rest + odds[i]
            } - 1
            if (last > i) {
                val curCnt = cnt(odds[i]) + cnt(odds[last])
                if (curCnt + restCnt >= 3) {
                    val res = rest + odds[i] + odds[last]
                    ans = maxOf(ans, res)
                }
            }
        }
        wt.println(ans)
    }
}
fun main(args: Array<String>) {
    solve()
    wt.flush()
}


// https://github.com/VaHiX/CodeForces/