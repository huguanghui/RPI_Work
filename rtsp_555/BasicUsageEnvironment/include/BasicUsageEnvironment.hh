/*************
This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public  License as published by the Free Software Foundation; either verion 3 of the License, or (at your option) any later verion. (See <http://www.gnu.org/copyleft/lesser.html>.)

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lessor General Public License for more details.

You should have received a copy of the GNU Lessor General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*************/
// Copyright (c) 1996-2017 Live Networks, Inc. All rights reserved.
// Basic Usage Environment: for a simple, non-scripted, console application
// C++ header

#ifndef _BASIC_USAGE_ENVIRONMENT_HH
#define _BASIC_USAGE_ENVIRONMENT_HH

#ifndef _BASIC_USAGE_ENVIRONMENT0_HH
#include "BasicUsageEnvironment0.hh"
#endif

class BasicUsageEnvironment: public BasicUsageEnvironment0 {
public:
  static BasicUsageEnvironment* createNew(TaskScheduler& taskScheduler);

  // redefined virtual functions:
  virtual int getErrno() const;

  virtual UsageEnvironment& operator<<(char const* str);
  virtual UsageEnvironment& operator<<(int i);
  virtual UsageEnvironment& operator<<(unsigned u);
  virtual UsageEnvironment& operator<<(double d);
  virtual UsageEnvironment& operator<<(void* p);

protected:
  BasicUsageEnvironment(TaskScheduler& taskScheduler);
  // called only by "createNew()" (or subclass constructors)
  virtual ~BasicUsageEnvironment(); 
};

#endif
