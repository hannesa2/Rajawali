package org.rajawali3d.examples

import android.Manifest
import android.os.Bundle
import androidx.test.espresso.intent.Intents
import androidx.test.espresso.matcher.ViewMatchers.*
import androidx.test.ext.junit.runners.AndroidJUnit4
import androidx.test.rule.GrantPermissionRule
import com.android21buttons.fragmenttestrule.FragmentTestRule
import org.junit.After
import org.junit.Before
import org.junit.Rule
import org.junit.Test
import org.junit.rules.TestName
import org.junit.runner.RunWith
import org.rajawali3d.examples.examples.general.CollisionDetectionFragment

@RunWith(AndroidJUnit4::class)
class ExamplesTest {

    @get:Rule
    var fragmentTestRule: FragmentTestRule<*, CollisionDetectionFragment> = FragmentTestRule.create(CollisionDetectionFragment::class.java)

//    @get:Rule
//    val activityScenarioRule = activityScenarioRule<LauncherActivity>()

    @get:Rule
    var nameRule = TestName()

    @Before
    fun setUp() = Intents.init()

    @After
    fun cleanUp() = Intents.release()

    @get:Rule
    val grantPermissionRule: GrantPermissionRule = GrantPermissionRule.grant(
        Manifest.permission.CAMERA,
        Manifest.permission.WRITE_EXTERNAL_STORAGE,
        Manifest.permission.READ_EXTERNAL_STORAGE
    )

    @Test
    fun fragmentStart() {
        val fragmentArgs = Bundle()
//        launchFragmentInContainer<CollisionDetectionFragment>(fragmentArgs)

//        onView(withId(R.id.recycler)).check(matches(isDisplayed()))
//        onView(isRoot())
//            .captureToBitmap()
//            .writeToTestStorage("${javaClass.simpleName}_${nameRule.methodName}")
//
//        onView(RecyclerViewMatcher(R.id.recycler).atPositionOnView(3, R.id.textItem))
//            .check(matches(isDisplayed()))
//            .perform(click())
//        Intents.intended(hasComponent(ExamplesActivity::class.java.name))
//        Espresso.pressBack()
    }
}
