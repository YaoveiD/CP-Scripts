/*
*  author: yaoveil
*  date:   2021-06-22 23:19:13
*/

const int MOD = 1e9 + 7;
long long modpow(long long a, long long b){
  long long result = 1;
  
  while (b) {
    if (b & 1) {
      result = result * a % MOD;
    }
    a = a * a % MOD;
    b >>= 1;
  }
  
  return result;
}