package com.example.bot

import android.app.AlarmManager
import android.content.*
import android.net.ConnectivityManager
import android.net.wifi.WifiManager


class RestartReceiver : BroadcastReceiver() {

    override fun onReceive(context: Context, intent: Intent) {
        println("Registered broadcasts")
    }
}
