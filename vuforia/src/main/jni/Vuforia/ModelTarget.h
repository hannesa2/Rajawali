/*===============================================================================
Copyright (c) 2020 PTC Inc. All Rights Reserved.

Vuforia is a trademark of PTC Inc., registered in the United States and other
countries.

\file
ModelTarget.h

\brief
Header file for the ModelTarget Trackable type.
===============================================================================*/

#ifndef _VUFORIA_MODELTARGET_H_
#define _VUFORIA_MODELTARGET_H_

// Include files
#include <Vuforia/ObjectTarget.h>
#include <Vuforia/Vectors.h>
#include <Vuforia/Obb3D.h>
#include <Vuforia/List.h>

namespace Vuforia
{

// Forward declarations
class GuideView;

/// A type of ObjectTarget that recognizes and tracks objects by shape using existing 3D models.
/**
 * A Model Target tracks a real world object by its shape, based on a 3D model
 * of the object.
 *
 * In order to initialize tracking of a Model Target, the user is required to
 * position their device so that the object to be tracked appears in the camera
 * at a particular position and orientation. This initialization pose is called
 * a Guide View. To assist in this process, your application will typically
 * render an overlay in the camera image representing the position and
 * orientation of the object for the active Guide View. (Usually you will do
 * this by rendering the image returned by GuideView::getImage()).
 *
 * A Model Target dataset may contain multiple objects and/or multiple Guide
 * Views.
 * * If you have a Model Target dataset containing a single object with multiple
 * Guide Views, you can switch between the Guide Views using
 * setActiveGuideViewIndex().
 * * If you have an Advanced Model Target dataset with multiple objects and/or
 * multiple Guide Views, the activated Guide View changes automatically when
 * recognized.
 * * If you have an Advanced 360 Model Target dataset, no Guide View access is
 * necessary.
 *
 * \note
 * It is not possible to modify a ModelTarget while its DataSet is active. See
 * the DataSet class for more information.
 */
class VUFORIA_API ModelTarget : public ObjectTarget
{
public:

    /// Return the Type for class "ModelTarget".
    static Type getClassType();

    /// Get the bounding box of this target.
    /**
     * \note
     * A call to setSize() will change the bounding box. If you have cached the
     * result of getBoundingBox(), you will need to call it again to obtain an
     * updated bounding box after every call to setSize().
     *
     * \returns An axis-aligned box that completely encloses the 3D geometry
     * that this ModelTarget represents, including any scaling applied via
     * setSize().
     */
    virtual const Obb3D& getBoundingBox() const = 0;
    
    /// Returns a list of guide views (write access).
    /**
     * Return a list of the GuideViews defined for this Model Target.
     */
    virtual List<GuideView> getGuideViews() = 0;

    /// Returns a list of guide views (read-only access).
    /**
     * Return a list of the Guide Views defined for this Model Target.
     */
    virtual List<const GuideView> getGuideViews() const = 0;

    /// Set the index of the Guide View you want to be active.
    /**
     * \note It is possible to use this function even when the dataset is deactivated.
     *
     * \note The default active GuideView is the first one in the dataset, i.e.
     * the one with index 0.
     *
     * \note If you are using an Advanced Model Target dataset containing either
     * multiple Model Targets and/or multiple Guide Views, the active Guide View index
     * is set automatically when a Model Target/Guide View is recognized.
     
     * \note If you are using an Advanced 360 Model Target, setting an active Guide View
     * is not necessary.
     *
     * \param idx The index of the GuideView to set as active, in the range
     * 0..(getGuideViews().size()-1) .
     * \returns true on success, false on failure (check application logs for
     * failure details).
     */
    virtual bool setActiveGuideViewIndex(int idx) = 0;

    /// Get the index of the currently active GuideView.
    /**
     * \note The default active GuideView is the first one in the dataset, i.e.
     * the one with index 0 for Model Targets. Advanced Model Targets will not have
     * an active Guide View set until one is recognized.
     *
     * \returns The index of the active GuideView in the range
     * 0..(getGuideViews().size()-1), or -1 in case no Guide View is active.
     */
    virtual int getActiveGuideViewIndex() const = 0;
    
    /// Tracking modes to optimize tracking quality and robustness for different target types.
    enum TRACKING_MODE
    {
        DEFAULT = 0,                ///< Tracking parameters optimized to work well on a broad range of object types.
        CAR = 1,                    ///< Tracking parameters optimized for car exteriors.
        SCAN = 2                    ///< Tracking parameters optimized for scanned models with photorealistic textures.
    };

    /// Set the tracking mode to indicate the type of the model target.
    /*
     * This hint modifies the internal Model Target tracking parameters to optimize
     * the tracking quality and robustness for different target types.
     *
     * \note Only changes between 'DEFAULT' and 'CAR' are supported.
     *
     * \note The DataSet this target belongs to must be deactivated when this
     * function is called.
     *
     * \param mode The tracking mode.
     * \returns true if the mode was set successfully, or false if the DataSet is
     * active or the operation is not supported.
     */
    virtual bool setTrackingMode(TRACKING_MODE mode) = 0;

    /// Get the tracking mode of this target.
    /**
    * For more details on the meaning of the value, please see the
    * documentation of setTrackingMode().
    * \returns The current tracking mode of this target.
    */
    virtual TRACKING_MODE getTrackingMode() const = 0;
};

} // namespace Vuforia

#endif //_VUFORIA_MODELTARGET_H_
