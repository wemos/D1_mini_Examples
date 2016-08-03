/*
Switch
Copyright (C) 2012  Albert van Dalen http://www.avdweb.nl
This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License at http://www.gnu.org/licenses .
*/

#ifndef SWITCH_H
#define SWITCH_H

class Switch
{
public:
  Switch(byte _pin, byte PinMode=INPUT_PULLUP, bool polarity=LOW, int debounceDelay=50, int longPressDelay=400, int doubleClickDelay=250);
  bool poll(); // Returns 1 if switched
  bool switched(); // will be refreshed by poll()
  bool on();
  bool pushed(); // will be refreshed by poll()
  bool released(); // will be refreshed by poll()
  bool longPress(); // will be refreshed by poll()
  bool doubleClick(); // will be refreshed by poll()

  unsigned long _switchedTime, pushedTime;

protected:
  const byte pin;
  const int debounceDelay, longPressDelay, doubleClickDelay;
  const bool polarity;
  bool level, _switched, _longPress, longPressLatch, _doubleClick;
};

#endif
