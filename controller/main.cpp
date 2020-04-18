/*
 * Copyright (c) 2010-2011, Fabian Greif
 * Copyright (c) 2012-2014, 2017, Niklas Hauser
 * Copyright (c) 2013, Sascha Schade
 *
 * This file is part of the modm project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
// ----------------------------------------------------------------------------

#include <modm/board.hpp>
#include <modm/platform.hpp>
#include <modm/io/iostream.hpp>
#include <modm/driver/display/ssd1306.hpp>
using namespace modm::literals;

using namespace modm::platform;

typedef A4 Sda;
typedef A5 Scl;
typedef I2cMaster MyI2cMaster;
modm::Ssd1306<MyI2cMaster> display;



// using Sck = D11;
// using Mosi = D12;
// using Miso = D13;
// using SpiMaster = SpiMaster2;

void initialize()
{
}

int
main()
{
	Board::initialize();

	MyI2cMaster::connect<Scl::Scl, Sda::Sda>();
	MyI2cMaster::initialize<Board::SystemClock, 400_kHz>();

	display.initializeBlocking();
	display.setFont(modm::font::ArcadeClassic);
	display << "Hello World!";
	display.update();

	modm::ShortPeriodicTimer timer(100);
	uint16_t counter(0);

	//display.drawRectangle(0, 0, 127, 63);
	while (true)
	{
		if (timer.execute())
		{
			display.setCursor(0,20);
			display << counter++;
			display.update();
		}
	}
}
