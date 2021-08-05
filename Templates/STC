//c stytle function
template<typename T>
class ST {
public:
  vector<vector<T> > mat;
  int n;
  T (*func)(const T&, const T&);

  ST(const vector<T>& A, T (*_f)(const T&, const T&)) : func(_f) {
    n = (int) A.size();
    int max_log = 32 - __builtin_clz(n);
    mat.resize(max_log);
    mat[0] = A;
    for (int j = 1; j < max_log; ++j) {
      int cutoff = (n - (1 << j) + 1);
      mat[j].resize(cutoff);
      for (int i = 0; i < cutoff; ++i) {
        mat[j][i] = (*func)(mat[j - 1][i], mat[j - 1][i + (1 << (j - 1))]);
      }
    }
  }

  T query(int from, int to) {
    assert(0 <= from and from <= to and to <= n - 1);
    int k = 31 - __builtin_clz(to - from + 1);
    return func(mat[k][from], mat[k][to - (1 << k) + 1]);
  }
};
