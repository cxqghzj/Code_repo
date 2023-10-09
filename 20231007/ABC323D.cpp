#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
#include <set>
#include <unordered_map>
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
const int N = 1e5 + 5;
unordered_map <long long, int> dis;
set <long long> isl;
int lowbit(int x) {
	return x & -x;
}
signed main() {
	int n = read();
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		int x = read(), y = read();
		dis[x] = y;
		ans += y;
		isl.insert(x);
	}
	for (auto x : isl) {
		int tp = dis[x];
		ans -= dis[x];
		dis[x] = 0;
		while (tp) {
			if (!dis[1ll * lowbit(tp) * x])
				isl.insert(1ll * lowbit(tp) * x);
			dis[1ll * lowbit(tp) * x]++;
			ans++;
			tp -= lowbit(tp);
		}
	}
	write(ans), puts("");
	return 0;
}
