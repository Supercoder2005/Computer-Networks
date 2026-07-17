#include<stdio.h>

void xor(int temp[],int divisor[],int start,int m){
    for(int i=0;i<m;i++){
        temp[start + i] ^= divisor[i];
    }
}

int main(){
    int data[20], divisor[20], temp[50], receive[50];
    int n,m,i,error = 0;

    // input taking for data
    printf("\nEnter the number of data bits : ");
    scanf("%d",&n);
    printf("\nEnter the databits : \n");
    for(i=0;i<n;i++){
        scanf("%d",&data[i]);
        temp[i] = data[i];
    }

    // input taking for divisor
    printf("\nEnter the number of divisor bits : ");
    scanf("%d",&m);
    printf("\nEnter the divisor bits : \n");
    for(i=0;i<m;i++){
        scanf("%d",&divisor[i]);
    }

    // append (divisior bits - 1) number of zeros at the end of databits
    for(i=n;i<n+m-1;i++){
        temp[i] = 0;
    }

    // Sender side CRC division
    for(i=0;i<n;i++){
        if(temp[i] == 1){
            xor(temp,divisor,i,m);
        }
    }
    
    // Sender side CRC bits
    printf("\nSender side CRC bits :");
    for(i=n;i<n+m-1;i++){
        printf("%d",temp[i]);
    }

    // Transmitted data
    printf("\nTransmitted Data : ");
    for(i=0;i<n;i++){
        printf("%d",data[i]);
    }
    for(i=n;i<n+m-1;i++){
        printf("%d",temp[i]);
    }

    // Receiver side 
    printf("\n-----------Receiver--------------\n");
    printf("\nEnter the received codeword (%d bits) :\n",n+m-1);

    for(i=0;i<n+m-1;i++){
        scanf("%d",&receive[i]);
    }
    // Receiver CRC calculation
    for(i=0;i<n;i++){
        if(receive[i] == 1){
            xor(receive,divisor,i,m);
        }
    }

    // check the remainder 
    for(i=n;i<n+m-1;i++){
        if (receive[i] !=0 ){
            error = 1;
            break;
        }
    }
    if(error == 0){
        printf("\nNo error detected.\n");
    }
    else{
        printf("\nError detected.\n");
    }
    return 0;
}