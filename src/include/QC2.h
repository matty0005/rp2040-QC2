#ifndef QC2_H
#define QC2_h

#define QC_5V 0 
#define QC_9V 1
#define QC_12V 2

void handshake_init();

void set_voltage(uint8_t voltage);

#endif