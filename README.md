**Cache Simulator**
===================


Cache simulator for basic load/store architecture.  Implemented in C++, this architecture takes different parameters of the desired cache along with a trace file. The simulated result will be the output of this program.

----------


Documents
-------------

> **Files:**

> -  Confs/*.conf: This file contains the configuration of the cache to be used. They are: block-size, associativity, cache size, replacement policy, miss penalty and write allocate.
	> - Traces/*.trace: This is the trace file for the cache. Each line consists of memory address instruction ie load or store with specifying the memory address that is being accessed and the number of instructions executed since the last memory address.
	> - Output/*.out: Contains the output of the simulated result.

#**Usage**

To simulate the result, use it by:

1) Run the __make__ command first.
2) It produces the object __simulator__ after compiling.
3) After this, run the program as one of this example:
		__./simulator ./confs/small-dm.conf ./traces/gzip.trace__
4) The output will be presented in the output folder as __gzip.trace.out__