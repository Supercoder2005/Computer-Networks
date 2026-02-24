#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAX_FRAMES 100

int window_size, total_frames;
int acked[MAX_FRAMES];   // To track acknowledged frames

/* Function to send a single frame */
void send_frame(int i) {
    printf("Sending Frame %d\n", i);
    sleep(1);
}

int main() {
    srand(time(0));

    printf("Enter the window size: ");
    scanf("%d", &window_size);

    printf("Enter total number of frames to send: ");
    scanf("%d", &total_frames);

    if (total_frames > MAX_FRAMES || window_size > total_frames) {
        printf("Invalid input! Window size must be <= total frames\n");
        return 1;
    }

    // Initialize all frames as not acknowledged
    for (int i = 0; i < total_frames; i++) {
        acked[i] = 0;
    }

    int base = 0;

    while (base < total_frames) {

        int end;
        if (base + window_size < total_frames)
            end = base + window_size;
        else
            end = total_frames;

        /* Send frames in window which are not yet acknowledged */
        for (int i = base; i < end; i++) {
            if (acked[i] == 0) {
                send_frame(i);

                /* Simulate random loss */
                int lost = rand() % 2;   // 0 or 1

                if (lost == 0) {
                    printf("ACK received for Frame %d\n", i);
                    acked[i] = 1;
                } else {
                    printf("Frame %d lost! Will resend later\n", i);
                }
            }
        }

        /* Slide window only if base frame is acknowledged */
        while (base < total_frames && acked[base] == 1) {
            base++;
        }

        printf("\n");
    }

    printf("All frames sent successfully using Selective Repeat\n");
    return 0;
}