/*===============================================================================
Copyright (c) 2020 PTC Inc. All Rights Reserved.

Copyright (c) 2012-2014 Qualcomm Connected Experiences, Inc. All Rights Reserved.

Vuforia is a trademark of PTC Inc., registered in the United States and other 
countries.

\file
    TargetFinder.h

\brief
    Header file for TargetFinder class.
===============================================================================*/

#ifndef _VUFORIA_TARGET_FINDER_H_
#define _VUFORIA_TARGET_FINDER_H_

// Include files
#include <Vuforia/Vuforia.h>
#include <Vuforia/System.h>
#include <Vuforia/TargetSearchResult.h>
#include <Vuforia/List.h>
#include <Vuforia/NonCopyable.h>

namespace Vuforia
{

// Forward declarations
class DataSet;
class ObjectTarget;
class ObjectTarget;

/// Data structure to contain the TargetFinder search results of updateQueryResults()
struct TargetFinderQueryResult
{
    /// One of the UPDATE_* status codes
    /**
     * If new results are available, is UPDATE_RESULTS_AVAILABLE. Otherwise,
     * one of the other UPDATE_* status codes.
     */
    int status;

    /// List of TargetFinder search results
    List<const TargetSearchResult> results;
};

/// Efficiently recognizes particular targets in the camera feed.
/**
 * A TargetFinder identifies Image Targets in the camera feed. It can perform
 * detection and recognition, but is not able to track targets, nor provide
 * any kind of pose.
 *
 * A TargetFinder allows your application to support the detection and tracking
 * of a dramatically increased number of targets, by acting as a sort of filter
 * mechanism on the tracking environment. Based on the results of a TargetFinder
 * search, your application can selectively enable tracking for individual
 * targets *only when those targets are actually present* - avoiding expensive
 * and redundant tracking attempts for targets which are not present.
 *
 * A TargetFinder should be considered to operate asynchronously, offering
 * discrete results outside of the typical State lifecycle:
 * * TargetFinder results are not stored in the State.
 * * TargetFinder results may take several frames (or longer) to compute
 * (notably when using cloud-based image recognition) and may be delivered
 * asynchronously.
 * * TargetFinder results are delivered on-demand and must be explicitly
 * requested.
 *
 * Obtain a TargetFinder instance from the ObjectTracker by calling
 * ObjectTracker::getTargetFinder().
 */
class VUFORIA_API TargetFinder : private NonCopyable
{
public:

    /// Status codes returned by getInitState()
    enum
    {
        INIT_DEFAULT = 0,                       ///< Initialization has not started
        INIT_RUNNING = 1,                       ///< Initialization is running
        INIT_SUCCESS = 2,                       ///< Initialization completed successfully
        INIT_ERROR_NO_NETWORK_CONNECTION = -1,  ///< No network connection
        INIT_ERROR_SERVICE_NOT_AVAILABLE = -2,  ///< Service is not available
    };

    /// Status codes returned from updateQueryResults()
    enum
    {
        UPDATE_NO_MATCH = 0,                      ///< No matches since the last update
        UPDATE_NO_REQUEST = 1,                    ///< No recognition request since the last update
        UPDATE_RESULTS_AVAILABLE = 2,             ///< New search results have been found
        UPDATE_ERROR_AUTHORIZATION_FAILED = -1,   ///< Credentials are wrong or outdated
        UPDATE_ERROR_PROJECT_SUSPENDED = -2,      ///< The specified project was suspended.
        UPDATE_ERROR_NO_NETWORK_CONNECTION = -3,  ///< Device has no network connection
        UPDATE_ERROR_SERVICE_NOT_AVAILABLE = -4,  ///< Server not found, down or overloaded.
        UPDATE_ERROR_BAD_FRAME_QUALITY = -5,      ///< Low frame quality has been continuously observed
        UPDATE_ERROR_UPDATE_SDK = -6,             ///< SDK Version outdated.
        UPDATE_ERROR_TIMESTAMP_OUT_OF_RANGE = -7, ///< Client/Server clocks too far away.
        UPDATE_ERROR_REQUEST_TIMEOUT = -8         ///< No response to network request after timeout.
    };

    /// Filter modes for updateQueryResults()
    enum
    {
        FILTER_NONE = 0,              ///< No results are filtered, all successful queries are returned
        FILTER_CURRENTLY_TRACKED = 1  ///< Filter out targets that are currently being tracked (Most Common)
    };
    
