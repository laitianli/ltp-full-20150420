/*
 * Copyright (c) 2000 Silicon Graphics, Inc.  All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it would be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * Further, this software is distributed without any warranty that it is
 * free of the rightful claim of any third person regarding infringement
 * or the like.  Any license provided herein, whether implied or
 * otherwise, applies only to this software file.  Patent licenses, if
 * any, provided herein do not apply to combinations of this program with
 * other software, or any other product whatsoever.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,
 * Mountain View, CA  94043, or:
 *
 * http://www.sgi.com
 *
 * For further information regarding this notice, see:
 *
 * http://oss.sgi.com/projects/GenInfo/NoticeExplan/
 *
 */
/* $Id: lseek01.c,v 1.5 2009/11/02 13:57:17 subrata_modak Exp $ */
/**********************************************************
 *
 *    OS Test - Silicon Graphics, Inc.
 *
 *    TEST IDENTIFIER	: lseek01
 *
 *    EXECUTED BY	: anyone
 *
 *    TEST TITLE	: Basic test for lseek(2)
 *
 *    PARENT DOCUMENT	: usctpl01
 *
 *    TEST CASE TOTAL	: 3
 *
 *    WALL CLOCK TIME	: 1
 *
 *    CPU TYPES		: ALL
 *
 *    AUTHOR		: William Roske
 *
 *    CO-PILOT		: Dave Fenner
 *
 *    DATE STARTED	: 03/30/92
 *
 *    INITIAL RELEASE	: UNICOS 7.0
 *
 *    TEST CASES
 *
 * 	1.) lseek(2) returns...(See Description)
 *
 *    INPUT SPECIFICATIONS
 * 	The standard options for system call tests are accepted.
 *	(See the parse_opts(3) man page).
 *
 *    OUTPUT SPECIFICATIONS
 *$
 *    DURATION
 * 	Terminates - with frequency and infinite modes.
 *
 *    SIGNALS
 * 	Uses SIGUSR1 to pause before test if option set.
 * 	(See the parse_opts(3) man page).
 *
 *    RESOURCES
 * 	None
 *
 *    ENVIRONMENTAL NEEDS
 *      No run-time environmental needs.
 *
 *    SPECIAL PROCEDURAL REQUIREMENTS
 * 	None
 *
 *    INTERCASE DEPENDENCIES
 * 	None
 *
 *    DETAILED DESCRIPTION
 *	This is a Phase I test for the lseek(2) system call.  It is intended
 *	to provide a limited exposure of the system call, for now.  It
 *	should/will be extended when full functional tests are written for
 *	lseek(2).
 *
 * 	Setup:
 * 	  Setup signal handling.
 *	  Pause for SIGUSR1 if option specified.
 *
 * 	Test:
 *	 Loop if the proper options are given.
 * 	  Execute system call
 *	  Check return code, if system call failed (return=-1)
 *		Log the errno and Issue a FAIL message.
 *	  Otherwise, Issue a PASS message.
 *
 * 	Cleanup:
 * 	  Print errno log and/or timing stats if options given
 *
 *
 *#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#**/

#include <sys/types.h>
#include <sys/fcntl.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include "test.h"

void setup();
void cleanup();

char *TCID = "lseek01";
int TST_TOTAL = 3;

char Fname[255];
int Fd;

int Whence[] = { SEEK_SET, SEEK_CUR, SEEK_END, -1 };

int main(int ac, char **av)
{
	int lc;

	int ind;
	int offset;

    /***************************************************************
     * parse standard options
     ***************************************************************/
	tst_parse_opts(ac, av, NULL, NULL);

    /***************************************************************
     * perform global setup for test
     ***************************************************************/
	setup();

    /***************************************************************
     * check looping state if -c option given
     ***************************************************************/
	for (lc = 0; TEST_LOOPING(lc); lc++) {

		tst_count = 0;

		offset = (lc % 100) * 4096;	/* max size is 100 blocks */

		for (ind = 0; Whence[ind] >= 0; ind++) {

			/*
			 *  Call lseek(2)
			 */
			TEST(lseek(Fd, (long)offset, Whence[ind]));

			/* check return code */
			if (TEST_RETURN == -1) {
				tst_resm(TFAIL,
					 "lseek(%s, %d, 0) Failed, errno=%d : %s",
					 Fname, offset, TEST_ERRNO,
					 strerror(TEST_ERRNO));
			} else {
				tst_resm(TPASS,
					 "lseek(%s, %d, %d) returned %ld",
					 Fname, offset, Whence[ind],
					 TEST_RETURN);
			}
		}

	}

	cleanup();
	tst_exit();
}

/***************************************************************
 * setup() - performs all ONE TIME setup for this test.
 ***************************************************************/
void setup(void)
{

	tst_sig(NOFORK, DEF_HANDLER, cleanup);

	TEST_PAUSE;

	tst_tmpdir();

	sprintf(Fname, "tfile_%d", getpid());
	if ((Fd = open(Fname, O_RDWR | O_CREAT, 0700)) == -1) {
		tst_brkm(TBROK, cleanup,
			 "open(%s, O_RDWR|O_CREAT,0700) Failed, errno=%d : %s",
			 Fname, errno, strerror(errno));
	}
}

/***************************************************************
 * cleanup() - performs all ONE TIME cleanup for this test at
 *		completion or premature exit.
 ***************************************************************/
void cleanup(void)
{

	/* close the file we have open */
	if (close(Fd) == -1) {
		tst_resm(TWARN, "close(%s) Failed, errno=%d : %s", Fname, errno,
			 strerror(errno));
	}

	tst_rmdir();

}