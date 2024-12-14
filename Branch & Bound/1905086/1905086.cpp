#include<bits/stdc++.h>
using namespace std;
class mat_object{
public:
    vector<vector<char>> vec;
    int fixed_row;
    int fixed_col;
    int bound;
    int level;
    int order;
    mat_object(vector<vector<char>>& arr,int fix_row,int fix_col,int lvl,int ord,int bound){
        vec = arr;
        vec.resize(arr.size(),vector<char>(arr.size()));
        fixed_row = fix_row;
        fixed_col = fix_col;
        level = lvl;
        order = ord;
        this->bound = bound;
    }
};
class comparator_class{
public:
    bool operator()(mat_object o1,mat_object o2)
    {
        if(o1.bound>o2.bound)return true;
        else if(o1.bound == o2.bound && o1.level < o2.level) return true;
        else if(o1.bound == o2.bound && o1.level == o2.level && o1.order < o2.order) return true;
        else return false;
    }
};

int unfix_band(vector<vector<char>>& vec,int fixRow, int fixCol){
    int maxRowSum = 0;
    for(int i = fixRow+1; i<vec.size(); i++){
            int sum = 0;
        for(int j = fixCol+1; j<vec[0].size(); j++){
            if(vec[i][j]=='X') sum+=1;
        }
        //cout<<sum<<" ";
        maxRowSum = max(maxRowSum,sum);
    }
    //cout<<endl;
    //cout<<maxRowSum<<endl;
    int maxColSum = 0;
    for(int i = fixCol+1; i<vec[0].size(); i++){
            int sum = 0;
        for(int j = fixRow+1; j<vec.size(); j++){
            if(vec[j][i]=='X') sum+=1;
        }
        //cout<<sum<<" ";
        maxColSum = max(maxColSum,sum);
    }
    //cout<<endl;
    //cout<<maxColSum<<endl;
    int cnt = max(maxColSum,maxRowSum);
    int band = (cnt+1)/2;
    return band;
}

int fixcol_band(vector<vector<char>>&vec, int fixRow, int fixCol){
    int maxCol = 0;
    for(int k = 0; k <= fixCol; k++){
       int value = 0;
       int colup = 1, coldown = 1,cnt = 0,final_col_down = 0;
       for(int i = k; i >= 0 ; i--){
        if(vec[i][k] == 'X')
            colup = k-i+1;
       }
       for(int i = fixRow+1; i<vec.size(); i++){
        if(vec[i][k] == 'X'){
            cnt++;
        }
       }
       for(int i = k; i <=fixRow; i++){
        if(vec[i][k] == 'X'){
            coldown = i-k+1;
        }
       }
       if(cnt == 0){
        final_col_down = coldown;
       }
       else{
        final_col_down = (fixRow+cnt+1) - k;
       }
       //cout<<colup<<" "<<final_col_down<<endl;
     value = max(colup,final_col_down);
     //cout<<value<<endl;
     maxCol = max(maxCol,value);
    }
    return maxCol;
}

int fixrow_band(vector<vector<char>>&vec, int fixRow, int fixCol){
    int maxRow = 0;
    for(int k = 0; k <= fixRow; k++){
       int value = 0;
       int row_left = 1, row_right = 1,cnt = 0,final_row_right = 0;
       for(int i = k; i >= 0 ; i--){
        if(vec[k][i] == 'X')
            row_left = k-i+1;
       }
       for(int i = fixCol+1; i<vec[0].size(); i++){
        if(vec[k][i] == 'X'){
            cnt++;
        }
       }
       for(int i = k; i <=fixCol; i++){
        if(vec[k][i] == 'X'){
            row_right = i-k+1;
        }
       }
       if(cnt == 0){
        final_row_right = row_right;
       }
       else{
        final_row_right = (fixCol+cnt+1) - k;
       }
      //cout<<row_left<<" "<<final_row_right<<endl;
      value = max(row_left,final_row_right);
      //cout<<value<<endl;
      maxRow = max(maxRow,value);
    }
    return maxRow;
}
int band_matrix(vector<vector<char>>&vec, int fixRow, int fixCol){
    int unfixed = unfix_band(vec,fixRow,fixCol);
    int fix_row = fixrow_band(vec,fixRow,fixCol);
    int fix_col = fixcol_band(vec,fixRow,fixCol);
    int fixed = max(fix_row,fix_col);
    int band = max(fixed,unfixed);
    return band;
}
vector<vector<char>> row_swap(vector<vector<char>>&vec,int fixed_row, int row){
    vector<vector<char>> demo = vec;
    demo.resize(vec.size(),vector<char>(vec.size()));

    vector<char> temp = demo[row];
    temp.resize(vec.size());
    for(int i = row; i>fixed_row; i--){
        demo[i] = demo[i-1];
    }
    demo[fixed_row] = temp;
    return demo;
}
vector<vector<char>>col_swap(vector<vector<char>>&vec, int fixed_col, int col) {
    vector<vector<char>> demo = vec;
    demo.resize(vec.size(),vector<char>(vec.size()));
    int cnt = fixed_col;
    for (int i=0; i<demo.size(); i++) {
        demo[i][fixed_col] = vec[i][col];
    }
    for (int i=fixed_col; i<vec.size(); i++) {
        if (i == col) {
            continue;
        }
        for (int j=0; j<vec.size(); j++) {
            demo[j][cnt+1] = vec[j][i];
        }
        cnt++;
    }

    return demo;
}
int main(){
   // fstream cin("in.txt");
    vector<vector<char>> arr;
    int n;
    cin>>n;
    arr.resize(n,vector<char>(n));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin>>arr[i][j];
        }
    }
    cout<<endl;

    int bound = band_matrix(arr,-1,-1);
    mat_object mat1(arr,-1,-1,1,0,bound);
    priority_queue<mat_object,vector<mat_object>,comparator_class> pq;
    pq.push(mat1);
    while(!pq.empty()){
       mat_object mat2 = pq.top();
       pq.pop();

       if(mat2.fixed_row == n-2){
        cout<<mat2.bound<<endl;
        for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout<<mat2.vec[i][j]<<" ";
        }
        cout<<endl;
        }
        cout<<endl;
        break;
       }
       int fix_row = mat2.fixed_row, fix_col = mat2.fixed_col;
       if(mat2.fixed_row == mat2.fixed_col){
            fix_col++;
       }
        else{
           fix_row++;
        }
        int lvl = mat2.level+1;
        int order = 0;
        int startIdx = (fix_col > fix_row) ? fix_col : fix_row;

        for(int i = startIdx; i < n; i++){
            vector<vector<char>> temp = (fix_col > fix_row) ? col_swap(mat2.vec,fix_col,i) : row_swap(mat2.vec, fix_row, i);
            int bound = band_matrix(temp,fix_row,fix_col);
            order++;

            pq.push(mat_object(temp,fix_row,fix_col,lvl,order,bound));
        }
    }
    return 0;
}
