#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

#define MAX_FRAMES 100
#define TIMEOUT 2

int window_size,total_frames;

void send_frames(int start,int end){
    for(int i=start;i<end;i++){
        printf("\n Sending Frame %d ",i);
    }
}

int main(){
    srand(time(NULL));
    printf("\n Enter the window size :");
    scanf("%d",&window_size);
    printf("\n Enter the total no of frames to send :");
    scanf("%d",&total_frames);
    if(total_frames > MAX_FRAMES || window_size > total_frames){
        printf("\n Invalid input ! Window size must be less than or equal to total frames .");
        return 1;
    }
    int base = 0;
    int end;
    while(base < total_frames){
        if(base + window_size < total_frames){
            end = base + window_size;
        }
        else{
            end = total_frames;
        }
        send_frames(base,end);
        sleep(TIMEOUT);

        int ack = base + (rand() % ((end - base) + 1));
        if(ack>=end){
            printf("\n All frames from %d to %d acknowledged ",base,end-1);
            base = ack;
        }
        else{
            printf("\n Acknowledgement lost or frame %d lost ! Resending from frame %d",ack,ack);
            base = ack;
        }
    }
    printf("\n All frames sent successfully.");
    return 0;
}