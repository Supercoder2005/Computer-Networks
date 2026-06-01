#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

#define MAX_FRAMES 100
#define TIMEOUT 2 

void send(int start,int end){
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

    if(total_frames > MAX_FRAMES || window_size > total_frames){
        printf("\nInvalid input !!!");
        return 1;
    }

    srand(time(NULL));
    int base = 0; // oldest unacknowledged frame
    int end; // end of the window 

    while(base < total_frames){
        // fix window size
        if(base + window_size < total_frames){
            end = base + window_size;
        }
        else{
            end = total_frames;
        }

        // print the current window
        printf("\nCurrent window is from [%d to %d]\n",base,end-1);

        // Sender side : sending frames of current window 
        send(base,end);
        sleep(TIMEOUT);

        // generating random errors and 3 cases 
        int event = rand()%3;
        // event 0 : all ok transmission successfull
        // event 1 : frame lost
        // event 2 : ack lost
        if(event == 0){
            printf("\nReceiver : All frames received successfully.");
            printf("\nSender : All frames acknowledged successfully.\n");
            base = end;
        }
        if(event == 1){
            int lost_frame = base + (rand()%(end-base));
            printf("\nReceiver : Frame lost, for frame %d",lost_frame);
            printf("\nSender : Will resend from frame %d\n",lost_frame);
            base = lost_frame;
        }
        if(event == 2){
            printf("\nReceived : All frames received successfully.");
            printf("\nSender : ACK lost for frame %d",base);
            printf("\nSender : will resend from frame %d\n",base);
        }
    }
    printf("\nAll frames transmitted successfully\n");
    return 0;    
}