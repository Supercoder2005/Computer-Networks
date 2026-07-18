#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

#define TIMEOUT 2
#define MAX_FRAMES 100

int main(){
    int window_size,total_frames;
    printf("\nEnter the size of the window :");
    scanf("%d",&window_size);
    printf("\nEnter total number of frames to send :");
    scanf("%d",&total_frames);
    
    if(total_frames > MAX_FRAMES || window_size > total_frames){
        printf("\nInvalid input !!!\n");
        return 1;
    }

    srand(time(NULL));
    int acked[MAX_FRAMES] = {0}; // sender size buffer to track acknowledged frames 
    int received[MAX_FRAMES] = {0}; // receiver side buffer to store received frames

    int base = 0; // oldest unacknowledged frame
    int end;
    int delivered = 0; 

    // loop will continue untill all frames are acknowledged
    while(base<total_frames){
        // fix the window size
        if(base + window_size < total_frames){
            end = base + window_size;
        }
        else{
            end = total_frames;
        }
        // currrent window size
        printf("\nCurrent window size : [%d to %d]\n",base,end-1);
        // Sender sending the frame
        for(int i=base;i<end;i++){
            //send only unacknowledged frames
            if(acked[i] == 0){
                printf("\nSender : Sending frame %d\n",i);
                sleep(TIMEOUT);
                // random error generator
                int event = rand()%3;
                //success
                if(event == 0){
                    printf("\nReceiver : Frame %d received successfully.",i);
                    received[i] = 1;
                    printf("\nReceiver : ACK sent for frame %d",i);
                    printf("\nSender : ACK received for frame %d\n",i);
                    acked[i] = 1;
                }
                // frame lost
                else if(event == 1){
                    printf("\nReceiver : Frame lost for frame %d",i);
                    printf("\nSender : Will resend frame %d\n",i);
                }
                // ACK lost
                else{
                    printf("\nReceiver : Frame %d received successfully",i);
                    received[i] = 1;
                    printf("\nReceiver : ACK sent for frame %d",i);
                    printf("\nSender : ACL lost for frame %d",i);
                    printf("\nSender : Will resend frame %d\n",i);
                }
            }
        }
        // slide the window
        while(base<total_frames && acked[base]==1){
            base++;
        }
        // Deliver the frames in correct order
        while(delivered<total_frames && received[delivered]==1){
            printf("\nReceiver :Frame %d delivered in order\n",delivered);
            delivered++;
        }
    }
    if(delivered == total_frames){
        printf("\nAll frames transmitted and delivered successfully from sender to the receiver\n");
    }
    return 0;
}
