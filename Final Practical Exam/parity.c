#include<stdio.h>
int main(){
    int n,i;
    int parity = 0;
    printf("\nEnter the number of databits : ");
    scanf("%d",&n);
    int data[n];
    int transmitted[n+1]; // as transmitted codeword = databits + paritybit
    int received[n+1]; // transmitted data will be received at the receiver end

    // sender side
    printf("\nEnter databits : \n");
    for(i=0;i<n;i++){
        scanf("%d",&data[i]);
        transmitted[i] = data[i];

        // generate even parity bit using XOR 
        parity ^= data[i];
    }

    transmitted[n] = parity; //even parity bit
    printf("\nEven parity bit = %d",parity);

    printf("\nTransmitted Data : ");
    for(i=0;i<n+1;i++){
        printf("%d",transmitted[i]);
    }

    // Receiver side
    printf("\nEnter the received databits (including parity bit) : ");
    for(i=0;i<n+1;i++){
        scanf("%d",&received[i]);
    }
    // checking receiver side parity bit 
    parity = 0;
    for(i=0;i<=n;i++){
        parity ^= received[i];
    }

    if(parity == 0){
        printf("\nNo error detected.");
    }
    else{
        printf("\nError detected.");
    }
    return 0;
}