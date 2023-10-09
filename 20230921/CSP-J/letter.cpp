#include <iostream>
#include <algorithm>
#include <cstdio>
#include <queue>
#define int long long
using namespace std;
/* #ifdef ONLINE_JUDGE */

/* #define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++) */
/* char buf[1 << 23], *p1 = buf, *p2 = buf, ubuf[1 << 23], *u = ubuf; */

/* #endif */
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
const int N = 1e6 + 5;
int lowbit(int x) {
	return x & -x;
}
int edge[N];
void modify(int x, int y, int n) {
	while (x <= n) {
		edge[x] += y;
		x += lowbit(x);
	}
	return;
}
int query(int x) {
	int ans = 0;
	while (x) {
		ans += edge[x];
		x -= lowbit(x);
	}
	return ans;
}

queue <int> isl[27];
int h[N];
char strbuf[N];
signed main() {
	freopen("letter.in", "r", stdin);
	freopen("letter.out", "w", stdout);
	int n = read();
	scanf("%s", strbuf);
	string s = strbuf;
	int tp = 1;
	for (int i = 0; i < s.size(); i++)
		isl[s[i] - 'A'].push(tp++);
	scanf("%s", strbuf);
	s = strbuf;
	for (int i = 0; i < s.size(); i++) {
		h[i] = isl[s[i] - 'A'].front();
		isl[s[i] - 'A'].pop();
	}
	int ans = 0;
	for (int i = s.size() - 1; ~i; i--) {
		/* write(h[i]), putchar(32); */
		ans += query(h[i]);
		modify(h[i], 1, n);
	}
	/* puts(""); */
	write(ans), puts("");
	return 0;
}
