#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAX_FRAMES 100

int is_frame_received(){
    return rand()%2;
}

int main(){
    srand(time(NULL));
    int window_size,total_frames;
    int sent[MAX_FRAMES] = {0};
    int ack[MAX_FRAMES] = {0};
    printf("\n enter window size :");
    scanf("%d",&window_size);
    printf("\n enter total no of frames to send :");
    scanf("%d",&total_frames);
    printf("\n---------Starting Selective Repeat Simulation----------\n");
    int i = 0;
    while(1){
        int sent_in_this_round = 0;
        for(int j=0;j<window_size && i+j<total_frames;j++){
            int frame_index = i+j;
            if(!ack[frame_index]){
                printf("\nSending Frame [%d]",frame_index);
                sent[frame_index] = 1;
                if(is_frame_received()){
                    printf("\n Frame received successfully");
                    ack[frame_index] = 1;
                }
                else{
                    printf("\n Frame lost , will resend the frame ");
                }
                sent_in_this_round++;
            }
        }
        while(ack[i] && i<total_frames){
            i++;
        }
        if(i>=total_frames){
            break;
        }
    }
    printf("\n All frames received and acknowledged successfully");
    return 0;
}