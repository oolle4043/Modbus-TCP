#include <stdio.h>
#include <errno.h>
#include <modbus/modbus.h>

int main() {
    // Modbus TCP ������ ����
    modbus_t *ctx = modbus_new_tcp("127.0.0.1", 1502);
    if (modbus_connect(ctx) == -1) {
        fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
        modbus_free(ctx);
        return -1;
    }

    // ������ ������ �뿪���� ����
    int n_loop = 10; // �ݺ� Ƚ��
    int nb_points = 10; // ������ ����Ʈ ��
    uint8_t tab_bit[nb_points];

    // Modbus �Լ� �ڵ� 01�� ����Ͽ� Coils ���� �б�
    int i, rc;
    for (i = 0; i < n_loop; i++) {
        rc = modbus_read_bits(ctx, 0, nb_points, tab_bit);
        if (rc == -1) {
            fprintf(stderr, "%s\n", modbus_strerror(errno));
            modbus_close(ctx);
            modbus_free(ctx);
            return -1;
        }

        // ���� Coils ���� ���
        printf("Coils values read: ");
        for (int j = 0; j < nb_points; j++) {
            printf("%d ", tab_bit[j]);
        }
        printf("\n");
    }

    // ���� ����
    modbus_close(ctx);
    modbus_free(ctx);

    return 0;
}
