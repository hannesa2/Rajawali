package org.rajawali3d.examples

import androidx.recyclerview.widget.RecyclerView
import androidx.test.core.app.takeScreenshot
import androidx.test.core.graphics.writeToTestStorage
import androidx.test.espresso.Espresso
import androidx.test.espresso.Espresso.onView
import androidx.test.espresso.action.ViewActions.click
import androidx.test.espresso.assertion.ViewAssertions.matches
import androidx.test.espresso.contrib.RecyclerViewActions
import androidx.test.espresso.intent.Intents
import androidx.test.espresso.matcher.ViewMatchers.*
import androidx.test.espresso.screenshot.captureToBitmap
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
            .captureToBitmap()
            .writeToTestStorage("${javaClass.simpleName}_${nameRule.methodName}-A")

        onView(withId(R.id.recycler)).check(matches(isDisplayed()))
        onView(isRoot())
            .captureToBitmap()
            .writeToTestStorage("${javaClass.simpleName}_${nameRule.methodName}-R")

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
        Thread.sleep(300)
        if (itemIndex != 34) {
            onView(withId(R.id.rajwali_surface))
                .captureToBitmap()
                .writeToTestStorage("${javaClass.simpleName}_${nameRule.methodName}-A$itemIndex")
        }
        Espresso.pressBack()
    }
}
