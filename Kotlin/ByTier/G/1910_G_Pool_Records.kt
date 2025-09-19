// Contest 1910, Problem G: Pool Records
// URL: https://codeforces.com/contest/1910/problem/G

fun readString(): String {
  var s = StringBuilder()
  var c: Int
  var any = false
  while (true) {
    c = System.`in`.read()
    if (!(c != 32 && c != 10 && c != 9 && c != 13 && c >= 0)) {
      if (c >= 0 && !any) continue
      break
    }
    s.append(c.toChar())
    any = true
  }
  return s.toString()
}

fun readInt(): Int {
  return Integer.parseInt(readString())
}

fun print(x: Any?) {
  System.out.println(x)
}

fun stringToCharArray(x: String): CharArray {
  var ans = CharArray(x.length)
  var i = 0
  while (i < x.length) ans[i] = x[i]
  return ans
}

fun charArrayToString(x: CharArray): String {
  var ans = StringBuilder()
  for (i in x) ans.append(i)
  return ans.toString()
}

fun check(data: IntArray): Boolean {
  var k1 = data[0]
  var k1_next = k1 + k1
  var k2 = 0
  var k2_next = 0
  var i = 0
  while (data.size > ++i) {
    var ok = false
    if (data[i] == k1_next) {
      k1_next += k1
      ok = true
    } else if (data[i] > k1_next) return false
    else if (k2 == 0) {
      k2 = data[i]
      k2_next = k2
    }
    if (data[i] == k2_next) {
      k2_next += k2
      ok = true
    } else if (k2 != 0 && data[i] > k2_next) return false
    if (!ok) return false
  }
  return true
}

fun main(x: Array<String>) {
  var T = readInt()
  while (T-- > 0) {
    var n = readInt()
    var data = IntArray(n)
    var i = -1
    while (n > ++i) data[i] = readInt()
    if (check(data)) print("VALID") else print("INVALID")
  }
}
