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
const int N = 1e3 + 5, M = 1e4 + 5, K = 1e7 + 5, mod = 998244353;
int pow_(int x, int k, int p) {
	int ans = 1;
	while (k) {
		if (k & 1) ans = ans * x % p;
		x = x * x % p;
		k >>= 1;
	}
	return ans;
}
array <int, K> s, idx;
array <int, K> f;
signed main() {
	int n = read(), m = read();
	/* m++; */
	for (int i = 1; i <= n; i++)
		s[i] = read();
	int pk = s[1];
	/* sort(s.begin() + 1, s.begin() + 1 + n); */
	/* int pos = m / s[1] + 1; */
	f[0] = 1;
	for (int j = 1; j <= m; j++) {
		for (int i = 1; i <= n; i++) {
			if (j < s[i]) continue;
			f[j] += f[j - s[i]] * pow_(n, mod - 2, mod) % mod;
			if (f[j] >= mod) f[j] -= mod;
		}
		for (int j = 1; j <= m; j++) {
			/* write(f[j]), putchar(32); */
		}
		/* puts(""); */
	}
	int ans = 0;
	for (int i = m; i + pk > m; i--) {
		ans += f[i] * pow_(n, mod - 2, mod) % mod;
		if (ans >= mod) ans -= mod;
	}
	write(ans), puts("");
	return 0;
}
