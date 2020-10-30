/*===============================================================================
Copyright (c) 2019 PTC Inc. All Rights Reserved.

Copyright (c) 2014 Qualcomm Connected Experiences, Inc. All Rights Reserved.

Vuforia is a trademark of PTC Inc., registered in the United States and other 
countries.

\file
    ObjectTracker.h

\brief
    Header file for ObjectTracker class.
===============================================================================*/

#ifndef _VUFORIA_OBJECT_TRACKER_H_
#define _VUFORIA_OBJECT_TRACKER_H_

// Include files
#include <Vuforia/Tracker.h>
#include <Vuforia/Vuforia.h>
#include <Vuforia/List.h>

namespace Vuforia
{

// Forward Declaration
class Trackable;
class DataSet;
class ImageTargetBuilder;
class RuntimeImageSource;
class TargetFinder;

/// A type of Tracker that tracks objects in the real world.
/**
 *  An ObjectTracker tracks all target types that inherit from ObjectTarget (for
 *  a full list, refer to the inheritance tree diagram for ObjectTarget).
 *
 *  The data for these Trackable instances is stored in DataSet instances, which
 *  are owned and managed by the ObjectTracker.
 *
 *  The ObjectTracker class provides methods for creating, activating and
 *  deactivating DataSets.
 *
 *  \note Calls to activateDataSet() and deactivateDataSet() should be avoided
 *  while the ObjectTracker is actively processing a frame, as such calls will
 *  block until the ObjectTracker has finished.
 *
 *  If you do need to call these methods during execution, the suggested way of
 *  doing so is via the UpdateCallback mechanism, as the callback is done at a
 *  point where the ObjectTracker is guaranteed to be idle. Alternatively, the
 *  ObjectTracker can be explicitly stopped and then restarted. However this is
 *  a very expensive operation.
 */
class VUFORIA_API ObjectTracker : public Tracker
{
public:

    /// Returns the Type for class 'ObjectTracker'.
    static Type getClassType();

    /// Create an empty DataSet.
    /**
     *  \returns the new instance on success, NULL otherwise.
     *
     *  Use destroyDataSet() to destroy a DataSet that is no longer needed.
     */      
    virtual DataSet* createDataSet() = 0;

    /// Destroy the given DataSet and release allocated resources.
    /**
     * \returns true on success, or false if the DataSet is active.
     */
    virtual bool destroyDataSet(DataSet* dataset) = 0;

    /// Activate the given DataSet.
    /**
     * \returns true if the DataSet was successfully activated, otherwise false
     * (check application log for failure details).
     *
     * \note To activate a dataset, you should use one of these 3 supported mechanisms:
     * - initialization time: activate it before starting the tracker,
     * - run time: if you have started the tracker, activate the dataset in the UpdateCallback,
     * - run time: if you have started the tracker, stop the tracker first, activate the dataset,
     * then restart the tracker.
     */
    virtual bool activateDataSet(DataSet* dataset) = 0;
    
    /// Deactivate the given DataSet.
    /**
     * \returns true if the DataSet was successfully deactivated, otherwise
     * false (e.g. because the DataSet is not currently active) (check
     * application log for failure details).
     *
     * \note To deactivate a dataset, you should use one of these 3 supported mechanisms:
     * - deinitialization time: deactivate it after stopping the tracker,
     * - run time: if you have started the tracker, deactivate the dataset in the UpdateCallback,
     * - run time: if you have started the tracker, stop the tracker first, deactivate the dataset,
     * then restart the tracker.
     */
    virtual bool deactivateDataSet(DataSet* dataset) = 0;

    /// Provides access to the list of currently active active datasets.
    virtual List<DataSet> getActiveDataSets() = 0;

    /// Get the ImageTargetBuilder for the current scene.
    /**
     * \returns The ImageTargetBuilder that should be used if you want to
     * generate <span>ImageTarget</span>s at runtime from the camera input.
     */
    virtual ImageTargetBuilder* getImageTargetBuilder() = 0;
    
    /// Get the RuntimeImageSource for the current session.
    /**
     * This RuntimeImageSource instance should be reused to create multiple image targets.
     *
     * \returns The RuntimeImageSource that should be used if you want to
     * generate <span>ImageTarget</span>s at runtime from external image sources (e.g. file, raw buffer).
     */
    virtual RuntimeImageSource* getRuntimeImageSource() = 0;


    /// The type of Target finder to return
    /**
     * Enum describing the different TargetFinder types that Vuforia can return
     */
    enum TargetFinderType
    {
        CLOUD_RECO, ///< A TargetFinder to recognize ImageTargets using cloud-based
                    ///< image recognition.
    };
    
    /// Get the TargetFinder for the current scene.
    /**
     * \param type The type of the TargetFinder to be returned.
     * \returns The requested TargetFinder.
     */
    virtual TargetFinder* getTargetFinder(
        TargetFinderType type = CLOUD_RECO
    ) = 0;

};

} // namespace Vuforia

#endif //_VUFORIA_OBJECT_TRACKER_H_
