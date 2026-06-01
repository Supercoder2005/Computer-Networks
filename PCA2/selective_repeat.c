#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

#define MAX_FRAMES 100
#define TIMEOUT 2

int main(){
    int window_size,total_frames;
    printf("\nEnter the window size :");
    scanf("%d",&window_size);
    printf("\nEnter number of frames to send :");
    scanf("%d",&total_frames);
    if(total_frames > MAX_FRAMES || window_size > total_frames){
        printf("\nInvalid input !");
        return 1;
    }
    srand(time(NULL));
    int ack[MAX_FRAMES] = {0}; // sender side ACK tracking ( 0 : not acknowledged, 1 : acknowledged)
    int received[MAX_FRAMES] = {0}; // receiver side array : stored received frames

    int base = 0 ; // oldest unacknowledged frame 
    int end;

    // loop will run untill all frames are acknowledged
    while(base < total_frames){

        // window size fixed
        if(base+window_size < total_frames){
            end = base + window_size;
        }
        else{
            end = total_frames;
        }

        printf("\nCurrent Window : [%d to %d]\n",base,end-1);

        // sending frames
        for(int i=base;i<end;i++){
            if(ack[i] == 0){//frame will be send only when it is not acknowledged
                printf("\n Sender : Sending frame %d",i);
                sleep(TIMEOUT);

                int event = rand()%3;
                // Successfull
                if(event == 0){
                    printf("\nReceiver : Frame %d received",i);
                    received[i] = 1;
                    printf("\nReceiver : ACK sent for frame %d",i);
                    printf("\nSender : ACK received for frame %d\n",i);
                    ack[i] = 1;
                }
                // Frame lost
                else if(event == 1){
                    printf("\nReceiver : Frame %d not received, frame lost",i);
                    printf("\nSender : Will resend the frame %d\n",i);

                }
                // ACK lost
                else{
                    printf("\nReceiver : Frame %d received",i);
                    received[i] = 1;
                    printf("\nReceiver : ACK sent for frame %d",i);
                    printf("\nSender : ACK lost for frame %d",i);
                    printf("\nSender : Will resend the frame %d\n",i);
                }
            }
        }
        // slide sender window only when base frame is acknowledged 
        while(base < total_frames && ack[base]==1){
            base++;
        }
    }
    printf("\nAll frames transmitted successfully.\n");
    return 0;
}