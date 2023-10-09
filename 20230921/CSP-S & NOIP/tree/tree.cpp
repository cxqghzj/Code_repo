#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
#include <set>
#include <vector>
#include <bitset>
#define int long long
#define pii pair <int, int>
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
#define fi first
#define se second
const int mod = 998244353;
namespace G {

const int N = 2e5 + 5, M = 4e5 + 5;
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

namespace T {

const int N = 2005, M = 4005;
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

namespace math {

const int N = 2e5 + 5;
array <int, N> fac, inv;
int pow_(int x, int k, int p) {
	int ans = 1;
	while (k) {
		if (k & 1) ans = ans * x % p;
		x = x * x % p;
		k >>= 1;
	}
	return ans;
}
void init() {
	int n = 2e5;
	fac[0] = 1;
	for (int i = 1; i <= n; i++)
		fac[i] = fac[i - 1] * i % mod;
	inv[n] = pow_(fac[n], mod - 2, mod);
	for (int i = n; i; i--)
		inv[i - 1] = inv[i] * i % mod;
}
int C(int n, int m) {
	if (n < m || n < 0 || m < 0) return 0;
	return fac[n] * inv[m] % mod * inv[n - m] % mod;
}
void Mod(int &x) {
	if (x >= mod) x -= mod;
	if (x < 0) x += mod;
}

}


namespace init {

const int N = 2e5 + 5;
bitset <N> vis;
array <int, N> fa;
array <int, N> isl, dep;
using namespace G;

void dfs(int x) {
	for (int i = fir[x]; i; i = nex[i]) {
		if (to[i] == fa[x]) continue;
		fa[to[i]] = x;
		isl[to[i]] = vis[x] ? x : isl[x];
		dep[to[i]] = dep[x] + 1;
		dfs(to[i]);
	}
}

}

namespace solve {

using namespace T;
using init::N, math::C, math::Mod;
set <int, greater <int> > isl;
array <int, N> dep;
int ans, k, m;

void dfs1(int x, int fa) {
	for (int i = fir[x]; i; i = nex[i]) {
		if (to[i] == fa) continue;
		dep[to[i]] = dep[x] + len[i];
		dfs1(to[i], x);
	}
	isl.insert(dep[x]);
}
void dfs2(int x, int fa) {
	for (int i = fir[x]; i; i = nex[i]) {
		if (to[i] == fa) continue;
		dfs2(to[i], x);
	}
	int i = 0;
	for (auto y : isl) {
		if (y == dep[x]) {
			break;
		}
		i++;
	}
	ans += C(isl.size() - i - 1, k - 1) * dep[x] % mod, Mod(ans);
	ans += (C(m - 1, k - 1) - C(isl.size() - i - 1, k - 1) + mod) % mod * dep[x] % mod * 2 % mod, Mod(ans);
}

}
signed main() {
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	int n = read(), m = read(), k = read();
	for (int i = 1; i <= m; i++) {
		int x = read();
		init::vis[x] = 1;
	}
	math::init();
	for (int i = 2; i <= n; i++) {
		int x = read(), y = read();
		G::add(x, y), G::add(y, x);
	}
	init::dep[1] = 1;
	init::dfs(1);
	for (int i = 1; i <= n; i++) {
		T::add(i, init::isl[i], -init::dep[init::isl[i]] + init::dep[i]);
		T::add(init::isl[i], i, -init::dep[init::isl[i]] + init::dep[i]);
		/* write(init::isl[i]), putchar(32); */
	}
	/* puts(""); */
	solve::k = k;
	for (int i = 1; i <= n; i++) {
		solve::dep.fill(0);
		solve::isl.clear();
		solve::dfs1(i, 0);
		for (int j = 1; j <= n; j++) {
			write(solve::dep[j]), putchar(32);
		}
		puts("");
		solve::dfs2(i, 0);
	}
	write(solve::ans), puts("");
	write(solve::ans * math::pow_(math::C(m, k), mod - 2, mod) % mod), puts("");
	return 0;
}
