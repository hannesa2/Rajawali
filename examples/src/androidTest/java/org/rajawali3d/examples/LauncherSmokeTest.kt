package org.rajawali3d.examples

import android.graphics.Bitmap
import androidx.recyclerview.widget.RecyclerView
import androidx.test.core.graphics.writeToTestStorage
import androidx.test.espresso.Espresso
import androidx.test.espresso.Espresso.onView
import androidx.test.espresso.action.ViewActions.captureToBitmap
import androidx.test.espresso.action.ViewActions.click
import androidx.test.espresso.assertion.ViewAssertions.matches
import androidx.test.espresso.contrib.RecyclerViewActions
import androidx.test.espresso.intent.Intents
import androidx.test.espresso.matcher.ViewMatchers.isDisplayed
import androidx.test.espresso.matcher.ViewMatchers.isRoot
import androidx.test.espresso.matcher.ViewMatchers.withId
import androidx.test.ext.junit.runners.AndroidJUnit4
import info.hannes.timber.DebugFormatTree
import org.junit.After
import org.junit.Before
import org.junit.Rule
import org.junit.Test
import org.junit.rules.TestName
import org.junit.runner.RunWith
import org.rajawali3d.examples.data.ExamplesDataSet
import org.rajawali3d.examples.tools.RecyclerViewMatcher
import timber.log.Timber

@RunWith(AndroidJUnit4::class)
class LauncherSmokeTest : BaseExampleTest() {

    @get:Rule
    var nameRule = TestName()

    @Before
    fun setUp() {
        Intents.init()
        Timber.plant(DebugFormatTree())
    }

    @After
    fun cleanUp() {
        Intents.release()
    }

    @Test
    fun smokeTestSimplyStart() {
        Thread.sleep(300)
        onView(isRoot())
            .perform(captureToBitmap { bitmap: Bitmap -> bitmap.writeToTestStorage("${javaClass.simpleName}_${nameRule.methodName}-A") })

        onView(withId(R.id.recycler)).check(matches(isDisplayed()))
        onView(isRoot())
            .perform(captureToBitmap { bitmap: Bitmap -> bitmap.writeToTestStorage("${javaClass.simpleName}_${nameRule.methodName}-R") })

        var overallIndex = 0
        ExamplesDataSet.instance?.categories?.forEach {
            it.examples.forEach { _ ->
                overallIndex++
                Timber.d("Click on $overallIndex")
                clickOnExample(overallIndex)
            }
            overallIndex++
        }
    }

    override fun clickOnExample(itemIndex: Int) {
        onView(withId(R.id.recycler)).perform(RecyclerViewActions.scrollToPosition<RecyclerView.ViewHolder>(itemIndex))

        onView(RecyclerViewMatcher(R.id.recycler).atPositionOnView(itemIndex, R.id.textItem))
            .check(matches(isDisplayed()))
            .perform(click())
        //  Intents.intended(hasComponent(ExamplesActivity::class.java.name))

        if (itemIndex != 34) {
            onView(isRoot())
                .perform(captureToBitmap { bitmap: Bitmap -> bitmap.writeToTestStorage("${javaClass.simpleName}_${nameRule.methodName}-A$itemIndex") })
        }
        Espresso.pressBack()
    }
}
