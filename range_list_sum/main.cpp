#include <stdint.h>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct range_t {
	int start;
	int end;
	uint64_t value;
	range_t(int s, int e, uint64_t v) : start(s), end(e), value(v) {}
};

int main() {
	int n, m, a, b, pause;
	size_t rSize;
	uint64_t k, vMax = 0;
	cin >> n >> m;
	vector<range_t> R, T;	
	R.emplace_back(1, n, 0);

	while (m-- > 0)
	{
		cin >> a >> b >> k;
		
		/*
		for (size_t i = 0; i < R.size(); ++i)
		{
			if (R[i].invalid) continue;
			cout << "r: " << R[i].start << ' ' << R[i].end << ' ' << R[i].value << endl;
		}
		*/
		cout << "abk: " << a << ' ' << b << ' ' << k << endl;
		
		for (size_t i = 0; i < R.size();)
		{
			// If the range we are investigating ends before
			//   beginning of the i-th, ordered range, continue
			if (b < R[i].start)
			{
			    i++;   
			    continue;
			}
			// If the range we are investigating starts after
			//   the end of the i-th, ordered range, break
			if (a > R[i].end) break;
            if (a < R[i].start)
			{
			    if (b < R[i].end)
			    {
				    T.emplace_back(R[i].start, b, k + R[i].value);
				    vMax = max(T.back().value, vMax);
				    T.emplace_back(b + 1, R[i].end, R[i].value);
				    vMax = max(T.back().value, vMax);
				    i += 1;
			    }
			    else
			    {
				    T.emplace_back(R[i].start, R[i].end, k + R[i].value);
				    vMax = max(T.back().value, vMax);
			    }
			}
			else
			{
                T.emplace_back(R[i].start, a - 1, R[i].value);
				vMax = max(T.back().value, vMax);
				if (b < R[i].end)
				{
				    T.emplace_back(a, b, k + R[i].value);
				    vMax = max(T.back().value, vMax);
				    T.emplace_back(b + 1, R[i].end, R[i].value);
				    vMax = max(T.back().value, vMax);
				    i += 2;
			    }
				else
				{
				    T.emplace_back(a, R[i].end, R[i].value + k);
				    vMax = max(T.back().value, vMax);
				    i += 1;
				}
			}
			
			R[i] = T[0];
			if (T.size() > 1)
			{
			    R.insert(R.begin()+i+1, T.begin()+1, T.end());				
			}
			T.clear();
		}
	}
	for (size_t i = 0; i < R.size(); ++i)
	{
		cout << "r: " << R[i].start << ' ' << R[i].end << ' ' << R[i].value << endl;
	}
	cout << vMax;
	cin >> pause;
	return 0;
}
