#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<stdbool.h>

#define TIMEOUT 2 

typedef struct{
    int data;
    int seq_no;
}Frame;

typedef enum{
    IDLE,
    WAITING_FOR_ACK
}State;

bool simulate_error(){
    return rand()%2;
}

int main(){
    srand(time(NULL));
    int data[] = {10,20,30,40,50};
    int total_frames = sizeof(data)/sizeof(data[0]);
    State state = IDLE;
    int seq_no = 0;
    for(int i=0;i<total_frames;i++){
        Frame frame;
        frame.data = data[i];
        frame.seq_no = seq_no;
        printf("\n Sending frame : Data %d,Seq_no %d",frame.data,frame.seq_no);
        while(1){
            if(state == IDLE){
                if(simulate_error()){
                    printf("\n Frame Lost : Data %d,Seq_no %d\n",frame.data,frame.seq_no);
                }
                else{
                    printf("\n Frame sent successfully : Data %d,Seq_no %d\n",frame.data,frame.seq_no);
                    state = WAITING_FOR_ACK;
                }
            }
            if(state == WAITING_FOR_ACK){
                if(simulate_error()){
                    sleep(TIMEOUT);
                    printf("\n ACK lost : : Data %d,Seq_no %d",frame.data,frame.seq_no);
                    printf("\n Resending frame : Data %d,Seq_no %d\n",frame.data,frame.seq_no);
                    state = IDLE;
                }
                else{
                    printf("\n ACK received successfully : Data %d,Seq_no %d\n",frame.data,frame.seq_no);
                    seq_no = 1-seq_no;
                    state = IDLE;
                    break;
                }
            }
        }
    }
    printf("\n All frames sent and acknowledged successfully\n");
    return 0;
}