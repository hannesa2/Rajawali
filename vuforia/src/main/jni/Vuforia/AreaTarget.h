/*===============================================================================
Copyright (c) 2020 PTC Inc. All Rights Reserved.

Vuforia is a trademark of PTC Inc., registered in the United States and other 
countries.

\file
    AreaTarget.h

\brief
    Header file for the AreaTarget Trackable type.
===============================================================================*/

#ifndef _VUFORIA_AREATARGET_H_
#define _VUFORIA_AREATARGET_H_

// Include files
#include <Vuforia/Trackable.h>
#include <Vuforia/Vectors.h>
#include <Vuforia/Box3D.h>

namespace Vuforia
{

/// A type of Trackable that represents a scanned physical environment.
class VUFORIA_API AreaTarget : public Trackable
{
public:
    /// Get the Type for class "Trackable".
    static Type getClassType();

    /// Get the persistent system-wide unique id for this target.
    /**
     * A target's unique id, which may be generated offline, identifies an
     * AreaTarget across multiple %Vuforia sessions. It is a property of
     * %Vuforia's model of the physical environment being tracked, and
     * typically resides on permanent storage as part of loadable DataSet.
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

    /// Get the bounding box of this target.
    /**
     * \returns An axis-aligned box that completely encloses the 3D geometry
     * that this AreaTarget represents.
     */
    virtual const Box3D& getBoundingBox() const = 0;

    /// Set approximate position within the target from an external localization source.
    /**
     * Setting up the external position only succeeds when the target is activated.
     * 
     * \note
     * The provided external position is valid until a successful localization,
     * target deactivation, or updating the external position by a repeated call
     * of this method (whichever happens first).
     * 
     * \param position Position (x, z) in target coordinate system (which is y-up).
     * \param radius Uncertainty of the position in meters. Must be positive.
     * \returns true on success, false on failure.
     */
    virtual bool setExternalPosition(const Vuforia::Vec2F& position, float radius) = 0;

    /// Check whether the target requires external positions for initial detection.
    /**
     * Large targets require external positions to provide an initial hint about
     * which data to load. Until an external position is provided, the large 
     * target will not be detected. This is also necessary after an extended loss
     * of tracking, e.g. after pausing the app and moving to a new location.
     *
     * \note
     * The external position should be set using AreaTarget::setExternalPosition().
     *
     * \returns true if the target needs external positions for initial detection
     * or after extended loss of tracking.
     */
    virtual bool requiresExternalPositions() const = 0;
};

} // namespace Vuforia

#endif //_VUFORIA_AREATARGET_H_
