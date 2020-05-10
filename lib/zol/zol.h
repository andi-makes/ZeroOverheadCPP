#pragma once

#include "io/digitalPin.h"
#include "zol/timer/timer.h"
#include "util/register.h"

#include <avr/interrupt.h>

extern "C" {

void setup();
void loop();
int main();

} // END extern "C"