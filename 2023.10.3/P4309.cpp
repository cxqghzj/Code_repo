#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
#include <cmath>
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
const int N = 2e5 + 5;
namespace Bit {

array <int, N> edge;
int lowbit(int x) {
	return x & -x;
}
void modify(int x, int y, int n) {
	while (x <= n) {
		edge[x] += y;
		x += lowbit(x);
	}
	return;
}
int kth(int k, int n) {
	int sum = 0, x = 0;
	for (int i = log2(n); ~i; i--) {
		x += 1 << i;
		if (x >= n || sum + edge[x] >= k)
			x -= 1 << i;
		else
			sum += edge[x];
	}
	return x + 1;
}

}
namespace _Bit {

array <int, N> edge;
int lowbit(int x) {
	return x & -x;
}
void modify(int x, int y, int n) {
	while (x <= n) {
		edge[x] = max(edge[x], y);
		x += lowbit(x);
	}
	return;
}
int query(int x) {
	int ans = 0;
	while (x) {
		ans = max(ans, edge[x]);
		x -= lowbit(x);
	}
	return ans;
}

}
array <int, N> s, h, rk;
int main() {
	/* freopen("1.in", "r", stdin); */
	/* freopen("my.txt", "w", stdout); */
	int n = read();
	for (int i = 1; i <= n; i++)
		s[i] = read();
	Bit::edge.fill(0);
	for (int i = n; i; i--) {
		rk[i] = Bit::kth(s[i], n);
		Bit::modify(rk[i], 1, n);
	}
	/* for (int i = n; i; i--) */
		/* write(rk[i]), putchar(32); */
	/* puts(""); */
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		int x = _Bit::query(rk[i] - 1) + 1;
		_Bit::modify(rk[i], x, n);
		ans = max(ans, x);
		write(ans), puts("");
	}
	return 0;
}
