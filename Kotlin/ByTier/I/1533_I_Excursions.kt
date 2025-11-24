// Problem: CF 1533 I - Excursions
// https://codeforces.com/contest/1533/problem/I

import java.io.*
import java.util.*
object program {
  @JvmStatic
  fun main(args: Array<String>) {
    val inputStream = System.`in`
    val outputStream: OutputStream = System.out
    val `in` = InputReader(inputStream)
    val out = PrintWriter(outputStream)
    val solver = IEkskursii()
    solver.solve(1, `in`, out)
    out.close()
  }
  internal class IEkskursii {
    var nv = 0 // Total number of nodes (sights) visited in current component
    var ne = 0 // Total number of edges (bus routes) in current component
    var mink = 0 // Minimum number of tourists starting at any sight in current component
    fun solve(testNumber: Int, `in`: InputReader, out: PrintWriter) {
      val n1 = `in`.nextInt() // Number of sights in Saratov
      val n2 = `in`.nextInt() // Number of sights in Engels
      val m = `in`.nextInt() // Number of bus routes
      val k = IntArray(n1) // Number of tourists starting at each sight in Saratov
      for (i in 0 until n1) k[i] = `in`.nextInt()
      val e = Array(n1) { BooleanArray(n2) } // Adjacency matrix representing bus routes
      for (i in 0 until m) {
        val a1 = `in`.nextInt() - 1 // Convert to 0-based indexing
        val a2 = `in`.nextInt() - 1
        e[a1][a2] = true // Mark bus route from sight a1 in Saratov to sight a2 in Engels
      }
      val mark = BooleanArray(n1) // Visited array for Saratov sights
      val mark2 = BooleanArray(n2) // Visited array for Engels sights
      var res = 0 // Result: minimum number of tourists returning to original sight
      for (i in 0 until n1) if (!mark[i]) { // For each unvisited sight in Saratov
        mink = k[i]
        nv = 0
        ne = 0
        dfs1(i, e, k, mark, mark2) // Start DFS from this sight
        ne /= 2 // Each edge was counted twice (once for each direction)
        if (nv > ne) res += mink // If more sights than bus routes, some tourists must return
      }
      out.println(res)
    }
    private fun dfs1(
        i: Int,
        e: Array<BooleanArray>,
        k: IntArray,
        mark: BooleanArray,
        mark2: BooleanArray,
    ) {
      if (mark[i]) return // Already visited
      ++nv // Count this sight
      mark[i] = true
      mink = Math.min(mink, k[i]) // Update minimum tourists starting here
      for (j in 0 until e[i].size) if (e[i][j]) { // For each connected Engels sight
        ++ne // Count edge
        dfs2(j, e, k, mark, mark2) // Continue DFS in Engels
      }
    }
    private fun dfs2(
        j: Int,
        e: Array<BooleanArray>,
        k: IntArray,
        mark: BooleanArray,
        mark2: BooleanArray,
    ) {
      if (mark2[j]) return // Already visited
      ++nv // Count this sight
      mark2[j] = true
      for (i in e.indices) if (e[i][j]) { // For each connected Saratov sight
        ++ne // Count edge
        dfs1(i, e, k, mark, mark2) // Continue DFS in Saratov
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