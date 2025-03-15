// 串口输出函数
static inline void outb(unsigned short port, unsigned char data) {
    asm volatile ("outb %0, %1" :: "a"(data), "d"(port));
}

// 设置串口
void init_serial() {
    outb(0x3F8 + 1, 0x00); // 关闭中断
    outb(0x3F8 + 3, 0x80); // 设定波特率分频
    outb(0x3F8 + 0, 0x03); // 38400 波特率 (低字节)
    outb(0x3F8 + 1, 0x00); // 高字节
    outb(0x3F8 + 3, 0x03); // 8位, 无校验, 1停止位
    outb(0x3F8 + 2, 0xC7); // FIFO 控制
    outb(0x3F8 + 4, 0x0B); // IRQs 使能
}

// 向串口打印字符串
void serial_print(const char *str) {
    while (*str) {
        outb(0x3F8, *str);
        str++;
    }
}

// 入口点 `_start`
void _start(void) {
    init_serial(); // 初始化串口
    serial_print("Hello, TTY!\n");

    while (1); // 防止 CPU 执行到奇怪的地方
}
