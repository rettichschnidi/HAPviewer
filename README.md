Introduction
============
HAPviewer is a host application profile graphlet viewer. It visualizes
network data through graphs on a per-host level in such a way that
running applications are apparent. Moreover, it summarizes groups of 
flows in an intelligent way providing aggregates of per-role traffic.
Supported roles are: client, server, multi-clients and variations of
peer-to-peer.

Licensing
=========
Distributed under the GNU General Public License version 2 (GPL.txt)
or the modified BSD (BSD.txt) license unless specified otherwise.
A list of authors can be found in file 'AUTHORS' which is part of
the source code package.

Installation
============
Basic Requirements

 * Boost regex, confirmed to work with version 1.40+
 * CMake, version 2.6 or later
 * g++, confirmed to work with version 4.2.4+
 * GNU/Linux, FreeBSD or OpenBSD

Additional GUI requirements

 * Boost graph, confirmed to work with version 1.40+
 * libgraphviz (libgvc), confirmed to work with version 2.16+
 * libgtkmm-2.4 (incl. freetype), confirmed to work with version 2.12.5+

Additional requirements for libtest, showcflow, mkcflows, mktestcflows

 * Boost program_options, iostreams, filesystem, confirmed to work with version 1.40+

Additional requirements for cflow support

 * Boost iostreams, filesystem (Cflow support), confirmed to work with version 1.40+

Additional requirements for IPFIX support

 * libfixbuf (IPFIX support), confirmed to work with version 0.9.0
 * glib, confirmed to work with version 2.16.6 and later
 
Additional requirements for IPFIX support

 * libpcap++ (pcap support), confirmed to work with svn revision 140

Additional requirements to build the documentation

 * Doxygen

Configuring the project
=======================
	mkdir build_hapviewer
	cd build_hapviewer
	cmake ../hapviewer
	ccmake .                 # configure HAPviewer according to your needs

NOTICE: in case of configuration errors please consult file 'INSTALL_FAQ.txt'.

Overview of some configuration options supported:

HAPVIEWER_DEBUG*	: Enables debug messages (usually off)

HAPVIEWER_ENABLE_ARGUS	: Enables import of Argus data 
			  (http://www.qosient.com/argus/index.shtml)

HAPVIEWER_ENABLE_CFLOW	: Enables import of HAPviewer proprietary binary 
			  flow data (see cflow.h for details)

HAPVIEWER_ENABLE_IPFIX	: Enables import of bidirectional IPFIX flow data 
			  (for import template see gfilter_ipfix_vx5ipfix_bi.cpp)

HAPVIEWER_ENABLE_NFDUMP	: Enables import of uncompressed nfdump flow data
			  (http://nfdump.sourceforge.net/)

HAPVIEWER_ENABLE_NFDUMP	: Enables import of PCAP packet data
			  (http://wiki.wireshark.org/Development/LibpcapFileFormat)


Make targets
============
	make           # build all the enabled targets (hapviz, haplibtest, HAPviewer, etc.)
	make test      # run the integrated tests (if enabled in ccmake)
	make clean     # clean up the project
	make doc       # build the doxygen documentation (if enabled in ccmake)
	make install   # installs the built targets (requires root permissions)


Documentation
=============
A basic project and program description can be found under: http://hapviewer.sourceforge.net/

A description of the source code can be created by "make doc" and will be placed into
the sub-directory "doxygen_docu/html" in the build directory. To view just open 
file index.html with your preferred web browser.
