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
    int nb_registers = 10; // �������� ��
    uint16_t tab_reg[nb_registers];

    // Modbus �Լ� �ڵ� 03�� ����Ͽ� Holding Registers ���� �б�
    int i, rc;
    for (i = 0; i < n_loop; i++) {
        rc = modbus_read_registers(ctx, 0, nb_registers, tab_reg);
        if (rc == -1) {
            fprintf(stderr, "%s\n", modbus_strerror(errno));
            modbus_close(ctx);
            modbus_free(ctx);
            return -1;
        }

        // ���� Holding Registers ���� ���
        printf("Holding Registers values read: ");
        for (int j = 0; j < nb_registers; j++) {
            printf("%d ", tab_reg[j]);
        }
        printf("\n");
    }

    // ���� ����
    modbus_close(ctx);
    modbus_free(ctx);

    return 0;
}