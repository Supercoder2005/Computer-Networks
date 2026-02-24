#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>

#define TIMEOUT 2
#define MAX_FRAMES 100 

void send_frames(int start,int end){
    for(int i=start;i<end;i++){
        printf("\n Sending Frame %d",i);
    }
}

int main(){
    int window_size,total_frames;
    printf("\n Enter the size of the window :");
    scanf("%d",&window_size);
    printf("\n Enter the no of frames to send :");
    scanf("%d",&total_frames);
    
    srand(time(NULL));
    int base = 0; // oldest unacknowledged frame of the window
    int end;     // end of the window

    if(total_frames>MAX_FRAMES || window_size>total_frames){
        printf("\n Invalid Input !!! Window size must be less than or equal to toal frames...");
        return 1;
    }

    while(base < total_frames){ // loop will run untill all frames are acknowledged (base = total_frames --> all frames are acknowledged)
        // fitting the window size 
        if(base + window_size < total_frames){
            end = base + window_size;
        }
        else{
            end = total_frames;
        }

        // send frames of the current window 
        send_frames(base,end);
        // waiting for acknowledgement for timeout time
        sleep(TIMEOUT);

        // generate loss --> partiall acknowledgement 
        int ack = base + (rand() % ((end-base)+1));
        // when all the frames of the current window are acknowledged
        if(ack>=end){
            printf("\n All frames are acknowledged ...");
            base = ack;
        }
        else{
            printf("\n Ack lost or frame %d lost !!! Resending from frame %d",ack,ack);
            base = ack;
        }
    }
    printf("\n All frames sent successfully ...");
    return 0;
}