#include "Serial.h"

#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <cstring>
#include <errno.h>
 

Serial::Serial(const char* port) {
    configurePort(port);
}

Serial::~Serial() {
    closePort();
}

bool Serial::configurePort(const char *port) {
    fd = open(port, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd == -1) {
        std::cerr << "Failed to open port: " << strerror(errno) << std::endl;
        return false;
    }

    struct termios tty;
    memset(&tty, 0, sizeof(tty));

    if (tcgetattr(fd, &tty) != 0) {
        std::cerr << "Failed to get port attributes: " << strerror(errno) << std::endl;
        close(fd);
        return false;
    }

    /* Setting baudrate (for SBUS - 100k) */
    cfsetospeed(&tty, SBUS_BAUDRATE);
    cfsetispeed(&tty, SBUS_BAUDRATE);

    /* Setting parity */
    /* 8 bit packet */
    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;
    /* no parity */
    tty.c_cflag &= ~PARENB;                   
    /* 1 stop bit */
    tty.c_cflag &= ~CSTOPB;              
    /* Allow receiving and ignore modem control */
    tty.c_cflag |= CREAD | CLOCAL;

    /* Expecting uart to transceive data */
    /* Ignore parity errors */
    tty.c_iflag = IGNPAR;
    /* No exit processing */
    tty.c_oflag = 0;         
    /* No terminal control */
    tty.c_lflag = 0;

    /* Clean buffers and apply configuration */
    tcflush(fd, TCIOFLUSH);
    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        std::cerr << "Configuration error: " << strerror(errno) << std::endl;
        close(fd);
        return false;
    }

    return true;
}

void Serial::closePort() {
    if (fd != -1) {
        close(fd);
        fd = -1;
    }
}

int Serial::readData(unsigned char *buffer, int length) {
    if (fd == -1) {
        std::cerr << "Port is unintialized!" << std::endl;
        return -1;
    }

    int bytes_read = read(fd, buffer, length);
    if (bytes_read < 0) {
        std::cerr << "Failed to read data: " << strerror(errno) << std::endl;
        return -1;
    }
    return bytes_read;
}

int Serial::writeData(const unsigned char *data, int length) {
    if (fd == -1) {
        std::cerr << "Port is uninitialized!" << std::endl;
        return -1;
    }

    int bytes_written = write(fd, data, length);
    if (bytes_written < 0) {
        std::cerr << "Failed to write data: " << strerror(errno) << std::endl;
        return -1;
    }
    return bytes_written;
}
