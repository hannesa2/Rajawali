/*===============================================================================
Copyright (c) 2019 PTC Inc. All Rights Reserved.

Vuforia is a trademark of PTC Inc., registered in the United States and other
countries.

\file
    Driver.h

\brief
    Header file for the Vuforia Driver.
===============================================================================*/

#ifndef VUFORIA_DRIVER_H_
#define VUFORIA_DRIVER_H_

#include <stdint.h>

#if defined(_MSC_VER)
#define VUFORIA_DRIVER_PACKED_STRUCT(...) __pragma(pack(push, 1)) struct __VA_ARGS__ __pragma(pack(pop))
#define VUFORIA_DRIVER_API_EXPORT __declspec(dllexport)
#define VUFORIA_DRIVER_CALLING_CONVENTION __cdecl
#elif defined(__GNUC__) || defined(__clang__)
#define VUFORIA_DRIVER_PACKED_STRUCT(...) struct __attribute__((__packed__)) __VA_ARGS__
#if defined(__APPLE__)
#define VUFORIA_DRIVER_API_EXPORT __attribute__((visibility("default")))
#define VUFORIA_DRIVER_CALLING_CONVENTION
#else 
#define VUFORIA_DRIVER_API_EXPORT
#define VUFORIA_DRIVER_CALLING_CONVENTION
#endif
#else
#error "Unsupported compiler."
#endif



#if defined(__ANDROID__)
#include <jni.h>
#endif

namespace Vuforia {
namespace Driver {

/// External provider API-version number, that this header defines.
const uint32_t VUFORIA_DRIVER_API_VERSION = 4;

/// Platform specific initialization data.
#if defined(__ANDROID__)
/// On Android all the necessary data to access Java functions through JNI are provided.
VUFORIA_DRIVER_PACKED_STRUCT(PlatformData
{
    JavaVM* javaVM{ nullptr };      ///< Pointer to the current JVM.
    jobject activity{ nullptr };    ///< Java object reference to current Activity.
    jint jniVersion{ -1 };          ///< JNI version number.
});
#else
/// On other platforms just use an empty struct.
VUFORIA_DRIVER_PACKED_STRUCT(PlatformData
{
});
#endif

/// A list of the supported pixel formats for camera frames.
enum class PixelFormat : int32_t
{
    UNKNOWN,    ///< Unknown format.
    YUYV,       ///< YUV 4:2:2. Single 16bit interleaved plane. Same as YUY2.
    NV12,       ///< YUV 4:2:0. 8bit Y plane + 8bit interleaved UV plane (subsampled 2x2).
    NV21,       ///< YUV 4:2:0. 8bit Y plane + 8bit interleaved VU plane (subsampled 2x2).
};

/// Camera focus modes.
enum class FocusMode : int32_t
{
    UNKNOWN,            ///< Unknown focus mode.
    AUTO,               ///< Single trigger auto focus.
    CONTINUOUS_AUTO,    ///< Continuous auto focus.
    MACRO,              ///< Macro mode.
    INFINITY_FOCUS,     ///< Focus to infinity.
    FIXED               ///< Fixed focus that can't be adjusted.
};

/// Camera exposure modes.
enum class ExposureMode : int32_t
{
    UNKNOWN,            ///< Unknown exposure mode.
    AUTO,               ///< Single trigger auto exposure.
    CONTINUOUS_AUTO,    ///< Continuous auto exposure.
    MANUAL,             ///< Manual exposure mode.
    SHUTTER_PRIORITY    ///< Shutter priority mode.
};

/// Driver Capabilities.
enum Capability: uint32_t
{
    CAMERA_IMAGE       = 0,  // Driver supports camera Image(s).
    CAMERA_POSE        = 1   // Driver supports camera pose(s).
};

/// enum to describe state of the camera pose.
enum class PoseReason
{
    INITIALIZING,           /// The pose is still intializing.
    VALID,                  /// Valid pose.
    EXCESSIVE_MOTION,      /// The user is moving the device to fast.
    INSUFFICIENT_FEATURES, /// There are not enough features to provide a valid pose.
    INSUFFICIENT_LIGHT,    /// There is not enough light to provide a valid pose.
    RELOCALIZING           /// The system is relocalizing.
};

/// Pose is expected to be in camera coordinate system.
enum class PoseCoordSystem
{
    CAMERA  ///Camera co-ordinate system.
};

/// Indicates validity (quality) of the pose.
enum class PoseValidity
{
    VALID,      /// The camera pose is valid.
    UNRELIABLE  /// The camera pose is valid, but the quality is not guaranteed.
};

/// enum to describe anchor update reason
enum class AnchorStatus
{
    /// Anchor(s) added
    ADDED,

