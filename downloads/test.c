#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    time_t cur_time;   // 宣告 time_t 型別的變數 cur_time 用來存放時間戳
    char* cur_t_string; // 宣告指標 cur_t_string 用來存放時間轉換後的字串
    cur_time = time(NULL); // 使用 time 函式獲取當前的時間戳
    if (cur_time == ((time_t)-1))
    {
        (void) fprintf(stderr, "Failure to get the current date and time.\n"); // 如果獲取時間戳失敗，輸出錯誤訊息
        exit(EXIT_FAILURE);
    }
    cur_t_string = ctime(&cur_time); // 將時間戳轉換成字串形式，並存入 cur_t_string
    if (cur_t_string == NULL)
    {
        (void) fprintf(stderr, "Failure to convert the current date and time.\n"); // 如果轉換時間字串失敗，輸出錯誤訊息
        exit(EXIT_FAILURE);
    }
    (void) printf("\n The Current time is : %s \n", cur_t_string); // 輸出格式化後的時間字串
    exit(EXIT_SUCCESS);
}