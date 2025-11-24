/******************************************************************************
 * Problem: 1906 D - Spaceship Exploration
 * https://codeforces.com/contest/1906/problem/D
 *
 * Description:
 * A geometric problem involving finding shortest paths between two points in a
 * polygonal environment. The task is to determine the minimum distance between
 * two points while considering possible reflections off a polygon's edges.
 *
 * Time Complexity Analysis:
 * - Overall: O(Q * (log N + K))
 *   where Q is number of queries
 *   N is number of vertices in polygon
 *   K is constant time for geometric calculations
 * - Binary search for cut points: O(log N)
 * - Geometric operations: O(1)
 *
 * Space Complexity:
 * - O(N) for storing polygon vertices and sorted coordinates
 * - O(1) additional space per query
 *
 * Key Components:
 * 1. Fast I/O implementation for performance
 * 2. Vector geometry operations
 * 3. Binary search for finding intersection points
 * 4. Custom geometric calculations for path finding
 ******************************************************************************/

#include <bits/stdc++.h>
using namespace std;
namespace Fread {
const int SIZE = 1 << 16;
char buf[SIZE], *S, *T;
inline char getchar() {
  if (S == T) {
    T = (S = buf) + fread(buf, 1, SIZE, stdin);
    if (S == T)
      return '\n';
  }
  return *S++;
}
} // namespace Fread
namespace Fwrite {
const int SIZE = 1 << 16;
char buf[SIZE], *S = buf, *T = buf + SIZE;
inline void flush() {
  fwrite(buf, 1, S - buf, stdout);
  S = buf;
}
inline void putchar(char c) {
  *S++ = c;
  if (S == T)
    flush();
}
struct NTR {
  ~NTR() { flush(); }
} ztr;
} // namespace Fwrite
#define getchar Fread::getchar
#define putchar Fwrite::putchar
#define Setprecision 15
#define between '\n'
#define __int128 long long
template <typename T> struct is_char {
  static constexpr bool value =
      (std::is_same<T, char>::value || std::is_same<T, signed char>::value ||
       std::is_same<T, unsigned char>::value);
};
template <typename T> struct is_integral_ex {
  static constexpr bool value =
      (std::is_integral<T>::value || std::is_same<T, __int128>::value) &&
      !is_char<T>::value;
};
template <typename T> struct is_floating_point_ex {
  static constexpr bool value =
      std::is_floating_point<T>::value || std::is_same<T, __float128>::value;
};
namespace Fastio {
struct Reader {
  template <typename T>
  typename std::enable_if_t<std::is_class<T>::value, Reader &>
  operator>>(T &x) {
    for (auto &y : x)
      *this >> y;
    return *this;
  }
  template <typename T>
  typename std::enable_if_t<is_integral_ex<T>::value, Reader &>
  operator>>(T &x) {
    char c = getchar();
    short f = 1;
    while (c < '0' || c > '9') {
      if (c == '-')
        f *= -1;
      c = getchar();
    }
    x = 0;
    while (c >= '0' && c <= '9') {
      x = (x << 1) + (x << 3) + (c ^ 48);
      c = getchar();
    }
    x *= f;
    return *this;
  }
  template <typename T>
  typename std::enable_if_t<is_floating_point_ex<T>::value, Reader &>
  operator>>(T &x) {
    char c = getchar();
    short f = 1, s = 0;
    x = 0;
    T t = 0;
    while ((c < '0' || c > '9') && c != '.') {
      if (c == '-')
        f *= -1;
      c = getchar();
    }
    while (c >= '0' && c <= '9' && c != '.')
      x = x * 10 + (c ^ 48), c = getchar();
    if (c == '.')
      c = getchar();
    else
      return x *= f, *this;
    while (c >= '0' && c <= '9')
      t = t * 10 + (c ^ 48), s++, c = getchar();
    while (s--)
      t /= 10.0;
    x = (x + t) * f;
    return *this;
  }
  template <typename T>
  typename std::enable_if_t<is_char<T>::value, Reader &> operator>>(T &c) {
    c = getchar();
    while (c == '\n' || c == ' ' || c == '\r')
      c = getchar();
    return *this;
  }
  Reader &operator>>(char *str) {
    int len = 0;
    char c = getchar();
    while (c == '\n' || c == ' ' || c == '\r')
      c = getchar();
    while (c != '\n' && c != ' ' && c != '\r')
      str[len++] = c, c = getchar();
    str[len] = '\0';
    return *this;
  }
  Reader &operator>>(std::string &str) {
    str.clear();
    char c = getchar();
    while (c == '\n' || c == ' ' || c == '\r')
      c = getchar();
    while (c != '\n' && c != ' ' && c != '\r')
      str.push_back(c), c = getchar();
    return *this;
  }
  Reader() {}
} cin;
const char endl = '\n';
struct Writer {
  typedef __int128 mxdouble;
  template <typename T>
  typename std::enable_if_t<std::is_class<T>::value, Writer &> operator<<(T x) {
    for (auto &y : x)
      *this << y << between;
    *this << '\n';
    return *this;
  }
  template <typename T>
  typename std::enable_if_t<is_integral_ex<T>::value, Writer &>
  operator<<(T x) {
    if (x == 0)
      return putchar('0'), *this;
    if (x < 0)
      putchar('-'), x = -x;
    static int sta[45];
    int top = 0;
    while (x)
      sta[++top] = x % 10, x /= 10;
    while (top)
      putchar(sta[top] + '0'), --top;
    return *this;
  }
  template <typename T>
  typename std::enable_if_t<is_floating_point_ex<T>::value, Writer &>
  operator<<(T x) {
    if (x < 0)
      putchar('-'), x = -x;
    mxdouble _ = x;
    x -= (T)_;
    static int sta[45];
    int top = 0;
    while (_)
      sta[++top] = _ % 10, _ /= 10;
    if (!top)
      putchar('0');
    while (top)
      putchar(sta[top] + '0'), --top;
    putchar('.');
    for (int i = 0; i < Setprecision; i++)
      x *= 10;
    _ = x;
    while (_)
      sta[++top] = _ % 10, _ /= 10;
    for (int i = 0; i < Setprecision - top; i++)
      putchar('0');
    while (top)
      putchar(sta[top] + '0'), --top;
    return *this;
  }
  template <typename T>
  typename std::enable_if_t<is_char<T>::value, Writer &> operator<<(T c) {
    putchar(c);
    return *this;
  }
  Writer &operator<<(char *str) {
    int cur = 0;
    while (str[cur])
      putchar(str[cur++]);
    return *this;
  }
  Writer &operator<<(const char *str) {
    int cur = 0;
    while (str[cur])
      putchar(str[cur++]);
    return *this;
  }
  Writer &operator<<(std::string str) {
    int st = 0, ed = str.size();
    while (st < ed)
      putchar(str[st++]);
    return *this;
  }
  Writer() {}
} cout;
} // namespace Fastio
#define cin Fastio::cin
#define cout Fastio::cout
#define endl Fastio::endl
// Type definitions for precision handling
typedef long double ll; // Long double for high precision calculations
typedef long double db; // Alias for database calculations

