#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

#define MAX_FRAMES 100
#define TIME_OUT 2 

int main(){
    int window_size,total_frames;
    printf("\nEnter the size of the window : ");
    scanf("%d",&window_size);
    printf("\nEnter the no of frames you want to send : ");
    scanf("%d",&total_frames);

    if(total_frames > MAX_FRAMES || window_size > total_frames){
        printf("\nInvalid input !!!");
        return 1;
    }

    srand(time(NULL));
    int base = 0;
    int end;
    int received[MAX_FRAMES] = {0};
    int ack[MAX_FRAMES] = {0};

    while(base < total_frames){
        // fix window size
        if(base + window_size < total_frames){
            end = base + window_size;
        }
        else{
            end = total_frames;
        }
        // current window
        printf("\nCurrent window from [%d to %d]\n",base,end-1);
        // Sender side : sending data of current window 
        for(int i=base;i<end;i++){
            while(ack[i] == 0){
                printf("\nSender : Sending frame %d",i);
                sleep(TIME_OUT);
                // generate random error 
                int event = rand()%3;
                // event 0 : successfull
                if(event == 0){
                    printf("\nReceiver : frame %d received successfully",i);
                    received[i] = 1;
                    printf("\nReceiver : ack sent for frame %d",i);
                    printf("\nSender : frame %d acknowledged successfully\n",i);
                    ack[i] = 1;
                }
                // event 1 : frame lost 
                if(event == 1){
                    printf("\nReceiver : frame %d lost",i);
                    printf("\nSender : will resend the frame %d\n",i);
                }
                // event 2 : ACK lost
                if(event == 2){
                    printf("\nReceiver : frame %d received successfully.",i);
                    received[i]=1;
                    printf("\nReceiver : frame %d sent for ACk",i);
                    printf("\nSender : ACK lost for frame %d",i);
                    printf("\nSender : Will resend the frame %d",i);
                }
            }
        }
        // slide the window only when the base is acknowledged 
        while(base<total_frames && ack[base] == 1){
            base++;
        }
    }
    printf("\n All frames sent and received successfully.\n");
    return 0;


}