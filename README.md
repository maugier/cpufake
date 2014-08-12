cpufake 0.1
===========

This is a completely pointless module whose purpose is to change the CPU model name
in /proc/cpuinfo. I wrote this for a client who was unpleased not to see the real CPU
name when running under a virtual machine. Whatever...

Installation:

- `make`
- `make install`

(`make install` may fail if your kernel has never been recompiled, in which case you can just keep
the `cpufake.ko` file around.

Usage:

- `modprobe cpufake` (Or if `make install` failed, `insmod cpufake.ko`)
- `echo -n "My UltraCool new Processor model" >/sys/modules/cpufake/parameters/cpuname`
