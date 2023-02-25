#pragma once

// This board has LFXT pins shared with P2.6 and P2.7 GPIOs
#define INIT_LFXTAL_PINS P2SEL1 = BIT6 | BIT7
