#include<stdio.h>
int main(){
    int n,i;
    printf("\nEnter the number of databits :");
    scanf("%d",&n);
    int data[n];
    int transmitted[n+1];
    int received[n+1];
    int parity = 0;
    // Sender side
    for(i=0;i<n;i++){
        printf("\nEnter databit no %d : ",i+1);
        scanf("%d",&data[i]);
        transmitted[i] = data[i];
        parity ^= data[i];
    }
    int choice;
    printf("\nWhat do you want ? (0 - Even parity or 1 -Odd parity) : ");
    scanf("%d",&choice);
    if(choice == 0){
        printf("\nEven parity bit = %d",parity);
    }
    else if(choice == 1){
        parity = 1-parity;
        printf("\nOdd parity bit = %d",parity);
    }
    // Transmitted data = databits + paritybit
    transmitted[n] = parity;
    printf("\nTransmitted data : ");
    for(i=0;i<=n;i++){
        printf("%d",transmitted[i]);
    }
    // Receiver side
    int rparity = 0;
    printf("\nEnter the received data along with the parity bit:");
    for(i=0;i<=n;i++){
        printf("\nEnter received data %d:",i+1);
        scanf("%d",&received[i]);
        rparity ^= received[i];
    }
    if(rparity == 0){
        printf("\nNo Error Detected !");
    }
    else{
        printf("\nError Detected!!!");
    }
    return 0;
}