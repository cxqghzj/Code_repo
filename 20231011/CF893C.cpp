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
const int N = 1e5 + 5;
namespace uni {

array <int, N> siz, fa;
int find(int x) {
	if (x == fa[x]) return x;
	return fa[x] = find(fa[x]);
}
void merge(int x, int y) {
	int fx = find(x),
		fy = find(y);
	if (fx == fy) return;
	fa[fx] = fy;
	siz[fy] = min(siz[fy], siz[fx]);
}


}
signed main() {
	int n = read(), m = read();
	for (int i = 1; i <= n; i++)
		uni::siz[uni::fa[i] = i] = read();
	for (int i = 1; i <= m; i++) {
		int x = read(), y = read();
		uni::merge(x, y);
	}
	int ans = 0;
	for (int i = 1; i <= n; i++)
		if (uni::fa[i] == i) ans += uni::siz[i];
	write(ans), puts("");
	return 0;
}
