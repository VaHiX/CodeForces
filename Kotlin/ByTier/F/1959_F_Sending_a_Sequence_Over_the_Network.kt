// Contest 1959, Problem F: Sending a Sequence Over the Network
// URL: https://codeforces.com/contest/1959/problem/F

import java.util.StringTokenizer

fun main() =
    with(System.`in`.bufferedReader()) {
      var bw = System.`out`.bufferedWriter()
      var t = readLine().toInt()
      repeat(t) {
        var n = readLine().toInt()
        var answer = BooleanArray(n + 1) { false }
        answer[0] = true
        var st = StringTokenizer(readLine())
        for (i in 0 until n) {
          var m = st.nextToken().toInt()
          if (answer[i]) {
            if (i + m + 1 <= n) {
              answer[i + m + 1] = true
            }
          }
          if (-1 < i - m && answer[i - m]) {
            answer[i + 1] = true
          }
        }
        if (answer[n]) {
          bw.write("YES\n")
        } else {
          bw.write("NO\n")
        }
      }
      bw.flush()
      bw.close()
    }