    /// Anchor(s) updated
    UPDATED,

    /// Anchor(s) removed
    REMOVED,

    /// Anchor(s) paused
    PAUSED
};

/// Describes the size, frame rate and format of a camera frame.
VUFORIA_DRIVER_PACKED_STRUCT(CameraMode
{
    uint32_t width{ 0 };                        ///< Frame width.
    uint32_t height{ 0 };                       ///< Frame height.
    uint32_t fps{ 0 };                          ///< Frame rate. Frames per second.
    PixelFormat format{ PixelFormat::YUYV };    ///< Frame format.
});

/// Properties required to support the intrinsics for a camera.
/**
 * These values should be obtained from camera calibration.
 */
VUFORIA_DRIVER_PACKED_STRUCT(CameraIntrinsics
{
    /// Focal length x-component. 0.f if not available.
    float focalLengthX{ 0.f };

    /// Focal length y-component. 0.f if not available.
    float focalLengthY{ 0.f };

    /// Principal point x-component. 0.f if not available.
    float principalPointX{ 0.f };

    /// Principal point y-component. 0.f if not available.
    float principalPointY{ 0.f };

    /// An 8 element array of distortion coefficients.
    /**
     * Array should be filled in the following order (r: radial, t:tangential):
     * [r0, r1, t0, t1, r2, r3, r4, r5]
     * Values that are not available should be set to 0.f.
     */
    float distortionCoefficients[8]{ 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f };
});

/// Describes a camera frame.
VUFORIA_DRIVER_PACKED_STRUCT(CameraFrame
{
    /// Frame timestamp at end of exposure in nanoseconds.
    /**
     * The time base varies between the platforms:
     * Android: CLOCK_MONOTONIC, current timestamp can be obtained with clock_gettime()
     */
    uint64_t timestamp{ 0 };

    /// Exposure duration in nanoseconds.
    uint64_t exposureTime{ 0 };

    /// Pointer to first byte of the pixel buffer.
    uint8_t* buffer{ nullptr };

    /// Size of the pixel buffer in bytes.
    uint32_t bufferSize{ 0 };

    /// Frame index, ascending number.
    uint32_t index{ 0 };

    /// Frame width.
    uint32_t width{ 0 };

    /// Frame height.
    uint32_t height{ 0 };

    /// Indicates how many bytes are used per row.
    /// If the frame is tightly packed this should equal to width * bytes per pixel.
    /// For NV12 and NV21 images this should be the stride of the Y plane in bytes and
    /// the stride of the UV plane must be identical.
    uint32_t stride{ 0 };
    PixelFormat format{ PixelFormat::YUYV };    ///< Frame format.
    CameraIntrinsics intrinsics;                ///< Camera intrinsics used to capture the frame.
});

/// Describes a Pose.
VUFORIA_DRIVER_PACKED_STRUCT(Pose
{
    uint64_t timestamp{ 0 };           /// Timestamp when pose was captured.
    //The array contains translation vector values (x, y, z) associated with the pose.
    float translationData[3];
    //The array contains elements of 3*3 rotation matrix associated with the pose.
    float rotationData[9];
    PoseReason reason;                 /// Reason for the pose update.
    PoseCoordSystem coordinateSystem;  /// Coordinate system for the pose.
    PoseValidity validity;             /// Quality/validity of the pose.
});

/// Structure for storing translation and rotation matrix associated with an anchor.
VUFORIA_DRIVER_PACKED_STRUCT(AnchorPose
{
    //The array contains translation vector values (x, y, z) associated with the anchor.
    float translationData[3];
    //The array contains elements of 3*3 rotation matrix associated with the anchor.
    float rotationData[9];
});

/// Structure for storing an anchor information.
VUFORIA_DRIVER_PACKED_STRUCT(Anchor
{
    //UUID associated with an anchor. A successful call to createAnchor generates an UUID.
    const char* uuid;
    //Stores pose associated with this anchor.
    AnchorPose pose;
});

/// Interface that will be used to deliver camera frames to %Vuforia.
class CameraCallback
{
public:
    virtual void VUFORIA_DRIVER_CALLING_CONVENTION onNewCameraFrame(CameraFrame* frame) = 0;
};

/// Interface that will be used to deliver pose(s) to %Vuforia.
class PoseCallback
{
public:
    virtual void VUFORIA_DRIVER_CALLING_CONVENTION onNewPose(Pose* pose) = 0;
};

/// Interface to notify about anchor updates.
class AnchorCallback
{
public:
    virtual void VUFORIA_DRIVER_CALLING_CONVENTION onAnchorUpdate(Anchor* anchors, int numAnchors, AnchorStatus status ) = 0;
};

/// Interface used by %Vuforia to interact with the external camera implementation.
/**
 *  The sequence of events between %Vuforia and the external camera implementation is as follows:
 *  1. %Vuforia calls VuforiaDriver::createExternalCamera() when the driver capability includes CAMERA_IMAGE.
 *  2. The implementation creates an ExternalCamera instance and returns it to %Vuforia.
 *  3. %Vuforia calls ExternalCamera::open() on the returned instance.
 *  4. %Vuforia discovers supported camera modes by iterating them by getting the number of modes
 *     with ExternalCamera::getNumSupportedCameraModes() and then iterates over the list
 *     with ExternalCamera::getSupportedCameraMode().
 *  5. %Vuforia calls ExternalCamera::start(), which starts the flow of frames into
 *     the provided CameraCallback.
 *  6. On shutdown %Vuforia calls
 *     -> ExternalCamera::stop()
 *     -> ExternalCamera::close()
 *     -> and finally VuforiaDriver::destroyExternalCamera().
 */
class ExternalCamera
{
public:
    /// Open the camera.
    /**
     * After opening the camera, the supported video modes should be available to be queried
     * with getNumSupportedCameraModes() and getSupportedCameraMode().
     *
     * \return True if the camera was opened, otherwise false.
     */
    virtual bool VUFORIA_DRIVER_CALLING_CONVENTION open() = 0;

