// Contest 1170, Problem C: Minus and Minus Give Plus
// URL: https://codeforces.com/contest/1170/problem/C

import java.io.*
import java.util.*

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
