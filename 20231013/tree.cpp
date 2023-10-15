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
int pow_(int x, int k, int p) {
	int ans = 1;
	while (k) {
		if (k & 1) ans = ans * x % p;
		x = x * x % p;
		k >>= 1;
	}
	return ans;
}
const int N = 1e5 + 5, M = 2e5 + 5, mod = 998244353;
array <int, N> s;

namespace G {

array <int, N> fir;
array <int, M> nex, to;
int cnt;
void add(int x, int y) {
	cnt++;
	nex[cnt] = fir[x];
	to[cnt] = y;
	fir[x] = cnt;
}

}

void Mod(int &x) {
	if (x >= mod) x -= mod;
	if (x < 0) x += mod;
}

namespace Subtask1 {

void main(int n, int S) {
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		if (i == S) continue;
		ans += (n - 1) * s[i] % mod, Mod(ans);
		/* write(n - 1), putchar(32); */
		/* write(s[i]), puts("@"); */
	}
	/* write(ans), puts(""); */
	write(ans * pow_((n - 1) * (n - 1) % mod, mod - 2, mod) % mod), puts("");
}

}

signed main() {
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	int n = read(), S = read();
	for (int i = 1; i <= n; i++)
		s[i] = read();
	bool flg = false;
	for (int i = 2; i <= n; i++) {
		int x = read(), y = read();
		G::add(x, y), G::add(y, x);
		if (x != S && y != S)
			flg = 1;
	}
	if (!flg) Subtask1::main(n, S);
	return 0;
}