    /// Close the camera.
    /**
     * \return True if the camera was closed, otherwise false.
     */
    virtual bool VUFORIA_DRIVER_CALLING_CONVENTION close() = 0;

    /// Start the camera.
    /**
     * \param cameraMode The requested mode that the camera should deliver the frames in.
     * \param cb Callback that the camera frames should be delivered to.
     *
     * \return True if the camera was started, otherwise false.
     */
    virtual bool VUFORIA_DRIVER_CALLING_CONVENTION start(CameraMode cameraMode, CameraCallback* cb) = 0;

    /// Stops the camera.
    /**
     * \return True if the camera was stopped, otherwise false.
     */
    virtual bool VUFORIA_DRIVER_CALLING_CONVENTION stop() = 0;

    /// Get the number of supported camera modes.
    /**
     *  Should return the total number of supported camera modes.
     *  %Vuforia uses this number then to query the camera modes with
     *  getSupportedCameraMode(), which iterates from 0 to totalNumber - 1.
     *
     * \return Number of camera modes that this camera supports.
     */
    virtual uint32_t VUFORIA_DRIVER_CALLING_CONVENTION getNumSupportedCameraModes() = 0;

    /// Get a camera mode from a certain index.
    /**
     * \param index The index of the mode to get, in the range 0..getNumSupportedCameraModes()-1.
     * \param out On return, will be populated with the camera mode corresponding to the requested index.
     *
     * \return True on success, or false if the index was out of bounds.
     */
    virtual bool VUFORIA_DRIVER_CALLING_CONVENTION getSupportedCameraMode(uint32_t index, CameraMode* out) = 0;

    /// Get whether a particular exposure mode is supported.
    /**
     * \return True if the mode is supported, otherwise false.
     */
    virtual bool VUFORIA_DRIVER_CALLING_CONVENTION supportsExposureMode(ExposureMode parameter) = 0;

    /// Get current exposure mode.
    /**
     * \return The current exposure mode.
     */
    virtual ExposureMode VUFORIA_DRIVER_CALLING_CONVENTION getExposureMode() = 0;

