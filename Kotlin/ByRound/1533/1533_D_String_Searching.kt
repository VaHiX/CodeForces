// Problem: CF 1533 D - String Searching
// https://codeforces.com/contest/1533/problem/D

import java.io.*
import java.util.*
object program {
  @JvmStatic
  fun main(args: Array<String>) {
    val inputStream = System.`in`
    val outputStream: OutputStream = System.out
    val `in` = InputReader(inputStream)
    val out = PrintWriter(outputStream)
    val solver = DPoiskStrok()
    solver.solve(1, `in`, out)
    out.close()
  }
  internal class DPoiskStrok {
    fun solve(testNumber: Int, `in`: InputReader, out: PrintWriter) {
      val n = `in`.nextInt() // Number of strings in the array
      val m = `in`.nextInt() // Length of each string
      val counts: MutableMap<String, Int> = HashMap() // Map to store frequency of each string
      for (i in 0 until n) {
        val s = `in`.next() // Read each string
        val old = counts[s] // Get current count
        if (old == null) counts[s] = 1 else counts[s] = old + 1 // Update count
      }
      val q = `in`.nextInt() // Number of queries
      val seen: MutableSet<String> = HashSet() // Set to keep track of already processed substrings
      for (qi in 0 until q) {
        val t = `in`.next() // Read query string
        seen.clear() // Clear seen set for each query
        var res = 0 // Initialize result counter
        for (i in 0 until t.length) {
          // Generate substring by removing one character at position i
          val cur = t.substring(0, i) + t.substring(i + 1)
          // Skip if we've already processed this substring
          if (!seen.add(cur)) continue
          // Check if this substring exists in our counts map
          val got = counts[cur]
          if (got != null) res += got // Add frequency to result
        }
        out.println(res) // Print result for current query
      }
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