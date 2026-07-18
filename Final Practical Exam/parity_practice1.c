#include<stdio.h>
int main(){
    int i,n;
    int parity = 0;
    printf("\nEnter the number of databits : ");
    scanf("%d",&n);

    int data[n],transmitted[n+1];
    printf("\nEnter the databits : \n");
    for(i=0;i<n;i++){
        scanf("%d",&data[i]);
        transmitted[i] = data[i];
    }
    //even parity calculation of sender side
    for(i=0;i<n;i++){
        parity ^= data[i];
    }
    printf("\nGenerated even parity bit for the sender side = %d",parity);
    transmitted[n] = parity;
    // receiver
    int received[n+1];
    printf("\nEnter the received bits along with the parity bit also : \n");
    for(i=0;i<=n;i++){
        scanf("%d",&received[i]);
    }
    int rparity = 0;
    for(i=0;i<=n;i++){
        rparity ^= received[i];
    }
    if(rparity == 0){
        printf("\nNo Error Detected !!!");
    }
    else{
        printf("\nError Detected !!!");
    }
    return 0;
}
