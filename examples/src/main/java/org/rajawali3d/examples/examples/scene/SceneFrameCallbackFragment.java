package org.rajawali3d.examples.examples.scene;

import android.content.Context;
import android.os.Bundle;
import android.os.Handler;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.TextView;

import org.rajawali3d.Object3D;
import org.rajawali3d.examples.R;
import org.rajawali3d.examples.examples.AExampleFragment;
import org.rajawali3d.lights.DirectionalLight;
import org.rajawali3d.materials.Material;
import org.rajawali3d.materials.textures.ATexture;
import org.rajawali3d.materials.textures.Texture;
import org.rajawali3d.primitives.Sphere;
import org.rajawali3d.scene.ASceneFrameCallback;

import timber.log.Timber;

public class SceneFrameCallbackFragment extends AExampleFragment {

    private Handler mHandler;

    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        super.onCreateView(inflater, container, savedInstanceState);
        TextView mRenderTimeView = new TextView(getActivity());
        final FrameLayout.LayoutParams params = new FrameLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT, Gravity.BOTTOM | Gravity.CENTER_HORIZONTAL);
        mLayout.addView(mRenderTimeView, params);
        mRenderTimeView.bringToFront();
        mRenderTimeView.setTextColor(getResources().getColor(android.R.color.white));
        mHandler = new Handler(requireActivity().getMainLooper());

        return mLayout;
    }

    @Override
    public AExampleRenderer createRenderer() {
        return new BasicRenderer(getActivity(), this);
    }

    private final class BasicRenderer extends AExampleRenderer {

        private Object3D mSphere;

        public BasicRenderer(Context context, @Nullable AExampleFragment fragment) {
            super(context, fragment);
        }

        @Override
        protected void initScene() {
            DirectionalLight mLight = new DirectionalLight(1f, 0.2f, -1.0f); // set the direction
            mLight.setColor(1.0f, 1.0f, 1.0f);
            mLight.setPower(2);

            getCurrentScene().addLight(mLight);

            try {
                Material material = new Material();
                material.addTexture(new Texture("earthColors",
                        R.drawable.earthtruecolor_nasa_big));
                material.setColorInfluence(0);
                mSphere = new Sphere(1, 24, 24);
                mSphere.setMaterial(material);
                getCurrentScene().addChild(mSphere);
            } catch (ATexture.TextureException e) {
                Timber.e(e);
            }

            getCurrentCamera().setZ(6);

            getCurrentScene().registerFrameCallback(new ElapsedTimeFrameCallback());
        }

        @Override
        protected void onRender(long elapsedRealtime, double deltaTime) {
            super.onRender(elapsedRealtime, deltaTime);
            mSphere.setRotY(mSphere.getRotY() + 1);
        }
    }

    private final class ElapsedTimeFrameCallback extends ASceneFrameCallback {

        @Override
        public void onPreFrame(long sceneTime, double deltaTime) {
            // Do nothing
        }

        @Override
        public void onPreDraw(long l, double v) {

        }

        @Override
        public void onPostFrame(final long sceneTime, double deltaTime) {
            mHandler.post(() -> Timber.d("Scene Time: " + sceneTime + "ns"));
        }

        @Override
        public boolean callPostFrame() {
            return true;
        }
    }
}
