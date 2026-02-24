#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>

#define TIMEOUT 2
#define MAX_FRAMES 100 

void send_frames(int start,int end){
    for(int i=start;i<end;i++){
        printf("\n Sender : Sending Frame %d",i);
    }
}

int main(){
    int window_size,total_frames;
    printf("\n Enter the window size :");
    scanf("%d",&window_size);
    printf("\n Enter the no of frames to send :");
    scanf("%d",&total_frames);

    if(total_frames>MAX_FRAMES || window_size>total_frames){
        printf("\n Invalid Input !!! Window size must be less than or equal to total frames\n");
        return 1;
    }

    srand(time(NULL)); //seed random function with current time as starting point for generating random numbers 
    int base = 0;     // oldest unacknowledged frame 
    int end;         // end of the window 

    printf("\n ------------ Go-Back-N ARQ Simulation ---------------\n");
    while(base < total_frames){ // loop will run untill all frames are acknowledged (base = total_frames --> all frames are acknowledged)
        // Fix window size 
        if(base + window_size < total_frames){
            end = base + window_size;
        }
        else{
            end = total_frames;
        }

        printf("\nCurrent window : [%d to %d]\n",base,end-1);

        // Sending frames of a particular window
        send_frames(base,end);
        sleep(TIMEOUT); // after sending waiting for timeout time for receiving ack

        // Random error generation :
        int event = rand()%3;
        // event = 0 ---> success (no frame lost , no ack lost)
        // event = 1 ---> frame lost (sender sends but in the path frame lost)
        // event = 2 ---> ack lost (receiver sends ack but in the path it losts)
        if(event == 0){
            printf("\n Receiver : All frames received successfully");
            printf("\n Sender : ACK received for frames %d to %d\n",base,end-1);
            base = end; // slide window completely
        }
        else if(event == 1){
            int lost_frame = base + (rand() % (end-base));
            printf("\n Receiver : Frame lost for frame %d",lost_frame);
            printf("\n Sender : Resending from frame %d\n",lost_frame);
            base = lost_frame; // Go back to lost frame
        }
        else{
            printf("\n Receiver : All frames received");
            printf("\n Sender : ACK lost for frame %d",base);
            printf("\n Sender : Resending from frame %d",base);
        }
    }
    printf("\n All frames sent successfully\n");
    return 0;
}