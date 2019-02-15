#include <iostream>
using namespace std;

const int T = 10752; 
int g[7][7];
int count = 0;
bool row[7][7];
bool col[7][7];
int ans[T][7][7];

void searchtable(int i, int j){
	if (i == j) j++;
	if (j > 6){
		i++; j = 1;
	}
	if (i > 6){
		memcpy(ans[count], g, sizeof(g));
		count++;
		return;
	}
	for (int k = 1; k <= 6; k++)
		if (!row[i][k] && !col[j][k]){
			row[i][k] = true;
			col[j][k] = true;
			g[i][j] = k;
			searchtable(i, j + 1);
			row[i][k] = false;
			col[j][k] = false;
		}
}

int indexT[8][8][8];
unsigned __int64 bins[64];
unsigned __int64 tuples[8][T][4];

void prepare(){
	bins[0] = 1;
	for (int i = 1; i < 64; i++) bins[i] = bins[i - 1] + bins[i - 1];
	int t = 0;
	int a, b, c;
	for (a = 1; a <= 7; a++)
		for (b = 1; b <= 7; b++)
			for (c = 1; c <= 7; c++)
				if (a != b && b != c && a != c){
					indexT[a][b][c] = t;
					t++;
				}
	for (int x = 1; x <= 7; x++)
		for (int y = 0; y < T; y++){
			memcpy(g, ans[y], sizeof(g));
			for (int j = 1; j <= 6; j++)
				for (int k = 1; k <= 6; k++)
					if (j != k){
						a = j; if (a >= x) a ++;
						b = k; if (b >= x) b ++;
						c = g[j][k]; if (c >= x) c ++;
						int i = indexT[a][b][c];
						int ii = i & 63; i = (i - ii) / 64;
						tuples[x][y][i] += bins[ii];
					}
		}
}

bool d(int x1, int y1, int x2, int y2){
	for (int i = 0; i < 4; i++)
		if ((tuples[x1][y1][i] & tuples[x2][y2][i]) > 0) return false;  
	return true;
}

void DFS(){
	for (int y1 = 0; y1 < T; y1++){
		if (y1 % 300 == 0) cout << y1 << endl;
		for (int y2 = 0; y2 < T; y2++)
			if (d(1, y1, 2, y2))
			for (int y3 = 0; y3 < T; y3++)
				if (d(1, y1, 3, y3) && d(2, y2, 3, y3))
				for (int y4 = 0; y4 < T; y4++)
					if (d(1, y1, 4, y4) && d(2, y2, 4, y4) && d(3, y3, 4, y4))
					for (int y5 = 0; y5 < T; y5++)
						if (d(1, y1, 5, y5) && d(2, y2, 5, y5) && d(3, y3, 5, y5) && d(4, y4, 5, y5))
						for (int y6 = 0; y6 < T; y6++)
							if (d(1, y1, 6, y6) && d(2, y2, 6, y6) && d(3, y3, 6, y6) && d(4, y4, 6, y6) && d(5, y5, 6, y6))
							for (int y7 = 0; y7 < T; y7++)
							if (d(1, y1, 7, y7) && d(2, y2, 7, y7) && d(3, y3, 7, y7) && d(4, y4, 7, y7) && d(5, y5, 7, y7) && d(6, y6, 7, y7))
								cout << y1 << ' ' << y2 << ' ' << y3 << ' ' << y4 << ' ' << y5 << ' ' << y6 << ' ' << y7 << endl;
	}
	//The result is that no combination (y1,y2,...,y7) will be output.
}

void main(){
	for (int i = 1; i <= 6; i++){
		row[i][i] = true;
		col[i][i] = true;
		g[i][i] = i;
	}
	searchtable(1, 2);
	prepare();
	DFS();
}