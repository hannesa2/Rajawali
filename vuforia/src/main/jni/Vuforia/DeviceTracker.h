/*==============================================================================
Copyright (c) 2019 PTC Inc. All Rights Reserved.

Copyright (c) 2015 Qualcomm Connected Experiences, Inc. All Rights Reserved.

Vuforia is a trademark of PTC Inc., registered in the United States and other
countries.

\file
    DeviceTracker.h

\brief
    Header file for DeviceTracker class. 
==============================================================================*/

#ifndef _VUFORIA_DEVICE_TRACKER_H_
#define _VUFORIA_DEVICE_TRACKER_H_

// Include files
#include <Vuforia/Tracker.h>
#include <Vuforia/Matrices.h>

namespace Vuforia
{

/// Tracks the device that %Vuforia is running on in the user's environment.
/**
 *  A DeviceTracker can be used to track the user's viewpoint (i.e. the position
 *  and orientation of the mobile or head-mounted device they are using to view
 *  the augmented world).
 *
 *  A DeviceTracker makes its results available via <span>DeviceTrackableResult</span>s,
 *  returned to the user via the State. The pose returned by DeviceTrackableResult::getPose()
 *  represents a transformation between a device frame of reference and the world
 *  frame of reference. For mobile devices, the device frame of reference is the
 *  same as the camera frame of reference. For eyewear devices, the device frame
 *  of reference varies by device.
 *
 *  The origin of the world is the starting position of the device.
 *
 */
class VUFORIA_API DeviceTracker : public Tracker
{
public:

    /// Get the Type for class 'DeviceTracker'.
    static Type getClassType();
};

} // namespace Vuforia

#endif //_VUFORIA_DEVICE_TRACKER_H_