    /// Start initialization of the cloud-based recognition system.
    /**
     * Initialize this TargetFinder to recognize Image Targets using cloud-based
     * recognition. Initialization requires a network connection and runs
     * asynchronously. Use getInitState() to query the progress and final result
     * of initialization.
     *
     * After initialization completes, call startRecognition() to begin
     * continuous recognition of Image Targets in the camera feed. Calls to
     * updateQueryResults() will return search results representing known Image
     * Targets that the cloud-based image recognition system has detected in the
     * camera feed (if any).
     *
     * \param userAuth User name for logging in to the visual search server
     * \param secretAuth User secret for logging in to the visual search server
     */
    virtual bool startInit(const char* userAuth, const char* secretAuth) = 0;

     /// Get the current state of the initialization process
    /**
     * \returns one of the INIT_* values from the enum above.
     */
    virtual int getInitState() const = 0;

    /// Block the current thread until initialization is completed.
    virtual void waitUntilInitFinished() = 0;

    /// Deinitializes the cloud-based recognition system
    virtual bool deinit() = 0;

    /// Start visual recognition
    /**
     * Starts continuous recognition of Targets in the camera feed.
     *
     * Use updateQueryResults() to retrieve search matches.
     */
    virtual bool startRecognition() = 0;

    /// Stop visual recognition
    virtual bool stop() = 0;

    /// Get whether the TargetFinder is currently awaiting the results of a query.
    virtual bool isRequesting() const = 0;

    /// Updates and returns visual search results.
    /**
     * Get an updated list of visual search results. Results represent Image Targets.
     * You may want to cast the results to CloudRecoSearchResult for more details.
     *
     * The visual search process runs asynchronously, and only when recognition
     * is running (i.e. after you call startRecognition()). A call to
     * updateQueryResults() returns the latest available results, which may be
     * several frames out of date with respect to the current camera frame. They
     * should therefore be treated as an indication as to which targets are
     * present in the scene in general, with the understanding that those same
     * targets may not necessarily be visible in the current camera frame.
     *
     * To enable full tracking on one the targets, pass the matching
     * TargetSearchResult instance to enableTracking().
     *
     * TargetSearchResult instances are owned by the TargetFinder. Each call to
     * updateQueryResults() invalidates all previously obtained results.
     *
     * \note By default, targets that are already enabled for tracking are
     * not included in the returned list, unless the target or its associated
     * metadata has been updated since they were last enabled for tracking. If
     * you want to override this and include all results, pass FILTER_NONE for
     * the filter argument.
     *
     * \param filter Filter to apply to the search results. If you pass
     * FILTER_CURRENTLY_TRACKED, only search results that are not currently
     * being tracked (i.e. targets that have NOT been enabled for tracking via
     * enableTracking()) will be returned. Pass FILTER_NONE to return all
     * results regardless of current tracking state.
     *
     * \returns a TargetFinderQueryResult representing the latest-available
     * visual search results.
     */
    virtual TargetFinderQueryResult updateQueryResults(int filter = FILTER_CURRENTLY_TRACKED) = 0;

    /// Enable tracking for a particular search result.
    /**
     * Creates an ObjectTarget for local detection and tracking of a detected target.
     * The pose of this target will be included in State::getTrackableResults().
     *
     * If this TargetFinder is performing cloud-based image recognition (i.e.
     * if it was initialized via startInit(const char*, const char*), then the
     * returned object will be an instance of ImageTarget.
     *
     * \note For performance and/or memory management reasons, calling this
     * function may result in the disabling and destruction of a previously
     * created ObjectTarget. For this reason you should only hold on to the
     * returned ObjectTarget pointer at most until the next call to
     * enableTracking().
     *
     * \param result The search result that you want to start tracking.
     * \returns A newly created ObjectTarget representing the requested search
     * result, or NULL if the target could not be enabled for tracking (check
     * application logs for failure details).
     */
    virtual ObjectTarget* enableTracking(const TargetSearchResult& result) = 0;

    /// Disable tracking on all previously-enabled search results
    /**
     * Disable and destroy all of the ObjectTargets created via enableTracking().
     */
    virtual void clearTrackables() = 0;

    /// Returns a list of ObjectTargets currently enabled for tracking
    virtual List<ObjectTarget> getObjectTargets() = 0;
};

} // namespace Vuforia

#endif //_VUFORIA_TARGET_FINDER_H_
