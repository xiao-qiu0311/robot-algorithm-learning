#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <cstring>

#if 0
// 逆序字符串
void Reverse(char arr[], int size){
    char* p = arr;
    char* q = arr + size -1;
    while(p < q){
        char ch = *p;
        *p = *q;
        *q = ch;
        p++;
        q--;
    }
};

int main(){
    char arr[] = "hello world";
    
    Reverse(arr, strlen(arr));

    std::cout << arr << std::endl;
}
#endif

// #if 0
// 整型数组，把偶数调整到数组左边，把奇数调整到数组的右边
void AdjustArray(int arr[], int size){
    int* p = arr;
    int* q = arr + size - 1;
    while(p < q){
        // p->奇数 用位与 & => 按位与   注：按位与的优先级 < ==
        // 如果一个数是偶数，最低位是0 -> x & 0x1 == 0
        // 如果一个数是奇数，最低位是1 -> x & 0x1 == 1
        while(p < q){
            if((*p & 0x1) == 0){
                break;
            }
            p++;
        }


        // q <- 偶数
        while(p < q){
            if((*q & 0x1) == 1){
            break;
            }
            q --;
        }
        

        // 此时p->奇数 q->偶数
        if(p < q){
            int tmp = *p;
            *p = *q;
            *q = tmp;
            p++;
            q--;
        }
    }  
}

int main(){
    int arr[10] = {0};
    srand(time(0));
    for(int i = 0; i < 10; i++){
        arr[i] = rand() % 100;
    }

    AdjustArray(arr, 10);

    for(int v : arr){
        std::cout << v << " ";
    }
    std::cout << std::endl;

    return 0;
}
// #endif

