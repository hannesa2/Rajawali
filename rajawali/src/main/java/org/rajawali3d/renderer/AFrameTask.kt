package org.rajawali3d.renderer

import timber.log.Timber

abstract class AFrameTask : Runnable {
    protected abstract fun doTask()

    override fun run() {
        try {
            doTask()
        } catch (e: Exception) {
            Timber.e("Execution Failed: ${e.message}")
        }
    }
}
