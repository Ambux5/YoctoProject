#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include "ssd1306.h"
#include "ina219.h"
#include "ina219_basic.h"

void ina219(int times) // Přidáme parametr times
{
    uint8_t res;
    int i;

    res = ina219_basic_init(INA219_ADDRESS_0, 0.1);
    if (res != 0)
    {
        ina219_interface_debug_print("ina219: Initialization failed.\n");
        return;  // Vracíme bez hodnoty, protože funkce je typu void
    }

    for (i = 0; i < times; i++)
    {
        float mV;
        float mA;
        float mW;

        res = ina219_basic_read(&mV, &mA, &mW);
        if (res != 0)
        {
            (void)ina219_basic_deinit();
            ina219_interface_debug_print("ina219: Read failed.\n");
            return;  // Vracíme bez hodnoty, protože funkce je typu void
        }

        ina219_interface_debug_print("ina219: %d/%d.\n", i + 1, times);
        ina219_interface_debug_print("ina219: bus voltage is %0.3fmV.\n", mV);
        ina219_interface_debug_print("ina219: current is %0.3fmA.\n", mA);
        ina219_interface_debug_print("ina219: power is %0.3fmW.\n", mW);
        ina219_interface_delay_ms(1000);
    }

    (void)ina219_basic_deinit();
}

// void oled()
// {
//     uint8_t i2c_node_address = 2;
//     int x = -1;
//     int y = -1;
//     char line[25] = {0};
//     char msg[200] = {0};
//     char oled_type[10] = {0};
//     int clear_line = -1;
//     int clear_all = -1;
//     int orientation = -1;
//     int inverted = -1;
//     int display = -1;
//     int font = 0;
//     int cmd_opt = 0;

//     uint8_t rc = 0;

//     void get_cpu_usage(long *idle, long *total)
//     {
//         FILE *file;
//         long user, nice, system, idle_tmp, iowait, irq, softirq;

//         file = fopen("/proc/stat", "r");
//         fscanf(file, "cpu %ld %ld %ld %ld %ld %ld %ld", &user, &nice, &system, &idle_tmp, &iowait, &irq, &softirq);
//         fclose(file);

//         *idle = idle_tmp;
//         *total = user + nice + system + idle_tmp + iowait + irq + softirq;
//     }

//     rc = ssd1306_init(i2c_node_address);

//     if (rc != 0)
//     {
//         printf("no oled attached to /dev/i2c-%d\n", i2c_node_address);
//         return 1;
//     }

//     rc += ssd1306_oled_default_config(64, 128);
//     rc += ssd1306_oled_clear_screen();

//     int values[3] = {0, 0, 0};
//     char buffer[20];
//     const char *names[] = {
//         "CPU",
//         "Usage",
//         "Temp"};
//     const char *units[] = {
//         "Mhz",
//         "%%",
//         "C"};

//     long idle1, total1, idle2, total2;
//     double usage;

//     get_cpu_usage(&idle1, &total1);
//     sleep(1);
//     get_cpu_usage(&idle2, &total2);
//     usage = (1.0 - (double)(idle2 - idle1) / (total2 - total1)) * 100;

//     printf("CPU usage: %.2f%%\n", usage);

//     char buffer2[50];
//     sprintf(buffer2, "%.2f", usage);

//     printf("Převedená hodnota: %s\n", buffer2);

//     for (int i = 0; i < 3; i++)
//     {
//         rc += ssd1306_oled_set_X(1);
//         rc += ssd1306_oled_set_Y(i);
//         rc += ssd1306_oled_write_string(font, names[i]);
//         rc += ssd1306_oled_set_X(45);
//         rc += ssd1306_oled_write_string(font, buffer2);
//         rc += ssd1306_oled_set_X(80);
//         rc += ssd1306_oled_write_string(font, units[i]);

//         values[i]++;
//         sleep(1);
//     }
//     ssd1306_end();
// }

int main(int argc, char **argv)
{
    // oled();
    ina219(3);

    return 0;
}