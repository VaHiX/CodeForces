// Problem: CF 1533 B - Nearest Point Function
// https://codeforces.com/contest/1533/problem/B

import java.io.*
import java.util.*
object program {
  @JvmStatic
  fun main(args: Array<String>) {
    val inputStream = System.`in`
    val outputStream: OutputStream = System.out
    val `in` = InputReader(inputStream)
    val out = PrintWriter(outputStream)
    val solver = BFunktsiyaPoiskaBlizhaisheiTochki()
    val testCount = `in`.next().toInt()
    for (i in 1..testCount) solver.solve(i, `in`, out)
    out.close()
  }
  internal class BFunktsiyaPoiskaBlizhaisheiTochki {
    fun solve(testNumber: Int, `in`: InputReader, out: PrintWriter) {
      val n = `in`.nextInt()
      val x = IntArray(n)
      for (i in 0 until n) {
        x[i] = `in`.nextInt()
      }
      var i = 0
      while (i + 1 < n) {
        // Check if the average of two consecutive points is an integer
        // If yes, then there exists a point y that is equidistant from both points
        // which causes the function to crash
        if ((x[i] + x[i + 1]) % 2 == 0) {
          out.println("YES")
          return
        }
        ++i
      }
      out.println("NO")
    }
  }
  internal class InputReader(stream: InputStream?) {
    var reader: BufferedReader
    var tokenizer: StringTokenizer?
    operator fun next(): String {
      while (tokenizer == null || !tokenizer!!.hasMoreTokens()) {
        tokenizer =
            try {
              StringTokenizer(reader.readLine())
            } catch (e: IOException) {
              throw RuntimeException(e)
            }
      }
      return tokenizer!!.nextToken()
    }
    fun nextInt(): Int {
      return next().toInt()
    }
    init {
      reader = BufferedReader(InputStreamReader(stream), 32768)
      tokenizer = null
    }
  }
}


// https://github.com/VaHiX/CodeForces/