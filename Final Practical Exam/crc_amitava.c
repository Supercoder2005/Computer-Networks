#include <stdio.h>

void xor(int temp[], int divisor[], int start, int m)
{
    int i;

    for(i = 0; i < m; i++)
        temp[start + i] ^= divisor[i];
}

int main()
{
    int data[20], divisor[20], temp[30], receive[30];
    int n, m, i, error = 0;

    printf("Enter number of data bits: ");
    scanf("%d", &n);

    printf("Enter data bits:\n");
    for(i = 0; i < n; i++)
    {
        scanf("%d", &data[i]);
        temp[i] = data[i];
    }

    printf("Enter number of divisor bits: ");
    scanf("%d", &m);

    printf("Enter divisor bits:\n");
    for(i = 0; i < m; i++)
        scanf("%d", &divisor[i]);

    // Append zeros
    for(i = n; i < n + m - 1; i++)
        temp[i] = 0;

    // Sender CRC Division
    for(i = 0; i < n; i++)
    {
        if(temp[i] == 1)
            xor(temp, divisor, i, m);
    }

    printf("\nCRC Bits: ");
    for(i = n; i < n + m - 1; i++)
        printf("%d", temp[i]);

    printf("\nTransmitted Data: ");
    for(i = 0; i < n; i++)
        printf("%d", data[i]);
    for(i = n; i < n + m - 1; i++)
        printf("%d", temp[i]);

    // ---------------- Receiver ----------------

    printf("\n\n----- Receiver -----\n");
    printf("Enter the received codeword (%d bits):\n", n + m - 1);

    for(i = 0; i < n + m - 1; i++)
        scanf("%d", &receive[i]);

    // Receiver CRC Division
    for(i = 0; i < n; i++)
    {
        if(receive[i] == 1)
            xor(receive, divisor, i, m);
    }

    // Check remainder
    for(i = n; i < n + m - 1; i++)
    {
        if(receive[i] != 0)
        {
            error = 1;
            break;
        }
    }

    if(error == 0)
        printf("\nNo Error Detected.\n");
    else
        printf("\nError Detected.\n");

    return 0;
}