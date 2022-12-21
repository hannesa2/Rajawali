package org.rajawali3d.examples

import android.app.Activity
import android.os.Bundle
import info.hannes.logcat.LoggingApplication
import timber.log.Timber

class RajawaliApplication : LoggingApplication() {

    override fun onCreate() {
        super.onCreate()

        registerActivityLifecycleCallbacks(object : ActivityLifecycleCallbacks {
            override fun onActivityCreated(activity: Activity, savedInstanceState: Bundle?) = Timber.d(activity.javaClass.simpleName)

            override fun onActivityStarted(activity: Activity) = Timber.v("${activity.javaClass.simpleName} onStart() starting")

            override fun onActivityResumed(activity: Activity) = Timber.v("${activity.javaClass.simpleName} onResume() starting")

            override fun onActivityPaused(activity: Activity) = Timber.v("${activity.javaClass.simpleName} onPause() ending")

            override fun onActivityStopped(activity: Activity) = Timber.v("${activity.javaClass.simpleName} onStop() ending")

            override fun onActivitySaveInstanceState(activity: Activity, outState: Bundle) = Timber.v(activity.javaClass.simpleName)

            override fun onActivityDestroyed(activity: Activity) = Timber.v("${activity.javaClass.simpleName} onDestroy() ending")
        })
    }
}
