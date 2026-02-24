#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

#define MAX_FRAMES 100
#define TIMEOUT 2

int main(){

    int window_size, total_frames;
    int ack[MAX_FRAMES] = {0};   // 0 = not acknowledged, 1 = acknowledged

    printf("\n Enter window size: ");
    scanf("%d", &window_size);

    printf(" Enter total number of frames: ");
    scanf("%d", &total_frames);

    if(total_frames > MAX_FRAMES || window_size > total_frames){
        printf("\n Invalid Input! Window size must be <= total frames.\n");
        return 1;
    }

    srand(time(NULL));

    int base = 0;
    int end;

    printf("\n\n -------- Selective Repeat ARQ Simulation --------\n");

    while(base < total_frames){

        // Set window range
        if(base + window_size < total_frames)
            end = base + window_size;
        else
            end = total_frames;

        printf("\n\n Current Window: [%d to %d]\n", base, end-1);

        // Send frames in current window
        for(int i = base; i < end; i++){

            if(!ack[i]){

                printf("Sender: Sending Frame %d\n", i);

                // Simulate transmission delay
                sleep(TIMEOUT);

                if(rand() % 2 == 0){
                    printf("Receiver: Frame %d received\n", i);
                    printf("Sender: ACK received for Frame %d\n\n", i);
                    ack[i] = 1;
                }
                else{
                    printf("Receiver: Frame %d lost!\n", i);
                    printf("Sender: Frame %d, will retransmit\n\n", i);
                }
            }
        }

        // Slide window only if base frame is acknowledged
        while(base < total_frames && ack[base]){
            base++;
        }
    }

    printf("\n All frames transmitted and acknowledged successfully.\n");

    return 0;
}