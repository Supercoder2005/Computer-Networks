#include<stdio.h>
void xor(int temp[],int divisor[],int start, int m){
    for(int i=0;i<m;i++){
        temp[start+i]^=divisor[i];
    }
}
int main(){
    int data[20],divisor[20],temp[50],receive[50];
    int n,m,i,error = 0;
    //taking the input data
    printf("\nEnter the number of databits : ");
    scanf("%d",&n);
    printf("\nEnter the databits : \n");
    for(i=0;i<n;i++){
        scanf("%d",&data[i]);
        temp[i] = data[i];
    }
    //taking the input divisor
    printf("\nEnter the number of divisor-bits : ");
    scanf("%d",&m);
    printf("\nEnter the divisor-bits : \n");
    for(i=0;i<m;i++){
        scanf("%d",&divisor[i]);
    }
    //Appending (m-1) no of zeros after the data to generate the codeword
    for(i=n;i<n+m-1;i++){
        temp[i] = 0;
    }
    //Sender side CRC calculation
    for(i=0;i<n;i++){
        if(temp[i] == 1){
            xor(temp,divisor,i,m);
        }
    }
    //showing the sender side's calculated CRC bits
    printf("\nThe CRC bits generated at the sender side : ");
    for(i=n;i<n+m-1;i++){
        printf("%d",temp[i]);
    }
    //transmitted data from sender to receiver
    printf("\nTransmitted data from sender to the receiver :\n");
    for(i=0;i<n;i++){
        printf("%d",data[i]);
    }
    for(i=n;i<n+m-1;i++){
        printf("%d",temp[i]);
    }

    // Receiver Side
    printf("\nEnter the received data : \n");
    for(i=0;i<n+m-1;i++){
        scanf("%d",&receive[i]);
    }
    // calculate the receiver side CRC
    for(i=0;i<n;i++){
        if(receive[i]==1){
            xor(receive,divisor,i,m);
        }
    }

    // checking the remainder/CRC bit of the receiver
    for(i=n;i<n+m-1;i++){
        if(receive[i] != 0){
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