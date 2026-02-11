package org.owasp.mastestapp

// SUMMARY: This demo checks debuggable status and active JDWP debugging signals.

import android.content.Context
import android.content.pm.ApplicationInfo
import android.os.Debug

class MastgTest (private val context: Context){

    fun mastgTest(): String {
        val r = DemoResults("0040")

        try {
            val debuggable = isDebuggable(context)
            val debuggerConnected = Debug.isDebuggerConnected()

            // FAIL: [MASTG-TEST-0046-1] android:debuggable enabled in the app flags.
            // PASS: [MASTG-TEST-0046-1] android:debuggable disabled in the app flags.
            if (debuggable) {
                r.add(Status.FAIL, "android:debuggable appears enabled via ApplicationInfo.FLAG_DEBUGGABLE.")
            } else {
                r.add(Status.PASS, "android:debuggable appears disabled (FLAG_DEBUGGABLE not set).")
            }

            // FAIL: [MASTG-TEST-0046-1] Debug.isDebuggerConnected reports a debugger.
            // PASS: [MASTG-TEST-0046-1] Debug.isDebuggerConnected reports no debugger.
            if (debuggerConnected) {
                r.add(Status.FAIL, "Debug.isDebuggerConnected reports an attached debugger.")
            } else {
                r.add(Status.PASS, "Debug.isDebuggerConnected reports no debugger attached.")
            }

        } catch (e: Exception) {
            r.add(Status.ERROR, "Unexpected error while running anti-debugging checks: ${e.javaClass.simpleName}: ${e.message}")
        }

        return r.toJson()
    }

    private fun isDebuggable(context: Context): Boolean {
        val appInfo = context.applicationContext.applicationInfo
        return (appInfo.flags and ApplicationInfo.FLAG_DEBUGGABLE) != 0
    }

}
