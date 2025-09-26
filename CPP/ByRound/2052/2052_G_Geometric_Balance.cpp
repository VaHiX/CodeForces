/*
 * Problem URL : https://codeforces.com/problemset/submit
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

void input();
void solve();

int main() {
  input();
  solve();
}

int n;
int qt[50003];
ll qv[50003];
char str[12];

void input() {
  scanf("%d", &n);
  for (int i = 2; i <= n + 1; i++) {
    scanf("%s %lld", str, &qv[i]);
    qt[i] = (str[0] == 'r' ? 0 : str[0] == 'd' ? 1 : 2);
    if (qt[i] == 0)
      qv[i] /= 45;
  }
  n++;
}

struct Num {
  ll a, b; /// a + b sqrt(2)
  Num() {}
  Num(ll a) : a(a) { b = 0; }
  Num(ll a, ll b) : a(a), b(b) {}

  Num operator+(const Num r) const { return Num(a + r.a, b + r.b); }
  Num operator-(const Num r) const { return Num(a - r.a, b - r.b); }
  Num operator*(const ll r) const { return Num(a * r, b * r); }
  Num operator/(const ll r) const { return Num(a / r, b / r); }

  Num operator*(const Num r) const {
    return Num(a * r.a + b * r.b * 2, a * r.b + b * r.a);
  }
  Num operator-() const { return Num(-a, -b); }

  bool operator<(const Num r) const {
    ll p = a - r.a, q = r.b - b;
    if (p == 0 && q <= 0)
      return 0;
    if (p == 0 && q > 0)
      return 1;
    if (p < 0 && q == 0)
      return 1;
    if (p >= 0 && q == 0)
      return 0;
    if (p < 0 && q > 0)
      return 1;
    if (p > 0 && q < 0)
      return 0;
    if (p > 0 && q > 0)
      return ld(p) * p < ld(q) * q * 2;
    return ld(p) * p > ld(q) * q * 2;
  }
  bool operator==(const Num r) const { return a == r.a && b == r.b; }
  bool operator!=(const Num r) const { return a != r.a || b != r.b; }
};

struct Point {
  Num x, y;
  Point() {}
  Point(Num x, Num y) : x(x), y(y) {}

  Point operator+(const Point r) const { return Point(x + r.x, y + r.y); }
  Point operator-(const Point r) const { return Point(x - r.x, y - r.y); }
  Point operator*(const ll r) const { return Point(x * r, y * r); }
  Point operator/(const ll r) const { return Point(x / r, y / r); }

  Num dot(const Point r) const { return x * r.x + y * r.y; }

  Point simplify() const {
    ll g = __gcd(__gcd(abs(x.a), abs(x.b)), __gcd(abs(y.a), abs(y.b)));
    return *this / g;
  }

  bool operator<(const Point r) const {
    if (x == r.x)
      return y < r.y;
    return x < r.x;
  }

  bool operator==(const Point r) const { return x == r.x && y == r.y; }

  bool operator!=(const Point r) const { return x != r.x || y != r.y; }

  void print() {
    printf("x: %lld+%lldsqrt(2), y: %lld+%lldsqrt(2)\n", x.a, x.b, y.a, y.b);
  }

  Point perp() { return Point(y, -x); }
};

const Point dd[8] = {
    Point(Num(2, 0), Num(0, 0)),  Point(Num(0, 1), Num(0, 1)),
    Point(Num(0, 0), Num(2, 0)),  Point(Num(0, -1), Num(0, 1)),
    Point(Num(-2, 0), Num(0, 0)), Point(Num(0, -1), Num(0, -1)),
    Point(Num(0, 0), Num(-2, 0)), Point(Num(0, 1), Num(0, -1))};

struct Format {
  vector<pair<Point, Point>> vec;

  void init() {
    //        Point a = Point(Num(0,0), Num(20,0)), b = Point(Num(0,0),
    //        Num(0,0)); Point c = min(a,b); Point d = max(a,b); c.print();
    //        d.print();

    Point st(0, 0);
    int dir = 0;
    for (int i = 1; i <= n; i++) {
      if (qt[i] == 0)
        dir = (dir + qv[i]) & 7;
      else if (qt[i] == 1) {
        Point st2 = st + dd[dir] * qv[i];
        vec.push_back(make_pair(min(st, st2), max(st, st2)));
        st = st2;
      } else
        st = st + dd[dir] * qv[i];
      //            printf("st "), st.print();
    }

    sort(vec.begin(), vec.end(),
         [&](pair<Point, Point> a, pair<Point, Point> b) {
           Point p = (a.second - a.first).simplify(),
                 q = (b.second - b.first).simplify();
           if (p != q)
             return p < q;
           Num pv = a.first.dot(p.perp()), qv = b.first.dot(q.perp());
           if (pv != qv)
             return pv < qv;
           return a.first < b.first;
         });

    vector<pair<Point, Point>> vec2;
    for (int l = 0; l < (int)vec.size(); l++) {
      int r = l;
      while (r + 1 < n && vec[r].second == vec[r + 1].first &&
             (vec[r].second - vec[r].first).simplify() ==
                 (vec[r + 1].second - vec[r + 1].first).simplify())
        r++;
      vec2.push_back(make_pair(vec[l].first, vec[r].second));
      l = r;
    }
    swap(vec, vec2);
    sort(vec.begin(), vec.end());

    Num minX = vec[0].first.x, minY = vec[0].first.y;
    for (auto [p, q] : vec) {
      minX = min({minX, p.x, q.x});
      minY = min({minY, p.y, q.y});
    }
    for (auto &[p, q] : vec) {
      p.x = p.x - minX, p.y = p.y - minY;
      q.x = q.x - minX, q.y = q.y - minY;
    }

    //        for(auto &[p, q]: vec){
    //            printf("Start: "), p.print();
    //            printf("End: "), p.print();
    //        }
    //        printf("End\n\n");
  }

  bool operator==(const Format &r) const { return vec == r.vec; }
} format[4];

void solve() {
  qv[1] = 0;
  format[0].init();

  qv[1] = 1;
  format[1].init();
  if (format[0] == format[1]) {
    puts("45");
    return;
  }

  qv[1] = 2;
  format[2].init();
  if (format[0] == format[2]) {
    puts("90");
    return;
  }

  qv[1] = 4;
  format[3].init();
  if (format[0] == format[3]) {
    puts("180");
    return;
  }

  puts("360");
}
