#include<stdio.h>
int main(){
    int n,i;
    int parity = 0;

    printf("\nEnter the no of data bits:");
    scanf("%d",&n);

    int data[n];
    int transmitted[n+1]; // as (transmitted data = databits + paritybit)
    int received[n+1]; // transmitted data will be received at receiver end

    // Sender side
    printf("Enter data bits: ");
    for(i=0;i<n;i++){
        scanf("%d",&data[i]);
        transmitted[i] = data[i];

        // generate even parity bit using XOR
        parity ^= data[i];
    }

    transmitted[n] = parity; // even parity bit
    printf("\nEven parity bit = %d",parity);

    printf("\n Transmitted Data :");
    for(i=0;i<=n;i++){
        printf("%d",transmitted[i]);
    }

    // Receiver side
    printf("\n Enter received bits (including parity bit) :");
    for(i=0;i<=n;i++){
        scanf("%d",&received[i]);
    }
    // check parity using XOR
    parity = 0;
    for(i=0;i<=n;i++){
        parity ^= received[i];
    }

    if(parity == 0){
        printf("\nNo Error Detected.");
    }
    else{
        printf("\n Error Detected");
    }

    return 0;
    
}