#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
#include <cmath>
#define int __int128
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
const int N = 2e6 + 5, mod = 998244353;
array <int, N> r;
int pow_(int x, int k, int p) {
	int ans = 1;
	while (k) {
		if (k & 1) ans = ans * x % p;
		x = x * x % p;
		k >>= 1;
	}
	return ans;
}
signed main() {
	int n = read(), m = read();
	int tp = n, ans = 1;
	bool flg = false;
	for (int i = 2; i <= 2e6; i++) {
		if (tp % i) continue;
		int siz = 0;
		while (tp % i == 0)
			tp /= i, siz++;
		ans = ans * (siz * (m % mod) % mod + 1) % mod;
		if ((siz * m + 1) % (int)2 == (int)0)
			flg = 1;
	}
	/* write(flg), puts(""); */
	if (tp > 1) {
		ans = ans * (m % mod + 1) % mod;
		if ((m + 1) % (int)2 == (int)0)
			flg = 1;
	}
	/* ans = ans * m % mod; */
	/* write(ans), puts(""); */
	/* m /= 2; */
	if (!flg && m % 2)
		ans = (ans - 1 + mod) % mod;
	ans = ans * pow_(2, mod - 2, mod) % mod * m % mod;
	if (!flg && m % 2)
		ans = (ans + m / 2) % mod;
	write(ans), puts("");
	return 0;
}
