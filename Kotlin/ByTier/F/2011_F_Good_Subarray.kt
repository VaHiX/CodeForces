// Contest 2011, Problem F: Good Subarray
// URL: https://codeforces.com/contest/2011/problem/F

import java.io.BufferedOutputStream
import java.io.IOException
import java.io.InputStream
import java.io.PrintWriter
import kotlin.math.*

const val singleTest: Boolean = false

fun solve() {
  val n = ni()
  val arr = nextIntArray(n)
  val lastPos = IntArray(n)
  val seen = Array(n + 3) { -1 }

  for (i in 0 until n) {
    val l = maxOf(seen[arr[i]], seen[arr[i] + 1], seen[arr[i] - 1])
    lastPos[i] = l
    seen[arr[i]] = i
  }

  val stack = ArrayDeque<Int>()
  var res = 0L
  for (i in n - 1 downTo 0) {
    while (stack.isNotEmpty() && lastPos[stack.first()] >= i) stack.removeFirst()
    val r = if (stack.isEmpty()) n else stack.first()
    res += (r - i)
    stack.addFirst(i)
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