    /// Set the current exposure mode.
    /**
     * \param mode New exposure mode.
     *
     * \return True if setting the mode succeeded, otherwise false.
     */
    virtual bool VUFORIA_DRIVER_CALLING_CONVENTION setExposureMode(ExposureMode mode) = 0;

    /// Get whether setting the exposure manually is supported.
    /**
     * \return True if usage of setExposureValue() is supported, otherwise false.
     */
    virtual bool VUFORIA_DRIVER_CALLING_CONVENTION supportsExposureValue() = 0;

    /// Get the minimum supported value for manual exposure.
    /**
     * \return The minimum value that can be provided for setExposureValue().
     */
    virtual uint64_t VUFORIA_DRIVER_CALLING_CONVENTION getExposureValueMin() = 0;

    /// Get the maximum supported value for manual exposure.
    /**
     * \return The maximum value that can be provided for setExposureValue().
     */
    virtual uint64_t VUFORIA_DRIVER_CALLING_CONVENTION getExposureValueMax() = 0;

    /// Get the current manual exposure value.
    /**
     * \return The current value.
     */
    virtual uint64_t VUFORIA_DRIVER_CALLING_CONVENTION getExposureValue() = 0;

    /// Set the current manual exposure value.
    /**
     * \param exposureTime New value for manual exposure.
     *
     * \note To use this supportsExposureValue() must return true
     * and the provided value must be in the range speficied by
     * getExposureValueMin() and getExposureValueMax() inclusive.
     *
     * \return True value was set successfully, otherwise false.
     */
    virtual bool VUFORIA_DRIVER_CALLING_CONVENTION setExposureValue(uint64_t exposureTime) = 0;

    /// Get whether a particular focus mode is supported.
    /**
     * \return True if the mode is supported, otherwise false.
     */
    virtual bool VUFORIA_DRIVER_CALLING_CONVENTION supportsFocusMode(FocusMode parameter) = 0;

    /// Get the current focus mode.
    /**
     * \return The current focus mode.
     */
    virtual FocusMode VUFORIA_DRIVER_CALLING_CONVENTION getFocusMode() = 0;

    /// Set the current focus mode.
    /**
     * \param mode The new focus mode.
     *
     * \return A boolean indicating if setting succeeded.
     */
    virtual bool VUFORIA_DRIVER_CALLING_CONVENTION setFocusMode(FocusMode mode) = 0;

    /// Get whether setting manual focus distance is supported.
    /**
     * \return True if usage of setFocusValue() is supported, otherwise false.
     */
    virtual bool VUFORIA_DRIVER_CALLING_CONVENTION supportsFocusValue() = 0;

    /// Get the minimum supported value for manual focus distance.
    /**
     * \return The minimum value in millimeters that can be provided for setFocusValue().
     */
    virtual float VUFORIA_DRIVER_CALLING_CONVENTION getFocusValueMin() = 0;

    /// Get the maximum supported value for manual focus distance.
    /**
     * \return The maximum value in millimeters that can be provided for setFocusValue().
     */
    virtual float VUFORIA_DRIVER_CALLING_CONVENTION getFocusValueMax() = 0;

    /// Get the current manual focus distance.
    /**
     * \return Current manual focus value in millimeters.
     */
    virtual float VUFORIA_DRIVER_CALLING_CONVENTION getFocusValue() = 0;

    /// Set the current manual focus value.
    /**
     * \param value The new value for manual focus distance in millimeters.
     *
     * \note To use this supportsFocusValue() must return true
     * and the provided value must be in the range specified by
     * getFocusValueMin() and getFocusValueMax() inclusive.
     *
     * \return True value was set successfully, otherwise false.
     */
    virtual bool VUFORIA_DRIVER_CALLING_CONVENTION setFocusValue(float value) = 0;
};

/// Interface used by %Vuforia to interact with the external positional device tracker implementation.
/**
 *  The sequence of events between %Vuforia and the external positional device tracker implementation is as follows:
 *  1. %Vuforia calls VuforiaDriver::createExternalPositionalDeviceTracker() when the driver capability includes CAMERA_POSE.
 *  2. The implementation creates an ExternalPositionalDeviceTracker instance and returns it to %Vuforia.
 *  3. %Vuforia calls ExternalPositionalDeviceTracker::open() on the returned instance.
 *  4. %Vuforia calls ExternalPositionalDeviceTracker::start(), which starts the flow of poses into
 *     the provided PoseCallback.
 *  5. On shutdown %Vuforia calls
 *     -> ExternalPositionalDeviceTracker::stop()
 *     -> ExternalPositionalDeviceTracker::close()
 *     -> and finally VuforiaDriver::destroyExternalPositionalDeviceTracker().
 */
class ExternalPositionalDeviceTracker
{
public:
    /// open the external positional device tracker.
    /**
     * \return True if the external positional device tracker is opened successfully, otherwise false.
     */
    virtual bool VUFORIA_DRIVER_CALLING_CONVENTION open() = 0;

