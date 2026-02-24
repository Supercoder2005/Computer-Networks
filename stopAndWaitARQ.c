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

// enum is used for giving particular names to integer values (State 0 --> IDLE, State 1 --> WAITING_FOR_ACK)
typedef enum{
    IDLE,
    WAITING_FOR_ACK
}State;

// function to simulate error 
bool simulate_error(){
    return rand()%2; // only generate 0/1 , if returns 1 --> error occured if returns 0 --> no error
}

int main(){
    srand(time(NULL)); // seed random function --> always generate random values with a starting point , here the starting point is current time = time(NULL)
    int data[] = {10,20,30,40,50};
    int no_frames = sizeof(data)/sizeof(data[0]);
    State state = IDLE;
    int seq_no = 0;
    for(int i=0;i<no_frames;i++){
        Frame frame;
        frame.data = data[i];
        frame.seq_no = seq_no;
        printf("\n Sending Frame : Data %d, Seq_no %d",frame.data,frame.seq_no);
        while(1){
            if(state == IDLE){
                if(simulate_error()){
                    printf("\n Frame Lost : Data %d, Seq_no %d",frame.data,frame.seq_no);
                }
                else{
                    printf("\n Frame sent successfully : Data %d, Seq_no %d",frame.data,frame.seq_no);
                    state = WAITING_FOR_ACK;
                }
            }
            if(state == WAITING_FOR_ACK){
                sleep(TIMEOUT); // sleep() --> time in unit sec
                if(simulate_error()){
                    printf("\n Acknowledgement Lost : Data %d, Seq_no %d",frame.data,frame.seq_no);
                    printf("\n Resending Frame : Data %d, Seq_no %d",frame.data,frame.seq_no);
                    state = IDLE;
                }
                else{
                    printf("\n Acknowledged successfully : Data %d, Seq_no %d",frame.data,frame.seq_no);
                    seq_no = 1-seq_no;
                    state = IDLE;
                    break;
                }
            }
        }
    }
    return 0;
}