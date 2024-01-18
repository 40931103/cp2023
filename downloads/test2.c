#include <stdio.h>   // 包含標準輸入/輸出標頭檔。

void main()
{
    int num1, rem1;   // 宣告兩個整數變數 'num1' 和 'rem1'。

    printf("輸入一個整數：");   // 提示使用者輸入一個整數。
    scanf("%d" , &num1);   // 讀取並將使用者的輸入存儲在 'num1' 中。
    rem1 = num1 % 2;   // 計算 'num1' 除以 2 的餘數。
    if (rem1 == 0)   // 檢查餘數是否等於 0。
        printf("%d 是偶數\n", num1);   // 輸出一條消息，指示 'num1' 是偶數。
    else
        printf("%d 是奇數\n", num1);    // 輸出一條消息，指示 'num1' 是奇數。
}