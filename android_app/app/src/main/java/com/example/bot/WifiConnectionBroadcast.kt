package com.example.bot

import android.content.BroadcastReceiver
import android.content.Context
import android.content.Intent
import android.net.NetworkInfo
import com.example.bot.tools.*
import java.util.*
import kotlin.collections.ArrayList

class WifiConnectionBroadcast : BroadcastReceiver() {

    override fun onReceive(context: Context?, intent: Intent?) {
        val wifiState : NetworkInfo = intent!!.extras["networkInfo"] as NetworkInfo

        val currentTime = Date()
        val time = getSharedPreferenceLong(context!!, context.getString(R.string.time))

        if (checkNetwork(context) && wifiState.isConnected && currentTime.time > time) {
            var pos = ArrayList<Int>()
            pos.add(0)
            pos.add(0)
            pos.add(0)
            println("Open window shade")
            sendWindowShadeRequest(
                context,
                getSharedPreferenceString(context, context.getString(R.string.sh_id))!!,
                -1,
                pos
            )

            setSharedPreferenceLong(context, R.string.time, Long.MAX_VALUE)
        }
    }
}