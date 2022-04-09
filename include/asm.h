#include <stdint.h>


uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile ( "inb {%[port], %[retreg] | %[retreg], %[port]}"
                   : [retreg]"=a"(ret)
                   : [port]"Nd"(port) );
    return ret;
}
//Sends a 8/16/32-bit value on a I/O location. Traditional names are outb, outw and outl respectively.
void outb(uint16_t port, uint8_t byte)
{
    asm volatile ( "outb {%[byte], %[port] | %[port], %[byte]}"
                   :
                   : [byte]"a"(byte),
                     [port]"Nd"(port) );
}
void outw(uint16_t port, uint16_t byte)
{
    asm volatile ( "outw {%[byte], %[port] | %[port], %[byte]}"
                   :
                   : [byte]"a"(byte),
                     [port]"Nd"(port) );
}

void io_wait(void)
{
    outb (0x80, 0);
}