// Basic mathematical utilities
inline __float128 fabs(__float128 a) {
  return a < 0 ? -a : a;
} // Absolute value
inline long double sq(db w) { return w * w; } // Square function
// 2D Vector structure with basic geometric operations
struct vec {
  db x, y; // Coordinates

  // Constructor with default values
  vec(db _x = 0, db _y = 0) : x(_x), y(_y) {}

  // Vector addition
  inline vec operator+(vec other) { return vec(x + other.x, y + other.y); }

  // Vector subtraction
  inline vec operator-(vec other) { return vec(x - other.x, y - other.y); }

  // Dot product
  inline db operator*(vec other) { return x * other.x + y * other.y; }

  // Cross product (returns z-component)
  inline db operator^(vec other) { return x * other.y - y * other.x; }

  // Debug printing
  inline void print() { cout << x << ' ' << y << ' '; }
};
inline db len(vec x) { return sqrt(sq(x.x) + sq(x.y)); }
constexpr db eps = 1e-10;
int n, q;
vec p[100005];
inline db cmax(db a, db b) {
  if (fabs(a + 1) < eps)
    return b;
  if (fabs(b + 1) < eps)
    return a;
  return min(a, b);
}
inline bool chkrt(vec A, vec B, vec C) { return ((B - A) ^ (C - A)) < 0; }
inline bool chkrrt(vec A, vec B, vec C) { return !chkrt(A, C, B); }
// Node structure for polygon vertices with sorting capability
struct node {
  ll x, y; // Coordinates
  int id;  // Original index in polygon

  // Constructor with default values
  node(ll _x = 0, ll _y = 0, int _id = 0) : x(_x), y(_y), id(_id) {}

