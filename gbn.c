#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

#define MAX_FRAMES 100
#define TIMEOUT 2 

void send_frames(int start,int end){
    for(int i=start;i<end;i++){
        printf("\n Sender : Sending frame %d",i);
    }
}

int main(){
    int window_size,total_frames;
    printf("\n Enter the window size :");
    scanf("%d",&window_size);
    printf("\n Enter no of frames to send :");
    scanf("%d",&total_frames);
    while(total_frames > MAX_FRAMES || window_size > total_frames){
        printf("\n Invalid input !!!");
        return 1;
    }

    srand(time(NULL));
    int base = 0;
    int end;
    printf("\n-------Go-Back-N ARQ Simulation---------\n");
    while(base < total_frames){
        // fixing window size
        if(base + window_size < total_frames){
            end = base+window_size;
        }
        else{
            end = total_frames;
        }
        printf("\n Current window : [%d to %d]\n",base,end-1);

        // sending frames of the current window 
        send_frames(base,end);
        sleep(TIMEOUT);

        int event = rand()%3;
        if(event == 0){
            printf("\n Receiver : All Frames from %d to %d received successfully",base,end-1);
            printf("\n Sender : All Frames from %d to %d acknowledged successfully\n",base,end-1);
            base = end;
        }
        else if(event == 1){
            int lost_frame = base + (rand() % (end-base));
            printf("\n Sender : All frames from sent successfully");
            printf("\n Receiver : Frame lost for frame %d",lost_frame);
            printf("\n Sender : Resending from frame %d\n",lost_frame);
            base = lost_frame;
        }
        else{
            printf("\n Receiver : All frame received");
            printf("\n Sender : ACK lost for frame %d",base);
            printf("\n Sender : Resending from frame %d\n",base);
        }
    }
    printf("\n All frames transmitted successfully \n");
    return 0;
}
