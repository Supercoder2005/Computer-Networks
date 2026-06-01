#include<stdio.h>
#define SIZE 4

void add(int a[],int b[],int result[]){
    // binary addition
    int carry = 0;
    for(int i = SIZE-1; i>=0; i--){
        int sum = a[i] + b[i] + carry;
        result[i] = sum%2;
        carry = sum/2;
    }
    // End carry wrapping
    while(carry){
        for(int i = SIZE-1; i>=0; i--){
            int sum = result[i] + carry;
            result[i] = sum%2;
            carry = sum/2;

            if(carry==0){
                break;
            }
        }
    }
}

int main(){
    int n;
    printf("\n Enter the number of groups :");
    scanf("%d",&n);
    int data[n][SIZE];
    printf("\nEnter %d-bit groups :",SIZE);
    for(int i=0;i<n;i++){
        for(int j=0;j<SIZE;j++){
            scanf("%d",&data[i][j]);
        }
    }

    // Sender side
    int sum[SIZE] = {0};
    for(int i=0;i<n;i++){
        add(sum,data[i],sum);
    }
    int checksum[SIZE];
    printf("\nChecksum = ");
    for(int i=0;i<SIZE;i++){
        checksum[i] = 1-sum[i]; // complement
        printf("%d",checksum[i]);
    }

    // Receiver side
    int received[n+1][SIZE];
    printf("\nEnter received groups including checksum:");
    for(int i=0;i<n+1;i++){
        for(int j=0;j<SIZE;j++){
            scanf("%d",&received[i][j]);
        }
    }
    int rsum[SIZE] = {0};
    for(int i=0;i<n+1;i++){
        add(rsum,received[i],rsum);
    }
    int rchecksum[SIZE] = {0};
    printf("\nReceived data's checksum = ");
    for(int i=0;i<SIZE;i++){
        rchecksum[i] = 1-rsum[i];
        printf("%d",rchecksum[i]);
    }

    int error = 0;
    for(int i=0;i<SIZE;i++){
        if(rchecksum[i] != 0){
            error = 1;
            break;
        }
    }
    if(error){
        printf("\nError Detected!");
    }
    else{
        printf("\nNo Error Detected.");
    }

    return 0;
}