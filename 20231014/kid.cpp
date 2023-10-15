#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
#define int long long
using namespace std;
#ifdef ONLINE_JUDGE

#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
char buf[1 << 23], *p1 = buf, *p2 = buf, ubuf[1 << 23], *u = ubuf;

#endif
int read() {
	int p = 0, flg = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-') flg = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		p = p * 10 + c - '0';
		c = getchar();
	}
	return p * flg;
}
void write(int x) {
	if (x < 0) {
		x = -x;
		putchar('-');
	}
	if (x > 9) {
		write(x / 10);
	}
	putchar(x % 10 + '0');
}
namespace Subtask1 {

void main(int n, int m, int k) {
	if (k == n) write(m == (n - 1) || m == n), puts("");
	else puts("0");
}

}

namespace Subtask2 {

void main(int n, int m, int k) {
	if (n == m && k == n) {
		int ans = 1;
		for (int i = 1; i <= n; i++) {
			ans = ans * i % (int)(1e9 + 7);
		}
		write(ans), puts("");
	}
	else puts("0");
}

}
const int N = 305, mod = 1e9 + 7;
namespace Subtask3 {

int k;
array <int, N> fac, inv;
void Mod(int x) {
	if (x >= mod) x -= mod;
	if (x < 0) x += mod;
}
int pow_(int x, int k, int p) {
	int ans = 1;
	while (k) {
		if (k & 1) ans = ans * x % p;
		x = x * x % p;
		k >>= 1;
	}
	return ans;
}
void init(int n) {
	fac[0] = 1;
	for (int i = 1; i <= n; i++)
		fac[i] = fac[i - 1] * i % mod;
	inv[n] = pow_(fac[n], mod - 2, mod);
	for (int i = n; i; i--)
		inv[i - 1] = inv[i] * i % mod;
}
array <array <int, N>, N> f;
int C(int n, int m) {
	if (n < m) return 0;
	return fac[n] * inv[m] % mod * inv[n - m] % mod;
}
void main(int n, int m, int _k)	{
	Subtask3::k = _k;
	init(n);
	f[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		f[i][1] = 1;
		for (int j = 2; j <= i; j++) {
			for (int k = 1; k <= Subtask3::k && k <= (i + 1) / 2; k++) {
				f[i][j] += C(i, k) * f[i - k][j - 1] % mod;
				Mod(f[i][j]);
			}
			write(i), putchar(32);
			write(j), putchar(32);
			write(f[i][j]), puts("");
		}
	}
	write(f[n][n - m] + f[n][n - m + 1]), puts("");
}

}
signed main() {
	freopen("kid.in", "r", stdin);
	freopen("kid.out", "w", stdout);
	int n = read(), m = read(), k = read();
	if (n <= k) return Subtask1::main(n, m, k), 0;
	if (n <= m) return Subtask2::main(n, m, k), 0;
	return Subtask3::main(n, m, k), 0;
}
