// Problem: CF 1170 C - Minus and Minus Give Plus
// https://codeforces.com/contest/1170/problem/C

import java.io.*
import java.util.*
/*
Algorithm/Technique: Two Pointers
Approach:
- Use two pointers, one for each string s (a) and t (b).
- When characters at both pointers match, advance both pointers.
- If s[pos1] is '-', and the next character in s is also '-', we can merge two minuses into one plus.
  In this case, advance pos1 by 2 (consume two minus signs) and pos2 by 1 (consume one plus sign).
- If none of the above conditions apply, break the loop.
- If both pointers reach the end of their respective strings, the transformation is possible.

Time Complexity: O(n + m) where n and m are the lengths of strings s and t.
Space Complexity: O(1) - only using a constant amount of extra space.
*/
fun solve(cin: FastReader, out: PrintWriter) {
  val k = cin.nextLine().toInt()
  nextop@ repeat(k) {
    val a = cin.nextLine()
    val b = cin.nextLine()
    var pos1 = 0
    var pos2 = 0
    while (pos1 != a.length && pos2 != b.length) {
      if (a[pos1] == b[pos2]) {
        pos1++
        pos2++
        continue
      }
      if (a[pos1] == '-' && pos1 + 1 < a.length && a[pos1 + 1] == '-') {
        pos1 += 2
        pos2++
        continue
      }
      break
    }
    if (pos1 == a.length && pos2 == b.length) out.println("YES") else out.println("NO")
  }
}
class FastReader(input: InputStream) {
  private val br = BufferedReader(InputStreamReader(input))
  private var st = StringTokenizer("")
  fun next(): String {
    while (!st.hasMoreTokens()) st = StringTokenizer(br.readLine())
    return st.nextToken()
  }
  fun int(): Int {
    return next().toInt()
  }
  fun double(): Double {
    return next().toDouble()
  }
  fun long(): Long {
    return next().toLong()
  }
  fun nextLine(): String {
    return br.readLine()
  }
}
fun main(args: Array<String>) {
  val cin = FastReader(System.`in`)
  val out = PrintWriter(BufferedOutputStream(System.out))
  solve(cin, out)
  out.flush()
}


// https://github.com/VaHiX/CodeForces/