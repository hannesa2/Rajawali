/*===============================================================================
Copyright (c) 2020 PTC Inc. All Rights Reserved.

Vuforia is a trademark of PTC Inc., registered in the United States and other 
countries.

\file
    SessionRecorder.h

\brief
    Header file for SessionRecorder class.
===============================================================================*/

#ifndef _VUFORIA_SESSION_RECORDER_H_
#define _VUFORIA_SESSION_RECORDER_H_

#include <Vuforia/NonCopyable.h>

namespace Vuforia
{

/// API for recording data from sources such as camera and sensors on the device
/// running Vuforia.
class VUFORIA_API SessionRecorder : private NonCopyable
{
public:

    /// Combinable flag bits indicating which sources to record from.
    enum Source
    {
        Camera = 0x01, /** Camera images, and device poses. Please note that
                        * pose data is not available on all devices. If pose data
                        * is unavailable, then only camera images are recorded. */
        Sensors = 0x02 /** Data from accelerometer, gyroscope, and magnetometer.
                        * Please note that not all three sensors are available
                        * on all devices. In that case only data from available
                        * sensors is recorded. */
    };

    /// Current recording status.
    enum RecordingStatus
    {
        RecordingNotStarted = 1, /** Not recording. */
        RecordingInProgress = 2, /** A recording is in progress. */
        SourcesNotAvailable = 3, /** One or more requested sources are physically
                                  * unavailable on this platform. */
        StorageLocationRetrievalError = 4, /** Unable to retrieve a suitable location
                                            * for storing the data on the device. */
        SourceOperationError = 5, /** Could not operate some requested sources. */
        InsufficientFreeSpace = 6, /** There isn't sufficient free space on the device
                                    * for recording the data - a recording could not
                                    * be started or was aborted due to this reason. */
        OrientationNotSupported = 7, /** Recording is only supported if the App
                                      * orientation is landscape. */
    };

    /// Get the singleton instance.
    static SessionRecorder& getInstance();

    /// Get flag value indicating sources supported on this device.
    /**
     * This method should be called after Vuforia has been initialized.
     * Otherwise, some supported sources may not be recognized.
     * @sa Source
     * @return a combination of source flag bits indicating which data sources
     * are supported on this device.
     */
    virtual int getSupportedSources() const = 0;

    /// Start recording data from the specified sources.
    /**
     * If recording fails or is not stopped before Vuforia is deinitialized,
     * any created files are not cleaned up and may not be valid for playback.
     * This method should be called after Vuforia has been initialized. Failure
     * to do so may result in the incorrect status value being returned. In
     * particular, the camera device should be properly initialized and started.
     * @sa getSupportedSources
     * @sa RecordingStatus
     * @param sources flag indicating which sources to record data from
     * @return a status value indicating whether a recording has been started /
     * is in progress, or the error otherwise. In case of an error, check the
     * application logs for details.
     */
    virtual RecordingStatus start(int sources) = 0;

    /// Stop current recording.
    /**
     * Currently this API does not provide a pause/resume capability. Hence,
     * when an app is paused, it should call stop (BEFORE stopping the camera);
     * and on the subsequent resume it should call start. This implies that the
     * current recording will be finalized on pause, and a new one will be started
     * on resume.
     *
     * If on pausing an application, an ongoing recording is not stopped as instructed
     * above, Vuforia::onPause will force-stop it. However, in this case the resulting
     * recording is not guaranteed to be in a usable state.
     */
    virtual void stop() = 0;

    /// Get the recording output path.
    /**
     * The method will return null until a recording has been started, the path
     * is updated each time start is called.
     * @return the full path where the recording is output. Note that on the
     * next call to start, this pointer may be invalidated (could be freed). So
     * if the returned path is to be retained beyond that, it's recommended to
     * make a copy of it.
     */
    virtual const char* getRecordingPath() const = 0;

    /// Get current recording status.
    /**
     * @return whether a recording is in progress, or the error otherwise. In
     * case of an error, check the application logs for details.
     */
    virtual RecordingStatus getRecordingStatus() const = 0;

    /// Remove all previously recorded sequences.
    /**
     * @return true if all recorded sequences have been removed successfully,
     * or false otherwise (check application logs for details), for instance
     * if called while a recording is in progress.
     */
    virtual bool clean() const = 0;

};

} // namespace Vuforia

#endif // _VUFORIA_SESSION_RECORDER_H_
