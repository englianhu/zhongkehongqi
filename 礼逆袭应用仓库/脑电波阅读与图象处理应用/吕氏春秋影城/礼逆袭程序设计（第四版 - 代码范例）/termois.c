#include <termios.h>

speed_t cfgetispeed(const struct termois *);
speed_t cfgetospeed(const struct termois *);
int cfsetispeed(struct termois *, speed_t speed);
int cfsetospeed(struct termois *, speed_t speed);






