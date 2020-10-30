/*===============================================================================
Copyright (c) 2020 PTC Inc. All Rights Reserved.

Vuforia is a trademark of PTC Inc., registered in the United States and other 
countries.

\file
    AreaTracker.h

\brief
    Header file for AreaTracker class.
===============================================================================*/

#ifndef _VUFORIA_AREATRACKER_H_
#define _VUFORIA_AREATRACKER_H_

// Include files
#include <Vuforia/Tracker.h>
#include <Vuforia/Vuforia.h>
#include <Vuforia/List.h>

namespace Vuforia
{

// Forward Declaration
class Trackable;
class DataSet;

/// A type of Tracker that tracks scanned physical environments.
/**
 *  An AreaTracker tracks AreaTargets.
 *
 *  The data for these Trackable instances is stored in DataSet instances, which
 *  are owned and managed by the AreaTracker.
 *
 *  The AreaTracker class provides methods for creating, activating and
 *  deactivating DataSets.
 *
 *  \note Calls to activateDataSet() and deactivateDataSet() should be avoided
 *  while the AreaTracker is actively processing a frame, as such calls will
 *  block until the AreaTracker has finished.
 *
 *  \note AreaTracker requires Platform fusion provider and won't work with
 *  Vuforia Sensor Fusion and Vuforia Vision Only.
 *  
 *  If you do need to call these methods during execution, the suggested way of
 *  doing so is via the UpdateCallback mechanism, as the callback is done at a
 *  point where the AreaTracker is guaranteed to be idle. Alternatively, the
 *  AreaTracker can be explicitly stopped and then restarted. However this is
 *  a very expensive operation.
 */
class VUFORIA_API AreaTracker : public Tracker
{
public:

    /// Returns the Type for class 'AreaTracker'.
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
     * \note Activating a DataSet during live processing can be a blocking
     * operation. To avoid this, call activateDataSet via the UpdateCallback
     * mechanism (which guarantees that the AreaTracker will be idle), or
     * explicitly stop the AreaTracker first, and then start it again when
     * finished.
     */
    virtual bool activateDataSet(DataSet* dataset) = 0;
    
    /// Deactivate the given DataSet.
    /**
     * \returns true if the DataSet was successfully deactivated, otherwise
     * false (e.g. because the DataSet is not currently active) (check
     * application log for failure details).
     *
     * \note Deactivating a DataSet during live processing can be a blocking
     * operation. To avoid this, call deactivateDataSet via the UpdateCallback
     * mechanism (which guarantees that the AreaTracker will be idle), or
     * explicitly stop the AreaTracker first, and then start it again when
     * finished.
     */
    virtual bool deactivateDataSet(DataSet* dataset) = 0;

    /// Provides access to the list of currently active datasets.
    virtual List<DataSet> getActiveDataSets() = 0;

};

} // namespace Vuforia

#endif //_VUFORIA_AREATRACKER_H_
