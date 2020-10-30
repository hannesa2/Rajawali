/*===============================================================================
Copyright (c) 2020 PTC Inc. All Rights Reserved.

Copyright (c) 2015 Qualcomm Connected Experiences, Inc. All Rights Reserved.

Vuforia is a trademark of PTC Inc., registered in the United States and other
countries.

\file
RenderingPrimitives.h

\brief
Header file for RenderingPrimitives class.
===============================================================================*/

#ifndef _VUFORIA_RENDERING_PRIMITIVES_H_
#define _VUFORIA_RENDERING_PRIMITIVES_H_

// Include files
#include <Vuforia/View.h>
#include <Vuforia/ViewList.h>
#include <Vuforia/Mesh.h>
#include <Vuforia/Matrices.h>
#include <Vuforia/Vectors.h>
#include <Vuforia/CameraCalibration.h>

namespace Vuforia
{

/// Provides low-level information and tools for rendering AR and VR content.
/**
 * %RenderingPrimitives provides a set of unified function calls that are
 * designed to work across all AR/VR display devices, including hand-held,
 * head-mounted (monocular/stereo) and wearable mobile devices.
 *
 * This means that you can write a single common rendering loop and have it work
 * across multiple output platforms, AR or VR, mono and stereo, with a minimum
 * of device-specific or context-specific code required.
 *
 * A valid %RenderingPrimitives instance can only be obtained from the Device
 * singleton instance after:
 * - the CameraDevice has been initialized, and
 * - %Vuforia has been informed of the rendering surface size via calls to
 * Vuforia::onSurfaceCreated() and Vuforia::onSurfaceChanged().
 *
 * The transformation measurement unit used is the same as the one used
 * to define the target size (usually meters).
 */
class VUFORIA_API RenderingPrimitives
{
public:

    virtual ~RenderingPrimitives();

    /// Copy constructor.
    RenderingPrimitives(const RenderingPrimitives& other);

    /// Returns true if the rendering primitives are valid
    virtual bool isValid() const;

    /// Get the set of <span>VIEW</span>s available for rendering from these primitives.
    /**
     * In the most common use case (handheld AR on a mobile device), the returned
     * ViewList will contain just a single entry, VIEW::VIEW_SINGULAR.
     *
     * In other use cases (such as stereo head-mounted AR or VR) the returned ViewList
     * may contain multiple entries: typically VIEW::VIEW_LEFTEYE and VIEW::VIEW_RIGHTEYE.
     *
     * For see-through AR, the list will typically contain VIEW::VIEW_LEFTEYE and
     * VIEW::VIEW_RIGHTEYE.
     *
     * An empty list is returned if rendering primitives are invalid
     */
    virtual ViewList& getRenderingViews() const;

    /// Get the viewport for a particular VIEW.
    /**
     * The returned vector describes the starting position, width, and height of
     * the area where content for the given viewID should be rendered, in screen
     * coordinates (i.e. pixels).
     *
     * \param viewID The VIEW you want a viewport for
     * \return The viewport for the given View in the format (x, y, width,
     * height) in screen coordinates (i.e. pixels). An all-zeroes vector is returned if
     * rendering primitives are invalid
     */
    virtual Vec4I getViewport(VIEW viewID) const;

    /// Get the normalized viewport for a particular VIEW.
    /**
     * The returned vector describes the starting position, width, and height of
     * the area where content for the given viewID should be rendered, in
     * normalized coordinates (i.e. all values are in the range 0..1).
     *
     * \param viewID The VIEW you want a viewport for.
     * \return The normalized viewport for the given View in the format (x, y,
     * width, height) where all values are in the range 0..1. An all-zeroes vector
     * is returned if rendering primitives are invalid
     */
    virtual Vec4F getNormalizedViewport(VIEW viewID) const;

