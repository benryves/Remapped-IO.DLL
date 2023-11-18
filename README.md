# Remapped IO.DLL

_Letting old software work with "modern" parallel ports._

## Disclaimer

This software is presented as a quick fix to a problem with software that is hard-coded to use legacy port addresses. It has not been thoroughly tested.

I cannot accept any liability for any damages (to your computer, programmer, devices being programmed or any other device) that might occur when using this software. You use this software at your own risk.

[Inpout32.dll](http://logix4u.net/Legacy_Ports/Parallel_Port/Inpout32.dll_for_Windows_98/2000/NT/XP.html) is by Logix4u, [io.dll](http://www.geekhideout.com/iodll.shtml) is by Fred.

## Installation

Simply copy io.dll, io.ini and inpout32.dll to the directory that contains the current io.dll. Open io.ini and change the default address (0x378) to the base address of your parallel port. Now run your software as normal.

You may need to also install the [VC++ 2008 runtimes](http://www.microsoft.com/downloads/details.aspx?FamilyID=9b2da534-3e03-4391-8a4d-074b9f2bc1bf&displaylang=en).

## How it Works

Included in this zip file is a cut-down version of [io.dll](http://www.geekhideout.com/iodll.shtml), originally written by Fred. This version of io.dll has been written from scratch. It only exposes three of the functions in io.dll, `PortOut()`, `PortIn()` and `IsDriverInstalled()`.

When one of these functions is called, the port address is checked. If it lies in the port range of the legacy LPT1 (0x378~0x37F) it is offset to a user-specified base address.

I couldn't get the original io.dll to work from the DLL (I kept getting privileged instruction errors), so I'm using Inpout32.dll instead, which has a much simpler interface.

## Testing

I haven't tested this software very thoroughly, but it appears to work fine with Willem Eprom (0.97ja) when programming an AM29F010B 128K×8 Flash memory and a 24LC256 32K×8 I2C serial EEPROM.

## Problems/Contact

If you have any problems, contact me at benryves@benryves.com.

The most likely problem I can see you having is an access violation at address 0x00000000, which will be triggered if the programming software calls a function I have not reimplemented. Failing that, check that you have set the working directory properly when running the software, as it may not pick up io.ini otherwise.

## Source Code

I have included the source code and VC++ Express 2008 project files. Someone may find it useful!