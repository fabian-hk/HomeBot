package com.example.bot

import android.content.BroadcastReceiver
import android.content.Context
import android.content.Intent
import android.os.Bundle
import android.widget.Toast
import com.example.bot.tools.checkNetwork
import com.example.bot.tools.getSharedPreferenceString
import com.example.bot.tools.sendWindowShadeRequest
import com.example.bot.tools.setSharedPreferenceLong

class ControlShadeBroadcast : BroadcastReceiver() {

    override fun onReceive(context: Context?, intent: Intent?) {
        if (checkNetwork(context!!)) {
            val list: ArrayList<Int> = intent!!.extras["values"] as ArrayList<Int>

            var status = sendWindowShadeRequest(
                context,
                getSharedPreferenceString(context, context.getString(R.string.sh_id))!!,
                -1,
                list
            )
            Toast.makeText(context, "Status: " + if (status) 0 else 1, Toast.LENGTH_SHORT).show()
        }
    }

}