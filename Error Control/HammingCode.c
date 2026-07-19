#include <stdio.h>
#include <math.h>

int main()
{
    int data[20], ham[30];
    int i, j, m, r = 0, n, k;
    int parity, error = 0;

    // Input number of data bits
    printf("Enter number of data bits: ");
    scanf("%d", &m);

    // Input data bits
    printf("Enter data bits:\n");
    for(i = 0; i < m; i++)
        scanf("%d", &data[i]);

    // Find number of parity bits
    while(pow(2, r) < (m + r + 1))
        r++;

    n = m + r;

    // Place data and parity bits
    k = m - 1;
    int p = 0;

    for(i = 1; i <= n; i++)
    {
        if(i == pow(2, p))
        {
            ham[i] = 0;
            p++;
        }
        else
        {
            ham[i] = data[k];
            k--;
        }
    }

    // Calculate parity bits
    for(i = 0; i < r; i++)
    {
        int pos = pow(2, i);
        parity = 0;

        for(j = 1; j <= n; j++)
        {
            if(j & pos)
                parity ^= ham[j];
        }

        ham[pos] = parity;
    }

    // Display Hamming code
    printf("\nHamming Code: ");

    for(i = n; i >= 1; i--)
        printf("%d", ham[i]);

    // Receiver side
    printf("\n\nEnter received Hamming Code:\n");

    for(i = n; i >= 1; i--)
        scanf("%d", &ham[i]);

    // Find error position
    error = 0;

    for(i = 0; i < r; i++)
    {
        int pos = pow(2, i);
        parity = 0;

        for(j = 1; j <= n; j++)
        {
            if(j & pos)
                parity ^= ham[j];
        }

        if(parity)
            error += pos;
    }

    // Check and correct error
    if(error == 0)
    {
        printf("\nNo Error Detected.\n");
    }
    else
    {
        printf("\nError at Position %d\n", error);

        ham[error] ^= 1;

        printf("Corrected Code: ");

        for(i = n; i >= 1; i--)
            printf("%d", ham[i]);
    }

    return 0;
}