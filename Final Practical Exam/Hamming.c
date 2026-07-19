#include<stdio.h>
#include<math.h>

int main(){
    int data[20],ham[50]; // ham[] stores the code word = databits + paritybits
    int i,j,m,n,k,r=0; // m = total databits , r = total parity bits, n = total bits on the code word (m+r)
    int parity,error = 0; // parity stores the value of parity bit of corresponding position

    // input 
    printf("\nEnter the number of databits : ");
    scanf("%d",&m);
    printf("\nEnter the databits : \n");
    for(i=0;i<m;i++){
        scanf("%d",&data[i]);
    }
    // calculating the number of parity bits using 2^r>=(m+r+1) formula
    while(pow(2,r)<(m+r+1)){
        r++;
    }
    n = m + r;

    // place the databits and paritybits in their corresponding positions on the ham[] array
    k = m - 1; // to track databits 
    int p = 0; // to track the paritybits

    // positions : 1   2   3   4   5    6   7
    // codewords : r1  r2  d3  r3  d2  d1   d0
    for(i=1;i<=n;i++){
        if(i == pow(2,p)){
            ham[i] = 0; // fill the parity positions with 0 initially
            p++;
        }
        else{
            ham[i] = data[k];
            k--;
            // fill the data in reverse order: data[3]   data[2]    data[3]
        }
    }

    // calculate paritybits r1,r2,r3
    for(i=0;i<r;i++){
        int pos = pow(2,i); // pos means the position of each parity bit r1,r2,r3
        parity = 0;

        for(j=1;j<=n;j++){
            if(j & pos){ // bitwise and operation
                parity ^= ham[j];
            }
        }
        ham[pos] = parity;
    }

    // display the hamming code by reversing the ham[] array
    printf("\nHamming Code : ");
    for(i=n;i>=1;i--){
        printf("%d",ham[i]);
    }

    // Receiver side -- > stores the user input received code word in the ham[] also in reversed order
    printf("\nEnter the received hamming code : ");
    for(i=n;i>=1;i--){
        scanf("%d",&ham[i]);
    }

    // find the error position
    for(i=0;i<r;i++){
        int pos = pow(2,i);
        parity = 0;

        for(j=1;j<=n;j++){
            if(j & pos){
                parity ^= ham[j];
            }
        }
        
        if(parity){
            error += pos; // error will stores the position of the errorneous parity bits
        }
    }

    // check and correct error
    if(error == 0){
        printf("\nNo Error Detected.\n");
    }
    else{
        printf("\nError Detected at Position %d\n",error);
        ham[error] ^= 1; // XOR operation will flip the error bit's value

        printf("\nCorrected Code : ");
        for(i=n;i>=1;i--){
            printf("%d",ham[i]);
        }
    }
    return 0;
}