    /// close the external positional device tracker.
    /**
     * \return True if the external positional device tracker is closed successfully, otherwise false.
     */
    virtual bool VUFORIA_DRIVER_CALLING_CONVENTION close() = 0;

    /// start the external positional device tracker.
    /**
     * \param cb Callback that the pose should be delivered to.
     * \param acb Anchor callback to be notified when anchors are updated.
     *
     * \return True if the external positional device tracker was started, otherwise false.
     */
    virtual bool VUFORIA_DRIVER_CALLING_CONVENTION start(PoseCallback* cb, AnchorCallback* acb = nullptr) = 0;

    /// stop the external positional device tracker.
    /**
     * \return True if the external positional device tracker was stopped, otherwise false.
     * Once the stop returns true, driver implementation should stop pushing additional poses via PoseCallback.
     * PoseCallback should be considered as invalid once stop returns true.
     */
    virtual bool VUFORIA_DRIVER_CALLING_CONVENTION stop() = 0;

    /// notify external positional device tracker to reset tracking the world/pose.
    /**
     * \return True if the external positional device tracker is successful in resetting tracking else returns false.
     */
    virtual bool VUFORIA_DRIVER_CALLING_CONVENTION resetTracking() = 0;

    /// Query the driver to check if it supports anchors.
    /**
     * \return True if the anchors are supported else returns false.
     * Anchor support is an optional feature, so, default implementation is to return false.
     */
    virtual bool VUFORIA_DRIVER_CALLING_CONVENTION isAnchorSupported() { return false; }

    /// Create an anchor for the given pose.
    /**
     * \param anchorPose An anchor pose.
     * \return UUID (char*) if successful in creating an anchor.
     * Anchor support is an optional feature, so, default implementation is to return nullptr.
     */
    virtual const char* VUFORIA_DRIVER_CALLING_CONVENTION createAnchor(AnchorPose* anchorPose)
    {
        (void)anchorPose;
        return nullptr;
    }

    /// Remove the Anchor for the given UUID.
    /**
     * \param uuid UUID of the anchor to be removed. This UUID was obtained via successful call to createAnchor.
     * \return True if successful in removing Anchor else returns false.
     * Anchor support is an optional feature, so, default implementation is to return false.
     */
    virtual bool VUFORIA_DRIVER_CALLING_CONVENTION removeAnchor(const char* uuid)
    {
        (void)uuid;
        return false;
    }
};

/// Interface used by %Vuforia to interact with the Vuforia Driver implementation.
/**
 *  The sequence of events between %Vuforia and the external driver implementation is as follows:
 *  1. %Vuforia calls vuforiaDriver_init().
 *  2. %Vuforia uses the VuforiaDriver.
 *  3. On shutdown %Vuforia calls vuforiaDriver_deinit().
 */
class VuforiaDriver
{
public:
    /// Constructs a new instance of an ExternalCamera.
    /**
    * %Vuforia will use this instance to interact with a camera. The object is
    * expected to be valid until destroyExternalCamera() is called.
    * The memory for the object is owned by the library.
    * Only one instance of ExternalCamera is created, a second call to
    * createExternalCamera without a call to destroyExternalCamera is
    * an error and the implementation should return a nullptr.
    *
    * \return New camera instance.
    */
    virtual ExternalCamera* VUFORIA_DRIVER_CALLING_CONVENTION createExternalCamera() = 0;

