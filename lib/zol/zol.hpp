#pragma once

#include "util/register.hpp"
#include "io/digitalPin.hpp"

#include <avr/interrupt.h>

extern "C" {
	void setup();
	void loop();
}