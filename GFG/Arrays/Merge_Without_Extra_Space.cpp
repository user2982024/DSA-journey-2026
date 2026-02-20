class Solution {
  public:
    void mergeArrays(vector<int>& a, vector<int>& b) {
        // code here
        int m = a.size();
        int n = b.size();
        
        for (int i = 0; i < n; i ++) {
            a.push_back(b[i]);
        }
        
        sort(a.begin(), a.end());
        
        int index = 0;
        
        for (int i = m; i < m + n; i ++) {
            b[index] = a[i];
            index ++;
        }
        
        for (int i = m; i < m + n; i ++) {
            a.pop_back();
        }
    }
};