/*==============================================================================
Copyright (c) 2019 PTC Inc. All Rights Reserved.

Copyright (c) 2015 Qualcomm Connected Experiences, Inc. All Rights Reserved.

Vuforia is a trademark of PTC Inc., registered in the United States and other
countries.

\file
Device.h

\brief
Header file for Device class.
==============================================================================*/

#ifndef _VUFORIA_DEVICE_H_
#define _VUFORIA_DEVICE_H_

// Include files
#include <Vuforia/NonCopyable.h>
#include <Vuforia/Type.h>
#include <Vuforia/RenderingPrimitives.h>

namespace Vuforia
{

/// Singleton representation of the device %Vuforia is currently running on.
/**
 * %Vuforia supports many different hardware configurations. This class
 * provides management and configuration functions for the specific
 * configuration that %Vuforia is currently running on.
 *
 * Changes made here primarily affect how the RenderingPrimitives are created
 * and structured.
 */
class VUFORIA_API Device : private NonCopyable
{
public:

    /// Get the singleton instance.
    /**
     * This function can be used immediately after Vuforia::init() has succeeded.
     * See the "Lifecycle of a Vuforia app" section on the main %Vuforia
     * reference page for more information.
     * \ref Lifecycle "Lifecycle of a Vuforia app"
     */
    static Device& getInstance();

    /// Get the Type for class "Device".
    static Type getClassType();

    /// Get the Type of this instance (may be a subclass of Device).
    virtual Type getType() const = 0;

    /// Get whether this Device instance's type equals or has been derived from the given type.
    virtual bool isOfType(Type type) const = 0;

    /// Tell %Vuforia that the configuration has changed, so new RenderingPrimitives need to be generated.
    virtual void setConfigurationChanged() = 0;

    /// Get a copy of the RenderingPrimitives for the current configuration.
    /**
     * The RenderingPrimitives returned from this function are immutable, and
     * tailored to the current device environment.
     *
     * RenderingPrimitives can be retrieved at the earliest after the first call
     * to Vuforia::onSurfaceChanged().
     *
     * New RenderingPrimitives will be created whenever the device environment
     * changes in one of the following ways:
     *    - display size and/or orientation (i.e., when Vuforia::onSurfaceChanged()
     *    is called)
     *    - video mode (i.e., when CameraDevice::selectVideoMode() is called)
     *    - video background configuration (i.e., when Renderer::setVideoBackgroundConfig()
     *    is called)
     *
     * If you have cached a copy of the RenderingPrimitives and you make any of
     * the above changes, you will need use this method to get an updated copy
     * of the RenderingPrimitives that reflects the new device environment.
     *
     * \note
     * Platform-specific lifecycle transitions (e.g. Pause/Resume) may also cause
     * the configuration to change, so it is advisable to retrieve new
     * RenderingPrimitives after those transitions.
     *
     * \note
     * RenderingPrimitives will not be valid until a CameraDevice has been initialised.
     *
     * \note
     * This method returns a copy, which has an associated cost. Performant apps
     * should avoid calling this method if the configuration has not changed.
     */
    virtual const RenderingPrimitives getRenderingPrimitives() = 0;

};

} // namespace Vuforia

#endif // _VUFORIA_DEVICE_H_
