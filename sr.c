#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>

#define TIMEOUT 2
#define MAX_FRAMES 100 

int main(){
    srand(time(NULL));

    int window_size,total_frames;
    printf("\n Enter the window size :");
    scanf("%d",&window_size);
    printf("\n Enter total no of frames to send :");
    scanf("%d",&total_frames);
    while(total_frames>MAX_FRAMES || window_size>total_frames){
        printf("\n Invalid Input");
        return 1;
    }
    int base = 0;
    int end;
    int ack[MAX_FRAMES] = {0};
    int received[MAX_FRAMES] = {0};

    while(base<total_frames){

        if(base+window_size < total_frames){
            end = base+window_size;
        }
        else{
            end = total_frames;
        }
        printf("\n Current window : [%d to %d]\n",base,end-1);

        for(int i=base;i<end;i++){
            if(ack[i] == 0){
                printf("\n Sender : Sending Frame %d",i);
                sleep(TIMEOUT);

                int event = rand()%3;
                if(event == 0){
                    printf("\n Receiver : Frame %d received successfully",i);
                    received[i] = 1;
                    printf("\n Receiver : ACK sent for frame %d",i);
                    printf("\n Sender : Frame %d acknowledged successfully\n",i);
                    ack[i] = 1;
                }
                else if(event == 1){
                    printf("\n Sender : Frame %d sent",i);
                    printf("\n Receiver : Frame lost for frame %d",i);
                    printf("\n Sender : Will resend frame %d\n",i);
                }
                else{
                    printf("\n Receiver : Frame %d received successfully",i);
                    received[i] = 1;
                    printf("\n Receiver : ACK sent for Frame %d ",i);
                    printf("\n Sender : ACK lost for frame %d",i);
                    printf("\n Sender : Will resend frame %d\n",i);
                }
            } 
        }
        // sliding window 
        while(base<total_frames && ack[base]==1){
            base++;
        }
    }
    printf("\n All frames transmitted successfully\n");
    return 0;
}