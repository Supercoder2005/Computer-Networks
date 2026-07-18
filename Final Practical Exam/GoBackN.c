#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

#define TIMEOUT 2
#define MAX_FRAMES 100 

void send_frame(int start,int end){
    for(int i=start;i<end;i++){
        printf("\nSender : Sending frame %d",i);
    }
}

int main(){
    int window_size,total_frames;
    printf("\nEnter the size of the window : ");
    scanf("%d",&window_size);
    printf("\nEnter total number of frames to send : ");
    scanf("%d",&total_frames);

    if(total_frames>MAX_FRAMES || window_size>total_frames){
        printf("\nInvalid Input ... window size must be less than equal to total number of frames");
        return 1;
    }

    srand(time(NULL));
    int base = 0; // oldest unacknowledged frame
    int end;

    while(base<total_frames){ // loop will run untill all the frames are acknowledged
        // fix the window size
        if(base + window_size < total_frames){
            end = base+window_size;
        }
        else{
            end = total_frames;
        }

        // current window size
        printf("\nCurrent window size : [%d to %d]\n",base,end-1);

        // Sending frames of a particular window 
        send_frame(base,end);
        sleep(TIMEOUT); // after sending a frame wait for timeout time to receive the ACK

        // generating random errors
        int event = rand()%3;
        // event = 0 --> no frame lost or ACK lost 
        // event = 1 --> frame lost
        // event = 2 --> ACK lost
        if(event == 0){
            printf("\nReceiver : All frames received successfully.");
            base = end; // slide the window completely
        }
        else if(event == 1){
            int lost_frame = base + (rand()%(end-base));
            printf("\nReceiver : Frame lost for frame %d",lost_frame);
            printf("\nSender : Resending from frame %d",lost_frame);
            base = lost_frame;
        }
        else{
            printf("\nReceiver : All frames received successfully.");
            printf("\nSender : ACK lost for frame %d",base);
            printf("\nSender : Resending from frame %d",base);
        }
    }
    printf("\nAll the frames transmitted from sender to the receiver successfully.\n");
    return 0;
}