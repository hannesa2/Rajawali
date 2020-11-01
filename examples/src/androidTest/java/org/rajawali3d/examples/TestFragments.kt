package org.rajawali3d.examples

import android.os.Bundle
import androidx.fragment.app.testing.launchFragmentInContainer
import androidx.test.espresso.Espresso.onView
import androidx.test.espresso.assertion.ViewAssertions.matches
import androidx.test.espresso.matcher.ViewMatchers.isDisplayed
import androidx.test.espresso.matcher.ViewMatchers.withId
import androidx.test.ext.junit.runners.AndroidJUnit4
import androidx.test.rule.GrantPermissionRule
import com.moka.utils.Screenshot
import org.junit.Rule
import org.junit.Test
import org.junit.runner.RunWith
import org.rajawali3d.examples.data.Example
import org.rajawali3d.examples.examples.AExampleFragment
import org.rajawali3d.examples.examples.general.BasicFragment

@RunWith(AndroidJUnit4::class)
class TestFragments {

    @get:Rule
    val grantPermissionRule: GrantPermissionRule = GrantPermissionRule.grant(*LauncherActivity.PERMISSIONS)

    @Test
    fun testBasicFragment() {

        val bundle = Bundle()
        bundle.putString(AExampleFragment.BUNDLE_EXAMPLE_URL, Example.BASE_URL)
        launchFragmentInContainer<BasicFragment>(bundle)

        onView(withId(R.id.rajwali_surface))
                .check(matches(isDisplayed()))

        Screenshot.takeScreenshot("end")
    }
}
