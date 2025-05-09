#include <stdio.h>

void findpairwithsum(int arr[], int n, int X){
    int left=0, right=n-1;

    while(left<right){
        int sum = arr[left] + arr[right];

        if(sum == X){
            printf("Pair found: (%d, %d)\n", arr[left], arr[right]);
            return;
        }
        else if(sum < X){
            left++;
        }
        else{
            right--;
        }
    }

    printf("No pair found with sum %d\n", X);
}

int main(){
    int n, X;

    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter sorted elements:\n ");
    for(int i=0; i<n; i++){
        scanf("%d", &arr[i]);
    }

    printf("Enter the sum X: ");
    scanf("%d", &X);

    findpairwithsum(arr, n, X);

    return 0;
}