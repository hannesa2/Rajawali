package org.rajawali3d.renderer;

import timber.log.Timber;

/**
 * @author Jared Woolston (jwoolston@tenkiv.com)
 */
public abstract class AFrameTask implements Runnable {

    protected abstract void doTask();

    @Override
    public void run() {
        try {
            doTask();
        } catch (Exception e) {
            Timber.e("Execution Failed: " + e.getMessage());
            e.printStackTrace();
        }
    }
}
