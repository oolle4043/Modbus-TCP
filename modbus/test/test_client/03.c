#include <stdio.h>
#include <errno.h>
#include <modbus/modbus.h>

int main() {
    // Modbus TCP 서버에 연결
    modbus_t *ctx = modbus_new_tcp("127.0.0.1", 1502);
    if (modbus_connect(ctx) == -1) {
        fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
        modbus_free(ctx);
        return -1;
    }

    // 측정할 데이터 대역폭을 정의
    int n_loop = 10; // 반복 횟수
    int nb_registers = 10; // 레지스터 수
    uint16_t tab_reg[nb_registers];

    // Modbus 함수 코드 03을 사용하여 Holding Registers 값을 읽기
    int i, rc;
    for (i = 0; i < n_loop; i++) {
        rc = modbus_read_registers(ctx, 0, nb_registers, tab_reg);
        if (rc == -1) {
            fprintf(stderr, "%s\n", modbus_strerror(errno));
            modbus_close(ctx);
            modbus_free(ctx);
            return -1;
        }

        // 읽은 Holding Registers 값을 출력
        printf("Holding Registers values read: ");
        for (int j = 0; j < nb_registers; j++) {
            printf("%d ", tab_reg[j]);
        }
        printf("\n");
    }

    // 연결 종료
    modbus_close(ctx);
    modbus_free(ctx);

    return 0;
}