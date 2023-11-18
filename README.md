# Remapped IO.DLL

_Letting old software work with "modern" parallel ports._

## Disclaimer

This software is presented as a quick fix to a problem with software that is hard-coded to use legacy port addresses. It has not been thoroughly tested.

I cannot accept any liability for any damages (to your computer, programmer, devices being programmed or any other device) that might occur when using this software. **You use this software at your own risk**.

Inpout32.dll was originally from [Logix4u](http://logix4u.net/Legacy_Ports/Parallel_Port/Inpout32.dll_for_Windows_98/2000/NT/XP.html), this package contains the updated 64-bit compatible version from [HighRez](http://www.highrez.co.uk/Downloads/InpOut32/), [io.dll](http://www.geekhideout.com/iodll.shtml) is by Fred.

Inpout32.dll comes with the following license text:

> Copyright (c) <2003-2015> Phil Gibbons <www.highrez.co.uk>
> Portions Copyright (c) <2000> <logix4u.net>
> 
> Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
> 
> The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
> 
> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. 
    
## Installation

Install the _Willem EPROM/FLASH Programmer_ software normally, then copy _io.dll_, _io.ini_ and _inpout32.dll_ to its installation directory (it should contain the current _io.dll_). Open _io.ini_ and change the default address (0x378) to the base address of your parallel port.

You can find the base address of your parallel port in Device Manager. Now run the Willem software normally, and ensure that it's using _LPT1 (0x378)_ and you should be good to go.

You may need to also install the [VC++ 2008 SP1 runtimes](http://www.microsoft.com/downloads/details.aspx?FamilyID=A5C84275-3B97-4AB7-A40D-3802B2AF5FC2).

## How it Works

Included in this zip file is a cut-down version of [io.dll](http://www.geekhideout.com/iodll.shtml), originally written by Fred. This version of io.dll has been written from scratch. It only exposes three of the functions in io.dll, `PortOut()`, `PortIn()` and `IsDriverInstalled()`.

When one of these functions is called, the port address is checked. If it lies in the port range of the legacy LPT1 (0x378~0x37F) it is offset to a user-specified base address.

I couldn't get the original io.dll to work from the DLL (I kept getting privileged instruction errors), so I'm using Inpout32.dll instead, which has a much simpler interface.

## Testing

I've been using this fix for a while, and it appears to work fine when programming an AM29F010B 128K×8 Flash memory, a 24LC256 32K×8 I2C serial EEPROM and a PIC 16F84 microcontroller.

I have also received a report that it works with an Atmel AT89C2051.

I am using a MosChip 9835 card, and have received a report that the software also works with the MosChip 9865.

## Problems/Contact

If you have any problems, contact me at benryves@benryves.com.

The most likely problem I can see you having is an access violation at address 0x00000000, which will be triggered if the programming software calls a function I have not reimplemented. Failing that, check that you have set the working directory properly when running the software, as it may not pick up io.ini otherwise.

## Source Code

I have included the source code and VC++ Express 2008 project files. Someone may find it useful!

## WinPic800

For programming a wider range of devices, you may wish to use [WinPic800](http://www.winpic800.com/) to complement the Willem software above. This too requires a bit of tweaking to work.

First, configure WinPic800 to use the Willem programmer via the _Settings_ → _Hardware_ menu. I left the settings at LPT1. Now exit the software, and browse to its installation directory. In the _Hardware_ directory, you should find a file named _WILLEM.hwp_. Make a back-up copy of it, then open it in a text editor. The following values need to be changed:

* AddrB, AddrD, AddrC: Base port address.
* AddrS: Base port address + 1.
* AddrV, AddrV2, AddrVdd, AddrM: Base port address + 2.

The port addresses must be converted to decimal first. My parallel port has a base address of 0xCCD8, and so that part of the file looks like this:

```
AddrB=52440
AddrD=52440
AddrC=52440
AddrS=52441
AddrV=52442
AddrV2=52442
AddrVdd=52442
AddrM=52442
```

Save the file and you should be able to use the Willem programmer with WinPic800 successfully.
