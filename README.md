# LTSM - Lightweight TSM API and TSM Console Client for Archiving Data

A lightweight high-level TSM API/library (called *ltsmapi*) supporting operations
* *archiving*
* *retrieving*
* *deleting*
* and *querying*.

In addition a simple console client (called *ltsmc*) is provided which demonstrates the use of *ltsmapi*.

## Getting Started <a id="getting.started"></a>
Before using LTSM a working access to a TSM server is required. One can install for testing purposes a fully working
TSM server (e.g. inside a KVM) for a period of 30 days before the license expires. A complete installation and setup guide is provided
at [TSM Server Installation Guide](http://web-docs.gsi.de/~tstibor/tsm/).

To compile *ltsmc* first clone the git repository
```
git clone https://github.com/tstibor/ltsm
```

Download and install the TSM API client provided at [7.1.4.0-TIV-TSMBAC-LinuxX86_DEB.tar](http://ftp.software.ibm.com/storage/tivoli-storage-management/maintenance/client/v7r1/Linux/LinuxX86_DEB/BA/v714/).
Make sure to install `tivsm-api64.amd64.deb` where the header files `dapitype.h, dsmapips.h, ...` and the low-level library `libApiTSM64.so` are provided.

The building of LTSMAPI/LTSMC is based on simple `Makefile`
```
make
```
Gives result when the header files and library are provided at the proper place:
```
gcc -m64 -DLINUX_CLIENT -std=c99 -Wall -D_FILE_OFFSET_BITS=64 -D_LARGEFILE64_SOURCE -O2 -DVERSION=\"0.0.1-19-g3f7bbbe\" -c src/qarray.c -I ibmtsm -o obj/src/qarray.o
gcc -m64 -DLINUX_CLIENT -std=c99 -Wall -D_FILE_OFFSET_BITS=64 -D_LARGEFILE64_SOURCE -O2 -DVERSION=\"0.0.1-19-g3f7bbbe\" -c src/tsmapi.c -I ibmtsm -o obj/src/tsmapi.o
gcc -m64 -DLINUX_CLIENT -std=c99 -Wall -D_FILE_OFFSET_BITS=64 -D_LARGEFILE64_SOURCE -O2 -DVERSION=\"0.0.1-19-g3f7bbbe\" -c src/ltsmc.c -I ibmtsm -o obj/src/ltsmc.o
gcc -m64 -DLINUX_CLIENT -std=c99 -Wall -D_FILE_OFFSET_BITS=64 -D_LARGEFILE64_SOURCE -O2 -DVERSION=\"0.0.1-19-g3f7bbbe\" -o bin/ltsmc   obj/src/qarray.o  obj/src/tsmapi.o  obj/src/ltsmc.o -lApiTSM64 -lm
gcc -m64 -DLINUX_CLIENT -std=c99 -Wall -D_FILE_OFFSET_BITS=64 -D_LARGEFILE64_SOURCE -O2 -DVERSION=\"0.0.1-19-g3f7bbbe\" -c src/test/test_dsstruct64_off_t.c -I src -I ibmtsm -I cutest -o obj/src/test/test_dsstruct64_off_t.o
gcc -m64 -DLINUX_CLIENT -std=c99 -Wall -D_FILE_OFFSET_BITS=64 -D_LARGEFILE64_SOURCE -O2 -DVERSION=\"0.0.1-19-g3f7bbbe\" -c src/test/test_qarray.c -I src -I ibmtsm -I cutest -o obj/src/test/test_qarray.o
gcc -m64 -DLINUX_CLIENT -std=c99 -Wall -D_FILE_OFFSET_BITS=64 -D_LARGEFILE64_SOURCE -O2 -DVERSION=\"0.0.1-19-g3f7bbbe\" -c src/test/ltsmc_testsuite.c -I src -I ibmtsm -I cutest -o obj/src/test/ltsmc_testsuite.o
gcc -m64 -DLINUX_CLIENT -std=c99 -Wall -D_FILE_OFFSET_BITS=64 -D_LARGEFILE64_SOURCE -O2 -DVERSION=\"0.0.1-19-g3f7bbbe\" -c src/test/CuTest.c -I src -I ibmtsm -I cutest -o obj/src/test/CuTest.o
gcc -m64 -DLINUX_CLIENT -std=c99 -Wall -D_FILE_OFFSET_BITS=64 -D_LARGEFILE64_SOURCE -O2 -DVERSION=\"0.0.1-19-g3f7bbbe\" -o bin/ltsmc_testsuite   obj/src/test/test_dsstruct64_off_t.o  obj/src/test/test_qarray.o  obj/src/test/ltsmc_testsuite.o  obj/src/test/CuTest.o   obj/src/qarray.o  obj/src/tsmapi.o   -lApiTSM64 -lm
```
To compile with DEBUG and VERBOSE flags for verbose output details set `ENV` variables `DEBUG=1 VERBOSE=1`:
```
DEBUG=1 VERBOSE=1 make
```
Gives result:
```
gcc -m64 -DLINUX_CLIENT -std=c99 -Wall -D_FILE_OFFSET_BITS=64 -D_LARGEFILE64_SOURCE -g -DDEBUG -DVERBOSE -DVERSION=\"0.0.1-19-g3f7bbbe\" -c src/qarray.c -I ibmtsm -o obj/src/qarray.o
gcc -m64 -DLINUX_CLIENT -std=c99 -Wall -D_FILE_OFFSET_BITS=64 -D_LARGEFILE64_SOURCE -g -DDEBUG -DVERBOSE -DVERSION=\"0.0.1-19-g3f7bbbe\" -c src/tsmapi.c -I ibmtsm -o obj/src/tsmapi.o
gcc -m64 -DLINUX_CLIENT -std=c99 -Wall -D_FILE_OFFSET_BITS=64 -D_LARGEFILE64_SOURCE -g -DDEBUG -DVERBOSE -DVERSION=\"0.0.1-19-g3f7bbbe\" -c src/ltsmc.c -I ibmtsm -o obj/src/ltsmc.o
gcc -m64 -DLINUX_CLIENT -std=c99 -Wall -D_FILE_OFFSET_BITS=64 -D_LARGEFILE64_SOURCE -g -DDEBUG -DVERBOSE -DVERSION=\"0.0.1-19-g3f7bbbe\" -o bin/ltsmc   obj/src/qarray.o  obj/src/tsmapi.o  obj/src/ltsmc.o -lApiTSM64 -lm
gcc -m64 -DLINUX_CLIENT -std=c99 -Wall -D_FILE_OFFSET_BITS=64 -D_LARGEFILE64_SOURCE -g -DDEBUG -DVERBOSE -DVERSION=\"0.0.1-19-g3f7bbbe\" -c src/test/test_dsstruct64_off_t.c -I src -I ibmtsm -I cutest -o obj/src/test/test_dsstruct64_off_t.o
gcc -m64 -DLINUX_CLIENT -std=c99 -Wall -D_FILE_OFFSET_BITS=64 -D_LARGEFILE64_SOURCE -g -DDEBUG -DVERBOSE -DVERSION=\"0.0.1-19-g3f7bbbe\" -c src/test/test_qarray.c -I src -I ibmtsm -I cutest -o obj/src/test/test_qarray.o
gcc -m64 -DLINUX_CLIENT -std=c99 -Wall -D_FILE_OFFSET_BITS=64 -D_LARGEFILE64_SOURCE -g -DDEBUG -DVERBOSE -DVERSION=\"0.0.1-19-g3f7bbbe\" -c src/test/ltsmc_testsuite.c -I src -I ibmtsm -I cutest -o obj/src/test/ltsmc_testsuite.o
gcc -m64 -DLINUX_CLIENT -std=c99 -Wall -D_FILE_OFFSET_BITS=64 -D_LARGEFILE64_SOURCE -g -DDEBUG -DVERBOSE -DVERSION=\"0.0.1-19-g3f7bbbe\" -c src/test/CuTest.c -I src -I ibmtsm -I cutest -o obj/src/test/CuTest.o
gcc -m64 -DLINUX_CLIENT -std=c99 -Wall -D_FILE_OFFSET_BITS=64 -D_LARGEFILE64_SOURCE -g -DDEBUG -DVERBOSE -DVERSION=\"0.0.1-19-g3f7bbbe\" -o bin/ltsmc_testsuite   obj/src/test/test_dsstruct64_off_t.o  obj/src/test/test_qarray.o  obj/src/test/ltsmc_testsuite.o  obj/src/test/CuTest.o   obj/src/qarray.o  obj/src/tsmapi.o   -lApiTSM64 -lm
```

### Executable and Testing
After successful compiling you will find two binaries: `bin/ltsmc_testsuite` and `bin/ltsmc`. The former is a simple test suite, the latter the console client:
```
Syntax: ./bin/ltsmc
	-a, --archive
	-r, --retrieve
	-q, --query
	-d, --delete
	-f, --fsname <STRING>
	-h, --hl <STRING>
	-l, --ll <STRING>
	-c, --description <STRING>
	-n, --node <STRING>
	-u, --username <STRING>
	-p, --password <STRING>
	-s, --servername <STRING>

Version: 0.0.5-1-gb460ddf,© Thomas Stibor <t.stibor@gsi.de>
```

## Examples of Core TSM Operations <a id="example.of.core.tsm.operations"></a>
Make sure to setup proper TSM servername, nodename and IP address entries in file `dsmopt/dsm.sys` or in the default file
`/opt/tivoli/tsm/client/api/bin64/dsm.sys`. For [TSM Server Installation Guide](http://web-docs.gsi.de/~tstibor/tsm/) the following entries are working:
```
SErvername              lxdv81-kvm-tsm-server
   Nodename             lxdv81
   TCPServeraddress     192.168.254.101

SErvername              polaris-kvm-tsm-server
   Nodename             polaris
   TCPServeraddress     192.168.254.102
```

In addition make sure to set variable `DSMI_CONFIG` pointing to the file `dsm.sys`, that is: ```export DSMI_CONFIG=`pwd`/dsmopt/dsm.sys``` or ```export DSMI_CONFIG=/opt/tivoli/tsm/client/api/bin64/dsm.sys```.
See also the [sanity script](https://github.com/tstibor/ltsm/blob/master/sanity1.sh) fore more details.

### Archiving data
For demonstrating of how to archive files and directories we first create an *archive* directories and place there some data.
```
mkdir -p /tmp/archives && wget --directory-prefix /tmp/archives https://www.kernel.org/pub/linux/kernel/Historic/linux-0.01.tar.gz && tar xvfz /tmp/archives/linux-0.01.tar.gz -C /tmp/archives && rm -rf /tmp/archives/linux-0.01.tar.gz
```

First we archive the single file `/tmp/archives/linux/Makefile`
```
bin/ltsmc --archive --fsname '/' -c 'Historic Linux Kernel Makefile' --node lxdv81 --password lxdv81 --servername=lxdv81-kvm-tsm-server /tmp/archives/linux/Makefile
```

For archiving the complete `/tmp/archives/linux` directory (with all sub-directories) perform following command:
```
bin/ltsmc --archive --fsname '/' -c 'Complete Historic Linux Kernel' --node lxdv81 --password lxdv81 --servername=lxdv81-kvm-tsm-server /tmp/archives/linux
```
### Querying Data
For querying all data stored in directory `/tmp/archives/linux`
```
bin/ltsmc --query --fsname '/' --node lxdv81 --password lxdv81 --servername=lxdv81-kvm-tsm-server --hl '/tmp/archives/linux/*' --ll '/*'
```
Querying the single file `/tmp/archives/linux/Makefile`
```
bin/ltsmc --query --fsname '/' --node lxdv81 --password lxdv81 --servername=lxdv81-kvm-tsm-server --hl '/tmp/archives/linux' --ll '/Makefile'
```
### Retrieving Data
We first delete all data in `/tmp/archives/linux` and the restore the data to that directory:
```
rm -rf /tmp/archives/linux && bin/ltsmc --retrieve --fsname '/' --node lxdv81 --password lxdv81 --servername=lxdv81-kvm-tsm-server --hl '/tmp/archives/linux/*' --ll '/*'
```
### Deleting Data
To delete data on the TSM perform the following command:
```
bin/ltsmc --delete --fsname '/' --node lxdv81 --password lxdv81 --servername=lxdv81-kvm-tsm-server --hl '/tmp/archives/linux/*' --ll '/*'
```
A subsequent *delete* or *query* command shows that there is no data left on the TSM side.
```
bin/ltsmc --delete --fsname '/' --node lxdv81 --password lxdv81 --servername=lxdv81-kvm-tsm-server --hl '/tmp/archives/linux/*' --ll '/*'
```

### Screenshot and Screencast
Klick on the screenshot to see the full screencast
<a href="http://web-docs.gsi.de/~tstibor/tsm/ltsm-screencast-1.mp4" rel="screencast">![screencast](http://web-docs.gsi.de/~tstibor/tsm/ltsm-screenshot.png)</a>

## TODOs
* Integrate LTSMAPI into the Lustre HSM framework.
* Implement multiple objects per transaction, currently a single object is processed per transaction.
* Extend LTSMAPI with new compression stream algorithm such as LZ4 (perform a comparison to TSM built-in compression).
 
## Pitfalls in libApiTSM64.so
### Empty Files
Large directories can contain empty files and naively setting the estimated file size as follows:
```
objAttrArea.sizeEstimate.hi = 0;
objAttrArea.sizeEstimate.lo = 0;
```
leads to error `dsmSendData: ANS0344E (RC2107) Cannot Send data with a zero byte sizeEstimate.`
Whenever you are using the low-level library `libApiTSM64.so` make sure to catch this issue. A simple approach is:
```
dsStruct64_t hi_lo_size = to_dsStruct64_t(st_buf.st_size);

objAttrArea.sizeEstimate.hi = hi_lo_size.hi;
objAttrArea.sizeEstimate.lo = (hi_lo_size.hi == 0 && hi_lo_size.lo == 0) ? 1 : hi_lo_size.lo;
```
### Directories containing more than `DSM_MAX_GET_OBJ` files
Before you can retrieve archived data, calling function `dsmBeginQuery(...)` is required. Subsequently filling e.g. an array
of query replies is achieved with (multiple) function calls of `dsmGetNextQObj(...)`. However, when retrieving data
make sure to call function `dsmBeginGetData` with parameter `dsmGetList` with not more than `DSM_MAX_GET_OBJ` objects
values, otherwise your retrieving process will brake. A simple solution is to partition the query replies in chunks
of `DSM_MAX_GET_OBJ` and call `dsmBeginGetData` on these max chunk sizes.

## Issues
### Options file '*' could not be found, or it cannot be read

If you experience the error
```
[ERROR] (src/tsmapi.c) dsmInitEx: handle: 0 ANS1035S (RC406) Options file '*' could not be found, or it cannot be read.
```
then the environment variable `DSMI_CONFIG` is either not set or is pointing to an improper option file. When you checkout the repository, e.g. make sure to set `DSMI_CONFIG` as follows
```
export DSMI_CONFIG=`pwd`/dsmopt/dsm.sys
```
If you see the error
```
[ERROR] (src/tsmapi.c) dsmInitEx: handle: 0 ANS1217E (RC409)  Server name not found in System Options File
```
then as the message suggests the specified servername e.g. `--servername=<lxdv81-kvm-tsm-non-server>`does not exists in the option file `dsm.sys`.

### Recursive query

Suppose you want to query and list all archived data, however you don't know exactly the file paths. The following simple command query all archived data for the registered node
```
bin/ltsmc --query --fsname '/' --node lxdv81 --password lxdv81 --servername=lxdv81-kvm-tsm-server --hl '*' --ll '/*'
```

## References
A thorough description and code examples of IBM's low-level TSM API/library can be found in the open document [Using the Application Programming Interface](http://web-docs.gsi.de/~tstibor/tsm/doc/using_the_programming_application_interface.pdf), 2007.

## License
LTSM itself is licensed under the [GPL-2 license](http://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html). The code however, depends on IBM's low-level TSM API/library which are distributed 
under different licenses. See [IBM Tivoli Storage Manager Server](http://ftp.software.ibm.com/storage/tivoli-storage-management/maintenance/server/v7r1/Linux/7.1.5.000/README.htm).