  // Comparison operator for sorting
  // Sorts primarily by x-coordinate, then by y-coordinate
  inline bool operator<(const node &other) {
    return x == other.x ? y < other.y : x < other.x;
  }
} z[100005]; // Array of vertices
// Find the two polygon vertices that form the tangent lines from point A
// Returns a pair of vectors representing these vertices
pair<vec, vec> SolveCutPoint(vec A) {
  // Binary search boundaries and result
  int l = 1, r = n, ans = -1;
  // Create a node from the query point
  auto w = node(A.x, A.y, 0);
  auto ww = *lower_bound(z + 1, z + n + 1, w);
  if (A.x == ww.x && A.y == ww.y) {
    int k = ww.id;
    if (chkrt(A, p[k - 1], p[k + 1]))
      return make_pair(p[k + 1], p[k - 1]);
    else
      return make_pair(p[k - 1], p[k + 1]);
  }
  if (!chkrt(A, p[1], p[2]) && !chkrt(A, p[1], p[0]))
    ans = 1;
  while (l < r) {
    int m = l + r + 1 >> 1;
    if (!chkrt(A, p[m], p[m + 1]) && !chkrt(A, p[m], p[m - 1])) {
      ans = m;
      break;
    }
    if (chkrt(A, p[l], p[l + 1])) {
      if (!chkrt(A, p[m], p[m + 1]))
        r = m - 1;
      else if (chkrt(A, p[l], p[m]))
        l = m;
      else
        r = m - 1;
    } else {
      if (chkrt(A, p[m], p[m + 1]))
        l = m;
      else if (!chkrt(A, p[l], p[m]))
        l = m;
      else
        r = m - 1;
    }
  }
  int ansb = -1;
  l = 1, r = n;
  if (chkrrt(A, p[1], p[2]) && chkrrt(A, p[1], p[0]))
    ansb = 1;
  while (l < r) {
    int m = l + r + 1 >> 1;
    if (chkrrt(A, p[m], p[m + 1]) && chkrrt(A, p[m], p[m - 1])) {
      ansb = m;
      break;
    }
    if (!chkrt(A, p[l], p[l + 1])) {
      if (chkrt(A, p[m], p[m + 1]))
        r = m - 1;
      else if (!chkrt(A, p[l], p[m]))
        l = m;
      else
        r = m - 1;
    } else {
      if (!chkrt(A, p[m], p[m + 1]))
        l = m;
      else if (chkrt(A, p[l], p[m]))
        l = m;
      else
        r = m - 1;
    }
  }
  assert(ans != -1);
  assert(ansb != -1);
  return make_pair(p[ans], p[ansb]);
}
inline int sgn(db x) {
  if (fabs(x) < eps)
    return 0;
  if (x > 0)
    return 1;
  return -1;
}
inline bool Mid(vec A, vec B, vec C, vec D) {
  return !chkrt(A, D, B) || !chkrt(A, C, D);
}
inline db Solvelen(vec Ax, vec Ay, vec Bx, vec By) {
  db Ak = (Ax.y - Ay.y) * 1.0 / (Ax.x - Ay.x);
  db Ab = Ax.y - Ax.x * Ak;
  db Bk = (Bx.y - By.y) * 1.0 / (Bx.x - By.x);
  db Bb = Bx.y - Bx.x * Bk;
  if (fabs(Ak - Bk) < eps)
    return -1;
  db X = (Bb - Ab) / (Ak - Bk);
  db Y = Ak * X + Ab;
  if (Ax.x == Ay.x) {
    if (Bx.x == By.x)
      return -1;
    X = Ax.x;
    Y = Bk * X + Bb;
  } else if (Bx.x == By.x)
    X = Bx.x, Y = Ak * X + Ab;
  if (sgn(Ax.x - X) == sgn(Ay.x - Ax.x) && fabs(Ax.x - X) > eps)
    return -1;
  if (sgn(Bx.x - X) == sgn(By.x - Bx.x) && fabs(Bx.x - X) > eps)
    return -1;
  return sqrt(sq(Ax.x - X) + sq(Ax.y - Y)) + sqrt(sq(Bx.x - X) + sq(Bx.y - Y));
}
// Solve a single query - find minimum distance between points A and B
// considering possible reflections off polygon edges
inline db solve() {
  // Read query points
  vec A, B;
  cin >> A.x >> A.y >> B.x >> B.y;

  // Find tangent points for both A and B
  pair<vec, vec> p1 = SolveCutPoint(A), p2 = SolveCutPoint(B);
  if (Mid(A, p1.first, p1.second, B) || Mid(B, p2.first, p2.second, A))
    return len(A - B);
  return cmax(cmax(Solvelen(A, p1.first, B, p2.first),
                   Solvelen(A, p1.first, B, p2.second)),
              cmax(Solvelen(A, p1.second, B, p2.first),
                   Solvelen(A, p1.second, B, p2.second)));
}
int main() {
  // Read number of polygon vertices
  cin >> n;

  // Read polygon vertices
  for (int i = 1; i <= n; i++) {
    cin >> p[i].x >> p[i].y;
  }

  // Set up circular references for polygon
  // p[0] points to last vertex, p[n+1] points to first vertex
  p[n + 1] = p[1];
  p[0] = p[n];
  for (int i = 1; i <= n; i++)
    z[i] = node(p[i].x, p[i].y, i);
  sort(z + 1, z + n + 1);
  cin >> q;
  while (q--) {
    cout << solve() << endl;
  }
}

// https://github.com/VaHiX/CodeForces/