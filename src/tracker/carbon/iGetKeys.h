/*
    File: iGetKeys.h
    
    Description:
       Internationally Savy GetKeys test type routines for your entertainment
       and enjoyment.

    
    Disclaimer:
        IMPORTANT:  This Apple software is supplied to you by Apple Computer, Inc.
        ("Apple") in consideration of your agreement to the following terms, and your
        use, installation, modification or redistribution of this Apple software
        constitutes acceptance of these terms.  If you do not agree with these terms,
        please do not use, install, modify or redistribute this Apple software.

        In consideration of your agreement to abide by the following terms, and subject
        to these terms, Apple grants you a personal, non-exclusive license, under Apple�s
        reproduce, modify and redistribute the Apple Software, with or without
        modifications, in source and/or binary forms; provided that if you redistribute
        the Apple Software in its entirety and without modifications, you must retain
        this notice and the following text and disclaimers in all such redistributions of
        the Apple Software.  Neither the name, trademarks, service marks or logos of
        Apple Computer, Inc. may be used to endorse or promote products derived from the
        Apple Software without specific prior written permission from Apple.  Except as
        expressly stated in this notice, no other rights or licenses, express or implied,
        are granted by Apple herein, including but not limited to any patent rights that
        may be infringed by your derivative works or by other works in which the Apple
        Software may be incorporated.

        The Apple Software is provided by Apple on an "AS IS" basis.  APPLE MAKES NO
        WARRANTIES, EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION THE IMPLIED
        WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A PARTICULAR
        PURPOSE, REGARDING THE APPLE SOFTWARE OR ITS USE AND OPERATION ALONE OR IN
        COMBINATION WITH YOUR PRODUCTS.

        IN NO EVENT SHALL APPLE BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL OR
        CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
        GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
        ARISING IN ANY WAY OUT OF THE USE, REPRODUCTION, MODIFICATION AND/OR DISTRIBUTION
        OF THE APPLE SOFTWARE, HOWEVER CAUSED AND WHETHER UNDER THEORY OF CONTRACT, TORT
        (INCLUDING NEGLIGENCE), STRICT LIABILITY OR OTHERWISE, EVEN IF APPLE HAS BEEN
        ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

    Change History (most recent first):
        Mon, Jan 15, 2001 -- created
*/

#ifndef __IGETKEYS__
#define __IGETKEYS__

#ifdef __APPLE_CC__
#include <Carbon/Carbon.h>
#else
#include <Carbon.h>
//#include <Types.h>
#endif

typedef struct {
	short kchrID;
        Str255 KCHRname;
	short transtable[256];
} Ascii2KeyCodeTable;



enum {
		/* modifier keys */
	kVirtualCapsLockKey = 0x039,
	kVirtualShiftKey = 0x038,
	kVirtualControlKey = 0x03B,
	kVirtualOptionKey = 0x03A,
	kVirtualCommandKey = 0x037,
		/* editing/utility keys */
	kVirtualHelpKey = 0x072,
	kVirtualDeleteKey = 0x033,
	kVirtualTabKey = 0x030,
	kVirtualEnterKey = 0x04C,
	kVirtualReturnKey = 0x024,
	kVirtualEscapeKey = 0x035,
	kVirtualForwardDeleteKey = 0x075,
		/* navigation keys */
	kVirtualHomeKey = 0x073,
	kVirtualEndKey = 0x002,
	kVirtualPageUpKey = 0x074,
	kVirtualPageDownKey = 0x079,
	kVirtualLeftArrowKey = 0x07B,
	kVirtualRightArrowKey = 0x07C,
	kVirtualUpArrowKey = 0x07E,
	kVirtualDownArrowKey = 0x07D

};

enum {
	kPublicBetaVirtualLeftArrowKey = 0x03B, /* Public Beta Only */
	kPublicBetaVirtualRightArrowKey = 0x03C, /* Public Beta Only */
	kPublicBetaVirtualUpArrowKey = 0x03E, /* Public Beta Only */
	kPublicBetaVirtualDownArrowKey = 0x03D, /* Public Beta Only */
	kPublicBetaVirtualCapsLockKey = 0x03D, /* Public Beta Only */
	kPublicBetaVirtualHelpKey = 0x03D /* Public Beta Only */
};


	/* InitAscii2KeyCodeTable initializes the ascii to key code
	look up table using the currently active KCHR resource. This
	routine calls GetResource so it cannot be called at interrupt time.*/
OSStatus InitAscii2KeyCodeTable(Ascii2KeyCodeTable *ttable);

	/* ValidateAscii2KeyCodeTable verifies that the ascii to key code
	lookup table is synchronized with the current KCHR resource.  If
	it is not synchronized, then the table is re-built. This routine calls
	GetResource so it cannot be called at interrupt time.*/
OSStatus ValidateAscii2KeyCodeTable(Ascii2KeyCodeTable *ttable,Boolean *wasChanged);

StringPtr GetKchrName(Ascii2KeyCodeTable *ttable);

	/* AsciiToKeyCode looks up the ascii character in the key
	code look up table and returns the virtual key code for that
	letter.  If there is no virtual key code for that letter, then
	the value -1 will be returned. */
short AsciiToKeyCode(Ascii2KeyCodeTable *ttable, short asciiCode);

char KeyCodeToAscii(short virtualKeyCode);

	/* TestForKeyDown returns true if the key with the given
	virtual key code is currently being held down. */
Boolean TestForKeyDown(short virtualKeyCode);


	/* TestForMultipleKeysDown returns true if all of the keys listed
	in its parameters are held down.  nkeys is the number of virtual key
	codes provided in the variable length parameter list that follows. */
Boolean TestForMultipleKeysDown(short nkeys, ...);
Boolean TestForArrayOfKeysDown(short nkeys, short *keyvec);


	/* TestForAsciiKeyDown returns true if the key with the given
	ascii code is currently being held down. */
Boolean TestForAsciiKeyDown(Ascii2KeyCodeTable *ttable, short asciiCode);


	/* TestForAsciiKeyDown returns true if all of the keys
	with the key with the given ascii codes are currently being
	held down. nkeys is the number of ascii codes provided in the
	variable length parameter list that follows. */
Boolean TestForMultipleAsciiKeysDown(Ascii2KeyCodeTable *ttable, short nkeys, ...);
Boolean TestForArrayOfAsciiKeysDown(Ascii2KeyCodeTable *ttable, short nkeys, unsigned char* asciiVec);

#endif