    /// Destructs an instance of an ExternalCamera object.
    /**
    * %Vuforia will call this to destroy the instance that was created with createExternalCamera().
    * \param instance camera instance to destroy.
    */
    virtual void VUFORIA_DRIVER_CALLING_CONVENTION destroyExternalCamera(ExternalCamera* instance) = 0;

    /// Constructs a new instance of an external positional device tracker. Vuforia will call this only if
    /// the driver capability includes CAMERA_POSE.
    /**
    * %Vuforia will use this instance to receive pose(s). The object is
    * expected to be valid until destroyExternalPositionalDeviceTracker() is called.
    * The memory for the object is owned by the library.
    * Only one instance of ExternalPositionalDeviceTracker is created, a second call to
    * createExternalPositionalDeviceTracker without a call to destroyExternalPositionalDeviceTracker is
    * an error and the implementation should return a nullptr.
    *
    * \return New ExternalPositionalDeviceTracker instance.
    */
    virtual ExternalPositionalDeviceTracker* VUFORIA_DRIVER_CALLING_CONVENTION createExternalPositionalDeviceTracker() { return nullptr; }

    /// Destructs an instance of an ExternalPositionalDeviceTracker object.
    /**
    * %Vuforia will call this to destroy the instance that was created with createExternalPositionalDeviceTracker().
    * \param instance ExternalPositionalDeviceTracker instance to destroy.
    */
    virtual void VUFORIA_DRIVER_CALLING_CONVENTION destroyExternalPositionalDeviceTracker(ExternalPositionalDeviceTracker* instance)
    {
        (void)instance;
    }

    ///Query the driver implementation for supported capabilities.
    /**
    * Vuforia will default to the Camera Image only capability.
    */
    virtual uint32_t VUFORIA_DRIVER_CALLING_CONVENTION getCapabilities() { return (uint32_t) Capability::CAMERA_IMAGE; }

};

} // namespace Driver
} // namespace Vuforia

extern "C"
{
    /// Returns the API version number.
    /**
     * This function returns the version of the Vuforia Driver API that this plugin conforms to.
     *
     * \return Should return EXTERNAL_PROVIDER_API_VERSION defined in this file.
     */
    VUFORIA_DRIVER_API_EXPORT uint32_t VUFORIA_DRIVER_CALLING_CONVENTION vuforiaDriver_getAPIVersion();

    /// Returns the library version number.
    /**
     * This function should write a versionString-parameter with a user defined library version string
     * with maximum length of maxLen.
     *
     * \note Empty strings are not supported
     *
     * \param versionString this should be populated with the library version string.
     * \param maxLen maximum length in bytes that can fit to versionString.
     * \return The number of bytes written into versionString.
     */
    VUFORIA_DRIVER_API_EXPORT uint32_t VUFORIA_DRIVER_CALLING_CONVENTION vuforiaDriver_getLibraryVersion(char* versionString, const uint32_t maxLen);

    /// Constructs a new instance of a VuforiaDriver.
    /**
     * %Vuforia will use this instance to interact with the library. The object is
     * expected to be valid until vuforiaDriver_deinit() is called.
     * The memory for the object is owned by the library.
     * Only one instance of VuforiaDriver is created, a second call to
     * vuforiaDriver_init without a call to vuforiaDriver_deinit is
     * an error and the implementation should return a nullptr.
     *
     * \param platformData Platform specific initialization data, that has been defined in the beginning of this header file.
     * \param userData userdata, that the developer provider as a second parameter to
     * Vuforia::setDriverLibrary().
     * \return New Vuforia Driver instance.
     */
    VUFORIA_DRIVER_API_EXPORT Vuforia::Driver::VuforiaDriver* VUFORIA_DRIVER_CALLING_CONVENTION vuforiaDriver_init(Vuforia::Driver::PlatformData* platformData, void* userData);

    /// Destructs an instance of a VuforiaDriver object.
    /**
     * %Vuforia will call this to destroy the instance that was created with vuforiaDriver_init().
     * \param instance to destroy.
     */
    VUFORIA_DRIVER_API_EXPORT void VUFORIA_DRIVER_CALLING_CONVENTION vuforiaDriver_deinit(Vuforia::Driver::VuforiaDriver* instance);
}

#endif // VUFORIA_DRIVER_H_
