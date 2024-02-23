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
    int nb_points = 10; // 데이터 포인트 수
    uint8_t tab_bit[nb_points];

    // Modbus 함수 코드 01을 사용하여 Coils 값을 읽기
    int i, rc;
    for (i = 0; i < n_loop; i++) {
        rc = modbus_read_bits(ctx, 0, nb_points, tab_bit);
        if (rc == -1) {
            fprintf(stderr, "%s\n", modbus_strerror(errno));
            modbus_close(ctx);
            modbus_free(ctx);
            return -1;
        }

        // 읽은 Coils 값을 출력
        printf("Coils values read: ");
        for (int j = 0; j < nb_points; j++) {
            printf("%d ", tab_bit[j]);
        }
        printf("\n");
    }

    // 연결 종료
    modbus_close(ctx);
    modbus_free(ctx);

    return 0;
}
