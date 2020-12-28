package org.rajawali3d.examples

import android.app.Application
import info.hannes.timber.DebugTree
import timber.log.Timber

class LogApplication : Application() {

    override fun onCreate() {
        super.onCreate()
        val oldHandler = Thread.getDefaultUncaughtExceptionHandler()

        Thread.setDefaultUncaughtExceptionHandler { t, e ->
            @Suppress("ControlFlowWithEmptyBody")
            Timber.e(e.cause?.also { } ?: run { e })
            oldHandler?.uncaughtException(t, e)
        }

        Timber.plant(DebugTree())
    }
}
