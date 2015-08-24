#
#    config.mk.in.
#
#    Copyright (C) 2009, Cisco Systems Inc.
#
#    This program is free software; you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation; either version 2 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License along
#    with this program; if not, write to the Free Software Foundation, Inc.,
#    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#
# Garrett Cooper, July 2009
#

# See this page for more info about LEX*:
# http://www.gnu.org/software/hello/manual/autoconf/Particular-Programs.html

# Application specifying variables. You should never have to change these.
AR			:= ar
CC			:= gcc
LEX			:= flex
RANLIB			:= ranlib
STRIP			:= strip
YACC			:= bison -y

# XXX: I'm lazy... but if someone has a working javac, they should have a
# working jar on their systems.
JAR			:= jar
JAVAC			:= @JAVAC@

AIO_LIBS		:= 
CAP_LIBS		:= 
ACL_LIBS		:= -lacl
CRYPTO_LIBS		:= -lcrypto
LEXLIB			:= -lfl
NUMA_CPPFLAGS		:= 
NUMA_LIBS		:= 
SELINUX_LIBS		:= -lselinux
TIRPC_CPPFLAGS		:= 
TIRPC_LIBS		:= 

prefix			:= /opt/ltp

datarootdir		:= ${prefix}/share
includedir		:= ${prefix}/include
exec_prefix		:= ${prefix}
bindir			:= ${exec_prefix}/bin
libdir			:= ${exec_prefix}/lib
mandir			:= ${datarootdir}/man

CPPFLAGS		:=  -D_FORTIFY_SOURCE=2
CFLAGS			:= -g -O2
LDLIBS			:= 
LDFLAGS			:= 

DEBUG_CFLAGS		?= -g
DEBUG_CXXFLAGS		?= $(DEBUG_CFLAGS)

# Please see README.mk-devel about -fstrict-aliasing.
OPT_CFLAGS		?= -O2 -fno-strict-aliasing -pipe
OPT_CXXFLAGS		?= $(OPT_CFLAGS)

WCFLAGS			?= -Wall -W -g -O2 -Wold-style-definition
WCXXFLAGS		?= $(WCFLAGS)

LDFLAGS			+= $(WLDFLAGS)
CFLAGS			+= $(DEBUG_CFLAGS) $(OPT_CFLAGS) $(WCFLAGS)
CXXFLAGS		+= $(DEBUG_CXXFLAGS) $(OPT_CXXFLAGS) $(WCXXFLAGS)

LINUX_VERSION		:= 2.6.18-402.el5
LINUX_DIR		:= /lib/modules/2.6.18-402.el5/build
LINUX_VERSION_MAJOR	:= 2
LINUX_VERSION_PATCH	:= 6
WITH_MODULES		:= yes

ifeq ($(strip $(prefix)),)
$(error you are using $$(prefix) incorrectly -- set it to $(abs_top_srcdir) if you want to build in the source tree)
endif

export datarootdir includedir libdir mandir prefix