    /// Get a projection matrix for rendering content for the specified VIEW.
    /**
     * \note The returned matrix is row-major. For OpenGL, you will need to
     * convert the matrix to column-major using one of the functions in Tool
     * (typically Tool::convertPerspectiveProjection2GLMatrix).
     *
     * \note In AR mode, the returned projection matrix will also include a
     * user interface orientation transform.
     *
     * \param viewID The VIEW you want a projection matrix for.
     * \param cameraCalibration Camera calibration details, or NULL. Typically,
     * you should pass in camera calibration returned from
     * State::getCameraCalibration(). If NULL, the camera calibration calculated
     * when this RenderingPrimitives instance was constructed will be used.
     * \param adjustForViewportCentreToEyeAxis If true, apply skew offsets (see
     * getViewportCentreToEyeAxis) for VIEW::VIEW_LEFTEYE and
     * VIEW::VIEW_RIGHTEYE. (DEPRECATED) 
     * \returns A 3x4 row-major projection matrix (use conversion functions in
     * the Tool class, if necessary, to convert the matrix for use with OpenGL).
     * An all-zeroes matrix is returned if rendering primitives are invalid
     */
    virtual Matrix34F getProjectionMatrix(VIEW viewID,
                                          const CameraCalibration* cameraCalibration,
                                          bool adjustForViewportCentreToEyeAxis = true);

    /// Get a matrix that can correct rendering to account for the offset of the eye from the central rendering position.
    /**
     * The returned matrix should be applied to the pose matrix of any tracked
     * object during rendering.
     *
     * The matrix is specified in meters. If your scene is defined in another
     * unit you will need to adjust the matrix (by scaling the offset parameters)
     * before applying it to your scene.
     *
     * Note that when working with OpenGL, this matrix will need be converted
     * to column-major format using Tool::convert2GLMatrix().
     *
     * \param viewID The VIEW you want an adjustment matrix for (typically
     * VIEW::VIEW_LEFTEYE or VIEW::VIEW_RIGHTEYE).
     * \returns The row-major eye/display adjustment matrix to use for the given
     * VIEW (use the conversion functions in the Tool class if required convert
     * to an OpenGL-compatible matrix). An all-zeroes matrix is returned if
     * rendering primitives are invalid
      */
    virtual Matrix34F getEyeDisplayAdjustmentMatrix(VIEW viewID) const;

    /// Get the size of a texture that can be used to render the video background.
    /**
     * Note that the returned size may be larger than the video background itself
     * (for example when a power-of-two texture size is required for performance).
     *
     * \returns The size that the video background texture needs to be. An all-zeroes
     * vector is returned if rendering primitives are invalid
     */
    virtual const Vec2I getVideoBackgroundTextureSize() const;

    /// Get a projection matrix to use when rendering the video frame as a background image for the augmentation.
    /**
     * Note that when working with OpenGL, this matrix will need be converted to
     * column-major format using Tool::convert2GLMatrix().
     *
     * \param viewID The VIEW you want a video background projection matrix for.
     * \param adjustForViewportCentreToEyeAxis If true, apply skew offsets
     * (\see getViewportCentreToEyeAxis).
     * \returns A 3x4 row-major projection matrix (use Tool::convert2GLMatrix()
     * to convert to column-major format for OpenGL). An all-zeroes matrix is returned if
     * rendering primitives are invalid
     */
    virtual Matrix34F getVideoBackgroundProjectionMatrix(VIEW viewID,
                                                         bool adjustForViewportCentreToEyeAxis = true) const;

    /// Get a simple mesh suitable for use when rendering the video frame as a background image.
    /**
     * The returned mesh has dimensions and texture coordinates that are
     * suitable for rendering a distortion-free camera frame in the requested
     * VIEW, compensating for any discrepancies between the camera and viewport
     * size and aspect ratio.
     *
     * The mesh should be rendered as a textured mesh, in combination with the
     * projection matrix returned by getVideoBackgroundProjectionMatrix(), using
     * the video frame image as a texture.
     *
     * \note If you intend to apply your own distortion to the video background,
     * you may need to construct a finer triangle mesh (based on this mesh), in
     * order to avoid rendering artefacts.
     *
     * \param viewID The VIEW you want the mesh for.
     * \returns A mesh to use when rendering the video frame as a background
     * image. An empty mesh is returned if rendering primitives are invalid
     */
    virtual const Mesh& getVideoBackgroundMesh(VIEW viewID) const;

protected:

    RenderingPrimitives();
    class Impl;
    Impl* mImpl;
};

} // namespace Vuforia

#endif // _VUFORIA_RENDERING_PRIMITIVES_H_
