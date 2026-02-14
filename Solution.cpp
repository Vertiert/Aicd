#include <vector>
using namespace std;

class Solution {
public:
    static const int MOD = 1000000007; 

    int colorTheGrid(int m, int n) {
        vector<int> masks;
        int total = 1;

        for (int i = 0; i < m; i++) total *= 3;

        //строим правильный столбец
        for (int i = 0; i < total; i++) {
            int x = i;
            int last = -1; 
            bool skip = false;

            for (int j = 0; j < m; j++) {
                int c = x % 3;  
                x /= 3;         

                if (c == last) {
                    skip = true;
                    break;
                }
                last = c;
            }

            if (!skip) {
                masks.push_back(i);
            }
        }

        int sz = masks.size();

        vector<vector<bool>> g(sz, vector<bool>(sz, false));

        //проверяем два столбца и ищем подходящие друг другу
        for (int i = 0; i < sz; i++) {
            for (int j = 0; j < sz; j++) {
                int a = masks[i];
                int b = masks[j];
                bool good = true;

                for (int row = 0; row < m; row++) {
                    int ca = a % 3;  
                    int cb = b % 3; 
                    a /= 3; 
                    b /= 3;

                    if (ca == cb) {
                        good = false;
                        break;
                    }
                }
                if (good) {
                    g[i][j] = true;  
                }
            }
        }

        vector<long long> old(sz, 1);  
        vector<long long> cur(sz, 0);  

        //всё соединяем
        for (int t = 1; t < n; t++) {
            fill(cur.begin(), cur.end(), 0);  

            for (int j = 0; j < sz; j++) {
                long long sum = 0;

                for (int i = 0; i < sz; i++) {
                    if (g[i][j]) sum += old[i];
                }
                cur[j] = sum % MOD; 
            }
            old.swap(cur);  
        }

        long long res = 0;

        for (int i = 0; i < sz; i++) {
            res += old[i];
        }

        return res % MOD;
    }
};