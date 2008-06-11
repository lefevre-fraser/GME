/*
 * Copyright (c) 2002, Vanderbilt University
 * All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written agreement is
 * hereby granted, provided that the above copyright notice, the following
 * two paragraphs and the author appear in all copies of this software.
 * 
 * IN NO EVENT SHALL THE VANDERBILT UNIVERSITY BE LIABLE TO ANY PARTY FOR
 * DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
 * OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE VANDERBILT
 * UNIVERSITY HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * THE VANDERBILT UNIVERSITY SPECIFICALLY DISCLAIMS ANY WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS
 * ON AN "AS IS" BASIS, AND THE VANDERBILT UNIVERSITY HAS NO OBLIGATION TO
 * PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
 *
 * Author: Miklos Maroti, Gyorgy Balogh
 * Date last modified: 10/23/03
 */

/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class org_isis_jaut_Apartment */

#ifndef _Included_org_isis_jaut_Apartment
#define _Included_org_isis_jaut_Apartment
#ifdef __cplusplus
extern "C" {
#endif
#undef org_isis_jaut_Apartment_COINIT_APARTMENTTHREADED
#define org_isis_jaut_Apartment_COINIT_APARTMENTTHREADED 2L
#undef org_isis_jaut_Apartment_COINIT_MULTITHREADED
#define org_isis_jaut_Apartment_COINIT_MULTITHREADED 0L
#undef org_isis_jaut_Apartment_COINIT_DISABLE_OLE1DDE
#define org_isis_jaut_Apartment_COINIT_DISABLE_OLE1DDE 4L
#undef org_isis_jaut_Apartment_COINIT_SPEED_OVER_MEMORY
#define org_isis_jaut_Apartment_COINIT_SPEED_OVER_MEMORY 8L
/*
 * Class:     org_isis_jaut_Apartment
 * Method:    coInitialize
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_isis_jaut_Apartment_coInitialize
  (JNIEnv *, jclass, jint);

/*
 * Class:     org_isis_jaut_Apartment
 * Method:    coUninitialize
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_isis_jaut_Apartment_coUninitialize
  (JNIEnv *, jclass);

#ifdef __cplusplus
}
#endif
#endif
