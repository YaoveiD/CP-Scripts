/*
*  author: yaoveil
*  date:   2021-06-22 23:19:13
*/

const int MOD = 1e9 + 7;
template<typename T>
T modpow(T a, T b){
  T ans = 1;
  while (b){
    if (b % 2 == 1){
      ans = ans * a % MOD;
    }
    a = a * a % MOD;
    b >>= 1;
  }
  return ans;
}