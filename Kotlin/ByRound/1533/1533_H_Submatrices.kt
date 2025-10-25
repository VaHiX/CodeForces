// Problem: CF 1533 H - Submatrices
// https://codeforces.com/contest/1533/problem/H

/*
 * Problem: H. Submatrices
 * Algorithm/Technique: Bitmask Dynamic Programming + Monotonic Stack
 * Time Complexity: O(n * m * 2^5) = O(n * m)
 * Space Complexity: O(n * m + 2^5) = O(n * m)
 *
 * The solution uses a bitmask to iterate through all possible combinations of
 * letters (from 1 to 5 letters), for each combination counting valid submatrices.
 * For each such combination, it computes for each column how many rows ending at
 * current row form a valid submatrix containing only those letters.
 * 
 * A monotonic stack technique is used to efficiently calculate the number
 * of valid rectangles in each column, considering only rows whose letters
 * are included in the current bitmask.
 * 
 * After computing total counts for each subset of letters, the inclusion-exclusion
 * principle is applied to determine how many submatrices contain exactly k different letters.
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
    val solver = HPodmatritsi()
    solver.solve(1, `in`, out)
    out.close()
  }
  internal class HPodmatritsi {
    fun solve(testNumber: Int, `in`: InputReader, out: PrintWriter) {
      val height = `in`.nextInt()
      val width = `in`.nextInt()
      val data = arrayOfNulls<String>(height)
      for (r in 0 until height) {
        data[r] = `in`.next()
      }
      val count = LongArray(1 shl 5) // count[s] stores number of submatrices for bitmask s
      val h = IntArray(width) // h[c] stores height of histogram at column c
      val stack = IntArray(width) // monotonic stack for histogram heights
      for (s in 1 until (1 shl 5)) { // iterate over each non-empty subset of letters
        Arrays.fill(h, 0)
        for (r in 0 until height) {
          var sp = 0 // stack pointer
          var total: Long = 0 // total count of rectangles for current row
          for (c in 0 until width) {
            // If current cell's letter belongs to subset s, extend histogram
            if (s and (1 shl data[r]!![c] - 'A') != 0) {
              ++h[c]
            } else {
              h[c] = 0 // reset histogram if letter not in subset
            }
            // Maintain monotonic increasing stack
            while (sp > 0 && h[stack[sp - 1]] >= h[c]) {
              val before = if (sp - 2 >= 0) stack[sp - 2] else -1
              total -= h[stack[sp - 1]] * (stack[sp - 1] - before).toLong()
              --sp
            }
            stack[sp++] = c
            // Update total count with contribution of current element
            val before = if (sp - 2 >= 0) stack[sp - 2] else -1
            total += h[stack[sp - 1]] * (stack[sp - 1] - before).toLong()
            count[s] += total
          }
        }
      }
      // Apply inclusion-exclusion principle:
      // For each subset s, subtract count of subsets that contain s (i.e., s with one more letter added)
      for (a in 0..4) {
        for (s in 0 until (1 shl 5)) {
          if (s and (1 shl a) == 0) {
            count[s or (1 shl a)] -= count[s]
          }
        }
      }
      // Compute result for exactly k letters
      val res = LongArray(6)
      for (i in 0 until (1 shl 5)) {
        res[Integer.bitCount(i)] += count[i] // bitCount of subset gives number of letters
      }
      for (i in 1..5) {
        out.print(res[i].toString() + " ")
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