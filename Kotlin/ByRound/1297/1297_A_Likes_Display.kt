// Problem: CF 1297 A - Likes Display
// https://codeforces.com/contest/1297/problem/A

import java.io.*
import java.util.*
object programkt {
  @JvmStatic
  fun main(args: Array<String>) {
    val inputStream = System.`in`
    val outputStream = System.out
    val `in` = InputReader(inputStream)
    val out = OutputWriter(outputStream)
    val solver = TaskA()
    val testCount = Integer.parseInt(`in`.next())
    for (i in 1..testCount) {
      solver.solve(i, `in`, out)
    }
    out.close()
  }
  internal class TaskA {
    fun solve(testNumber: Int, `in`: InputReader, out: OutputWriter) {
      val n = `in`.readInt()
      if (n < 1000) {
        // If n is less than 1000, display as is
        out.printLine(n)
        return
      }
      if (n < 999500) {
        // For numbers between 1000 and 999499 (inclusive),
        // round to nearest thousand and display as K
        // Adding 500 before division rounds correctly
        out.printLine(((n + 500) / 1000).toString() + "K")
        return
      }
      // For numbers 999500 and above,
      // round to nearest million and display as M
      // Adding 500000 before division rounds correctly
      out.printLine(((n + 500000) / 1000000).toString() + "M")
    }
  }
  internal class OutputWriter {
    private val writer: PrintWriter
    constructor(outputStream: OutputStream) {
      writer = PrintWriter(BufferedWriter(OutputStreamWriter(outputStream)))
    }
    constructor(writer: Writer) {
      this.writer = PrintWriter(writer)
    }
    fun print(vararg objects: Any) {
      for (i in objects.indices) {
        if (i != 0) {
          writer.print(' ')
        }
        writer.print(objects[i])
      }
    }
    fun printLine(vararg objects: Any) {
      print(*objects)
      writer.println()
    }
    fun close() {
      writer.close()
    }
    fun printLine(i: Int) {
      writer.println(i)
    }
  }
  internal class InputReader(private val stream: InputStream) {
    private val buf = ByteArray(1024)
    private var curChar: Int = 0
    private var numChars: Int = 0
    private val filter: InputReader.SpaceCharFilter? = null
    fun read(): Int {
      if (numChars == -1) {
        throw InputMismatchException()
      }
      if (curChar >= numChars) {
        curChar = 0
        try {
          numChars = stream.read(buf)
        } catch (e: IOException) {
          throw InputMismatchException()
        }
        if (numChars <= 0) {
          return -1
        }
      }
      return buf[curChar++].toInt()
    }
    fun readInt(): Int {
      var c = read()
      while (isSpaceChar(c)) {
        c = read()
      }
      var sgn = 1
      if (c == '-'.toInt()) {
        sgn = -1
        c = read()
      }
      var res = 0
      do {
        if (c < '0'.toInt() || c > '9'.toInt()) {
          throw InputMismatchException()
        }
        res *= 10
        res += c - '0'.toInt()
        c = read()
      } while (!isSpaceChar(c))
      return res * sgn
    }
    fun readString(): String {
      var c = read()
      while (isSpaceChar(c)) {
        c = read()
      }
      val res = StringBuilder()
      do {
        if (Character.isValidCodePoint(c)) {
          res.appendCodePoint(c)
        }
        c = read()
      } while (!isSpaceChar(c))
      return res.toString()
    }
    fun isSpaceChar(c: Int): Boolean {
      return filter?.isSpaceChar(c) ?: isWhitespace(c)
    }
    operator fun next(): String {
      return readString()
    }
    interface SpaceCharFilter {
      fun isSpaceChar(ch: Int): Boolean
    }
    companion object {
      fun isWhitespace(c: Int): Boolean {
        return c == ' '.toInt() ||
            c == '\n'.toInt() ||
            c == '\r'.toInt() ||
            c == '\t'.toInt() ||
            c == -1
      }
    }
  }
}


// https://github.com/VaHiX/CodeForces/