#include<bits/stdc++.h>
#include<cstring>
using namespace std;
int main()
{
    char str1[51], str2[51];
    cin>>str1;
    cin>>str2;
    int m = strlen(str1);
    int n = strlen(str2);
    int arr[m+1][n+1],i,j;
    for (i=0; i<=m; i++)
    {
        for (j=0; j<=n; j++)
        {
            if (i == 0 || j == 0)
                arr[i][j] = 0;

            else if (str1[i-1] == str2[j-1])
                arr[i][j] = arr[i-1][j-1] + 1;

            else
                arr[i][j] = max(arr[i-1][j], arr[i][j-1]);
        }
    }
    i = m;
    j = n;
    int length = arr[m][n];
    cout<<length<<endl;
    char str[length+1];
    str[length]='\0';
    while (i > 0 && j > 0)
    {
        if (str1[i-1] == str2[j-1])
        {
            str[length-1] = str1[i-1];
            i--;
            j--;
            length--;
        }
        else if (arr[i][j-1] > arr[i-1][j])
            j--;
        else
            i--;
    }
    cout<<str<<endl;
    return 0;
}
