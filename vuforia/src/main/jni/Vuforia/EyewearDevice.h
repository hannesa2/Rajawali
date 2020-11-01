/*===============================================================================
Copyright (c) 2019 PTC Inc. All Rights Reserved.

Confidential and Proprietary - Protected under copyright and other laws.
Vuforia is a trademark of PTC Inc., registered in the United States and other
countries.

\file
EyewearDevice.h

\brief
Header file for EyewearDevice class.
==============================================================================*/

#ifndef _VUFORIA_EYEWEAR_DEVICE_H_
#define _VUFORIA_EYEWEAR_DEVICE_H_

// Include files
#include <Vuforia/Device.h>
#include <Vuforia/EyewearUserCalibrator.h>

namespace Vuforia
{

/// A type of Device which is used when %Vuforia runs on dedicated eyewear.
class VUFORIA_API EyewearDevice : public Device
{
public:

    /// Device orientation
    enum ORIENTATION
    {
        ORIENTATION_UNDEFINED = 0,  ///< The device's orientation is undefined.
        ORIENTATION_PORTRAIT,       ///< The device orientation is portrait
        ORIENTATION_LANDSCAPE_LEFT, ///< The device orientation is landscape,
                                    ///< rotated left from portrait
        ORIENTATION_LANDSCAPE_RIGHT ///< The device orientation is landscape,
                                    ///< rotated right from portrait
    };

    /// Get the Type for class 'EyewearDevice'.
    static Type getClassType();

    /// Get whether this eyewear device has a see-through display.
    virtual bool isSeeThru() const = 0;

    /// Get the screen orientation that should be used when rendering for this device.
    virtual ORIENTATION getScreenOrientation() const = 0;

    /// Get the calibrator used for creating custom user calibration experiences. (DEPRECATED)
    /**
     * \deprecated This method has been deprecated. It will be removed in an
     * upcoming %Vuforia release.
     *
     * \note This calibration is only relevant for see-through eyewear devices.
     */
    virtual EyewearUserCalibrator& getUserCalibrator() = 0;
};

} // namespace Vuforia

#endif // _VUFORIA_EYEWEAR_DEVICE_H_
