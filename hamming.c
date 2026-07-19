#include<stdio.h>
#include<math.h>

int main(){
    int data[20],ham[50];
    int i,j,m,n,k,r=0;
    int parity, error = 0;
    printf("\nEnter the number of databits : ");
    scanf("%d",&m);
    printf("\nEnter the databits :\n");
    for(i=0;i<m;i++){
        scanf("%d",&data[i]);
    }
    while(pow(2,r)<r+m+1){
        r++;
    }
    n = m+r;
    k = m-1;
    int p = 0;
    for(i=1;i<=n;i++){
        if(i == pow(2,p)){
            ham[i] = 0;
            p++;
        }
        else{
            ham[i] = data[k];
            k--;
        }
    }
    parity = 0;
    for(i=0;i<r;i++){
        int pos = pow(2,i);
        for(j=1;j<=n;j++){
            if(j & pos){
                parity ^= ham[j];
            }
        }
        ham[pos] = parity;
    }


    printf("\nHamming Code : ");
    for(i=n;i>=1;i--){
        printf("%d",ham[i]);
    }

    printf("\nEnter the received hamming code :\n");
    for(i=n;i>=1;i--){
        scanf("%d",&ham[i]);
    }

    for(i=0;i<r;i++){
        int pos = pow(2,i);
        parity = 0;
        for(j=1;j<=n;j++){
            if(j & pos){
                parity ^= ham[j];
            }
        }
        if(parity){
            error += pos;
        }
    }
    if(error == 0){
        printf("\nNo Error Detected.");
    }
    else{
        printf("\nError detected at position : %d",error);
        ham[error] ^= 1;
        printf("\nCorrected hamming code : ");
        for(i=n;i>=1;i--){
            printf("%d",ham[i]);
        }
    }
    return 0;
}