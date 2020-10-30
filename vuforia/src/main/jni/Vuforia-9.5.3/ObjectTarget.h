/*===============================================================================
Copyright (c) 2019 PTC Inc. All Rights Reserved.

Copyright (c) 2014 Qualcomm Connected Experiences, Inc. All Rights Reserved.

Vuforia is a trademark of PTC Inc., registered in the United States and other 
countries.

\file
    ObjectTarget.h

\brief
    Header file for the ObjectTarget Trackable type.
===============================================================================*/

#ifndef _VUFORIA_OBJECTTARGET_H_
#define _VUFORIA_OBJECTTARGET_H_

// Include files
#include <Vuforia/Trackable.h>
#include <Vuforia/Vectors.h>

namespace Vuforia
{

/// A type of Trackable that represents a real-world object.
class VUFORIA_API ObjectTarget : public Trackable
{
public:
    /// Get the Type for class "ObjectTarget".
    static Type getClassType();

    /// Get the persistent system-wide unique id for this target.
    /**
     * A target's unique id, which may be generated offline, identifies an
     * ObjectTarget across multiple %Vuforia sessions. It is a property of
     * %Vuforia's model of the object being tracked, and typically resides on
     * permanent storage as part of loadable DataSet.
     *
     * \note
     * Be careful not to confuse getUniqueTargetId() (which is persistent
     * across %Vuforia sessions) with Trackable::getId() (which is generated at
     * runtime and not persistent).
     */
    virtual const char* getUniqueTargetId() const = 0;

    /// Get the size of this target.
    /**
     * \return The size of this target, in meters (width, height, depth).
     */
    virtual Vec3F getSize() const = 0;

    /// Apply a uniform scale to this target that makes it the given size.
    /**
     * The requested size must represent a uniform scaling of the original
     * target's size (within a small margin of error.)
     *
     * If you try to set a size that is not the result of a uniform scaling of
     * the model stored in the DataSet, this method will fail.
     *
     * Once the size is changed, the original size is lost. If you need to be
     * able to restore the original size, call getSize() first and store the
     * result.
     *
     * \note
     * The DataSet that this Target belongs must not be active when this
     * function is called.
     *
     * \note
     * Rescaling should only be used if you have different physical copies of the
     * object at different sizes (for example if you have an image printed at
     * both A4 and A0 sizes). Do not use this method if you want to virtually
     * re-scale the pose returned by the tracker - this should be handled by your
     * own application logic.
     *
     * \param size The desired size of the target, in meters (width, height,
     * depth).
     * \returns true if the size was set successfully, or false if the DataSet
     * is active or the requested size does not represent a uniform scaling of
     * the size of model stored in the DataSet.
     */
    virtual bool setSize(const Vec3F& size) = 0;

    /// Target property that indicates how the target moves in space
    enum MOTION_HINT
    {
        STATIC,     ///< Optimize performance for objects that remain at the
                    ///< same location throughout the experience. Setting this 
                    ///< value allows %Vuforia to reduce CPU and power 
                    ///< consumption when PositionalDeviceTracker is enabled.
        ADAPTIVE    ///< Automatically optimize performance for experiences 
                    ///< ranging from mostly static objects to fully dynamic
                    ///< objects.
                    ///< \note Some target types do not support the full motion
                    ///< range, e.g. ModelTarget only allows limited object 
                    ///< motion. Refer to the specific target documentation for
                    ///< more information on their behavior.
    };

    /// Set the motion hint to indicate how the target moves in space.
    /**
    * %Vuforia may use the hint to optimize tracking performance and/or power 
    * consumption.
    *
    * Setting the motion hint is currently only supported on ModelTarget
    * trackables. The default value for a ModelTarget is specified in the 
    * dataset during target generation in the Model Target Generator. For older 
    * datasets where no motion hint was defined, the motion hint defaults to 
    * STATIC.
    *
    * For all targets other than ModelTarget, the motion hint value cannot be 
    * changed and defaults to ADAPTIVE.
    *
    * \note The DataSet this target belongs to must be deactivated when this
    * function is called.
    *
    * \param hint The motion hint.
    * \returns true if the hint was set successfully, or false if the DataSet is
    * active or the operation is not supported.
    */
    virtual bool setMotionHint(MOTION_HINT hint) = 0;

    /// Get the motion hint of this target.
    /**
    * For more details on the meaning of the value, please see the 
    * documentation of setMotionHint().
    * \returns The current motion hint of this target.
    */
    virtual MOTION_HINT getMotionHint() const = 0;
};

} // namespace Vuforia

#endif //_VUFORIA_OBJECTTARGET_H_
