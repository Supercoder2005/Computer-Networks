#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAX_FRAMES 100

int window_size, total_frames;
int acked[MAX_FRAMES];        // Sender side ACK tracking
int received[MAX_FRAMES];     // Receiver buffer
int delivered = 0;            // Next frame to deliver in order

/* Send a frame */
void send_frame(int i) {
    printf("Sender: Sending Frame %d\n", i);
    sleep(1);
}

int main() {

    srand(time(0));

    printf("Enter window size: ");
    scanf("%d", &window_size);

    printf("Enter total number of frames: ");
    scanf("%d", &total_frames);

    if (total_frames > MAX_FRAMES || window_size > total_frames) {
        printf("Invalid input!\n");
        return 1;
    }

    // Initialize arrays
    for (int i = 0; i < total_frames; i++) {
        acked[i] = 0;
        received[i] = 0;
    }

    int base = 0;

    printf("\n------ Selective Repeat ARQ with Buffering ------\n\n");

    while (base < total_frames) {

        int end = (base + window_size < total_frames) 
                  ? base + window_size 
                  : total_frames;

        printf("Current Sender Window: [%d to %d]\n", base, end - 1);

        for (int i = base; i < end; i++) {

            if (acked[i] == 0) {

                send_frame(i);

                int event = rand() % 3;
                /*
                    0 → Success
                    1 → Frame Lost
                    2 → ACK Lost
                */

                if (event == 0) {
                    // Success
                    printf("Receiver: Frame %d received\n", i);
                    received[i] = 1;

                    printf("Receiver: ACK sent for Frame %d\n", i);
                    printf("Sender: ACK received for Frame %d\n\n", i);

                    acked[i] = 1;
                }
                else if (event == 1) {
                    // Frame Lost
                    printf("Receiver: Frame %d lost in channel\n", i);
                    printf("Sender: Timeout for Frame %d\n", i);
                    printf("Sender: Will resend Frame %d\n\n", i);
                }
                else {
                    // ACK Lost
                    printf("Receiver: Frame %d received\n", i);
                    received[i] = 1;

                    printf("Receiver: ACK sent for Frame %d\n", i);
                    printf("Sender: ACK lost for Frame %d\n", i);
                    printf("Sender: Timeout for Frame %d\n", i);
                    printf("Sender: Will resend Frame %d\n\n", i);
                }
            }
        }

        /* Slide sender window */
        while (base < total_frames && acked[base] == 1) {
            base++;
        }

        /* Deliver frames in order from receiver buffer */
        // while (delivered < total_frames && received[delivered] == 1) {
        //     printf("Receiver: Delivering Frame %d to upper layer\n", delivered);
        //     delivered++;
        // }
        /* Deliver frames in correct order */

        printf("Receiver: Checking for in-order delivery...\n");

        while (delivered < total_frames && received[delivered] == 1) {
            printf("Receiver: Frame %d delivered\n", delivered);
            delivered++;
        }

        printf("\n");
    }

    printf("All frames transmitted and delivered successfully.\n");

    return 0;
}