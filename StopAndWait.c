#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<stdbool.h>
#define TIMEOUT 2 

typedef struct{
    int data;
    int seq_num;
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
    int num_frame = sizeof(data)/sizeof(data[0]);
    int seq_num = 0;
    State state = IDLE; 
    for(int i=0;i<num_frame;i++){
        Frame frame;
        frame.data = data[i];
        frame.seq_num = seq_num;
        printf("Sending Frame : Data %d, Seq_num %d\n",frame.data,frame.seq_num);
        while(state == IDLE || state == WAITING_FOR_ACK){
            if(state == IDLE){
                if(simulate_error()){
                    printf("Frame Lost : Data %d, Seq_num %d\n",frame.data,frame.seq_num);
                }
                else{
                    printf("Frame sent successfully : Data %d, Seq_num %d\n",frame.data,frame.seq_num);
                    state = WAITING_FOR_ACK;
                }
            }
            if(state == WAITING_FOR_ACK){
                sleep(TIMEOUT);
                if(simulate_error()){
                    printf("Data lost : Data %d, Seq_num %d\n",frame.data,frame.seq_num);
                    printf("Resending Frame : Data %d, Seq_num %d\n",frame.data,frame.seq_num);
                    state = IDLE;
                }
                else{
                    printf("Data received : Data %d, Seq_num %d\n",frame.data,frame.seq_num);
                    seq_num = 1-seq_num;
                    state = IDLE;
                    break;
                }
            }
        }  
    }
    return 0;
}