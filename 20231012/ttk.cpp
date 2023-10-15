#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
#include <tuple>
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
const int N = 3e5 + 5, M = 6e5 + 5, K = 505, mod = 998244353;

namespace uni {

array <int, N> fa, siz;
int siz_;
int find(int x) {
	if (x == fa[x]) return x;
	return fa[x] = find(fa[x]);
}
void merge(int x, int y) {
	int fx = find(x),
		fy = find(y);
	/* write(fx), putchar(32); */
	/* write(fy), puts("@"); */
	if (fx == fy) return;
	if (siz[fx] > siz[fy]) swap(fx, fy);
	fa[fx] = fy;
	siz[fy] += fx;
	siz_--;
}
void init(int n) {
	for (int i = 1; i <= n; i++)
		siz[fa[i] = i] = 1;
	siz_ = n;
}

}

array <tuple <int, int, int>, N> qrl;
array <int, K> f, g;

void Mod(int &x) {
	if (x >= mod) x -= mod;
	if (x < 0) x += mod;
}

signed main() {
	/* freopen("ttk2.in", "r", stdin); */
	/* freopen("ttk.out", "w", stdout); */
	int n = read(), m = read(), k = read();
	for (int i = 1; i <= m; i++) {
		get <1>(qrl[i]) = read(), get <2>(qrl[i]) = read();
		get <0>(qrl[i]) = read();
	}
	uni::init(n);
	sort(qrl.begin() + 1, qrl.begin() + 1 + m);
	g[1] = n;
	for (int i = 1; i <= m; i++) {
		int lst = uni::siz_;
		while (get <0>(qrl[i]) == get <0>(qrl[i + 1]))
			uni::merge(get <1>(qrl[i]), get <2>(qrl[i])), i++;
		uni::merge(get <1>(qrl[i]), get <2>(qrl[i]));
		f.fill(0);
		/* write(i), putchar(32); */
		/* write(uni::siz_), puts(""); */
		/* write(i), puts(":"); */
		for (int j = 1; j <= k; j++) {
			f[j] = (g[j - 1] + 1) * (lst - uni::siz_) % mod;
			/* write(f[j]), putchar(32); */
			g[j] += f[j], Mod(g[j]);
		}
		/* puts(""); */
	}
	int ans = 1;
	for (int i = 1; i <= k; i++)
		ans += g[i], Mod(ans);
	write(ans), puts("");
	return 0;
}
