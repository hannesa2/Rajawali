/*===============================================================================
Copyright (c) 2018 PTC Inc. All Rights Reserved.

Vuforia is a trademark of PTC Inc., registered in the United States and other 
countries.

@file
    Vuforia_Android.h

@brief
    Header file for global Vuforia methods that are specific to Android
===============================================================================*/

#ifndef _VUFORIA_VUFORIA_ANDROID_H_
#define _VUFORIA_VUFORIA_ANDROID_H_

// Include files
#include <Vuforia/System.h>
#include <jni.h>

namespace Vuforia
{


/// Set %Vuforia initialization parameters.
/**
 * <b>Android:</b> Call this function before calling Vuforia::init().
 *
 * See the "Lifecycle of a Vuforia app" section on the main %Vuforia
 * reference page for more information. \ref Lifecycle "Lifecycle of a Vuforia app"
 *
 * \param activity The Activity that %Vuforia should run under.
 * \param flags Flags to set. See Vuforia::INIT_FLAGS for appropriate flags.
 * \param licenseKey Your %Vuforia license key.
 */
void VUFORIA_API setInitParameters(jobject activity, int flags, const char* licenseKey);

} // namespace Vuforia

#endif //_VUFORIA_VUFORIA_ANDROID_H_
