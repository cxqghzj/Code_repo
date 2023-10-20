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
const int N = 1e5 + 5, M = 2e5 + 5;

namespace G {

array <int, N> fir;
array <int, M> nex, to, len;
int cnt;
void add(int x, int y, int z) {
	cnt++;
	nex[cnt] = fir[x];
	to[cnt] = y;
	len[cnt] = z;
	fir[x] = cnt;
}

}

namespace Subtask1 {

using G::fir, G::nex, G::to, G::len;
array <int, N> siz, fa;
array <int, N> dis, c, f;
void dfs(int x) {
	siz[x] = 1;
	for (int i = fir[x]; i; i = nex[i]) {
		if (to[i] == fa[x]) continue;
		fa[to[i]] = x;
		dis[to[i]] = len[i];
		dfs(to[i]);
		siz[x] += siz[to[i]];
	}
}
void main(int n, int m) {
	dfs(1);
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		c[i] = dis[i] * (siz[1] - siz[i]) * siz[i];
		ans += c[i];
	}
	for (int i = 1; i <= n; i++) {
		/* write(dis[i]), putchar(32); */
		for (int j = m; j >= siz[i]; j--)
			f[j] = max(f[j - siz[i]] + c[i], f[j]);
		/* for (int j = 1; j <= m; j++) */
			/* write(f[j]), putchar(32); */
		/* puts(""); */
	}
	write(ans - f[m]), puts("");
}

}

namespace Subtask2 {


using G::fir, G::nex, G::to, G::len;
array <int, N> siz, fa;
array <int, N> dis, c, f;
void dfs(int x) {
	siz[x] = 1;
	for (int i = fir[x]; i; i = nex[i]) {
		if (to[i] == fa[x]) continue;
		fa[to[i]] = x;
		dis[to[i]] = len[i];
		dfs(to[i]);
		siz[x] += siz[to[i]];
	}
}
void main(int n, int m) {
	dfs(1);
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		c[i] = dis[i] * (siz[1] - siz[i]) * siz[i];
		ans += c[i];
	}
	sort(c.begin() + 1, c.begin() + 1 + n);
	for (int i = 1; i <= m; i++)
		ans -= c[i];
	write(ans), puts("");
}

}
signed main() {
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	int n = read(), m = read();
	bool flg = false;
	for (int i = 2; i <= n; i++) {
		int x = read(), y = read(), z = read();
		G::add(x, y, z);
		G::add(y, x, z);
		if (z > 1) flg = 1;
	}
	if (n <= 5000) Subtask1::main(n, m);
	else if (!flg) Subtask2::main(n, m);
	return 0;
}
