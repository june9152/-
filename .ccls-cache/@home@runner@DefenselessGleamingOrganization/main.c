#include <stdint.h>
#include <stdio.h>
#define COCOBETA_START_DLE 0xFE
#define COCOBETA_STX 0xFA
#define COCOBETA_ETX 0xFB
typedef enum {
  CMD_SUB_VERSION_REQ = 0x80,
  CMD_SUB_VERSION_RES,
  CMD_SUB_STATUS_REQ,
  CMD_SUB_STATUS_RES,
  CMD_REMOTECTRL_INPUT_REQ,
  CMD_REMOTECTRL_INPUT_RES,
  CMD_TIME_COIN_INPUT_REQ,
  CMD_TIME_COIN_INPUT_RES,
  CMD_MSG_SEND_REQ,
  CMD_MSG_SEND_RES,
  CMD_EMERGENCY_REQ,
  CMD_EMERGENCY_RES,
  CMD_SING_RESERVE_FIRSTRESERVE_PAUSE_RESERVECANCEL_REQ,

} COCOBETA_CMD_Index;
uint8_t stx_arr[] = {COCOBETA_START_DLE, COCOBETA_STX, CMD_SUB_STATUS_REQ};
uint8_t etx_arr[] = {COCOBETA_START_DLE, COCOBETA_ETX};
uint8_t arr[] = {0xFE, 0xFA, 0x82, 0x02, 0x09, 0xFE, 0xFB, 0xED,
                     0x6E, 0xFE, 0xFA, 0x83, 0x02, 0x08, 0x2B, 0x80,
                     0x00, 0x00, 0xFE, 0xFB, 0xD3, 0x19};
uint8_t rx_arr[50];
uint8_t Protocol_Search(uint8_t *data, uint8_t size) {
  uint8_t protocol_cnt = 0;
  uint8_t ret = 0;
  uint8_t startindex = 0;
  for (int i = 0; i < size; i++) {
    if (data[i] == stx_arr[0] && data[i + 1] == stx_arr[1] &&
        arr[i + 2] != stx_arr[2]) {
      protocol_cnt++;
      startindex = i;
      memcpy(rx_arr, &data[i], size - i);
    }
  }
  ret = protocol_cnt;
  printf("Search Result : %d \n", ret);
  for (int i = 0; i < size - startindex; i++)
    printf("%02X ", rx_arr[i]);
  return startindex != 0 ? size - startindex : 0;
}

int main(void) {
  Protocol_Search(arr, sizeof(arr));

  return 0;
}