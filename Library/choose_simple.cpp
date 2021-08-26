
constexpr int MOD = (int) 1e9 + 7; // 998244353
constexpr int MX = 100005;

vector<int> fact = {1, 1};
vector<int> inv = {1, 1};
vector<int> inv_fact = {1, 1};

// O(n)
void prepare_factorials(int maximum = MX - 1) {
  assert(maximum < MX);

  fact.resize(maximum + 1);
  inv.resize(maximum + 1);
  inv_fact.resize(maximum + 1);

  for (int i = 2; i <= maximum; ++i) {
    fact[i] = (int64_t) fact[i - 1] * i % MOD;
    inv[i] = (MOD - MOD / i) * (int64_t) inv[MOD % i] % MOD;
    inv_fact[i] = (int64_t) inv_fact[i - 1] * inv[i] % MOD;
  }
}

// n choose r
int choose(int n, int r) {
  if (r < 0 or r > n) {
    return 0;
  }
  return (int64_t) fact[n] * inv_fact[n - r] % MOD * inv_fact[r] % MOD;
}

// n!
int factorial(int n) {
  return n < 0 ? 0 : fact[n];
}

// P(n, r)
int permute(int n, int r) {
  if (r < 0 or r > n) {
    return 0;
  }
  return (int64_t) fact[n] * inv_fact[n - r] % MOD;
}

// convient modular arithmetic operations
namespace MOP {
  // += -= *= /= (mod MOD)
  template<typename T, typename U>
  void ADD(T& x, U v) {
    x -= MOD - v; if (x < 0) x += MOD;
  }
  template<typename T, typename U>
  void SUB(T& x, U v) {
    x -= v; if (x < 0) x += MOD;
  }
  template<typename T, typename U>
  void MUL(T& x, U v) {
    x = (int64_t) x * v % MOD;
  }
  template<typename T, typename U>
  void DIV(T& x, U v) {
    x = (int64_t) x * inv[v] % MOD;
  }

  // + - * / (mod MOD)
  template<typename T, typename U>
  T add(T x, U v) {
    x -= MOD - v; if (x < 0) x += MOD; return x;
  }
  template<typename T, typename U>
  T sub(T x, U v) {
    x -= v; if (x < 0) x += MOD; return x;
  }
  template<typename T, typename U>
  T mul(T x, U v) {
    x = (int64_t) x * v % MOD; return x;
  }
  template<typename T, typename U>
  T div(T x, U v) {
    x = (int64_t) x * inv[v] % MOD; return x;
  }
}

// O(log MOD)
int invert(int64_t a, int b = MOD - 2) {
  int64_t result = 1;

  while (b) {
    if (b & 1) {
      result = result * a % MOD;
    }
    a = a * a % MOD;
    b >>= 1;
  }

  return (int) result;
}