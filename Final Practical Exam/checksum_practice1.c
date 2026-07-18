#include<stdio.h>
#define SIZE 4
void binaryAddition(int a[],int b[],int result[]){
    int carry = 0;
    for(int i = SIZE-1;i>=0;i--){
        int sum = a[i]+b[i]+carry;
        result[i] = sum%2;
        carry = sum/2;
    }
    while(carry){
        for(int i = SIZE-1;i>=0;i--){
            int sum = result[i]+carry;
            result[i] = sum%2;
            carry = sum/2;
            if(carry == 0){
                break;
            }
        }
    }
}
int main(){
    int i,j,n,error = 0;
    int data[n][SIZE];
    printf("\nEnter the number of groups present in the data : ");
    scanf("%d",&n);
    printf("\nEnter the databits of each group one by one ----\n");
    for(i=0;i<n;i++){
        for(j=0;j<SIZE;j++){
            scanf("%d",&data[i][j]);
        }
    }
    int sum[SIZE] = {0};
    for(i=0;i<n;i++){
        binaryAddition(sum,data[i],sum);
    }

    int checksum[SIZE] = {0};
    for(i=0;i<SIZE;i++){
        checksum[i] = 1 - sum[i];
    }

    printf("\n Checksum = ");
    for(i=0;i<SIZE;i++){
        printf("%d",checksum[i]);
    }

    int received[n+1][SIZE];
    printf("\n Enter the received data including the checksum bits :\n");
    for(i=0;i<n+1;i++){
        for(j=0;j<SIZE;j++){
            scanf("%d",&received[i][j]);
        }
    }
    int rsum[SIZE] = {0};
    for(i=0;i<n+1;i++){
        binaryAddition(rsum,received[i],rsum);
    }

    int rchecksum[SIZE] = {0};
    for(i=0;i<SIZE;i++){
        rchecksum[i] = 1-rsum[i];
    }

    for(i=0;i<SIZE;i++){
        if(rchecksum[i] != 0 ){
            error = 1;
            break;
        }
    }
    if(error == 1){
        printf("\nError Detected !!!\n");
    }
    else{
        printf("\nNo Error Detected...\n");
    }
    return 0;

}