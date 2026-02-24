#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

#define MAX_FRAMES 100
#define TIMEOUT 2

int main(){
    int window_size,total_frames;
    printf("\n Enter the window size :");
    scanf("%d",&window_size);
    printf("\n Enter no of frames to send :");
    scanf("%d",&total_frames);
    if(total_frames > MAX_FRAMES || window_size > total_frames){
        printf("\n Invalid Input !");
        return 1;
    }

    srand(time(NULL));
    int ack[MAX_FRAMES] = {0}; // sender side ACK tracking ( 0 --> not acknowledged , 1 ---> acknowledged)
    int received[MAX_FRAMES] = {0}; // receiver side buffer ( stores received frames )

    int base = 0; // oldest unacknowledged frame 
    int end;
    printf("\n\n -------- Selective Repeat ARQ --------\n");
    // loop will run untill all frames are acknowledged
    while(base < total_frames){

        // window size fixing 
        if(base+window_size < total_frames){
            end = base+window_size;
        }
        else{
            end = total_frames;
        }
        printf("\n Current Window : [%d to %d]\n",base,end-1);
        // sending frames
        for(int i=base;i<end;i++){
            if(ack[i] == 0){ // frame will send only when it is not acknowledgegd
                printf("\n Sender : Sending frame %d",i);
                sleep(TIMEOUT);

                int event = rand() % 3;
                // successful 
                if(event == 0){
                    printf("\n Receiver : Frame %d received",i);
                    received[i] = 1;
                    printf("\n Receiver : ACK sent for frame %d",i);
                    printf("\n Sender : ACK received for frame %d\n",i);
                    ack[i] = 1;
                }
                // frame lost
                else if(event == 1){
                    printf("\n Receiver : Frame lost for frame %d",i);
                    printf("\n Sender : Will resend frame %d\n",i);
                }
                // ACK lost
                else{
                    printf("\n Receiver : Received frame %d",i);
                    received[i] = 1;
                    printf("\n Receiver : ACK sent for frame %d",i);
                    printf("\n Sender : ACK lost for frame %d",i);
                    printf("\n Sender : Will resend frame %d\n",i);
                }
            }
        }
        // Slide sender window only when base frame is acknowledged 
        while(base < total_frames && ack[base] == 1){
            base ++;
        }
    }
    printf("\n All frames transmitted successfully");
    return 0;
}