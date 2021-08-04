#include <bits/stdc++.h>
// something wrong
using namespace std;

namespace IO {
  //write
  template<typename T>
  inline void w(T x) { if (x > 9) w(x / 10); putchar(x % 10 + 48); }
  inline void wr(char sep, double f) { cout << f; }
  inline void wr(char sep, const string& s) { cout << s; }
  template<typename T, typename U>
  inline void wr(char sep, const pair<T, U>& p) { w(p.first); putchar(' '); w(p.second); }
  template<typename T>
  inline void wr(char sep, T x) { if(x < 0) putchar('-'), x = -x; w(x); }
  template<typename T>
  inline void wr(char sep, const vector<T>& v) {
    bool first = true;
    for (auto& x : v) {
      if (!first) { putchar(' '); }
      wr(sep, x);
      first = false;
    }
  }
  template<typename T, typename... U>
  void wr(char sep, const T& t, const U&... u) {
    wr(sep, t);
    putchar(sep);
    wr(sep, u...);
  }
  void write() { putchar('\n'); }
  template<typename ...T>
  void write(const T&... t) {
    wr(' ', t...);
    write();
  }

  //read
  template<typename T>
  inline void read(T& x) {
      x = 0; T f = 1; char c = getchar();
      for (; !isdigit(c); c = getchar()) if (c == '-') f = -1;
      for (; isdigit(c); c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
      x *= f;
  }
  inline void read(double& f) { cin >> f; }
  inline void read(string& s) { cin >> s; }
  template<typename T, typename... U>
  void read(T&, U&...);
  template<typename T, typename U>
  inline void read(pair<T, U>& p) {
    read(p.first, p.second);
  }
  template<typename T>
  inline void read(vector<T>& v) {
    for (auto& x : v) { read(x); }
  }
  template<typename T, typename... U>
  void read(T& t, U&... u) { read(t); read(u...); }
  #define ints(...) int __VA_ARGS__; read(__VA_ARGS__);
}
using namespace IO;

void test() {
  ints(tt);
  while (tt--) {
    ints(A, B);
    write(A + B);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  test();
  return 0;
}
