// Problem: CF 1533 F - Binary String Partition
// https://codeforces.com/contest/1533/problem/F

/*
 * Problem: Binary String Partition
 * Algorithm: Greedy with preprocessed positions
 * Time Complexity: O(n) where n is the length of the string
 * Space Complexity: O(n) for storing preprocessed arrays
 *
 * The approach uses greedy strategy:
 * For each k, we try to partition the string such that in each substring,
 * the count of either '0' or '1' does not exceed k.
 * We precompute positions of zeros and ones, then simulate greedy partitioning.
 */
import java.io.*
import java.util.*
object program {
  @JvmStatic
  fun main(args: Array<String>) {
    val inputStream = System.`in`
    val outputStream: OutputStream = System.out
    val `in` = InputReader(inputStream)
    val out = PrintWriter(outputStream)
    val solver = FRazbienieDvoichnoiStroki()
    solver.solve(1, `in`, out)
    out.close()
  }
  internal class FRazbienieDvoichnoiStroki {
    fun solve(testNumber: Int, `in`: InputReader, out: PrintWriter) {
      val s = `in`.next()
      val n = s.length
      // p0 and p1 store positions of 0s and 1s respectively
      val p0 = IntArray(n * 2 + 5)
      Arrays.fill(p0, n)
      var n0 = 0
      val p1 = IntArray(n * 2 + 5)
      Arrays.fill(p1, n)
      var n1 = 0
      // n0s[i] = number of 0s before position i
      // n1s[i] = number of 1s before position i
      val n0s = IntArray(n)
      val n1s = IntArray(n)
      // Preprocessing: count 0s and 1s before each position and store their positions
      for (i in 0 until s.length) {
        n0s[i] = n0
        n1s[i] = n1
        if (s[i] == '0') p0[n0++] = i else p1[n1++] = i
      }
      // For each k from 1 to n
      for (k in 1..n) {
        var at = 0
        var res = 0
        // Greedily partition the string
        while (at < n) {
          ++res
          // Find the furthest position we can go with current k
          at = Math.max(p0[n0s[at] + k], p1[n1s[at] + k])
        }
        out.print("$res ")
      }
      out.println()
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
    init {
      reader = BufferedReader(InputStreamReader(stream), 32768)
      tokenizer = null
    }
  }
}


// https://github.com/VaHiX/CodeForces/