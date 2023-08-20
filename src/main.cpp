#include <mbed.h>

#include <array>

constexpr unsigned int can_id = 29;

// IO
BufferedSerial pc{USBTX, USBRX, 115200};
CAN can{PA_11, PA_12, (int)1e6};

array<DigitalOut, 8> sol{PB_5, PB_6, PB_7, PB_0, PB_1, PA_8, PA_9, PB_4};

uint8_t sol_status = 0;
CANMessage msg;

int main() {
  printf("\nsetup\n");
  while(1) {
    if(can.read(msg)) {
      if(msg.id == can_id) sol_status = msg.data[0];
      printf("%d\t%d\n", sol_status, msg.id);
    } else {
      printf("I'm %x. no msg\n", can_id);
    }
    for(int i = 0; i < 8; ++i) {
      sol[i] = (sol_status >> i) & 1;
    }
  }
}
